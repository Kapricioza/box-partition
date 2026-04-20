#include <iostream>
#include <vector>
#include "../includes/types.h"
#include "../includes/solver.h"
#include "../includes/exporter.h"

using namespace std;
 

int main(){
    int m, n, k;
    cout << "Podaj wymiary pudelka (m n k): ";
    if (!(cin >> m >> n >> k)){
        cerr << "Nieprawidlowe dane wejsciowe" << endl;
        return 1;
    } 
    
    vector<vector<vector<int>>> grid(m, vector<vector<int>>(n, vector<int>(k, 0)));
    
    Solver solver;
    Partition currentP;
    vector<Placement> currentL;

    solver.solve(m, n, k, grid, currentP, currentL);

    Exporter::exportToJSON("../web/data/results.json",m,n,k,solver);

    cout << "Znaleziono i zapisano " << solver.partitions.size() << " unikalnych partycji." << endl;
    return 0;
}