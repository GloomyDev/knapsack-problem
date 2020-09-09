#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>

#include "knapsack.h"

int solveDynamic(int index, int max_weight, Matrix &matrix, const Knapsack &knapsack) {
    if (matrix[index][max_weight] != -1) return matrix[index][max_weight];

    std::pair<int, int> item = knapsack[index];

    if (index == 0) { // If last item
        if (item.first <= max_weight) return item.second;
        return 0;
    }

    if (max_weight == 0) return 0;

    if (item.first > max_weight) return solveDynamic(index-1, max_weight, matrix, knapsack);

    matrix[index][max_weight] = std::max(solveDynamic(index-1, max_weight, matrix, knapsack),
                                    solveDynamic(index-1, max_weight - item.first, matrix, knapsack) + item.second);  

    return matrix[index][max_weight];
}

int dynamic(const int &max_weight, const Knapsack &knapsack)
{
    Matrix matrix(knapsack.size(), std::vector<int>(max_weight + 1, -1));
    int result = solveDynamic(knapsack.size() - 1, max_weight, matrix, knapsack);
    return result;
}

int main(int argc, char *argv[])
{
    if (argc < 2) return 1;

    const std::string file = argv[1];

    Knapsack items = getKnapsackFromFile(file);
    int max_weight = items[0].second;
    items.erase(items.begin());
    items.erase(items.end() - 1);

    unsigned solution = dynamic(max_weight, items);
    auto averageTime = benchmarkKnapsackAlgorithm(dynamic, items, max_weight, 50);
    // cout << "Times used by Dynamic " << chrono::duration <double, milli> (diffDynamic).count() << " ms." << " Profit: " << testDynamic << endl;
    printResultsToFile("dynamic", items.size(), max_weight, solution, 50, averageTime);
    return 0;
}
