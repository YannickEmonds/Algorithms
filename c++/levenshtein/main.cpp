#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstddef>
#include <cstdint>


std::size_t recursive_levenshtein(const std::string a, const std::string b)
{
    if (a.size() == 0)
        return b.size();
    if (b.size() == 0)
        return a.size();
    if (a[0] == b[0])
        return recursive_levenshtein(a.substr(1), b.substr(1));

    const std::size_t deletion {recursive_levenshtein(a.substr(1), b)};
    const std::size_t insertion {recursive_levenshtein(a, b.substr(1))};
    const std::size_t substitution {recursive_levenshtein(a.substr(1), b.substr(1))};
    return 1 + std::min({deletion, insertion, substitution});
}


uint16_t iterative_levenshtein(const std::string a, const std::string b)
{
    const std::size_t n_rows {b.size() + 1};
    const std::size_t n_cols {a.size() + 1};
    std::vector<uint16_t> distance_matrix(n_rows * n_cols);

    for (std::size_t i=0; i<n_rows; ++i)
        distance_matrix[i * n_cols] = i;

    for (std::size_t i=0; i<n_cols; ++i)
        distance_matrix[i] = i;

    for (std::size_t j=1; j<n_rows; ++j)
    {
        for (std::size_t i=1; i<n_cols; ++i)
        {
            uint16_t substitution_cost = 1;
            if (a[i-1] == b[j-1])
                substitution_cost = 0;
            const uint16_t min = std::min({distance_matrix[j*n_cols + (i-1)] + 1,
                                          distance_matrix[(j-1)*n_cols + i] + 1,
                                          distance_matrix[(j-1)*n_cols + (i-1)] + substitution_cost});
            distance_matrix[j*n_cols + i] = min;
        }
    }

    return distance_matrix[n_rows * n_cols - 1];
}


int main(int argc, char** argv)
{

    std::cout << recursive_levenshtein(std::string("flaw"), std::string("lawn")) << '\n';
    std::cout << iterative_levenshtein(std::string("kitten"), std::string("sitting")) << '\n';
    return 0;
}
