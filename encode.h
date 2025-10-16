#ifndef ENCODE_H
#define ENCODE_H
#include <vector>
using namespace std;

// void encode(vector<vector<int>>& clause, vector<vector<int>>& fin_clauses, int rows, int cols, int t, int k, int seed);
void encode(vector<int>& variables, vector<vector<int>>& fin_clauses, int rows, int cols, int t, int k, int seed);
#endif