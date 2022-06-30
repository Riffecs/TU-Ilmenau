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

const std::string EMPTY = "";  /* kommt nie als Schlüssel vor */

std::vector<std::string> table;

const int p = 16777259;
const std::vector<std::uint64_t> a = {
    5902272, 7629265, 5333771,12383661,11774175,
    9802969,12640503, 3201625,16072600, 3335533,
    5101852,    3440,13405035,12903727,13147288,
    1825828,16182670,12801869, 8007159, 2376172,
};

int linHash(const std::string& s) {
    int64_t temp =  0;
    for(int i = 0; i < s.size(); i++){
        temp = a[i] * s[i] + temp;
    }

    return temp % p; 
}

int main() {
    size_t size; std::cin >> size;
    /* erzeuge Tabelle der Groesse size, jeder Eintrag ist EMPTY */
    table.resize(size,EMPTY);
    char c; std::string s;
    while(std::cin >> c >> s) {
        switch (c)
        {
        case 'p':
            std::cout<<table<<std::endl;
            break;
        case 'h':
            std::cout<<"h("<<s<<") = "<<linHash(s)<<std::endl;
            break;
        default:
            std::cout<<"Unknown command"<<std::endl;
            break;
        }
    }
}