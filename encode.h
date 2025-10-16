#ifndef ENCODE_H
#define ENCODE_H
#include <vector>
using namespace std;

void encode(vector<vector<long long>>& clause, vector<vector<long long>>& fin_clauses, int rows, int cols, int t, int k, int seed);
void encode(vector<long long>& variables, vector<vector<long long>>& fin_clauses, int rows, int cols, int t, int k, int seed);
#endif