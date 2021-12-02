//estructura lineal para acceder al deck. Con esto podemos estar tomando la carta superior.


#ifndef STACK
#define STACK

#include <string>
#include <sstream>
#include <vector>
#include "card.h"
using namespace std;

template <class T> class Stack;

template <class T>
class Link {
private:
	Link(T);
	Link(T, Link<T>*);
	Link(const Link<T>&);

	T	    value;
	Link<T> *next;

	friend class Stack<T>;
};

/***Funciones Link***/

//Constructores
template <class T>
Link<T>::Link(T val) : value(val), next(0) {}

template <class T>
Link<T>::Link(T val, Link* nxt) : value(val), next(nxt) {}

template <class T>
Link<T>::Link(const Link<T> &source) : value(source.value), next(source.next) {}



/**Inicio clase Stack**/

template <class T>

class Stack {

public:

    Stack();
    Stack(vector<T*>&);
	~Stack();

	string toString() const;

	void add(T);
	T pop();
	//Nueva
	string vaciar();
	bool empty();
private:

    Link<T> *head;
    int size;

};

/**Constructores**/

template <class T>
Stack<T>::Stack() : head(0), size(0) {}

template <class T>
Stack<T>::Stack(vector<T*> &source){
	head=0;
  size=0;
  for (int i = 0; i < source.size(); i++){
	  T val=*source[i];
    add(val);
    }	
	
}


template <class T>
Stack<T>::~Stack() {
	Link<T> *p, *q;
	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	size = 0;
}


template <class T>
string Stack<T>::toString() const {
	stringstream aux;
	Link<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		//aux << "p->value";
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
void Stack<T>::add(T val){
	Link<T>* p;
	p=new Link<T>(val,head);
	head=p;
	size++;
}

template <class T>
T Stack<T>::pop(){
	Link<T>* p=head;
	head=head->next;
	size--;
	return p->value;
}

template<class T>
string Stack<T>::vaciar(){
	if (size<=0){
		return "Este stack no tiene elementos";
	}
	string s="";
	while(size>0){
		s=s+pop().print();
	}
	return s;
}
template<class T>
bool Stack<T>::empty(){
	return size==0;
}
#endif