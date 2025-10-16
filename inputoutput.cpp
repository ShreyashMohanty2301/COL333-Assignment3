// Input format:
// The first line is either a 1 or a 2. 1 represents Scenario #1. Second line has four numbers: number of
// columns in the grid (N), number of rows in the grid (M), number of metro lines (K) and max number of
// turns allowed in a single line (J).
// Each subsequent line represents a metro line in order 0 to K-1. It has four number representing (x,y)
// location of start, and (x,y) locations of end on the grid.
// As an example, consider this:
// 1
// 8 6 2 1
// 0 0 5 2
// 2 1 4 3

#include "input.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

Problem read_input(string filename){
    ifstream infile;
    infile.open(filename);
    Problem prob;
    infile >> prob.scenario;
    if(prob.scenario == 1){
        infile >> prob.N >> prob.M >> prob.K >> prob.J;
        int x1, y1, x2, y2;
        for(int i=0; i<prob.K; i++){
            infile >> x1 >> y1 >> x2 >> y2;
            prob.lines.push_back({x1, y1, x2, y2});
        }
        prob.P = 0;
        infile.close();
        return prob;
    }
    else{
        infile >> prob.N >> prob.M >> prob.K >> prob.J>> prob.P;
        int x1, y1, x2, y2;
        for(int i=0; i<prob.K; i++){
            infile >> x1 >> y1 >> x2 >> y2;
            prob.lines.push_back({x1, y1, x2, y2});
        }
        for(int i=0; i<prob.P; i++){
            int a, b;
            infile >> a >> b;
            prob.popular.push_back({a, b});
        }
        infile.close();
        return prob;
    }
    
}