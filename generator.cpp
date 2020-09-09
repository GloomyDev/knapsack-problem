#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <tuple>
#include <utility>
#include <vector>

#define Item std::pair<int, int>
#define Items std::vector<Item>

Items generateItemsList(int num_items, int max_weight, int profit, int seed) {
    srand(seed);
    Items items;
    items.reserve(num_items);
    for (int i = 0; i < num_items; ++i) {
        items.emplace_back(
            (rand() % max_weight) + 1,
            (rand() % profit) + 1
        );
    }
    return items;
}

void printVectorToFile(int num_items, int max_weight, Items items, std::ofstream &f) {
    f << num_items << " " << max_weight << std::endl;
    for(int i = 0; i < num_items; ++i) {
        f << items[i].first << " " << items[i].second << std::endl;
    }
}

int main(int argc, char *argv[]) {

    if (argc != 5)
    {
        std::cerr << "Not enough parameters" << std::endl;
        return 1;
    }

    int num_items = atoi(argv[1]);
    int max_weight = atoi(argv[2]);
    int profit = atoi(argv[3]);
    int seed = atoi(argv[4]);

    std::vector<Item> items = generateItemsList(num_items, max_weight, profit, seed);
    std::string fileName = std::to_string(num_items) + "i_" + std::to_string(max_weight) + "w_" + std::to_string(profit) + "p.txt";
    std::ofstream file(fileName, std::fstream::out);
    printVectorToFile(num_items, max_weight, items, file);
    file.close();
    return 0;
}