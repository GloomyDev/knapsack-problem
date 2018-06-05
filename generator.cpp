#define Item pair<int, int>
#define Items vector<Item>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <tuple>
#include <fstream>
#include <iterator>
#include <utility>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;

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

void printVectorToFile(int num_items, int max_weight, Items items, ofstream &f) {
    f << num_items << " " << max_weight << endl;
    for(int i = 0; i < num_items; i++) {
        f << items[i].first << " " << items[i].second << endl;
    }
}

int main(int argc, char *argv[]) {
    int num_items = 0;
    int max_weight = 0; 
    int profit = 0;
    if(argc != 5) {
        cerr << "Not enough parameters" << endl;
    } else {
        num_items = atoi(argv[1]);    
        max_weight = atoi(argv[2]);
        profit = atoi(argv[3]);
        seed = atoi(argv[4]);
    }
    
    vector<Item> items = generateItemsList(num_items, max_weight, profit);
    string fileName = to_string(num_items) + "i_" + to_string(max_weight) + "w_" + to_string(profit) + "p.txt";
    ofstream f;
    f.open(fileName, fstream::out);
    printVectorToFile(num_items, max_weight, items, f);
    f.close();
    return 0;
}