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
using namespace std;

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

int main(int argc, char *argv[]) {
    unsigned int num_items = 0;
    unsigned int max_weight = 0;
    if (argc == 3) {
        num_items = atoi(argv[1]);
        max_weight = atoi(argv[2]);
    } else {
        cin >> num_items >> max_weight;
    }

    Knapsack mochila = knapsackGenerator(num_items, max_weight);

    // Benchmark Backtracking
    srand (time(NULL));
    cout << "steady_clock" << endl;
    cout << chrono::steady_clock::period::num << endl;
    cout << chrono::steady_clock::period::den << endl;
    cout << "steady = " << boolalpha << chrono::steady_clock::is_steady << endl << endl;

    auto startDynamic = chrono::steady_clock::now();
    unsigned int testDynamic = dynamic(max_weight, mochila);
    auto endDynamic = chrono::steady_clock::now();
    auto diffDynamic = endDynamic - startDynamic;
    cout << "Tiempo utilizado por Dynamic " << chrono::duration <double, milli> (diffDynamic).count() << " ms" << endl;
    cout << testDynamic << endl;

    return 0;
}