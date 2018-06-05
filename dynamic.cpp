#define Item pair<int, int>
#define Knapsack vector<Item>
#define Matrix vector<vector<int> >
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <math.h>
#include <fstream>
using namespace std;

string file = "mochila.txt";
int laps = 1;

bool myComparison(const Item &a, const Item &b)
{
       return a.second < b.second;
}

int solveDynamic(int index, int max_weight, Matrix &matrix, Knapsack &mochila) {
    if (matrix[index][max_weight] != -1) return matrix[index][max_weight];
    
    pair<int, int> item = mochila[index];

    if (index == 0) { //Si es el último item
        if (item.first <= max_weight) return item.second;
        return 0;
    }
    
    if (max_weight == 0) return 0;
    
    if (item.first > max_weight) return solveDynamic(index-1, max_weight, matrix, mochila);

    matrix[index][max_weight] = max(solveDynamic(index-1, max_weight, matrix, mochila),
                                    solveDynamic(index-1, max_weight - item.first, matrix, mochila) + item.second);  
    
    return matrix[index][max_weight];
}

int dynamic(int max_weight, Knapsack &mochila) {
    Matrix matrix(mochila.size(), vector<int>(max_weight + 1, -1));
    int result = solveDynamic(mochila.size() - 1, max_weight, matrix, mochila);
    return result;
}

Knapsack knapsackGenerator(unsigned int &num_items, unsigned int &max_weight) {
    Knapsack knapsack(num_items);
    for (int i = 0; i < num_items; i++) {
        // Random
        knapsack[i].first = (rand() % max_weight + 1);
        knapsack[i].second = (rand() % max_weight + 1);
        
        // Manual
        // cin >> mochila[i].first >> mochila[i].second;   
        // cout << mochila[i].first << " " << mochila[i].second << endl;
    }
    return knapsack;
}

Knapsack getKnapsackFromFile(string filename) {
    Knapsack pairs;
    ifstream ifs(filename);
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

    // sort(items.begin(), items.end(), myComparison);
    // for (int i = 0; i < items.size(); i++) {
    //     cout << items[i].first << " " << items[i].second << endl;
    // }

    // Benchmark Backtracking
    // srand (time(NULL));
    // cout << "steady_clock" << endl;
    // cout << chrono::steady_clock::period::num << endl;
    // cout << chrono::steady_clock::period::den << endl;
    // cout << "steady = " << boolalpha << chrono::steady_clock::is_steady << endl << endl;

    ofstream file;
    string dynamicTest = "dynamic.csv";
    file.open(dynamicTest, fstream::out);
    // file << "dynamic;items;max weight;profit;time;" << endl;
    auto startDynamic = chrono::steady_clock::now();
    unsigned int testDynamic = dynamic(max_weight, items);
    auto endDynamic = chrono::steady_clock::now();
    auto diffDynamic = endDynamic - startDynamic;
    auto averageTime = diffDynamic;
    for (int i = 1; i <= 50 - 1; i++) {
        startDynamic = chrono::steady_clock::now();
        testDynamic = dynamic(max_weight, items);
        endDynamic = chrono::steady_clock::now();
        diffDynamic = endDynamic - startDynamic;
        averageTime += diffDynamic;
    }
    // cout << "Tiempo utilizado por Dynamic " << chrono::duration <double, milli> (diffDynamic).count() << " ms." << " Profit: " << testDynamic << endl;
    file << "dynamic;" << items.size() << ";" << max_weight << ";" << testDynamic << ";" << std::fixed << chrono::duration <double, milli> (averageTime).count() / 50 << ";" << endl;
    file.close();
    return 0;
}