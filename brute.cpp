#include <string>
#include "knapsack.h"

void partialSums(const unsigned index, Item item, const Knapsack &items, Item &solution, const unsigned &max_weight)
{
    if (index == items.size())
    {
        if (item.weight <= max_weight && item.value > solution.value)
        {
            solution = item;
        }
    }
    else
    {
        partialSums(index + 1, item, items, solution, max_weight);
        item += items[index];
        partialSums(index + 1, item, items, solution, max_weight);
    }
}

unsigned brute_force(const unsigned max_weight, const Knapsack &knapsack)
{
    Item item {0,0};
    Item solution {0,0};
    partialSums(0, item, knapsack, solution, max_weight);
    const unsigned benefit = solution.value;
    return benefit;
}

int main(int argc, char *argv[])
{
    if (argc < 2) return 1;

    const std::string file = argv[1];

    Knapsack items = getKnapsackFromFile(file);
    const unsigned max_weight = items[0].value;
    items.erase(items.begin());
    items.erase(items.end() - 1);

    const unsigned solution = brute_force(max_weight, items);
    const auto averageTime = benchmarkKnapsackAlgorithm(brute_force, items, max_weight, 20);
    printResultsToFile("bruteforce", items.size(), max_weight, solution, 20, averageTime);
    return 0;
}
