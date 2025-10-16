#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include <set>
#include <string>   
#include <fstream>
using namespace std;
bool is_p_variable(int id, int N, int M, int K);

void strtPoint(int n , int m , int k , vector<vector<int>>& clauses, vector<vector<int>>& lines);
std::vector<int> decode_p(int id, int N, int M, int K);
void endPoint(int n , int m , int k , vector<vector<int>>& clauses, vector<vector<int>>& lines);
void flow(int n , int m , int k , vector<vector<int>>& clauses, set<pair<int, int>>& points);
void at_most_one_p(int n, int m, int k, vector<vector<int>>& fin_clauses, int seed);
void popularity(int n, int m, int k, vector<vector<int>>& fin_clauses, vector<vector<int>>& popular);
void limit_on_turns(int n , int m , int t , int J , vector<vector<int>>& clauses, int seed);
void path_consistency(int n, int m, int k, vector<vector<int>>& fin_clauses);
void create_inputfile_for_sat(vector<vector<int>>& clauses, string filename);
int hash_p(int k, int x, int y, int N, int M, int K);
int hash_d(int k, int x, int y, int dir, int N, int M, int K);
int hash_t(int k, int x, int y, int N, int M, int K);
void at_most_one_d(int n, int m, int k, vector<vector<int>>& fin_clauses, int seed);
#endif