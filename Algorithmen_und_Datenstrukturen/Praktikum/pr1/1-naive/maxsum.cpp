#include <iostream>
#include <vector>
#include <algorithm>

int maxsum(const std::vector<int>& A) {
    int best = 0;
    /* TODO */
    return best;
}

int main() {
    int size;
    while(std::cin >> size) {
        std::vector<int> v(size);
        for(int& x : v) std::cin >> x;
        std::cout << maxsum(v) << std::endl;
    }
}