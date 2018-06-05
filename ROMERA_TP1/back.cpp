#define Item pair<int, int>
#define Knapsack vector<Item>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <math.h>
using namespace std;

int solveBacktracking(int solution, int index, int max_weight, const Knapsack &mochila){
    if (index == mochila.size() || max_weight == 0){
        return solution;
    } else if (max_weight - mochila[index].first < 0){
        index++;
        return solveBacktracking(solution, index, max_weight, mochila);
    } else {
        int proximo = index + 1;
        return max(solveBacktracking(solution + mochila[index].second, proximo, max_weight - mochila[index].first, mochila),
                solveBacktracking(solution, proximo, max_weight, mochila));
    }
}

int backtracking(const int &max_weight, const Knapsack &mochila){
    return solveBacktracking(0, 0, max_weight, mochila);
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

    auto startBacktracking = chrono::steady_clock::now();
    unsigned int test_backtracking = backtracking(max_weight, mochila);
    auto endBacktracking = chrono::steady_clock::now();
    auto diffBacktracking = endBacktracking - startBacktracking;
    cout << "Tiempo utilizado por Backtracking " << chrono::duration <double, milli> (diffBacktracking).count() << " ms" << endl;
    cout << test_backtracking << endl;

    return 0;
}