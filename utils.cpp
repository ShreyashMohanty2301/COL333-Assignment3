#include "encode.h"
#include <vector>
#include <set>
#include <fstream>
using namespace std;

void oneEntry(long long n , long long m , long long t , vector<vector<long long>>& clauses, int seed) {
    for(long long i = 1; i <= n; i++) {
        for(long long j = 1; j <= m; j++) {
            vector<long long> res;
            for(int k = 0; k <= t - 1 ; k++) {
                for(int l = 1; l <= 4; l++) {
                    res.push_back((i*m + j - 1)*(8LL*t) + 8*k + l);
                }
            }
            encode(res , clauses , n, m, t, 1, seed);
        }
    }
}

void oneExit(long long n , long long m , long long t , vector<vector<long long>>& clauses, int seed) {
    for(long long i = 1; i <= n; i++) {
        for(long long j = 1; j <= m; j++) {
            vector<long long> res;
            for(int k = 0; k <= t - 1 ; k++) {
                for(int l = 5; l <= 8; l++) {
                    res.push_back((i*m + j - 1)*(8LL*t) + 8*k + l);
                }
            }
            encode(res , clauses , n ,m , t, 1, seed);
        }
    }
}

void flow(long long n , long long m , long long t , vector<vector<long long>>& clauses , set<pair<int,int>>& end_points) {
    for(long long i = 1; i <= n; i++) {
        for(long long j = 1; j <= m; j++) {
            if(end_points.find({i,j}) != end_points.end()) continue;
            vector<long long> res;
            for(int k = 0; k <= t - 1 ; k++) {
                for(int l = 1; l <= 4; l++) {
                    vector<long long> res;
                    res.push_back(-1LL*((i*m + j - 1)*(8LL*t) + 8*k + l));
                    res.push_back(-1LL*((i*m + j - 1)*(8LL*t) + 8*k + l + 4));
                    clauses.push_back(res);
                }
            }
        }
    }
    for(long long i = 1; i <= n; i++) {
        for(long long j = 1; j <= m; j++) {
            if(end_points.find({i,j}) != end_points.end()) continue;
            for(int k = 0; k <= t - 1 ; k++) {
                for(int l = 1; l <= 4; l++) {
                    vector<long long> res;
                    res.push_back(-1LL*((i*m + j - 1)*(8LL*t) + 8*k + l));
                    for(int e = 5; e <= 8; e++) {
                        if(e - l != 4) {
                            res.push_back(((i*m + j - 1)*(8LL*t) + 8*k + e));
                        }
                    }
                    clauses.push_back(res);
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
