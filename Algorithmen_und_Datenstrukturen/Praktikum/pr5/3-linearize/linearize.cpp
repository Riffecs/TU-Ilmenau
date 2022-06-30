#include "dfs.h"

/*****************************************************
* Definition/Implementierung der Callback-Funktionen
*****************************************************/

/* zusätzliche Variablen und Datenstrukturen */
/* TODO */

/* Aktionen direkt vor DFS() */
void preDFS() {
    /* TODO */
}

/* Präorder-Aktionen an Knoten v bei Entdeckung */
void dfsVisit(const int v) {
    /* TODO */
}

/* Postorder-Aktionen an Knoten v bei Abschluss */
void finVisit(const int v) {
    /* TODO */
}

/* Aktionen direkt nach DFS() */
void postDFS() {
    
    if(B.size() == 0){
    
        std::vector<int> help;
        help.resize(n);
        for(int i = 0; i<n; i++ ){
            help[fNum[i]] = i;
        }
        for(int i = n-1; i >= 0; --i){
            std::cout << help[i];
            if(i != 0){
                std::cout << " ";
            } 
        }
    }

    else{
        std::cout << "-";
    }
    std::cout << std::endl;
}
