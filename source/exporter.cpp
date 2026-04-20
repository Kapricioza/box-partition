#include "../includes/exporter.h"
#include <fstream>
#include <iostream>

using namespace std;

void Exporter::exportToJSON(const string& filename, int m, int n, int k, const Solver& solver){
    ofstream out(filename);
    if (!out.is_open()){
        cerr << "Nie mozna otworzyc pliku do zapisu" << endl;
        return;
    }

    out << "{\n  \"m\":" << m << ", \"n\":" << n << ", \"k\":" << k << ",\n";
    out << "  \"total_partitions\":" << solver.partitions.size() << ",\n";
    out << "  \"partitions\": [\n";

    int pIdx = 0;
    for (const auto& p : solver.partitions) {
        
        long long volSum = 0;
        for(auto const& b : p) volSum += (long long)b.d[0] * b.d[1] * b.d[2];

        out << "    {\n      \"id\":" << pIdx++ << ",\n";
        out << "      \"vol_check\": ";
        long long targetVolume = (long long)m * n * k;
        if (volSum == targetVolume) {
            
            out << "true";
        } else {
            
            out << "false";
        }
        out << ",\n";
        out << "      \"layout\": [\n";
        
        const auto& layout = solver.exampleLayouts.at(p);
        for (size_t i = 0; i < layout.size(); ++i) {
            out << "        {\"x\":" << layout[i].x << ",\"y\":" << layout[i].y << ",\"z\":" << layout[i].z 
                    << ",\"dx\":" << layout[i].dx << ",\"dy\":" << layout[i].dy << ",\"dz\":" << layout[i].dz << "}";
            if (i < layout.size() - 1) {
                out << ",";
            }else{
                out << "\n";
            }
        }
        out << "      ]\n    }";
        if (pIdx < (int)solver.partitions.size()) {
            out << ",";
        }else{
            out << "\n";
        }
        
    }

    out << "  ]\n}\n";
    out.close();


}