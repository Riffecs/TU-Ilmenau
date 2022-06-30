#include "dfs.h"

/*****************************************************
* Definition/Implementierung der Callback-Funktionen
*****************************************************/

/* zusätzliche Variablen und Datenstrukturen */
int level;
int treecount;

/* Aktionen direkt vor DFS() */
void preDFS() {
    level = 0;
    treecount = 0;
}

/* Präorder-Aktionen an Knoten v bei Entdeckung */
void dfsVisit(const int v) {
    
    ++level;
    std::cout << v << "(";
}

/* Postorder-Aktionen an Knoten v bei Abschluss */
void finVisit(const int v) {
    --level;

    std::cout << ")";
    if(level == 0){
        std::cout << " ";
        treecount++;
    }
}

/* Aktionen direkt nach DFS() */
void postDFS() {
    std::cout << ": " << treecount << std::endl;
}
