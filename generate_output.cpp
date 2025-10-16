#include "utils.h"
#include "input.h"
#include "inputoutput.h"
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
using namespace std;
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
// Output format:
// The output format for valid solution will be written as follows:
// R R R R R D D 0
// R R D D 0
// Here L represents left, R right, D down, and U up. The first row will be the path for 0th metro line, and so
// on. Each row ends with a 0.
// If the problem is unsatisfiable output only a single 0.
void gen_output(Problem& prob, map<int, bool>& var_map, string out_fname) {
    std::ofstream out(out_fname);
    if(var_map.size() == 0) {
        out << "0" << endl;
        // cout << "0" << endl;
        return;
    }
    for(int i = 0; i < prob.K; i++) {
        int sx = prob.lines[i][0];
        int sy = prob.lines[i][1];
        int ex = prob.lines[i][2];
        int ey = prob.lines[i][3];
        int cx = sx;
        int cy = sy;
        int parx = -1;
        int pary = -1;
        // open output file
        
        if(!out) {
            cerr << "Error: cannot open output file " << out_fname << endl;
            return;
        }

        while(!(cx == ex && cy == ey)) {
            bool moved = false;
            int base = hash_d(i, cx, cy, NORTH,  prob.N, prob.M, prob.K);
            // try move right (EAST)
            if(cx+1<prob.N && var_map.find(base + SOUTH) != var_map.end() && var_map.at(base + SOUTH) == true && !(parx == cx+1 && pary == cy)) {
                out << "R ";
                parx = cx;
                pary = cy;
                cx = cx + 1;
                moved = true;
            }
            // try move left (WEST)
            else if(cx-1>=0 && var_map.find(base + NORTH) != var_map.end() && var_map.at(base + NORTH) == true && !(parx == cx-1 && pary == cy)) {
                // if(moved){
                //     cout<<"1"<<endl;
                //     cout<<"Error: Multiple moves possible for metro line "<<i<<" at position ("<<cx<<", "<<cy<<")."<<endl;
                //     return;
                // }
                out << "L ";
                parx = cx;
                pary = cy;
                cx = cx - 1;
                moved = true;
            }
            // try move down (SOUTH)
            else if(cy+1<prob.M && var_map.find(base + EAST) != var_map.end() && var_map.at(base + EAST) == true && !(parx == cx && pary == cy+1)) {
                // if(moved){
                //     cout<<"2"<<endl;
                //     cout<<"Error: Multiple moves possible for metro line "<<i<<" at position ("<<cx<<", "<<cy<<")."<<endl;
                //     return;
                // }
                out << "D ";
                parx = cx;
                pary = cy;
                cy = cy + 1;
                moved = true;
            }
            // try move up (NORTH)
            else if(cy-1>=0 && var_map.find(base + WEST) != var_map.end() && var_map.at(base + WEST) == true && !(parx == cx && pary == cy-1)) {
                // if(moved){
                //     cout<<"3"<<endl;
                //     cout<<"Error: Multiple moves possible for metro line "<<i<<" at position ("<<cx<<", "<<cy<<")."<<endl;
                //     return;
                // }
                out << "U ";
                parx = cx;
                pary = cy;
                cy = cy - 1;
                moved = true;
            }
            else {
                // cout<<"4"<<endl;
                cout<<base<<endl;
                cerr << "Error: No valid move found for metro line " << i << " at position (" << cx << ", " << cy << ")." << endl;
                return;
            }
        }
        out << "0" << endl;
    }
    
}

int main(int argc, char* argv[]){
    Problem prob = read_input(argv[2]);
    map<int, bool> var_map = read_output(argv[1]);
    cout<<argv[1]<<" "<<argv[2]<<endl;
    string file = "";
    for(int i=0; i< strlen(argv[2]); i++){
        if(argv[1][i]=='.'){
            break;
        }
        file+=argv[1][i];
    }
    file += ".metromap";

    gen_output(prob, var_map, file);
    return 0;
}