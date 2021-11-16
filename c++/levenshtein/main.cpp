#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstddef>


std::size_t recursive_levenshtein(std::string a, std::string b)
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


std::size_t iterative_levenshtein(std::string a, std::string b)
{

}


int main(int argc, char** argv)
{

    std::cout << recursive_levenshtein(std::string("flaw"), std::string("lawn")) << '\n';
    return 0;
}
