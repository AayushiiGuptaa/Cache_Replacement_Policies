#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#include "cache.h"
#include "LRUPolicy.h"
#include "FIFOPolicy.h"
#include "RandomPolicy.h"
#include "Adaptive.h"

using namespace std;

vector<unsigned long> loadTrace(const string& filename)
{
    vector<unsigned long> trace;

    ifstream fin(filename);

    if (!fin.is_open())
    {
        cout << "Failed to open: " << filename << endl;
        return trace;
    }

    unsigned long address;

    while (fin >> std::hex >> address)
    {
        trace.push_back(address);
    }

    cout << filename << " -> Loaded " << trace.size() << " addresses" << endl;

    return trace;
}

void runSimulation(
    const string& traceFile,
    ReplacementPolicy* policy,
    ofstream& csv)
{
    Cache cache(
        4096,
        64,
        policy
    );

    vector<unsigned long> trace = loadTrace(traceFile);

    for (auto addr : trace)
    {
        cache.access(addr);
    }

    cout << "Policy : " << policy->name() << endl;
    cout << "Hits   : " << cache.getHits() << endl;
    cout << "Misses : " << cache.getMisses() << endl;
    cout << "HitRate: "
         << fixed
         << setprecision(4)
         << cache.getHitRate()
         << endl;

    csv
        << traceFile << ","
        << policy->name() << ","
        << cache.getHits() << ","
        << cache.getMisses() << ","
        << cache.getHitRate()
        << endl;

    cout << "--------------------------" << endl;
}

int main()
{
    ofstream csv("results/results.csv");

    csv << "Trace,Policy,Hits,Misses,HitRate\n";

    vector<string> traces =
   {
    "traces/sequential.txt",
    "traces/random.txt",
    "traces/looping.txt",
    "traces/matrix.txt"
   };

    for (const auto& trace : traces)
    {
        runSimulation(
            trace,
            new LRUPolicy(),
            csv
        );

        runSimulation(
            trace,
            new FIFOPolicy(),
            csv
        );

        runSimulation(
            trace,
            new RandomPolicy(),
            csv
        );

        AdaptivePolicy* adaptive =
            new AdaptivePolicy();

        adaptive->switchPolicy(true);

        runSimulation(
            trace,
            adaptive,
            csv
        );
    }

    csv.close();

    cout << "Simulation complete." << endl;
    cout << "Results written to results/results.csv" << endl;

    return 0;
}