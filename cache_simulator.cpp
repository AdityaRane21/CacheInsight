#include <bits/stdc++.h>
using namespace std;

struct CacheLine {
    bool valid;
    unsigned long tag;
    unsigned long lru;
};

struct CacheSet {
    vector<CacheLine> lines;
};

class CacheSimulator {
private:
    int cacheSize;
    int blockSize;
    int associativity;
    int numSets;

    int offsetBits;
    int indexBits;

    unsigned long timer;
    unsigned long hits;
    unsigned long misses;

    vector<CacheSet> cache;

public:
    CacheSimulator(int cSize, int bSize, int assoc)
        : cacheSize(cSize), blockSize(bSize), associativity(assoc),
          hits(0), misses(0), timer(0) {

        numSets = cacheSize / (blockSize * associativity);

        offsetBits = log2(blockSize);
        indexBits = log2(numSets);

        cache.resize(numSets);
        for (auto &set : cache) {
            set.lines.resize(associativity);
            for (auto &line : set.lines) {
                line.valid = false;
                line.lru = 0;
            }
        }
    }

    void access(unsigned long address) {
        unsigned long index =
            (address >> offsetBits) & ((1 << indexBits) - 1);
        unsigned long tag =
            address >> (offsetBits + indexBits);

        CacheSet &set = cache[index];

        // HIT check
        for (auto &line : set.lines) {
            if (line.valid && line.tag == tag) {
                hits++;
                line.lru = ++timer;
                return;
            }
        }

        // MISS
        misses++;

        // Empty line available
        for (auto &line : set.lines) {
            if (!line.valid) {
                line.valid = true;
                line.tag = tag;
                line.lru = ++timer;
                return;
            }
        }

        // LRU Replacement
        auto lruLine = min_element(
            set.lines.begin(), set.lines.end(),
            [](const CacheLine &a, const CacheLine &b) {
                return a.lru < b.lru;
            });

        lruLine->tag = tag;
        lruLine->lru = ++timer;
    }

    void printStats() {
        unsigned long total = hits + misses;
        cout << "\n===== Cache Simulation Results =====\n";
        cout << "Cache Size      : " << cacheSize << " bytes\n";
        cout << "Block Size      : " << blockSize << " bytes\n";
        cout << "Associativity   : " << associativity << "-way\n";
        cout << "Number of Sets  : " << numSets << "\n";
        cout << "-----------------------------------\n";
        cout << "Total Accesses  : " << total << "\n";
        cout << "Hits            : " << hits << "\n";
        cout << "Misses          : " << misses << "\n";
        cout << fixed << setprecision(2);
        cout << "Hit Rate        : "
             << (double)hits / total * 100 << "%\n";
        cout << "Miss Rate       : "
             << (double)misses / total * 100 << "%\n";
    }
};

int main(int argc, char *argv[]) {
    if (argc != 5) {
        cerr << "Usage: ./cache_sim <cache_size> <block_size> <associativity> <trace_file>\n";
        return 1;
    }

    int cacheSize = stoi(argv[1]);
    int blockSize = stoi(argv[2]);
    int associativity = stoi(argv[3]);
    string traceFile = argv[4];

    ifstream file(traceFile);
    if (!file.is_open()) {
        cerr << "Error opening trace file\n";
        return 1;
    }

    CacheSimulator simulator(cacheSize, blockSize, associativity);

    unsigned long address;
    while (file >> hex >> address) {
        simulator.access(address);
    }

    simulator.printStats();
    return 0;
}
