#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>

#include "knapsack.h"

unsigned solveDynamic(const unsigned index, const int max_weight, Matrix &matrix, const Knapsack &knapsack)
{
    if (matrix[index][max_weight] != -1) return matrix[index][max_weight];

    const Item item = knapsack[index];

    if (index == 0)
    { // If last item
        if (item.weight <= max_weight) return item.value;
        return 0;
    }

    if (max_weight == 0) return 0;

    if (item.weight > max_weight) return solveDynamic(index - 1, max_weight, matrix, knapsack);

    matrix[index][max_weight] = std::max(
        solveDynamic(index-1, max_weight, matrix, knapsack),
        solveDynamic(index-1, max_weight - item.weight, matrix, knapsack) + item.value
    );

    return matrix[index][max_weight];
}

unsigned dynamic(const unsigned max_weight, const Knapsack &knapsack)
{
    Matrix matrix(knapsack.size(), std::vector<int>(max_weight + 1, -1));
    return solveDynamic(knapsack.size() - 1, max_weight, matrix, knapsack);
}

int main(int argc, char *argv[])
{
    if (argc < 2) return 1;

    const std::string file = argv[1];

    Knapsack items = getKnapsackFromFile(file);
    const unsigned max_weight = items[0].value;
    items.erase(items.begin());
    items.erase(items.end() - 1);

    const unsigned solution = dynamic(max_weight, items);
    const auto averageTime = benchmarkKnapsackAlgorithm(dynamic, items, max_weight, 50);
    printResultsToFile("dynamic", items.size(), max_weight, solution, 50, averageTime);
    return 0;
}
