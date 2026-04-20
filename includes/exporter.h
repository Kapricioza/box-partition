#ifndef EXPORTER_H
#define EXPORTER_H

#include "solver.h"
#include <string>

using namespace std;

class Exporter {
    public:
        static void exportToJSON(const string& filename, int m, int n, int k, const Solver& solver );
};

#endif