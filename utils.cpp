#include "encode.h"
#include <vector>
#include <set>
#include <fstream>
#include <iostream>
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
using namespace std;

bool is_p_variable(int id, int N, int M, int K) {
    // The total number of P variables.
    long long p_variable_count = (long long)K * M * N;
    
    // P variables are allocated from ID 1 to p_variable_count.
    return (id >= 1 && id <= p_variable_count);
}

int hash_p(int k, int x, int y, int N, int M, int K) {
    return (k*M*N)+ (y*N)+ x+ 1;
}
int hash_d(int k, int x, int y, int dir, int N, int M, int K) {
    return (K*M*N)+ (k*M*N*4) + (y*N*4) + (x*4) + 1 + dir;
}
int hash_t(int k, int x, int y, int N, int M, int K) {
    //hash_T(k,x,y)=(K⋅N⋅M+K⋅N⋅M⋅4)+(k⋅N⋅M)+(y⋅N)+x+1
    return (K*M*N)+ (K*M*N*4) + (k*M*N) + (y*N) + x + 1;
}
void strtPoint(int n, int m, int k, vector<vector<int>>& clauses, vector<vector<int>>& lines) {
    for (int i = 0; i < lines.size(); i++) {
        int sx = lines[i][0];
        int sy = lines[i][1];

        // This start point must be on the path
        clauses.push_back({hash_p(i, sx, sy, n, m, k)});

        // Constraint: EXACTLY ONE outgoing path
        vector<int> outgoing_paths;
        outgoing_paths.clear();
        outgoing_paths.push_back(hash_d(i, sx, sy, NORTH, n, m, k));
        outgoing_paths.push_back(hash_d(i, sx, sy, SOUTH, n, m, k));
        outgoing_paths.push_back(hash_d(i, sx, sy, EAST, n, m, k));
        outgoing_paths.push_back(hash_d(i, sx, sy, WEST, n, m, k));
        if(sx == 2 && sy ==4){
            for(int temp=0; temp<outgoing_paths.size(); temp++){
                cout<<outgoing_paths[temp]<<" ";
            }
        }
        clauses.push_back(outgoing_paths); // At least one
        
        for (int j = 0; j < 4; j++) { // At most one (pairwise)
            for (int l = j + 1; l < 4; l++) {
                clauses.push_back({-outgoing_paths[j], -outgoing_paths[l]});
            }
        }

       
        if (sx > 0) {
            clauses.push_back({-hash_d(i, sx - 1, sy, SOUTH, n, m, k)});
        }
        
        if (sx < n - 1) {
            clauses.push_back({-hash_d(i, sx + 1, sy, NORTH, n, m, k)});
        }
        
        if (sy > 0) {
            clauses.push_back({-hash_d(i, sx, sy - 1, EAST, n, m, k)});
        }
      
        if (sy < m - 1) {
            clauses.push_back({-hash_d(i, sx, sy+1, WEST, n, m, k)});
        }
    }
}

void endPoint(int n, int m, int k, vector<vector<int>>& clauses, vector<vector<int>>& lines) {
    for (int i = 0; i < lines.size(); i++) {
        int ex = lines[i][2];
        int ey = lines[i][3];

        // This end point must be on the path
        clauses.push_back({hash_p(i, ex, ey, n, m, k)});

      
        std::vector<int> incoming_paths;
        // From West (ex-1, ey) moving EAST
        if (ex > 0) incoming_paths.push_back(hash_d(i, ex - 1, ey, SOUTH, n, m, k));
        // From East (ex+1, ey) moving WEST
        if (ex < n - 1) incoming_paths.push_back(hash_d(i, ex + 1, ey, NORTH, n, m, k));
        // From North (ex, ey-1) moving SOUTH
        if (ey > 0) incoming_paths.push_back(hash_d(i, ex, ey - 1, EAST, n, m, k));
        // From South (ex, ey+1) moving NORTH
        if (ey < m - 1) incoming_paths.push_back(hash_d(i, ex, ey + 1, WEST, n, m, k));
        
        clauses.push_back(incoming_paths); // At least one

        for (int j = 0; j < incoming_paths.size(); j++) { // At most one
            for (int l = j + 1; l < incoming_paths.size(); l++) {
                clauses.push_back({-incoming_paths[j], -incoming_paths[l]});
            }
        }

        // Constraint: ZERO outgoing paths
        clauses.push_back({-hash_d(i, ex, ey, NORTH, n, m, k)});
        clauses.push_back({-hash_d(i, ex, ey, SOUTH, n, m, k)});
        clauses.push_back({-hash_d(i, ex, ey, EAST, n, m, k)});
        clauses.push_back({-hash_d(i, ex, ey, WEST, n, m, k)});
    }
}
void flow(int n , int m , int k , vector<vector<int>>& clauses, set<pair<int,int>>& points) {
    for(int i = 0; i < n ;i++) {
        for(int j = 0; j < m; j++) {
            if(points.find({i , j}) != points.end()) continue;

            for(int l = 0; l < k; l++) {
                vector<int> rand = {-hash_p(l, i, j, n, m, k), 
                                    hash_d(l, i, j, NORTH, n, m, k),
                                    hash_d(l, i, j, EAST, n, m, k),
                                    hash_d(l, i, j, SOUTH, n, m, k),
                                    hash_d(l, i, j, WEST, n, m, k)};
                clauses.push_back(rand);
                rand.clear();
                rand.push_back(-hash_p(l, i, j, n, m, k));
                
                if(i-1>=0){
                    rand.push_back(hash_p(l, i - 1, j, n, m, k));
                }
                if(j+1<m){
                    rand.push_back(hash_p(l, i, j + 1, n, m, k));
                }
                if(i+1<n){
                    rand.push_back(hash_p(l, i + 1, j,  n, m, k));
                }
                if(j-1>=0){
                    rand.push_back(hash_p(l, i, j - 1,  n, m, k));
                }
                // rand.push_back(-hash_p(l, i, j, n, m, k));
                clauses.push_back(rand);
                // clauses.push_back(rand);
                for(int dir = NORTH; dir <= WEST; dir++) {
                    if( dir == NORTH && i-1<0) continue;
                    if( dir == EAST && j+1>=m) continue;
                    if( dir == SOUTH && i+1>=n) continue;
                    if( dir == WEST && j-1<0) continue;
                    vector<int>res;
                    if(dir == NORTH) {
                        res.push_back(-hash_d(l, i - 1, j, SOUTH, n, m, k));
                       
                        for(int d = 0; d <= 3; d++) {
                            for(int d2 = d+1; d2<=3; d2++){
                                if(d == NORTH || d2 == NORTH) continue;
                                vector<int> t;
                                t.push_back(-hash_d(l, i-1, j, SOUTH, n, m, k));
                                t.push_back(-hash_d(l, i, j, d, n, m, k));
                                t.push_back(-hash_d(l, i, j, d2, n, m, k));
                                clauses.push_back(t);
                            }
                        }
                    }
                    else if(dir == EAST) {
                        res.push_back(-hash_d(l, i, j + 1, WEST, n, m, k));
                        for(int d = 0; d <= 3; d++) {
                            for(int d2 = d+1; d2<=3; d2++){
                                if(d == EAST || d2 == EAST) continue;
                                vector<int> t;
                                t.push_back(-hash_d(l, i, j+1, WEST, n, m, k));
                                t.push_back(-hash_d(l, i, j, d, n, m, k));
                                t.push_back(-hash_d(l, i, j, d2, n, m, k));
                                clauses.push_back(t);
                            }
                        }
                    }
                    else if(dir == SOUTH) {
                        res.push_back(-hash_d(l, i + 1, j, NORTH, n, m, k));
                        for(int d = 0; d <= 3; d++) {
                            for(int d2 = d+1; d2<=3; d2++){
                                if(d == SOUTH || d2 == SOUTH) continue;
                                vector<int> t;
                                t.push_back(-hash_d(l, i+1, j, NORTH, n, m, k));
                                t.push_back(-hash_d(l, i, j, d, n, m, k));
                                t.push_back(-hash_d(l, i, j, d2, n, m, k));
                                clauses.push_back(t);
                            }
                        }
                    }
                    else if(dir == WEST) {
                        res.push_back(-hash_d(l, i, j - 1, EAST, n, m, k));
                        for(int d = 0; d <= 3; d++) {
                            for(int d2 = d+1; d2<=3; d2++){
                                if(d == WEST || d2 == WEST) continue;
                                vector<int> t;
                                t.push_back(-hash_d(l, i, j-1, EAST, n, m, k));
                                t.push_back(-hash_d(l, i, j, d, n, m, k));
                                t.push_back(-hash_d(l, i, j, d2, n, m, k));
                                clauses.push_back(t);
                            }
                        }
                    }
                    for(int dir2 = NORTH; dir2 <= WEST; dir2++) {
                        if(dir2 == dir) continue;
                        res.push_back(hash_d(l, i, j, dir2, n, m, k));
                    }
                    clauses.push_back(res);



                }
            }
        }
    }
}
//U - 0, R - 1, D- 2, L - 3
void limit_on_turns(int n , int m , int k , int J , vector<vector<int>>& fin_clauses, int seed) {
    
    for(int metro= 0; metro<k ; metro++){
        vector<int> variables;
        for(int i= 0; i<n; i++){
            for(int j =0; j<m; j++){
                // (x-1,y, D)^(x,y,R)=>T(metro,x,y) , (x-1,y,D)^(x,y,L)=>T(metro,x,y)
                variables.push_back(hash_t(metro, i, j, n, m, k));
                if(i-1>=0){
                    vector<int> res;
                    res = {-hash_d(metro, i-1, j, 2, n, m, k), -hash_d(metro, i, j, 1, n, m, k), hash_t(metro, i, j, n, m, k)};
                    fin_clauses.push_back(res);
                    res = {-hash_d(metro, i-1, j, 2, n, m, k), -hash_d(metro, i, j, 3, n, m, k), hash_t(metro, i, j, n, m, k)};
                    fin_clauses.push_back(res);
                }
                if(i+1<n){
                    // (x+1,y, U)^(x,y,R)=>T(metro,x,y) , (x+1,y,U)^(x,y,L)=>T(metro,x,y)
                    vector<int> res;
                    res = {-hash_d(metro, i+1, j, 0, n, m, k), -hash_d(metro, i, j, 1, n, m, k), hash_t(metro, i, j, n, m, k)};
                    fin_clauses.push_back(res);
                    res = {-hash_d(metro, i+1, j, 0, n, m, k), -hash_d(metro, i, j, 3, n, m, k), hash_t(metro, i, j, n, m, k)};         
                    fin_clauses.push_back(res);
                }
                if(j-1>=0){
                    // (x,y-1,R)^(x,y,U)=>T(metro,x,y) , (x,y-1,R)^(x,y,D)=>T(metro,x,y)
                    vector<int> res;
                    res = {-hash_d(metro, i, j-1, 1, n, m, k), -hash_d(metro, i, j, 0, n, m, k), hash_t(metro, i, j, n, m, k)};
                    fin_clauses.push_back(res);
                    res = {-hash_d(metro, i, j-1, 1, n, m, k), -hash_d(metro, i, j, 2, n, m, k), hash_t(metro, i, j, n, m, k)};
                    fin_clauses.push_back(res);
                }
                if(j+1<m){
                    // (x,y+1,L)^(x,y,U)=>T(metro,x,y) , (x,y+1,L)^(x,y,D)=>T(metro,x,y)        
                    vector<int> res;
                    res = {-hash_d(metro, i, j+1, 3, n, m, k), -hash_d(metro, i, j, 0, n, m, k), hash_t(metro, i, j, n, m, k)};
                    fin_clauses.push_back(res);
                    res = {-hash_d(metro, i, j+1, 3, n, m, k), -hash_d(metro, i, j, 2, n, m, k), hash_t(metro, i, j, n, m, k)};
                    fin_clauses.push_back(res);     
                }

            }
        }
        encode(variables, fin_clauses, n, m, k, J, seed+metro);
    }
}
void at_most_one_p(int n, int m, int k, vector<vector<int>>& fin_clauses, int seed) {
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            vector<int> vars;
            for(int metro=0; metro<k; metro++){

                    vars.push_back(hash_p(metro, i, j, n, m, k));

                    // fin_clauses.push_back(res);
               
            }
            encode(vars, fin_clauses, n, m, k, 1, seed+i*n+j);
        }
    }
   
} 
// void at_most_one_d(int n, int m, int k, vector<vector<int>>& fin_clauses, int seed) {
//     for(int i=0; i<n; i++){
//         for(int j=0; j<m; j++){
//             vector<int> vars;
//             for(int metro=0; metro<k; metro++){
//                     for(int dir = 0; dir < 4; dir++){
//                         vars.push_back(hash_d(metro, i, j, dir, n, m, k));
//                     }
//                     // fin_clauses.push_back(res);
               
//             }
//             encode(vars, fin_clauses, n, m, k, 1, seed+i*n*10+j*10);
//         }
//     }
   
// } 
void path_consistency(int n, int m, int k, vector<vector<int>>& fin_clauses) {
    for(int metro=0; metro<k; metro++){
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(j+1>=m){
                    fin_clauses.push_back({-hash_d(metro, i, j, 1, n, m, k)});
                }
                else{
                    vector<int> res;
                    res.push_back(-hash_d(metro, i, j, 1, n, m, k));
                    res.push_back(hash_p(metro, i, j+1, n, m, k));
                    fin_clauses.push_back(res); 
                    res.push_back(-hash_d(metro, i, j, 1, n, m, k));
                    res.push_back(hash_p(metro, i, j, n, m, k));
                    fin_clauses.push_back(res); 

                }
                if(j-1<0){
                    fin_clauses.push_back({-hash_d(metro, i, j, 3, n, m, k)});
                }
                else{
                    vector<int> res;
                    res.push_back(-hash_d(metro, i, j, 3, n, m, k));
                    res.push_back(hash_p(metro, i, j-1, n, m, k));
                    fin_clauses.push_back(res); 
                    res.push_back(-hash_d(metro, i, j, 3, n, m, k));
                    res.push_back(hash_p(metro, i, j, n, m, k));
                    fin_clauses.push_back(res); 

                }
                if(i+1>=n){
                    fin_clauses.push_back({-hash_d(metro, i, j, 2, n, m, k)});
                }
                else{
                    vector<int> res;      
                    res.push_back(-hash_d(metro, i, j, 2, n, m, k));
                    res.push_back(hash_p(metro, i+1, j, n, m, k));
                    fin_clauses.push_back(res); 
                    res.push_back(-hash_d(metro, i, j, 2, n, m, k));
                    res.push_back(hash_p(metro, i, j, n, m, k));
                    fin_clauses.push_back(res); 
                }
                if(i-1<0){
                    fin_clauses.push_back({-hash_d(metro, i, j, 0, n, m, k)});
                }
                else{
                    vector<int> res;      
                    res.push_back(-hash_d(metro, i, j, 0, n, m, k));
                    res.push_back(hash_p(metro, i-1, j, n, m, k));
                    fin_clauses.push_back(res); 
                    res.push_back(-hash_d(metro, i, j, 0, n, m, k));
                    res.push_back(hash_p(metro, i, j, n, m, k));
                    fin_clauses.push_back(res); 
                }
            }
        }
    }
}
void popularity(int n, int m, int k, vector<vector<int>>& fin_clauses, vector<vector<int>>& popular) {
    for(auto point : popular) {
        vector<int> res;
        for(int metro = 0; metro < k; metro++) {
            res.push_back(hash_p(metro, point[0], point[1], n, m, k));
        }
        fin_clauses.push_back(res);
    }
}
// void continuity(int n , int m , int t , vector<vector<int>>& clauses , set<pair<int,int>>& end_points) {
//     for(int i = 1 ; i <= n; i++) {
//         for(int j = 1; j <= m; j++) {
//             if(end_points.find({i,j}) != end_points.end()) continue;
//             for(int k = 0; k < t; k++) {
//                 for(int l = 5 ; l <= 8; l++) {
//                     if(i - 1 >= 1 && l == 5) {
//                         vector<int>res;
//                         res.push_back(-1LL*((i*m + j - 1)*(8LL*t) + 8*k + l));
//                         res.push_back(( ( (i-1)*m + j - 1)*(8LL*t) + 8*k + 3));
//                         clauses.push_back(res);
//                     }
//                     if(j + 1 <= m && l == 6) {
//                         vector<int>res;
//                         res.push_back(-1LL*((i*m + j - 1)*(8LL*t) + 8*k + l));
//                         res.push_back(((i*m + (j+1) - 1)*(8LL*t) + 8*k + 4));
//                         clauses.push_back(res);
//                     }
//                     if(i + 1 <= n && l == 7) {
//                         vector<int>res;
//                         res.push_back(-1LL*((i*m + j - 1)*(8LL*t) + 8*k + l));
//                         res.push_back((((i+1)*m + j - 1)*(8LL*t) + 8*k + 1));
//                         clauses.push_back(res);
//                     }
//                     if(j - 1 >= 1 && l == 8) {
//                         vector<int>res;
//                         res.push_back(-1LL*((i*m + j - 1)*(8LL*t) + 8*k + l));
//                         res.push_back(((i*m + (j - 1) - 1)*(8LL*t) + 8*k + 2));
//                         clauses.push_back(res);
//                     }
//                 }
//             }
//         }
//     }
// }
void create_inputfile_for_sat(vector<vector<int>>& clauses, string filename) {
    ofstream myfile;
    myfile.open (filename);
    myfile << "p cnf " << 1000000000 << " " << clauses.size() << "\n";
    for(auto clause : clauses) {
        for(auto literal : clause) {
            myfile << literal << " ";
        }
        myfile << "0\n";
    }
    myfile.close();
}


