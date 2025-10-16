#include "utils.h"
#include <iostream>
#include "input.h"
#include "inputoutput.h"
using namespace std;

int main(int argc, char* argv[]) {
    Problem prob = read_input(argv[1]);
    vector<vector<long long>> clauses;
    set<pair<int,int>> end_points;
    for(auto line : prob.lines) {
        end_points.insert({line[2], line[3]});
    }
    oneEntry(prob.N , prob.M , prob.K , clauses, 1);
    oneExit(prob.N , prob.M , prob.K , clauses, 2);
    flow(prob.N , prob.M , prob.K , clauses , end_points);
    continuity(prob.N , prob.M , prob.K , clauses , end_points);
    limit_on_turns(prob.N , prob.M , prob.K , prob.J , clauses, 3);
    for(int i = 1; i <= prob.N; i++) {
        for(int j = 0; j < prob.K; j++) {
            vector<long long> res;
            res.push_back(-1LL*((i*prob.M + 1 - 1)*(8LL*prob.J) +8*j + 4));
            clauses.push_back(res);
        }
    }
    for(int i = 1; i <= prob.N; i++) {
        for(int j = 0; j < prob.K; j++) {
            vector<long long> res;
            res.push_back(-1LL*((i*prob.M + prob.M - 1)*(8LL*prob.J) +8*j + 6));
            clauses.push_back(res);
        }
    }
    for(int i = 1; i <= prob.M; i++) {
        for(int j = 0; j < prob.K; j++) {
            vector<long long> res;
            res.push_back(-1LL*((1*prob.M + i - 1)*(8LL*prob.J) +8*j + 1));
            clauses.push_back(res);
        }
    }
    for(int i = 1; i <= prob.M; i++) {
        for(int j = 0; j < prob.K; j++) {
            vector<long long> res;
            res.push_back(-1LL*((prob.N*prob.M + i - 1)*(8LL*prob.J) +8*j + 7));
            clauses.push_back(res);
        }
    }
    for(int i = 1; i <= prob.N; i++) {
        for(int j = 0; j < prob.K; j++) {
            vector<long long> res;
            res.push_back(-1LL*((i*prob.M + 1 - 1)*(8LL*prob.J) +8*j + 8));
            clauses.push_back(res);
        }
    }
    for(int i = 1; i <= prob.N; i++) {
        for(int j = 0; j < prob.K; j++) {
            vector<long long> res;
            res.push_back(-1LL*((i*prob.M + prob.M - 1)*(8LL*prob.J) +8*j + 2));
            clauses.push_back(res);
        }
    }
    for(int i = 1; i <= prob.M; i++) {
        for(int j = 0; j < prob.K; j++) {
            vector<long long> res;
            res.push_back(-1LL*((1*prob.M + i - 1)*(8LL*prob.J) +8*j + 5));
            clauses.push_back(res);
        }
    }
    for(int i = 1; i <= prob.M; i++) {
        for(int j = 0; j < prob.K; j++) {
            vector<long long> res;
            res.push_back(-1LL*((prob.N*prob.M + i - 1)*(8LL*prob.J) +8*j + 3));
            clauses.push_back(res);
        }
    }
    for(auto line : prob.lines) {
        vector<long long> res;
        for(int j = 0; j < prob.K; j++) {
            for(int c = 5; c <= 8; c++) {
                res.push_back((line[0]*prob.M + line[1] - 1)*(8LL*prob.K) + 8*j + c);
            }
        }
        clauses.push_back(res);
    }
    for(auto line : prob.lines) {
        vector<long long> res;
        for(int j = 0; j < prob.K; j++) {
            for(int c = 1; c <= 4; c++) {
                res.push_back((line[2]*prob.M + line[3] - 1)*(8LL*prob.K) + 8*j + c);
            }
        }
        clauses.push_back(res);
    }
    for (int k = 0; k < prob.K; k++) {
        auto line = prob.lines[k];
        for (int c = 5; c <= 8; c++) {
            vector<long long> res;
            res.push_back(-1LL * ((line[0]*prob.M + line[1] - 1)*(8LL*prob.K) + 8*k + c));
            for (int e = 1; e <= 4; e++) {
                res.push_back((line[2]*prob.M + line[3] - 1)*(8LL*prob.K) + 8*k + e);
            }
            clauses.push_back(res);
        }
    }
    create_inputfile_for_sat(clauses, "satinput.txt");
    return 0;
}   