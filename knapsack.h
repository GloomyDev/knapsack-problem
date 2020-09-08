#pragma once

#include <fstream>
#include <string>
#include <utility>
#include <vector>

#define Item std::pair<int, int>
#define Knapsack std::vector<Item>

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
