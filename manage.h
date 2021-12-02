#ifndef MANAGE
#define MANAGE

#include <string>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
#include <fstream>
#include "card.h"
#include "stack.h"

//Random
#include <cstdlib>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
class Manage{

  private:
  void swap(int,int,std::vector<Card*> &);

  public:
  //Constructor
  Manage();

  //Getters

  //Mehtods
  std::vector<Card*> getCards();    //Return a vector of pointer of the class Card that read in the .csv
  std::string printCards(std::vector<Card*> &); //Given a vector as we returned in the previus method print all the cards contained.
  void shuffle(std::vector<Card*> &);
  void sortByCost(std::vector<Card*> &);
  void sortByName(std::vector<Card*> &);
  void sortById(std::vector<Card*> &);
  void save(std::vector<Card*> &);
  void restoreCSV();

  vector<int> ramdomCards(int);
  void bucket(vector<int>&);
  void bucketAux(vector<int>,vector<int>&);
  void swap(vector<int>&,int,int);
};

//Constructor
Manage::Manage(){}

//Getters


//Methods

std::vector<Card*> Manage::getCards(){//return the vector of pointers with all the cards
std::vector <std::string> vec;//Vector
    std::vector<Card*> cards;
  std::string line;
  std::ifstream myfile ("CardsData.csv");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      vec.clear();
      std::stringstream ss(line);
      while( ss.good() )
        {
            std::string substr;
            getline( ss, substr, ',' );
            vec.push_back( substr );
        }
     int id=std::stoi(vec[0]);
      std::string name=vec[1];
      int cost=std::stoi(vec[2]);
      std::string type=vec[3];
      std::string des=vec[4];

      Card* ptr=new Card(id,name,cost,type,des);
      cards.push_back(ptr);
    }
    myfile.close();
  }
  else {
    std::cout << "Unable to open file"; 
  }
  return cards;
}

//Print cards
std::string Manage::printCards(std::vector<Card*> &cards){
   vector<Card*>::iterator i;
    string x;
    string msg="";
    for(i = cards.begin(); i != cards.end(); ++i)
      {
      // Methos of the pointer i 
      x=(*i)->print();
      msg=msg+x;
      }
    return msg;
}


  void Manage::swap(int i, int j,std::vector<Card*> &cards) {
    Card* aux = cards[i];
    cards[i] = cards[j];
    cards[j] = aux;
  }

  void Manage::sortByCost(std::vector<Card*> &cards){
    for (int i=0;i<cards.size();i++){
    int j=i;
      while (j>0 && cards[j]->getCost()<cards[j-1]->getCost()){
        swap(j,j-1,cards);
        j=j-1;
      }
    }
  }

   void Manage::sortByName(std::vector<Card*> &cards){
    for (int i=0;i<cards.size();i++){
    int j=i;
      while (j>0 && cards[j]->getName()<cards[j-1]->getName()){
        swap(j,j-1,cards);
        j=j-1;
      }
    }
  }

  void Manage::sortById(std::vector<Card*> &cards){
    for (int i=0;i<cards.size();i++){
    int j=i;
      while (j>0 && cards[j]->getID()<cards[j-1]->getID()){
        swap(j,j-1,cards);
        j=j-1;
      }
    }
  }

   void Manage::shuffle(std::vector<Card*> &cards){
    int m=cards.size();
    for (int i=0;i<m;i++){
      swap(i,rand()%m+1,cards);
      m--;
    }
  }

  void Manage::save(std::vector<Card*> &cards){
     std::ofstream myfile;
     std::string s;
     vector<Card*>::iterator i;
      myfile.open ("CardsData.csv");
       for(i = cards.begin(); i != cards.end(); ++i)
      {
        s=std::to_string((*i)->getID())+","+(*i)->getName()+","+std::to_string((*i)->getCost())+","+(*i)->getType()+","+(*i)->getDescription()+"\n";
      myfile <<s;
      }
      myfile.close();
      std::cout<<"\nSaved\n";
  }

  void Manage::restoreCSV(){
    std::vector <std::string> vec;//Vector
    std::vector<Card*> cards;
  std::string line;
  std::ifstream myfile ("CartasOriginales.csv");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      vec.clear();
      std::stringstream ss(line);
      while( ss.good() )
        {
            std::string substr;
            getline( ss, substr, ',' );
            vec.push_back( substr );
        }
     int id=std::stoi(vec[0]);
      std::string name=vec[1];
      int cost=std::stoi(vec[2]);
      std::string type=vec[3];
      std::string des=vec[4];

      Card* ptr=new Card(id,name,cost,type,des);
      cards.push_back(ptr);
    }
    myfile.close();
  }
  else {
    std::cout << "Unable to open file"; 
  }
 save(cards);

  }

  vector<int> Manage::ramdomCards(int maxID){
    srand (time(NULL));
    vector<int> v;
    for (int i=0;i<3;i++){
       v.push_back(rand()%maxID);
    }
    while(v[1]==v[0]){
     v[1]=(rand()%maxID);
    }
    while(v[2]==v[0] || v[2]==v[1]){
      v[2]=(rand()%maxID);
    }
    return v;
    
  }

void Manage::bucket(vector<int>&vec){
  vector<int> buck[7];
  for(int j=0;j<vec.size();j++){
    int a=(int)(vec[j]/4);
    buck[a].push_back(vec[j]);
  }
  vec.clear();
  for (int i=0;i<7;i++){
    bucketAux(buck[i],vec);
  }
}

void Manage::bucketAux(vector<int> v,vector<int> &aux){
 for (int i=0;i<v.size();i++){
    int j=i;
    while (j>0 && v[j]<v[j-1]){
      swap(v,j,j-1);
      j=j-1;
    }
  }
  for (int i=0;i<v.size();i++){
    aux.push_back(v[i]);
  }
}

void Manage::swap(vector<int> &v,int a,int b){
  int aux=v[a];
  v[a]=v[b];
  v[b]=aux;
  
}
  
#endif