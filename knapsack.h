#pragma once

#include <chrono>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

#define Item std::pair<unsigned, unsigned>
#define Knapsack std::vector<Item>
#define Matrix std::vector<std::vector<int>>

bool myComparison(const Item &a, const Item &b)
{
    return a.second < b.second;
}

Knapsack knapsackGenerator(const unsigned num_items, const unsigned max_weight)
{
    Knapsack knapsack(num_items);
    for (int i = 0; i < num_items; i++)
    {
        knapsack[i].first = (rand() % max_weight + 1);
        knapsack[i].second = (rand() % max_weight + 1);
    }
    return knapsack;
}

Knapsack getKnapsackFromFile(const std::string &filename) {
    Knapsack pairs;
    std::ifstream ifs(filename);
    while (!ifs.eof())
    {
        Item item;
        ifs >> item.first >> item.second;
        pairs.push_back(item);
    }
    ifs.close();
    return pairs;
}

void printResultsToFile(
    const std::string &algorithmName,
    const unsigned numberOfItems,
    const unsigned maxWeight,
    const unsigned algorithmResult,
    const unsigned iterations,
    std::chrono::duration<int64_t, std::nano> averageTime)
{
    const std::string result_filename = algorithmName + ".csv";

    std::ofstream file(result_filename, std::fstream::out);

    file << algorithmName << ";"
         << numberOfItems << ";"
         << maxWeight << ";"
         << algorithmResult <<";"
         << std::fixed << std::chrono::duration <double, std::milli> (averageTime).count() / iterations << ";"
         << std::endl;

    file.close();
}

std::chrono::nanoseconds benchmarkKnapsackAlgorithm(
    unsigned (*algorithm)(const unsigned, const Knapsack&),
    const Knapsack &items,
    const unsigned max_weight,
    const unsigned iterations)
{
    std::chrono::nanoseconds averageTime {0};
    for (int i = 0; i < iterations; ++i)
    {
        auto start_time = std::chrono::steady_clock::now();
        algorithm(max_weight, items);
        auto end_time = std::chrono::steady_clock::now();
        averageTime += end_time - start_time;
    }
    return averageTime;
}
