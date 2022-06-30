#include <iostream>
#include <cassert>

int livingTrees = 0;
struct Tree {
    Tree* left;
    int key;
    Tree* right;
    Tree(Tree* l, int k, Tree* r) : left(l), key(k), right(r) {
        ++livingTrees;
    }
    ~Tree() {
        delete left; delete right;
        --livingTrees;
    }
};

std::ostream& operator<<(std::ostream& out, const Tree* T) {
    if (!T)
        return out << "-";
    else
        return out << "(" << T->left << "," << T->key << "," << T->right << ")";
}

bool lookup(const Tree* T, const int key) {
    /*
     * Verwendung:
     * Tree* T = new Tree{nullptr,2,nullptr}; // T == (-,2,-)
     * bool b = lookup(T, 4); // T == (-,2,-), b == false
     */
    
    if(T==nullptr){
        return false;
    }

    if(T->key==key){
        return true;
    }

    if(T->key > key){
        bool b = lookup(T->left, key);
        return b;
    }

    if(T->key < key){
        bool b = lookup(T->right, key);
        return b;
    }

    return false;

}

Tree* insert(Tree* T, const int key) {
    /*
     * Verwendung:
     * Tree* T = nullptr; // T == -
     * T = insert(T, 2);  // T == (-,2,-)
     * T = insert(T, 4);  // T == (-,2,(-,4,-))
     */
    if(T==nullptr){
        Tree* T = new Tree{nullptr,key,nullptr};
        return T;
    }

    if(T->key == key){
        return T;
    }

    if(T->key > key){
        T->left = insert(T->left, key);
        return T;
    }

    if(T->key < key){
        T->right = insert(T->right, key);
        return T;
    }

    return nullptr;
}

Tree* extractMin(Tree* T, int& minKey) {
    /*
     * Verwendung:
     * Tree* T = new Tree{nullptr,2,new Tree{nullptr,4,nullptr}}; // T == (-,2,(-,4,-))
     * int k; // k == undefiniert
     * T = extractMin(T, k); // T == (-,4,-), k == 2
     */
    if(T->left == nullptr){
    minKey = T->key;
    Tree* temp = T->right;
    T->right = nullptr;
    delete T;
    return temp; 
    }

    if(T->left != nullptr){

    T->left = extractMin(T->left, minKey);
    return T;
    }

    return nullptr;
}

Tree* erase(Tree* T, const int key) {
    /*
     * Verwendung:
     * Tree* T = new Tree{nullptr,2,new Tree{nullptr,4,nullptr}}; // T == (-,2,(-,4,-))
     * T = erase(T, 4); // T == (-,2,-)
     */
    if(T == nullptr){
        return T;
    }

    if(T->key < key){
        T->right = erase(T->right, key);
        return T;
    }

    if(T->key > key){
        T->left = erase(T->left, key);
        return T; 


    }

    if(T->key == key){
        if(T->right == nullptr && T->left == nullptr){
            delete T;
            return nullptr;
        }

        if(T->left == nullptr && T->right != nullptr){
            Tree* temp = T->right;
            T->right = nullptr;
            delete T;
            return temp;
        }

        if(T->right == nullptr && T->left != nullptr){
            Tree* temp = T->left;
            T->left = nullptr;
            delete T;
            return temp;
        }

        if(T->right != nullptr && T->left != nullptr){
            int r = 0;
            T->right = extractMin(T->right, r);
            T->key = r;
            return T; 
        }



    }

    return T;
}

int main() {
    char c; int key;
    Tree* T = nullptr;
    bool d = true; 

    while(std::cin >> c >> key) {
        
        if(c=='l'){
            bool b = lookup(T, key);
            std::cout << b << std::endl;
        }

        if(c=='i'){
            T = insert(T, key);
            if(d){ std::cout << T << std::endl; }
        }

        if(c == 'e'){
            T = extractMin(T, key);
            if(d){ std::cout << T << std::endl; }
        }
        if(c == 'd'){
            T = erase(T, key);
            if(d){ std::cout << T << std::endl; }
        }
        if(c == 'p'){
            if(key == 0){
            d = false;
            }
            if(key != 0){
            d = true;
            }
        }
    }
    delete T; T = nullptr;
    assert(livingTrees == 0);
}