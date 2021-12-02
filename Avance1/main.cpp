#include <iostream>
#include <cstring>
#include "graph.h"
#include "manage.h"
#include "store.h"
#include <vector>
#include "card.h"
using namespace std;

void menu(){
    cout<<"Bienvenido al recomendador de cartas de King of Tokyo."<<endl;
    cout<<"Te recomendamos que cartas comprar de acuerdo a la tienda generada. Elige una opción"<<endl<<endl;
    cout<<"1-Usar una muestra aleatoria"<<endl;
    cout<<"2-Ingresa el ID de tus cartas. Cuando hayas terminado ingresa -1"<<endl;
}

void printIndexVector(vector<int> v,vector<Card*> fullDeck){
 for (int i=0;i<v.size();i++){
        cout<<"Carta n° "+to_string(v[i]+1%fullDeck.size())+" ";//Modulo para evitar errores si el usuario ingresa numeros mayores al size
        cout<<fullDeck[v[i]%fullDeck.size()]->getName()<<endl;
    }
}

int main(int argc, char* argv[]) {
    Manage m;

    cout<<endl;
    vector<int> v={1,5,8,24,15,6,19,17,16};
    m.bucket(v);
    cout<<"Bucket"<<endl;
    for (int i=0;i<v.size();i++){
        cout<<" "+to_string(v[i]);
    }



    vector<Card*> fullDeck=m.getCards();
    int op;
    int num_cartas=24;
    vector<int> cards;
    Graph sin;//Grafo de sinergias
    sin.loadGraphList("grafo.txt", 24, 24);
    menu();
    cin>>op;
    if (op==1){
    //Creamos una tienda
    cards=m.ramdomCards(num_cartas);
    }
    else if(op==2){
        int x=1;
        cout<<"Ingresa el ID a tu carta (no mayor de "+to_string(num_cartas)<<")"<<endl;
        cout<<"Cuanda haya ingresado todas tus cartas escribe -1."<<endl;
        do{
            cin>>x;
            cards.push_back(x-1);
        }while(x>0 && x<num_cartas);
    }
    cout<<"\nMis cartas:"<<endl;
    printIndexVector(cards,fullDeck);
    cout<<endl;
    Store store(num_cartas);//Crear nueva tienda
    cout<<"En venta"<<endl;// La mostramos
    vector<int>venta=store.store2vector();
    printIndexVector(venta,fullDeck);
    cout<<endl<<"Compra recomendada:"<<endl;
    vector<int> rec=store.recomend(cards,sin);
    if(rec.size()==0){
        cout<<"No hay sinergias en el mercado";
    }
    printIndexVector(rec,fullDeck);
}