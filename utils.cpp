#include "encode.h"
#include <vector>
#include <set>
#include <fstream>
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
using namespace std;

void strtPoint(int n , int m , int k , vector<vector<int>>& clauses, int seed , vector<vector<int>>& lines) {
    for(int i = 0; i < lines.size(); i++) {
        vector<int>res;
        for(int dir = NORTH; dir <= WEST; dir++) {
            res.push_back(hash_d(i + 1, lines[i][0], lines[i][1], dir, n, m, k));
        }
        clauses.push_back({hash_p(i + 1, lines[i][0], lines[i][1], n, m, k)});
        clauses.push_back(res);
        encode(res,clauses, n, m, k, 1, seed);
        clauses.push_back(res);
        for(int j = 0;j < k; j++) {
            if(lines[i][0] - 1 >= 0) {
                clauses.push_back({-hash_d(j, lines[i][0] - 1, lines[i][1], SOUTH, n, m, k)});
            }
            if(lines[i][1] + 1 < m) {
                clauses.push_back({-hash_d(j, lines[i][0], lines[i][1] + 1, WEST, n, m, k)});
            }
            if(lines[i][0] + 1 < n) {
                clauses.push_back({-hash_d(j, lines[i][0] + 1, lines[i][1], NORTH, n, m, k)});
            }
            if(lines[i][1] - 1 >= 0) {
                clauses.push_back({-hash_d(j, lines[i][0], lines[i][1] - 1, EAST, n, m, k)});
            }
        }
    }
}

void endPoint(int n , int m , int k , vector<vector<int>>& clauses, int seed , vector<vector<int>>& lines) {
    for(int i = 0; i < lines.size(); i++) {
        vector<int>res;
        if(lines[i][2] - 1 >= 0) {
            res.push_back({hash_d(i + 1, lines[i][0] - 1, lines[i][1], SOUTH, n, m, k)});
        }
        if(lines[i][3] + 1 < m) {
            res.push_back({hash_d(i + 1, lines[i][0], lines[i][1] + 1, WEST, n, m, k)});
        }
        if(lines[i][2] + 1 < n) {
            res.push_back({hash_d(i + 1, lines[i][0] + 1, lines[i][1], NORTH, n, m, k)});
        }
        if(lines[i][3] - 1 >= 0) {
            res.push_back({hash_d(i + 1, lines[i][0], lines[i][1] - 1, EAST, n, m, k)});
        }
        clauses.push_back({hash_p(i + 1, lines[i][2], lines[i][3], n, m, k)});
        clauses.push_back(res);
        encode(res1,clauses, n, m, k, 1, seed);
        clauses.push_back(res);
        for(int j = 0;j < k; j++) {
            for(int dir = NORTH; dir <= WEST; dir++) {
                clauses.push_back({-hash_d(j, lines[i][2], lines[i][3], dir, n, m, k)});
            }
        }
    }
}

void flow(int n , int m , int k , vector<vector<int>>& clauses, set<pair<int,int>>& points) {
    for(int i = 0; i < n ;i++) {
        for(int j = 0; j < m; j++) {
            if(points.find({i , j}) != points.end()) continue;
            for(int l = 0; l < k; l++) {
                for(int dir = NORTH; dir <= WEST; dir++) {
                    vector<int>res;
                    res.push_back(-hash_d(l, i, j, dir, n, m, k));
                    vector<int>res1;
                    for(int dir2 = NORTH; dir2 <=WEST; dir2++) {
                        if(abs(dir - dir2) == 2) continue;
                        if(dir2 == NORTH && i - 1 >= 0) {
                            res.push_back(hash_d(l, i - 1, j, SOUTH, n, m, k));
                            res1.push_back(hash_d(l, i - 1, j, SOUTH, n, m, k));
                        }
                        if(dir2 == EAST && j + 1 < m) {
                            res.push_back(hash_d(l, i, j + 1, WEST, n, m, k));
                            res1.push_back(hash_d(l, i, j + 1, WEST, n, m, k));
                        }
                        if(dir2 == SOUTH && i + 1 < n) {
                            res.push_back(hash_d(l, i + 1, j, NORTH, n, m, k));
                            res1.push_back(hash_d(l, i + 1, j, NORTH, n, m, k));
                        }
                        if(dir2 == WEST && j - 1 >= 0) {
                            res.push_back(hash_d(l, i, j - 1, EAST, n, m, k));
                            res1.push_back(hash_d(l, i, j - 1, EAST, n, m, k));
                        }
                    }
                    encode();
                    res1.push_back(hash_d(l, i, j, dir, n, m, k));
                    clauses.push_back(res);
                    clauses.push_back(res1);
                }
            }
        }
    }
}
//U - 0, R - 1, D- 2, L - 3
void limit_on_turns(long long n , long long m , long long k , long long J , vector<vector<long long>>& fin_clauses, int seed) {
    
    for(int metro= 0; metro<k ; metro++){
        vector<long long> variables;
        for(int i= 0; i<n; i++){
            for(int j =0; j<m; j++){
                // (x-1,y, D)^(x,y,R)=>T(metro,x,y) , (x-1,y,D)^(x,y,L)=>T(metro,x,y)
                variables.push_back(hash_t(metro, i, j, n, m, k));
                if(i-1>=0){
                    vector<long long> res;
                    res = {-hash_d(metro, i-1, j, 2, n, m, k), -hash_d(metro, i, j, 1, n, m, k), hash_t(metro, i, j, n, m, k)};
                    fin_clauses.push_back(res);
                    res = {-hash_d(metro, i-1, j, 2, n, m, k), -hash_d(metro, i, j, 3, n, m, k), hash_t(metro, i, j, n, m, k)};
                    fin_clauses.push_back(res);
                }
                if(i+1<n){
                    // (x+1,y, U)^(x,y,R)=>T(metro,x,y) , (x+1,y,U)^(x,y,L)=>T(metro,x,y)
                    vector<long long> res;
                    res = {-hash_d(metro, i+1, j, 0, n, m, k), -hash_d(metro, i, j, 1, n, m, k), hash_t(metro, i, j, n, m, k)};
                    fin_clauses.push_back(res);
                    res = {-hash_d(metro, i+1, j, 0, n, m, k), -hash_d(metro, i, j, 3, n, m, k), hash_t(metro, i, j, n, m, k)};         
                    fin_clauses.push_back(res);
                }
                if(j-1>=0){
                    // (x,y-1,R)^(x,y,U)=>T(metro,x,y) , (x,y-1,R)^(x,y,D)=>T(metro,x,y)
                    vector<long long> res;
                    res = {-hash_d(metro, i, j-1, 1, n, m, k), -hash_d(metro, i, j, 0, n, m, k), hash_t(metro, i, j, n, m, k)};
                    fin_clauses.push_back(res);
                    res = {-hash_d(metro, i, j-1, 1, n, m, k), -hash_d(metro, i, j, 2, n, m, k), hash_t(metro, i, j, n, m, k)};
                    fin_clauses.push_back(res);
                }
                if(j+1<m){
                    // (x,y+1,L)^(x,y,U)=>T(metro,x,y) , (x,y+1,L)^(x,y,D)=>T(metro,x,y)        
                    vector<long long> res;
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
void at_most_one_p(long long n, long long m, long long k, vector<vector<long long>>& fin_clauses) {
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            vector<long long> variables;
            for(int metro=0; metro<k; metro++){
                for(int metro2 = metro+1; metro2<k; metro2++){
                    vector<long long> res;
                    res = {-hash_p(metro, i, j, n, m, k), -hash_p(metro2, i, j, n, m, k)};
                    fin_clauses.push_back(res);
                }
            }
        }
    }
}
void path_consistency(long long n, long long m, long long k, vector<vector<long long>>& fin_clauses) {
    for(int metro=0; metro<k; metro++){
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(j+1>=m){
                    fin_clauses.push_back({-hash_d(metro, i, j, 1, n, m, k)});
                }
                else{
                    vector<long long> res;
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
                    vector<long long> res;
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
                    vector<long long> res;      
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
                    vector<long long> res;      
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
void continuity(long long n , long long m , long long t , vector<vector<long long>>& clauses , set<pair<int,int>>& end_points) {
    for(int i = 1 ; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(end_points.find({i,j}) != end_points.end()) continue;
            for(int k = 0; k < t; k++) {
                for(int l = 5 ; l <= 8; l++) {
                    if(i - 1 >= 1 && l == 5) {
                        vector<long long>res;
                        res.push_back(-1LL*((i*m + j - 1)*(8LL*t) + 8*k + l));
                        res.push_back(( ( (i-1)*m + j - 1)*(8LL*t) + 8*k + 3));
                        clauses.push_back(res);
                    }
                    if(j + 1 <= m && l == 6) {
                        vector<long long>res;
                        res.push_back(-1LL*((i*m + j - 1)*(8LL*t) + 8*k + l));
                        res.push_back(((i*m + (j+1) - 1)*(8LL*t) + 8*k + 4));
                        clauses.push_back(res);
                    }
                    if(i + 1 <= n && l == 7) {
                        vector<long long>res;
                        res.push_back(-1LL*((i*m + j - 1)*(8LL*t) + 8*k + l));
                        res.push_back((((i+1)*m + j - 1)*(8LL*t) + 8*k + 1));
                        clauses.push_back(res);
                    }
                    if(j - 1 >= 1 && l == 8) {
                        vector<long long>res;
                        res.push_back(-1LL*((i*m + j - 1)*(8LL*t) + 8*k + l));
                        res.push_back(((i*m + (j - 1) - 1)*(8LL*t) + 8*k + 2));
                        clauses.push_back(res);
                    }
                }
            }
        }
    }
}
void create_inputfile_for_sat(vector<vector<long long>>& clauses, string filename) {
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