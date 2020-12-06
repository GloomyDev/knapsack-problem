#pragma once

#include <string>
#include "knapsack.h"

void partialSums(const unsigned index, Item item, const Knapsack &items, Item &solution, const unsigned max_weight)
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
    return solution.value;
}
