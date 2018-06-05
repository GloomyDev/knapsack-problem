#define Item pair<int, int>
#define Knapsack vector<Item>
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

    // Benchmark Fuerza Bruta
    // srand (time(NULL));
    // cout << "steady_clock" << endl;
    // cout << chrono::steady_clock::period::num << endl;
    // cout << chrono::steady_clock::period::den << endl;
    // cout << "steady = " << boolalpha << chrono::steady_clock::is_steady << endl << endl;
    // cout << "*************************" << endl;

    ofstream file;
    string bruteTest = "bruteforce.csv";
    file.open(bruteTest, fstream::out);
    // file << "bruteforce;items;max weight;profit;time;" << endl;
    auto start_fuerza_bruta = chrono::steady_clock::now();
    unsigned int test_fuerza_bruta = fuerza_bruta(max_weight, items);
    auto end_fuerza_bruta = chrono::steady_clock::now();
    auto diff_fuerza_bruta = end_fuerza_bruta - start_fuerza_bruta;
    auto averageTime = diff_fuerza_bruta;
    for (int i = 1; i <= 20 - 1; i++) {
        start_fuerza_bruta = chrono::steady_clock::now();
        test_fuerza_bruta = fuerza_bruta(max_weight, items);
        end_fuerza_bruta = chrono::steady_clock::now();
        diff_fuerza_bruta = end_fuerza_bruta - start_fuerza_bruta;
        averageTime += diff_fuerza_bruta;
    }
    // cout << "Tiempo utilizado por Brute Force " << chrono::duration <double, milli> (diff_fuerza_bruta).count() << " ms." << " Profit: " << test_fuerza_bruta << endl;
    file << "bruteforce;" << items.size() << ";" << max_weight << ";" << test_fuerza_bruta << ";" << std::fixed << chrono::duration <double, milli> (averageTime).count() / 20 << ";" << endl;
    file.close();
    return 0;
}