#include "../includes/solver.h"

using namespace std;


void Solver::solve(int m, int n, int k, vector<vector<vector<int>>>& grid, Partition& currentP, vector<Placement>& currentL, int currentEmptyCount) {
    
    if (currentEmptyCount == 0) {
        if (partitions.find(currentP) == partitions.end()){
            partitions.insert(currentP);
            exampleLayouts[currentP] = currentL;
        }
        return;
    }

    int fx = -1, fy = -1, fz = -1;
    
    // Szukaj pierwszej pustej komórki
    for(int i=0; i<m && fx == -1; ++i) {
        for(int j=0; j<n && fx == -1; ++j) {
            for(int l=0; l<k && fx == -1; ++l) {
                if(grid[i][j][l] == 0) {
                    fx = i; fy = j; fz = l;
                }
            }
        }
    }

    if (fx == -1) {
        return;
    }

    int maxA = m - fx;
    int maxB = n - fy;
    int maxC = k - fz;

    for(int a=maxA; a>=1; --a) {
        for(int b=maxB; b>=1; --b) {
            for(int c=maxC; c>=1; --c) {
                
                int blockSize = a * b * c;
                // Jeśli blok jest za duży, przerwij pętlę c (zmniejsz b i restartuj c)
                if(blockSize > currentEmptyCount) break; 

                bool ok = true;
                for(int i=fx; i<fx+a && ok; ++i)
                    for(int j=fy; j<fy+b && ok; ++j)
                        for(int l=fz; l<fz+c && ok; ++l)
                            if(grid[i][j][l] != 0) ok = false;

                if(ok) {
                    // Zaznacz blok
                    for(int i=fx; i<fx+a; ++i)
                        for(int j=fy; j<fy+b; ++j)
                            for(int l=fz; l<fz+c; ++l) grid[i][j][l] = 1;

                    currentP.insert(Block(a, b, c));
                    currentL.push_back({fx, fy, fz, a, b, c});
                    
                    solve(m, n, k, grid, currentP, currentL, currentEmptyCount - blockSize);

                    // Cofnij
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