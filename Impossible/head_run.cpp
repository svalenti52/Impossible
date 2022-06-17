//
// Created by svale on 6/9/2022.
//

#include <vector>
#include <valarray>
#include <iostream>

std::vector<double> n;

double calculate_current_value(int index)
{
    double n_minus_k_val = 0;
    if (index >= 3)
        n_minus_k_val = n[index-3];
    return n[index-1] + (1.0 - n_minus_k_val) * pow(0.5, 4);
}

void head_run()
{
     // we will do for a run of 3 first
    n = {0, 0, 0, 1.0/8}; // the first entries, including n = 3

    for (int ix = 4; ix <= 10; ++ix)
    {
        n.push_back(calculate_current_value(ix));
    }
    for (double x : n)
        std::cout << x << ' ';
}

void clear_head_run_vector()
{
    n.clear();
}
