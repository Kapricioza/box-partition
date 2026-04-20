#ifndef TyPES_H
#define TyPES_H

#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct Block {
    int d[3];
    Block(int a, int b, int c) {
        d[0] = a; d[1] = b; d[2] = c;
        sort(d, d + 3); 
    };
    bool operator < (const Block& other) const {
        for(int i=0; i<3; i++){
            if(d[i] != other.d[i]) return d[i] < other.d[i];
        }
        return false;
    }
};

struct Placement {
    int x, y, z, dx, dy, dz;
};

typedef multiset<Block> Partition;

#endif