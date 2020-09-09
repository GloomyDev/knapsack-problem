#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>

#include "knapsack.h"

unsigned solveBacktracking(const unsigned solution, const unsigned index, const int max_weight, const Knapsack &knapsack)
{
    if (index == knapsack.size() || max_weight == 0)
    {
        return solution;
    }
    else if (max_weight < knapsack[index].first)
    {
        return solveBacktracking(solution, index + 1, max_weight, knapsack);
    }
    else
    { 
        return std::max(
            solveBacktracking(solution + knapsack[index + 1].second, index + 1, max_weight - knapsack[index + 1].first, knapsack),
            solveBacktracking(solution, index + 1, max_weight, knapsack)
        );
    }
}

unsigned backtracking(const unsigned max_weight, const Knapsack &knapsack)
{
    return solveBacktracking(0, 0, max_weight, knapsack);
}

int main(int argc, char *argv[])
{
    if (argc < 2) return 1;

    const std::string file = argv[1];

    Knapsack items = getKnapsackFromFile(file);
    const unsigned max_weight = items[0].second;
    items.erase(items.begin());
    items.erase(items.end() - 1);

    const unsigned solution = backtracking(max_weight, items);
    const auto averageTime = benchmarkKnapsackAlgorithm(backtracking, items, max_weight, 25);
    printResultsToFile("backtracking", items.size(), max_weight, solution, 25, averageTime);
    return 0;
}
