#include "dfs.h"

/*****************************************************
* Definition/Implementierung der Callback-Funktionen
*****************************************************/

/* zusätzliche Variablen und Datenstrukturen */
std::vector<int64_t> rout;

/* Aktionen direkt vor DFS() */
void preDFS() {
    rout.resize(n);
}

/* Präorder-Aktionen an Knoten v bei Entdeckung */
void dfsVisit(const int v) {
    /* TODO */
}

/* Postorder-Aktionen an Knoten v bei Abschluss */
void finVisit(const int v) {
    if(v == n-1){
        rout[v] = 1;
    }
    else{
        int64_t count = 0;
        for(int i=0; i < G[v].size(); i++){
            count = count + rout[G[v][i]];
        }
        rout[v] = count;
    }
}

/* Aktionen direkt nach DFS() */
void postDFS() {
    if(B.size() == 0){
        std::cout << rout[0];
    }
    else{
        std::cout << "-";
        }
    std::cout << std::endl;
}
