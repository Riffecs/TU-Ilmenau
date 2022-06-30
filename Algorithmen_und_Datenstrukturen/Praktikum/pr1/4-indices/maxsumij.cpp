#include <iostream>
#include <vector>
#include <algorithm>

struct Sum {
    int i,j,s;
};

std::ostream& operator<<(std::ostream& s, const Sum& x) {
    return s << "(" << x.i << "," << x.j << "," << x.s << ")";
}

bool operator<(const Sum& x, const Sum& y) {
    /* TODO */
}

Sum maxsum(const std::vector<int>& A) {
    Sum best {0,-1,0};
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