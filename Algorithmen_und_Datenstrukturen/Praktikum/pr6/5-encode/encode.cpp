#include "encode.h"

/*
 * Die nachfolgenden Variablen/Datenstrukturen könnten für Sie nützlich sein.
 * - "n" ist die Anzahl unterschiedlicher ASCII-Zeichen in der Eingabe.
 *   Für 0 <= i < n ist "label[i]" das i-te tatsächlich vorkommende ASCII-
 *   Zeichen. Dieses kommt "p[i]" mal in der Eingabe vor.
 *   Die tatsächlich vorkommenden ASCII-Zeichen sind dabei wie gewünscht
 *   angeordnet:
 *     p[0] <= p[1] <= p[2] <= ... <= p[n-1]
 *   und
 *     wenn p[i] = p[i+1], dann label[i] < label[i+1].
 * - "labelIndex" ist die Umkehrung von "label", d.h. für ein in der Eingabe
 *   vorkommendes ASCII-Zeichen c gilt "label[labelIndex[c]] == c" und es kommt
 *   "p[labelIndex[c]]" mal in der Eingabe vor.
 * - "pred" und "mark" sind die Ausgaben des Huffman-Algorithmus.
 *   Sie enthalten "nodes" viele Einträge - die Anzahl Knoten des zugehörigen
 *   optimalen Codierungsbaums.
 */
// Folgendes können Sie mittels "input.countChars(n, labelIndex, label, p)"
// bestimmen lassen:
unsigned int n;                     // Anzahl verschiedener ASCII-Zeichen in der Eingabe = Anzahl Blätter
std::vector<int> labelIndex;        // labelIndex[c] = Index des Blattes mit Beschriftung (ASCII-Zeichen) c
std::vector<char> label;            // label[i] = Beschriftung (ASCII-Zeichen) des Blattes mit Index i
std::vector<unsigned int> p;        // p[i] = absolute Häufigkeiten (>0) des ASCII-Zeichens des Blattes mit Index i
// Folgendes müssen Sie manuell bestimmen:
unsigned int nodes;                 // Anzahl Knoten (des Huffman-Baums)
std::vector<unsigned int> pred;     // Vorgänger-Array
std::vector<bool> mark;             // Markierungs-Array: false = 0 = links, true = 1 = rechts

/*
 * Implementieren Sie den Algorithmus von Huffman aus der Vorlesung.
 * 
 * Verwenden Sie n, labelIndex, label und p als (global gegebene) Eingabe.
 * Bestimmen Sie nodes, pred und mark als (global verfügbare) Ausgabe.
 * 
 * Hinweise:
 * - Achten Sie darauf, dass die Indizierung in C++ bei 0 beginnt,
 *   in den Vorlesungsfolien hingegen bei 1.
 * - Vergessen Sie nicht, die Größe von p (mittels "p.resize(nodes)",
 *    wenn Sie "nodes" zuvor passend bestimmt haben) anzupassen,
 *    damit Sie die Häufigkeiten der Kunstbuchstaben zwischenspeichern können.
 * - Wenn Sie die Häufigkeiten in p mittels input.countChars(...) bestimmt haben
 *   und sich treu an den Pseudocode aus der Vorlesung halten, erreichen Sie das
 *   folgende erwünschte Verhalten automatisch:
 *     Immer dann, wenn (Kunst-)Buchstaben die gleiche Häufigkeit haben, soll
 *     zunächst derjenige (Kunst-)Buchstabe mit kleinstem Index gewählt werden,
 *     d.h., der in den Tabellen p/pred/mark am weitesten vorne/links steht.
 */
void huffman() {
    int i;
    int j;

    p.resize(2*n - 1);
    pred.resize(2*n -2);
    mark.resize(2*n -2);
    pred[0] = n;
    pred[1] = n;
    mark[0] = 0;
    mark[1] = 1;
    p[n] = p[0] + p[1];
    int k = 2;
    int h = n; 

    for(int b = n+1; b < 2*n-1; b++){
        if(k< n && p[k]<= p[h]){
            i = k;
            k++;
        }
        else{
            i = h;
            h++;
        }
        if(k<n && (h==b || p[k]<= p[h])){
            j = k;
            k++;
        }
        else{
            j = h;
            h++;
        }
        pred[i] = b;
        pred[j] = b;
        mark[i] = 0;
        mark[j] = 1; 
        p[b] = p[i] + p[j];
    }

}

/*
 * Um den Codierungsbaum ausgeben zu können, muss dieser zunächst mehr oder
 * weniger konkret berechnet werden. Eine Möglichkeit ist die Berechnung der
 * aus der Vorlesung bekannten Arrays "leaf" und "inner".
 * Auf ähnliche Weise kann man sich auch einen Baum wie bei der Decodierung
 * berechnen, indem man mit "nodes" vielen "leeren Knoten" startet
 *   vector<Tree*> treeNodes(nodes, nullptr);
 * anschließend die Blätter mit passenden Beschriftungen an Positionen 0 bis
 * n-1 und innere Knoten an Positionen n bis nodes-1 erzeugt und schließlich
 * "mark" und "pred" nutzt, um die Zeiger von Vater- zu Kindknoten zu ergänzen.
 * treeNodes[nodes-1] ist dann ein Zeiger auf die Wurzel des Codierungsbaums.
 */
Tree* computeTree() { // iterativ
std::vector<Tree*>leaf;

    leaf.resize(2*n-1);

    for(int i = 0; i < leaf.size(); i++){
        leaf[i] = new Tree(nullptr, '-', nullptr);
    }


    for(int i = 0; i < n; i++){
        leaf[i]->letter= label[i];
        if(mark[i] == 0 ){
            leaf[pred[i]]->left = leaf[i];
        }
        else{
            leaf[pred[i]]->right = leaf[i];
        }

    }
    for(int i = n; i < 2*n-2; i++){
        if(mark[i] == 0 ){
            leaf[pred[i]]->left = leaf[i];
        }
        else{
            leaf[pred[i]]->right = leaf[i];
        }
    }

    return leaf[2*n-2];
    
    }

/*
 * Nutzen Sie "output << b" (für "bool b") und "output << c" (für "char c"),
 * um den Baum, auf dessen Wurzel der Zeiger "codingTree" zeigt, in Präorder-
 * Reihenfolge gemäß der vereinbarten Codierung auszugeben.
 * Ein rekursiver Ansatz ist besonders einfach.
 */
void writeTree(Tree* codingTree) { // rekursiv
    if(codingTree-> left && codingTree -> right){
        output << false;
        writeTree(codingTree -> left);
        writeTree(codingTree -> right);
    }
    else{
        output << true;
        output << codingTree -> letter;
    }
    
}

/*
 * Nutzen Sie "mark", "pred" und "output << b" (für "bool b") zum Codieren von
 * Zeichen. Wenn Sie das ASCII-Zeichen "label[3]" codiert ausgeben wollen, soll
 * dies über
 *   encodeChar(3);
 * geschehen. Der "index" gibt dann bei einem rekursiven Ansatz die aktuell
 * betrachtete Position in "mark" und "pred" an.
 * "nodes - 1" ist der Index der Wurzel des Codierungsbaums.
 */
void encodeChar(unsigned int index) { // rekursiv
    if(index != n*2-2){
        encodeChar(pred[index]);
        output << mark[index];
    }
}

/*
 * Nutzen Sie "encodeChar" wiederholt, um die gesamte Eingabe zu codieren.
 * Falls "if(input)" zutrifft, gibt es noch ein weiteres zu codierendes ASCII-
 * Zeichen in der Eingabe, das Sie mittels "input >> c" (für "char c") erhalten.
 * (Sie können auch eine Formulierung mit "while(input >> c)" verwenden.)
 * Der Index dieses ASCII-Zeichens, d.h. die Position in
 * "p"/"label"/"pred"/"mark", den Sie mittels "labelIndex" ermitteln können,
 * ist dann Eingabe von "encodeChar".
 */
void encodeText() {
    char c;
    while(input >> c){
        for( int i = 0; i < label.size(); i++){
            if(label[i]==c){
                encodeChar(i);
                break;
            }
        }
    }
}

/*
 * Diese Methode ist der Startpunkt für Ihre Implementierung. Lesen Sie den
 * "ASCIIStream input" Stück für Stück aus und erzeugen Sie währenddessen die
 * in der Aufgabenstellung beschriebene gewünschte Ausgabe.
 * 
 * Verwenden Sie dazu "input.countChars(...)" und Ihre Implementierungen von
 * "huffman()", "computeTree()", "writeTree(...)" und "encodeText()".
 */
void run() {
    // zähle ASCII-Zeichen, berechne "n", "labelIndex", "label", "p"
    input.countChars(n, labelIndex, label, p);
    // berechne "nodes", pred", "mark" (Huffman-Algorithmus)
    huffman();
    // berechne Codierungsbaum (als Tree*) und gib diesen aus
    Tree* codingTree = computeTree();
    writeTree(codingTree);
    delete codingTree; codingTree = nullptr;
    // gib die Eingabe codiert aus
    encodeText();
    std::cout << std::endl;
}