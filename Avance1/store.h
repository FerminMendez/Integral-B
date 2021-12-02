#ifndef STORE
#define STORE


#include <string>
#include <iostream>
#include "graph.h"
//Random
#include <cstdlib>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class Store{
  private:
  int sell[3];
  public:
  Store(int);
  string printCards();
  vector<int> recomend(vector<int>,Graph);
  vector<int> store2vector();
};

Store::Store(int n){
    srand (time(NULL));
    int store[3]={-1,-1,-1};
    store[0]=(rand()*7%n);
    while(store[1]==store[0] || store[1]==-1){
        store[1]=(rand()*7%n);
    }
    while(store[2]==store[0] || store[2]==store[1] ||store[2]==-1){
        store[2]=(rand()*7%n);
    }
    sell[0]=store[0];
    sell[1]=store[1];
    sell[2]=store[2];
}

string Store::printCards(){
    return "\nEn venta: "+to_string(*(sell))+" "+to_string(*(sell+1))+" "+to_string(*(sell+2));
}

vector<int> Store::recomend(vector<int> v,Graph g){
    vector<int> s;
    int start;
    for(int i=0;i<3;i++){
        start=sell[i];
        if(g.BFS2(start,v)){
            s.push_back(sell[i]);
        }
    }
    return s;
}

vector<int> Store::store2vector(){
    vector<int> r;
    r.push_back(sell[0]);
    r.push_back(sell[1]);
    r.push_back(sell[2]);
    return r;
}


#endif 
