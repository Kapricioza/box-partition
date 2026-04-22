#ifndef SOLVER_H
#define SOLVER_H

#include "types.h"
#include <map>

class Solver {
    public:
        void solve(int m, int n, int k, vector<vector<vector<int>>>& grid, 
           Partition& currentP, vector<Placement>& currentL , int currentEmptyCount);

        set<Partition> partitions;
        map<Partition, vector<Placement>> exampleLayouts;

};

#endif