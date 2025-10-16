#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include <set>
#include <string>   
#include <fstream>
using namespace std;
void oneEntry(int n , int m , int t , vector<vector<int>>& clauses, int seed);
void oneExit(int n , int m , int t , vector<vector<int>>& clauses, int seed);
void flow(int n , int m , int t ,    vector<vector<int>>& clauses , set<pair<int,int>>& end_points);
void continuity(int n , int m , int t , vector<vector<int>>& clauses , set<pair<int,int>>& end_points);
void limit_on_turns(int n , int m , int t , int J , vector<vector<int>>& clauses, int seed);
void create_inputfile_for_sat(vector<vector<int>>& clauses, string filename);
int hash_p(int k, int x, int y, int N, int M, int K);
int hash_d(int k, int x, int y, int dir, int N, int M, int K);
int hash_t(int k, int x, int y, int N, int M, int K);

#endif