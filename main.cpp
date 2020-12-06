#include <string>
#include <thread>

#include "back.hpp"
#include "brute.hpp"
#include "dynamic.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2) return 1;

    const std::string file = argv[1];

    Knapsack items = getKnapsackFromFile(file);
    const unsigned max_weight = items[0].value;
    items.erase(items.begin());
    items.erase(items.end() - 1);

    std::thread dynamic_thread = std::thread([&](){
        const unsigned solution = dynamic(max_weight, items);
        const auto averageTime = benchmarkKnapsackAlgorithm(dynamic, items, max_weight, 50);
        printResultsToFile("dynamic", items.size(), max_weight, solution, 50, averageTime);
    });

    std::thread backtracking_thread = std::thread([&](){
        const unsigned solution = backtracking(max_weight, items);
        const auto averageTime = benchmarkKnapsackAlgorithm(backtracking, items, max_weight, 50);
        printResultsToFile("backtracking", items.size(), max_weight, solution, 50, averageTime);
    });

    std::thread brute_force_thread = std::thread([&](){
        const unsigned solution = brute_force(max_weight, items);
        const auto averageTime = benchmarkKnapsackAlgorithm(brute_force, items, max_weight, 50);
        printResultsToFile("brute_force", items.size(), max_weight, solution, 50, averageTime);
    });

    dynamic_thread.join();
    backtracking_thread.join();
    brute_force_thread.join();
    return 0;
}
