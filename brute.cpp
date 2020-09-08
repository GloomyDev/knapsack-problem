#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>

#define Item std::pair<int, int>
#define Knapsack std::vector<Item>

std::string file = "knapsack.txt";
int laps = 1;

bool myComparison(const Item &a, const Item &b)
{
    return a.second < b.second;
}

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

int main(int argc, char *argv[]) {
    if (argc > 1) {
        file = argv[1];
        if (argc > 2) {
            laps = atoi(argv[2]);
        }
    }
    Knapsack items = getKnapsackFromFile(file);
    int max_weight = items[0].second;
    items.erase(items.begin());
    items.erase(items.end() - 1);

    std::ofstream file;
    std::string bruteTest = "bruteforce.csv";
    file.open(bruteTest, std::fstream::out);

    auto start_brute_force = std::chrono::steady_clock::now();
    unsigned int test_brute_force = brute_force(max_weight, items);
    auto end_brute_force = std::chrono::steady_clock::now();
    auto diff_brute_force = end_brute_force - start_brute_force;
    auto averageTime = diff_brute_force;
    for (int i = 1; i <= 20 - 1; i++) {
        start_brute_force = std::chrono::steady_clock::now();
        test_brute_force = brute_force(max_weight, items);
        end_brute_force = std::chrono::steady_clock::now();
        diff_brute_force = end_brute_force - start_brute_force;
        averageTime += diff_brute_force;
    }
    // cout << "Time used by Brute Force " << chrono::duration <double, milli> (diff_brute_force).count() << " ms." << " Profit: " << test_brute_force << endl;
    file << "bruteforce;"
         << items.size() << ";"
         << max_weight << ";"
         << test_brute_force <<";"
         << std::fixed << std::chrono::duration <double, std::milli> (averageTime).count() / 20<< ";"
         << std::endl;
    file.close();
    return 0;
}
