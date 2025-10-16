#include "utils.h"
#include <iostream>
#include "input.h"
#include "inputoutput.h"
using namespace std;

int main(int argc, char* argv[]) {
    Problem prob = read_input(argv[1]);
    vector<vector<int>> clauses;
    set<pair<int,int>> end_points;
    for(auto line : prob.lines) {
        end_points.insert({line[2], line[3]});
    }
    cout<<"Input read done"<<endl;
    strtPoint(prob.N, prob.M, prob.K, clauses,  prob.lines);
    cout<<"Start Point done"<<endl;
    endPoint(prob.N, prob.M, prob.K, clauses, prob.lines);
    cout<<"End Point done"<<endl;
    flow(prob.N, prob.M, prob.K, clauses, end_points);
    cout<<"Flow done"<<endl;
    limit_on_turns(prob.N, prob.M, prob.K, prob.J, clauses, 1);
    cout<<"Limit on turns done"<<endl;
    at_most_one_p(prob.N, prob.M, prob.K, clauses, prob.J*prob.N*prob.M*10);
    cout<<"At most one P done"<<endl;
    // at_most_one_d(prob.N, prob.M, prob.K, clauses, prob.J*prob.N*prob.M*20);
    if(prob.scenario == 2) {
        popularity(prob.N, prob.M, prob.K, clauses, prob.popular);
    }
    path_consistency(prob.N, prob.M, prob.K, clauses);   
    cout<<"Path consistency done"<<endl;

    //l take as input a file named test.city (Part I) and
    // produce a file test.satinput – the input file for minisat. You can assume that test.city exists in
    // the present working directory. (‘test’ is a placeholder parameter and can be changed when
    // running).
    string file = "";
    for(int i=0; i< strlen(argv[1]); i++){
        if(argv[1][i]=='.'){
            break;
        }
        file+=argv[1][i];
    }
    file += ".satinput";
    create_inputfile_for_sat(clauses, file);
    return 0;
}   