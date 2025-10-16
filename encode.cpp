#include <iostream>
#include <vector>

using namespace std;
// int get_id(int i, int j, int rows, int cols){
//     return cols*rows + i*cols + j;
// }
// void encode(vector<vector<long long>>& clause, vector<vector<long long>>& fin_clauses, int rows, int cols, int t, int k, int seed){
//     // sij = sum upto pi has reached j or not
//     // id[sij] = cols*rows + i*cols + j

//     // p1 => s11.  (-p1 v s11 ) 
//     auto get_id = [&](int i, int j){
//         return ((cols*rows)*((8*t)))*seed + i*k +j;
//     };
//     vector<long long> temp;
//     temp = {-clause[0][0], -clause[0][1], get_id(1, 1)};
//     fin_clauses.push_back(temp);
//     for(int j = 2; j<= k; j++){
//         temp = {-get_id(1, j)};
//         fin_clauses.push_back(temp);
//     }
//     for(int i=2; i<clause.size(); i++){
//         long long a1 = clause[i-1][0];
//         long long a2 = clause[i-1][1];
//         temp = {-a1, -a2, get_id(i,1)};
//         fin_clauses.push_back(temp);
//         temp = {-get_id(i-1,1), get_id(i,1)};
//         fin_clauses.push_back(temp);
//         for(int j = 2; j<=k; j++){
//             temp = {-a1, -a2, -get_id(i-1,j-1), get_id(i,j)};
//             fin_clauses.push_back(temp);
//             temp = {-get_id(i-1,j), get_id(i,j)};
//             fin_clauses.push_back(temp);
//         }
//         temp = {-a1, -a2, -get_id(i-1,k)};
//         fin_clauses.push_back(temp);
//     }
//     temp = {-clause[clause.size()-1][0], -clause[clause.size()-1][1], -get_id(clause.size()-1,k)};
//     fin_clauses.push_back(temp);
// }
void encode(vector<long long>& variables, vector<vector<long long>>& fin_clauses, int rows, int cols, int t, int k, int seed){
    long long primary_var_count = (long long)t * rows * cols * 6;
    long long aux_block_size = (long long)variables.size() * k;
    long long base_offset = primary_var_count + 1 + ((long long)seed * aux_block_size);

    auto get_id = [&](int i, int j) {
        return base_offset + (long long)(i - 1) * k + (j - 1);
    };
    int n = variables.size();
    vector<long long> temp;
    temp = {-variables[0],  get_id(1, 1)};
    fin_clauses.push_back(temp);
    // temp = {-variables[n-1], -get_id(n-1, 1)};
    // fin_clauses.push_back(temp);
    for(int j = 2; j<= k; j++){
        temp = {-get_id(1, j)};
        fin_clauses.push_back(temp);
    }
    for(int i=2; i<n; i++){
        long long xi = variables[i-1];
        temp = {-xi, get_id(i,1)};
        fin_clauses.push_back(temp);
        temp = {-get_id(i-1,1), get_id(i,1)};
        fin_clauses.push_back(temp);
        for(int j = 2; j<=k; j++){
            temp = {-xi, -get_id(i-1,j-1), get_id(i,j)};
            fin_clauses.push_back(temp);
            temp = {-get_id(i-1,j), get_id(i,j)};
            fin_clauses.push_back(temp);
        }
        temp = {-xi, -get_id(i-1,k)};
        fin_clauses.push_back(temp);
    }
    temp = {-variables[n-1], -get_id(n-1,k)};
    fin_clauses.push_back(temp);
}
    