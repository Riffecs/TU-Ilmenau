#include <iostream>
#include <vector>
#include <algorithm>

int maxsum(const std::vector<int>& A) {
    /* Schritt 0: Trivialitätstest */
    if (A.size() == 0){
        return 0;
    }
    else{
        if(A.size() ==1){
            if(A[0] <0){
                return 0;
            }
            else{
                return A[0];
            }
        }
    }

    /* Schritt 1: Teile */
    int m = A.size()/2;
    const std::vector<int> Aleft (A.begin()  , A.begin()+m);
    const std::vector<int> Aright(A.begin()+m, A.end());

    /* Schritt 2: Rekursion */
    const int r1 = maxsum(Aleft);
    const int r2 = maxsum(Aright);

    /* Schritt 3: Kombiniere */
    int best = 0;
    int sl = 0;
    int sr = 0;
    int sum = 0;
    for(int i = m; i >= 0; i--){
        sum += A[i];
        if(sum > sl){
            sl = sum;
        }
    }

    sum = 0;
    
    for(int i = m+1; i < A.size(); i++){
        sum += A[i];
        if(sum > sr){
            sr = sum;
        }
    }

    sum = sl + sr;

    return std::max(r1, std::max(r2, sum));

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