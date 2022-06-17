//
// Created by svale on 6/2/2022.
//

/**
 * impossible.cpp
 * Actually taken from the book "Impossible?" by Julian Havil
 */

#include "impossible.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include "../../MonteCarlo/MonteCarlo/Combinatorics.h"
#include "../../MonteCarlo/MonteCarlo/Primes.h"

using namespace std;

using VVofI = vector<vector<int>>;
using VofI = vector<int>;
using TPairSumProd = tuple<VofI, int, int, bool>;

const int sel = 3; // selection index for ub_sum
const vector<tuple<int, int>> ub_sum = { {800, 403}, // { upper bound, sum removal filter }
                                         {867, 441},
                                         {2000, 1011},
                                         {5000, 2505}};

bool select(vector<int>& v)
{
    static Primes_List primesList(3000);

    // After Statement 1, eliminate product of primes
    if (primesList.is_prime(v[0]) && primesList.is_prime(v[1]))
        return false;

    // After Statement 1, eliminate prime^3
    if (v[0] * v[0] == v[1])
        return false;

    // After Statement 2, eliminate even sums because of Goldbach Conjecture
    int sum = accumulate(v.begin(), v.end(), 0);
    if (sum % 2 == 0)
        return false;

    // After Statement 2, eliminate prime+2=sum because of 2*p=product
    int primePoss = sum - 2;
    if (primePoss > 1 && primesList.is_prime(primePoss))
        return false;

    // After Statement 2, eliminate sum >= 403 because prod might have 401 (a prime) with other factor even
    // i.e., if x=401, y must contain all other factors of prod, and Polly could determine factors
    if (sum >= get<1>(ub_sum[sel])) // 2000:1011, 867:441, 800:403
        return false;
    return true;
}

bool sum_less_than(TPairSumProd& tpsp_lh, TPairSumProd& tpsp_rh)
{
    auto [v_lh, s_lh, p_lh, b_lh] = tpsp_lh;
    auto [v_rh, s_rh, p_rh, b_rh] = tpsp_rh;

    if (s_lh < s_rh)
        return true;
    return false;
}

bool prod_less_than(TPairSumProd& tpsp_lh, TPairSumProd& tpsp_rh)
{
    auto [v_lh, s_lh, p_lh, b_lh] = tpsp_lh;
    auto [v_rh, s_rh, p_rh, b_rh] = tpsp_rh;

    if (p_lh < p_rh)
        return true;
    return false;
}

void impossible()
{
    VofI vofi;
    VVofI vvofi;
    VofI unique_sum;
    VofI unique_prod;
    vector<TPairSumProd> tpsp;

    VofI symbols(get<0>(ub_sum[sel])-1, 0); // 1999, 866, 799
    iota(begin(symbols), end(symbols), 2);

/*
    for (int s : symbols)
        cout << s << ' ';
*/
    create_combinatorial_element_set<int>(symbols, vvofi, vofi, 0, 2, select, combinations_with_repetition<int>);

    cout << "Size of Set L is = " << vvofi.size() << '\n';

/*
    for (VofI& vi : vvofi) {
        for (int i: vi)
            cout << i << ' ';
        cout << '\n';
    }
*/

    for (VofI& v : vvofi) {
        int sum = accumulate(begin(v), end(v), 0);
        int prod = accumulate(begin(v), end(v), 1, multiplies());
        tpsp.emplace_back(make_tuple(v, sum, prod, true));
    }

    sort(begin(tpsp), end(tpsp), prod_less_than);

    for (int ix = 0; ix < tpsp.size() - 1; ++ix)
    {
        if (get<2>(tpsp[ix]) == get<2>(tpsp[ix+1])) {
            get<3>(tpsp[ix]) = false;
            get<3>(tpsp[ix+1]) = false;
        }
    }

    auto tpsp_it = partition(begin(tpsp), end(tpsp), [](TPairSumProd& h)
        {
            auto [v, s, p, b] = h;
            return b;
        });

    tpsp.erase(tpsp_it, tpsp.end());

    cout << "Unique Product: length of tpsp vector is = " << tpsp.size() << '\n';


/*
    for (TPairSumProd& t : tpsp)
        if (get<2>(t) == 19'776)
            cout << "Products = " << get<2>(t) << ' ' << get<3>(t) << '\n';
*/


    sort(begin(tpsp), end(tpsp), sum_less_than);

/*
    for (TPairSumProd& t : tpsp)
        if (get<1>(t) == 373)
            cout << "{" << get<0>(t)[0] << ", " << get<0>(t)[1] << "},  Sums = " << get<1>(t) << ' ' << get<3>(t) << '\n';
*/

    for (int ix = 0; ix < tpsp.size() - 1; ++ix)
    {
        if (get<1>(tpsp[ix]) == get<1>(tpsp[ix+1])) {
            get<3>(tpsp[ix]) = false;
            get<3>(tpsp[ix+1]) = false;
        }
    }

    auto tpsp_sum_it = partition(begin(tpsp), end(tpsp), [](TPairSumProd& h)
    {
        auto [v, s, p, b] = h;
        return b;
    });

    tpsp.erase(tpsp_sum_it, tpsp.end());

    cout << "Unique Sum: length of tpsp vector is = " << tpsp.size() << '\n';

    for (TPairSumProd& t : tpsp) {
        auto [v, s, p, b] = t;

        cout << v[0] << ", " << v[1] << '\n';
    }
}