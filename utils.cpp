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
void limit_on_turns(long long n , long long m , long long t , long long J , vector<vector<long long>>& clauses) {
    auto get_id = [&](int i, int j, int k, int dir, bool entry){
        return ((i*m)+(j-1))*(8*t +2)+ (8*k + (entry ? dir : dir + 4));
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
        encode(clauses , clauses , n, m, t, J);
    }
}