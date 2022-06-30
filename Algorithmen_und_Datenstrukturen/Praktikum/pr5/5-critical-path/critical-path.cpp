#include "dfs.h"

/*****************************************************
* Definition/Implementierung der Callback-Funktionen
*****************************************************/

/* zusätzliche Variablen und Datenstrukturen */
std::vector<int> critical;
int start;

/* Aktionen direkt vor DFS() */
void preDFS() {
    critical.resize(n);
    start = -1;
}

/* Präorder-Aktionen an Knoten v bei Entdeckung */
void dfsVisit(const int v) {
    /* TODO */
}

/* Postorder-Aktionen an Knoten v bei Abschluss */
void finVisit(const int v) {
    if(G[v].size() == 0){
        critical[v] = 1;
    }
    else{
        int temp = 0;
        for(int i = 0; i<G[v].size(); i++ ){
            if (critical[G[v][i]] > temp){
                temp = critical[G[v][i]];
            }

            
        }
        critical[v] = temp + 1;
        
    }
    if(start != -1){
        if(critical[v] > critical[start]){
            start = v;
        }
    }
    else{
        start = v;
    }
}

/* Aktionen direkt nach DFS() */
void postDFS() {
    if(B.size() == 0){
        int temp = start;
        std::cout << critical[temp] << ":";
        while(critical[temp] > 1){
            std::cout << " " << temp;
            for (int i = 0; i < G[temp].size(); i++){
                if(critical[temp]-1 == critical[G[temp][i]]){
                    temp = G[temp][i];
                    break;
                }
            }
            
        }
        std::cout << " " << temp;
    }
    else{
        std::cout << "-";
    }
    std::cout << std::endl;
}
