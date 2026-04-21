#include "../includes/solver.h"

using namespace std;


void Solver::solve(int m, int n, int k, vector<vector<vector<int>>>& grid, 
           Partition& currentP, vector<Placement>& currentL) {
    
    int fx = -1, fy = -1, fz = -1;
    int emptyCount = 0;
    
    
    for(int i=0; i<m; ++i)
        for(int j=0; j<n; ++j)
            for(int l=0; l<k; ++l) {
                if(grid[i][j][l] == 0) {
                    emptyCount++;
                    if(fx == -1) { fx=i; fy=j; fz=l; }
                }
            }

    if(fx == -1) { 
        if (partitions.find(currentP) == partitions.end()) {
            partitions.insert(currentP);
            exampleLayouts[currentP] = currentL;
        }
        return;
    }

    
    int maxA = m - fx;
    int maxB = n - fy;
    int maxC = k - fz;

    for(int a=1; a<=maxA; ++a) {
        for(int b=1; b<=maxB; ++b) {
            for(int c=1; c<=maxC; ++c) {
                
                if(a * b * c > emptyCount) break;

                bool ok = true;
                for(int i=fx; i<fx+a && ok; ++i)
                    for(int j=fy; j<fy+b && ok; ++j)
                        for(int l=fz; l<fz+c && ok; ++l)
                            if(grid[i][j][l] != 0) ok = false;

                if(ok) {
                    for(int i=fx; i<fx+a; ++i)
                        for(int j=fy; j<fy+b; ++j)
                            for(int l=fz; l<fz+c; ++l) grid[i][j][l] = 1;

                    currentP.insert(Block(a, b, c));
                    currentL.push_back({fx, fy, fz, a, b, c});
                    
                    solve(m, n, k, grid, currentP, currentL);

                    currentL.pop_back();
                    currentP.erase(currentP.find(Block(a, b, c)));
                    for(int i=fx; i<fx+a; ++i)
                        for(int j=fy; j<fy+b; ++j)
                            for(int l=fz; l<fz+c; ++l) grid[i][j][l] = 0;
                }
            }
        }
    }
}