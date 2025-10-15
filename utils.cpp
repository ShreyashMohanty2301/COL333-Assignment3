#include "encode.cpp"

void oneEntry(long long n , long long m , long long t , vector<vector<long long>>& clauses) {
    for(long long i = 1; i <= n; i++) {
        for(long long j = 1; j <= m; j++) {
            vector<long long> res;
            for(int k = 0; k <= t - 1 ; k++) {
                for(int l = 1; l <= 4; l++) {
                    res.push_back((i*m + j - 1)*(8LL*t) + 8*k + l);
                }
            }
            encode(res , clauses , n, m, t, 1);
        }
    }
}

void oneExit(long long n , long long m , long long t , vector<vector<long long>>& clauses) {
    for(long long i = 1; i <= n; i++) {
        for(long long j = 1; j <= m; j++) {
            vector<long long> res;
            for(int k = 0; k <= t - 1 ; k++) {
                for(int l = 5; l <= 8; l++) {
                    res.push_back((i*m + j - 1)*(8LL*t) + 8*k + l);
                }
            }
            encode(res , clauses , n ,m , t, 1);
        }
    }
}

void flow(long long n , long long m , long long t , vector<vector<long long>>& clauses) {
    for(long long i = 1; i <= n; i++) {
        for(long long j = 1; j <= m; j++) {
            vector<long long> res;
            for(int k = 0; k <= t - 1 ; k++) {
                for(int l = 1; l <= 4; l++) {
                    res.push_back(-1LL*((i*m + j - 1)*(8LL*t) + 8*k + l));
                    res.push_back(-1LL*((i*m + j - 1)*(8LL*t) + 8*k + l + 4));
                }
            }
            clauses.push_back(res);
        }
    }
    for(long long i = 1; i <= n; i++) {
        for(long long j = 1; j <= m; j++) {
            vector<long long> res;
            for(int k = 0; k <= t - 1 ; k++) {
                for(int l = 1; l <= 4; l++) {
                    res.push_back(-1LL*((i*m + j - 1)*(8LL*t) + 8*k + l));
                    for(int e = 1 ; e <= 7 ; e++) {
                        if(e != 4 && e + l >= 4 && e + l < 8) {
                            res.push_back((i*m + j - 1)*(8LL*t) + 8*k + l + e);;
                        } 
                    }
                }
            }
            clauses.push_back(res);
        }
    }
}

