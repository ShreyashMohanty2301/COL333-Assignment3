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