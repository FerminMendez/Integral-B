#ifndef MANAGE
#define MANAGE


#include <string>
#include <iostream>
#include "graph.h"
//Random
#include <cstdlib>

class Store{
  private:
  int sell[3];
  public:
  Store(int);
  string printCards();
  string recomend(vector<int>,Graph);
};

Store::Store(int n){
    int store[3]={-1,-1,-1};
    store[0]=(rand()%n);
    while(store[1]==store[0] || store[1]==-1){
        store[1]=(rand()%n);
    }
    while(store[2]==store[0] || store[2]==store[1] ||store[2]==-1){
        store[2]=(rand()%n);
    }
    sell[0]=store[0];
    sell[1]=store[1];
    sell[2]=store[2];
}

string Store::printCards(){
    return "\nEn venta: "+to_string(*(sell))+" "+to_string(*(sell+1))+" "+to_string(*(sell+2));
}

string Store::recomend(vector<int> v,Graph g){
    string s;
    int start;
    for(int i=0;i<3;i++){
        start=sell[i];
        if(g.BFS2(start,v)){
            s=s+to_string(sell[i])+" ";
        }
    }
    return "\nRecomendación de compra: "+s;
}



#endif 
