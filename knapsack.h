#pragma once

#include <chrono>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

#define Item std::pair<int, int>
#define Knapsack std::vector<Item>

bool myComparison(const Item &a, const Item &b)
{
    return a.second < b.second;
}

Knapsack knapsackGenerator(unsigned int &num_items, unsigned int &max_weight) {
    Knapsack knapsack(num_items);
    for (int i = 0; i < num_items; i++) {
        knapsack[i].first = (rand() % max_weight + 1);
        knapsack[i].second = (rand() % max_weight + 1);
    }
    return knapsack;
}

Knapsack getKnapsackFromFile(std::string filename) {
    Knapsack pairs;
    std::ifstream ifs(filename);
    while (!ifs.eof()) {
        Item item;
        ifs >> item.first >> item.second;
        pairs.push_back(item);
    }
    ifs.close();
    return pairs;
}

void printResultsToFile(
    const std::string &algorithmName,
    const int numberOfItems,
    const int maxWeight,
    const int algorithmResult,
    const int iterations,
    std::chrono::duration<int64_t, std::nano> averageTime)
{
    std::ofstream file;
    std::string result_filename = algorithmName + ".csv";

    file.open(result_filename, std::fstream::out);

    file << algorithmName << ";"
         << numberOfItems << ";"
         << maxWeight << ";"
         << algorithmResult <<";"
         << std::fixed << std::chrono::duration <double, std::milli> (averageTime).count() / iterations << ";"
         << std::endl;

    file.close();
}
