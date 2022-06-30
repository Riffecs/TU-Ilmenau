#include<iostream>
#include<vector>
#include<iterator>

template<class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
    out << '(';
    if(!v.empty()) {
        std::copy(v.begin(), v.end() - 1, std::ostream_iterator<T>(out, ","));
        out << v.back();
    }
    return out << ')';
}

const std::string EMPTY   = "",  /* kommen nie als Schlüssel vor */
                  DELETED = "-";

std::vector<std::string> table;

const int p = 16777259;
const std::vector<std::uint64_t> a = {
    5902272, 7629265, 5333771,12383661,11774175,
    9802969,12640503, 3201625,16072600, 3335533,
    5101852,    3440,13405035,12903727,13147288,
    1825828,16182670,12801869, 8007159, 2376172,
};

int linHash(const std::string& s) {
    /* TODO */
}

bool lookup(const std::string& s) {
    /* TODO */
}

const double alpha0 = 0.7,
             alpha1 = 0.8*alpha0;
int inUse = 0, load = 0;

void insert(const std::string& s) {
    /* TODO */
}

void _delete(const std::string& s) {
    /* TODO */
}

int main() {
    table.resize(2,EMPTY);
    char c; std::string s;
    while(std::cin >> c >> s) {
        /* TODO */
    }
}