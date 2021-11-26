#include <iostream>
#include <cstring>
#include "graph.h"
#include "manage.h"

using namespace std;

int main(int argc, char* argv[]) {
    
    int num_cartas=12;
    Graph sin;//Grafo de sinergias
    sin.loadGraphList("grafo.txt", 13, 13);
    cout<<sin.printAdjList();//El grafo es correcto

    //Creamos una tienda
    Store store(num_cartas);
    cout<<store.printCards();// La mostramos

    //Cartas del jugador usuario
    vector<int> cards={4,8,9};
    cout<<"\nMis cartas 4,8,9";
    cout<<store.recomend(cards,sin);
    
}