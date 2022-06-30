#include "dfs.h"

/*****************************************************
* Definition/Implementierung der Callback-Funktionen
*****************************************************/

/* zusätzliche Variablen und Datenstrukturen */
int level;
bool treeEnd;

/* Aktionen direkt vor DFS() */
void preDFS() {
    level = 0;
    treeEnd = false;
}

/* Präorder-Aktionen an Knoten v bei Entdeckung */
void dfsVisit(const int v) {
    
    if(treeEnd == false){
        if(level == 0 ){
            std::cout << v;
        }
        else{
            std::cout << " " << v;
        }
    }
    
    level++;
}
    
   

/* Postorder-Aktionen an Knoten v bei Abschluss */
void finVisit(const int v) {
    level--;
    if(level == 0){
        treeEnd = true;
    }
}

/* Aktionen direkt nach DFS() */
void postDFS() {
    std::cout << std::endl;
}
