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

std::string file = "mochila.txt";
int laps = 1;

bool myComparison(const Item &a, const Item &b)
{
    return a.second > b.second;
}

int solveBacktracking(int solution, int index, int max_weight, const Knapsack &mochila){
    if (index == mochila.size() || max_weight == 0){
        return solution;
    } else if (max_weight - mochila[index].first < 0){
        index++;
        return solveBacktracking(solution, index, max_weight, mochila);
    } else {
        int proximo = index + 1;
        return std::max(solveBacktracking(solution + mochila[index].second, proximo, max_weight - mochila[index].first, mochila),
                solveBacktracking(solution, proximo, max_weight, mochila));
    }
}

int backtracking(const int &max_weight, const Knapsack &mochila){
    return solveBacktracking(0, 0, max_weight, mochila);
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
    std::string backTest = "backtracking.csv";
    file.open(backTest, std::fstream::out);

    auto startBacktracking = std::chrono::steady_clock::now();
    unsigned int test_backtracking = backtracking(max_weight, items);
    auto endBacktracking = std::chrono::steady_clock::now();
    auto diffBacktracking = endBacktracking - startBacktracking;
    auto averageTime = diffBacktracking;
    for (int i = 1; i <= 25 - 1; i++) {
        startBacktracking = std::chrono::steady_clock::now();
        test_backtracking = backtracking(max_weight, items);
        endBacktracking = std::chrono::steady_clock::now();
        diffBacktracking = endBacktracking - startBacktracking;
        averageTime += diffBacktracking;
    }
    // cout << "Tiempo utilizado por Backtracking " << chrono::duration <double, milli> (diffBacktracking).count() << " ms." << " Profit: " << test_backtracking << endl;
    file << "backtracking;"
         << items.size() << ";"
         << max_weight << ";"
         << test_backtracking<< ";"
         << std::fixed << std::chrono::duration <double, std::milli> (averageTime).count() / 25 << ";"
         << std::endl;
    file.close();
    return 0;
}