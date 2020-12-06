#pragma once

#include <string>
#include "knapsack.h"

unsigned solveBacktracking(const unsigned solution, const unsigned index, const int max_weight, const Knapsack &knapsack)
{
    if (index == knapsack.size() || max_weight == 0)
    {
        return solution;
    }
    else if (max_weight < knapsack[index].weight)
    {
        return solveBacktracking(solution, index + 1, max_weight, knapsack);
    }
    else
    {
        return std::max(
            solveBacktracking(solution + knapsack[index + 1].value, index + 1, max_weight - knapsack[index + 1].weight, knapsack),
            solveBacktracking(solution, index + 1, max_weight, knapsack)
        );
    }
}

unsigned backtracking(const unsigned max_weight, const Knapsack &knapsack)
{
    return solveBacktracking(0, 0, max_weight, knapsack);
}
