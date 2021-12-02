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
    cout<<"2-Registra tus cartas."<<endl;
    cout<<"3-Registra tus cartas y la tienda actual"<<endl;
}

void printIndexVector(vector<int> v,vector<Card*> fullDeck){
 for (int i=0;i<v.size();i++){
        cout<<"Carta n° "+to_string(v[i]+1%fullDeck.size())+" ";//Modulo para evitar errores si el usuario ingresa numeros mayores al size
        cout<<fullDeck[v[i]%fullDeck.size()]->getName()<<endl;
    }
}

int main(int argc, char* argv[]) {
    Manage m;
    vector<Card*> fullDeck=m.getCards();
    
    int op;
    int num_cartas=24;
    vector<int> cards;
    Store store(num_cartas);//Crear nueva tienda
    Graph sin;//Grafo de sinergias
    sin.loadGraphList("grafo.txt", 24, 24);
    menu();
    cin>>op;
    if (op==1){
    //Creamos una tienda
    cards=m.ramdomCards(num_cartas);
    }
    else if(op==2 || op==3){
        int x=1;
        cout<<"Ingresa el ID de tus cartas (no mayor de "+to_string(num_cartas)<<")"<<endl;
        cout<<"Cuanda haya ingresado todas tus cartas escribe -1."<<endl;
        do{
            cin>>x;
            cards.push_back(x-1);
        }while(x>0 && x<num_cartas);
    }
    if(op==3){
        int a,b,c;
        cout<<"Ingresa los 3 ID de las cartas que estan en la tienda";
        cin>>a>>b>>c;
        store.set(a-1,b-1,c-1);
    }
    if(op==1 || op==2 || op==3){
         cout<<"\nMis cartas:"<<endl;
        m.bucket(cards);
        printIndexVector(cards,fullDeck);
        cout<<endl;

        cout<<"En venta"<<endl;
        vector<int>venta=store.store2vector();
        m.bucket(venta);
        printIndexVector(venta,fullDeck);

        cout<<endl<<"Compra recomendada:"<<endl;
        vector<int> rec=store.recomend(cards,sin);
        if(rec.size()==0){
            cout<<"No hay sinergias en el mercado";
        }
        else{
        m.bucket(rec);
        printIndexVector(rec,fullDeck);
        }
    }
    else{
        cout<<"Opción no válida"<<endl;
    }
   
}