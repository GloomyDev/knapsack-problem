#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>

#include "knapsack.h"

void partialSums(int index, Item item, const Knapsack &items, Item &solution, const int &max_weight)
{
    if (index == items.size()) {
        if (item.first <= max_weight && item.second > solution.second){
            solution.first = item.first;
            solution.second = item.second;
        }
    } else {
        index++;
        partialSums(index, item, items, solution, max_weight);

        item.first += items[index - 1].first;
        item.second += items[index - 1].second;
        partialSums(index, item, items, solution, max_weight);
    }
}

int brute_force(const int &max_weight, const Knapsack &knapsack){
    Item item (0,0);
    Item solution (0,0);
    partialSums(0, item, knapsack, solution, max_weight);
    unsigned int benefit = solution.second;
    return benefit;
}

int main(int argc, char *argv[])
{
    if (argc < 2) return 1;

    const std::string file = argv[1];

    Knapsack items = getKnapsackFromFile(file);
    int max_weight = items[0].second;
    items.erase(items.begin());
    items.erase(items.end() - 1);

    unsigned solution = brute_force(max_weight, items);
    auto averageTime = benchmarkKnapsackAlgorithm(brute_force, items, max_weight, 20);
    // cout << "Time used by Brute Force " << chrono::duration <double, milli> (diff_brute_force).count() << " ms." << " Profit: " << test_brute_force << endl;
    printResultsToFile("bruteforce", items.size(), max_weight, solution, 20, averageTime);
    return 0;
}
