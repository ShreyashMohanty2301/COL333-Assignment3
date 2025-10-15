#include "utils.h"
#include "encode.cpp"

vector<int> get_ids(long long i , long long j , long long m , long long t) {
    vector<int> res;
    for(int k = 0 ; k < 8 ; k++) {
        res.push_back(i*m + j + 8*t + k);
    }
    return res;
}s

void oneEntry(long long n , long long m , long long t , vector<vector<long long>>& clauses) {
    for(long long i = 1; i <= n; i++) {
        for(long long j = 1; j <= m; j++) {
            vector<long long> res;
            for(int k = 1; k <= t ; k++) {
                for(int l = 0; l < 4; l++) {
                    res.push_back((i*m + j - 1)*(8LL*t + 2) + 8*k + l);
                }
            }
            encode(n , m ,res , clauses , 1);
        }
    }
}

void oneExit(long long n , long long m , long long t , vector<vector<long long>>& clauses) {
    for(long long i = 1; i <= n; i++) {
        for(long long j = 1; j <= m; j++) {
            vector<long long> res;
            for(int k = 1; k <= t ; k++) {
                for(int l = 4; l < 8; l++) {
                    res.push_back((i*m + j - 1)*(8LL*t + 2) + 8*k + l);
                }
            }
            encode(n , m , res , clauses , 1);
        }
    }
}

void flow(long long n , long long m , long long t , vector<vector<long long>>& clauses) {
    for(long long i = 1; i <= n; i++) {
        for(long long j = 1; j <= m; j++) {
            vector<long long> res;
            for(int k = 1; k <= t ; k++) {
                for(int l = 0; l < 4; l++) {
                    res.push_back(-1LL*((i*m + j - 1)*(8LL*t + 2) + 8*k + l));
                    res.push_back(-1LL*((i*m + j - 1)*(8LL*t + 2) + 8*k + l + 4));
                }
            }
            clauses.push_back(res);
        }
    }
    for(long long i = 1; i <= n; i++) {
        for(long long j = 1; j <= m; j++) {
            vector<long long> res;
            for(int k = 1; k <= t ; k++) {
                for(int l = 0; l < 4; l++) {
                    res.push_back(-1LL*((i*m + j - 1)*(8LL*t + 2) + 8*k + l));
                    for(int e = 1 ; e <= 7 ; e++) {
                        if(e != 4 && e + l >= 4 && e + l < 8) {
                            res.push_back((i*m + j - 1)*(8LL*t + 2) + 8*k + l + e)
                        } 
                    }
                }
            }
            clauses.push_back(res);
        }
    }
}

void strtPoint(long long n , long long m , long long t , vector<vector<long long>>& clauses) {
    for(long long i = 1; i <= n; i++) {
        for(long long j = 1; j <= m; j++) {
            for(int k = 1; k <= t; k++) {
                for(int l = 0; l < 4; l++){
                    vector<long long> res;
                    res.push_back(-1LL((i*m + j - 1)*(8LL*t + 2) + 8LL*t + 1));
                    res.push_back(-1LL((i*m + j - 1)*(8LL*t + 2) + 8LL*k + l));
                    clauses.push_back(res);
                }
            }
        }
    }
}

void endPoint(long long n , long long m , long long t , vector<vector<long long>>& clauses) {
    for(long long i = 1; i <= n; i++) {
        for(long long j = 1; j <= m; j++) {
            vector<long long> res;
            res.push_back(-1LL*((m*i + j)*(8LL*t + 2) + 8LL*t + 2));
            for(int k = 4*t; k < 8LL*t; k++) {
                res.push_back((m*i + j)*(8LL*t + 2) + k);
            }
            clauses.push_back(res);
        }
    }
}