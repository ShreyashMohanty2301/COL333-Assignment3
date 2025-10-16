#ifndef INPUT_H
#define INPUT_H
#include <vector>

using namespace std;

class Problem{
    public:
    int scenario;
    int N;
    int M;
    int K;
    int J;
    int P;
    vector<vector<int>> lines; 
    vector<vector<int>> popular;
};
#endif