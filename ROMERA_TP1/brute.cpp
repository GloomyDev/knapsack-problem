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

void partialSums(int index, Item par, const Knapsack &items, Item &solution, const int &max_weight)
{
    if (index == items.size()) {
        if (par.first <= max_weight && par.second > solution.second){
            solution.first = par.first;
            solution.second = par.second;
        }
    } else {
        index++;
        partialSums(index, par, items, solution, max_weight);

        par.first += items[index - 1].first;
        par.second += items[index - 1].second;
        partialSums(index, par, items, solution, max_weight);
    }
}

int fuerza_bruta(const int &max_weight, const Knapsack &mochila){
    Item par (0,0);
    Item solution (0,0);
    partialSums(0, par, mochila, solution, max_weight);
    unsigned int benefit = solution.second;
    return benefit;
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

    // Benchmark Fuerza Bruta
    srand (time(NULL));
    cout << "steady_clock" << endl;
    cout << chrono::steady_clock::period::num << endl;
    cout << chrono::steady_clock::period::den << endl;
    cout << "steady = " << boolalpha << chrono::steady_clock::is_steady << endl << endl;
    cout << "*************************" << endl;

    auto start_fuerza_bruta = chrono::steady_clock::now();
    unsigned int test_fuerza_bruta = fuerza_bruta(max_weight, mochila);
    auto end_fuerza_bruta = chrono::steady_clock::now();
    auto diff_fuerza_bruta = end_fuerza_bruta - start_fuerza_bruta;
    cout << "Tiempo utilizado por Fuerza Bruta " << chrono::duration <double, milli> (diff_fuerza_bruta).count() << " ms" << endl;
    cout << test_fuerza_bruta << endl;

    return 0;
}