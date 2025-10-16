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
        encode();
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
        encode();
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
void limit_on_turns(long long n , long long m , long long t , long long J , vector<vector<long long>>& fin_clauses, int seed) {
    auto get_id = [&](int i, int j, int k, int dir, bool entry){
        return ((i*m)+(j-1))*(8*t)+ (8*k + (entry ? dir : dir + 4));
    };
    auto get_dir = [](int dir){
        dir = dir%4;
        if(dir ==0) return 4;
        else return dir;
    };
    for(int k = 0; k<t; k++){
        vector<vector<long long>> clauses;
        for(int i=1; i<=n; i++){
            for(int j = 1; j<=m; j++){
                vector<long long> temp;
                for(int dir = 0; dir < 4; dir++){
                    temp = {get_id(i,j,k,dir,true), get_id(i,j,k,get_dir(dir+1),false)};
                    clauses.push_back(temp);
                    temp = {get_id(i,j,k,dir,true), get_id(i,j,k,get_dir(dir+3),false)};
                    clauses.push_back(temp);
                }
                
            }
        }
        encode(clauses , fin_clauses , n, m, t, J, seed+k);
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