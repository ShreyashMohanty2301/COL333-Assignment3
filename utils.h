#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include <set>
#include <string>   
#include <fstream>
using namespace std;
void oneEntry(long long n , long long m , long long t , vector<vector<long long>>& clauses, int seed);
void oneExit(long long n , long long m , long long t , vector<vector<long long>>& clauses, int seed);
void flow(long long n , long long m , long long t ,    vector<vector<long long>>& clauses , set<pair<int,int>>& end_points);
void continuity(long long n , long long m , long long t , vector<vector<long long>>& clauses , set<pair<int,int>>& end_points);
void limit_on_turns(long long n , long long m , long long t , long long J , vector<vector<long long>>& clauses, int seed);
void create_inputfile_for_sat(vector<vector<long long>>& clauses, string filename);

#endif