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

Items items;

int seed;

Items generateItemsList(int num_items, int max_weight, int profit) {
    srand(seed);
    Items items;
    items.reserve(num_items);
    Item item;
    for (int i = 0; i < num_items; i++) {
        item.first = (rand() % max_weight) + 1;
        item.second = (rand() % profit) + 1;
        items.push_back(item);
    }
    return items;
}

void printVectorToFile(int num_items, int max_weight, Items items, std::ofstream &f) {
    f << num_items << " " << max_weight << std::endl;
    for(int i = 0; i < num_items; i++) {
        f << items[i].first << " " << items[i].second << std::endl;
    }
}

int main(int argc, char *argv[]) {
    int num_items = 0;
    int max_weight = 0; 
    int profit = 0;
    if(argc != 5) {
        std::cerr << "Not enough parameters" << std::endl;
    } else {
        num_items = atoi(argv[1]);    
        max_weight = atoi(argv[2]);
        profit = atoi(argv[3]);
        seed = atoi(argv[4]);
    }

    std::vector<Item> items = generateItemsList(num_items, max_weight, profit);
    std::string fileName = std::to_string(num_items) + "i_" + std::to_string(max_weight) + "w_" + std::to_string(profit) + "p.txt";
    std::ofstream f;
    f.open(fileName, std::fstream::out);
    printVectorToFile(num_items, max_weight, items, f);
    f.close();
    return 0;
}