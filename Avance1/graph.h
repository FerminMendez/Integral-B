/*
Grafos para recomendar cartas
*/

#ifndef Graph_H_
#define Graph_H_

#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>    // std::sort

using namespace std;


class Graph {
private:
		int edgesList;
		int nodes;
    	vector<int> *adjList;
public:
		//En proceso
		void loadGraphList(string,int,int);
		Graph(int);
		Graph();
		void addEdgeAdjList(int, int);//Auxiliar
		string printAdjList();//Imprimer la lista de adjacencia
		//Funciones de recorrido
		bool contains(list<int>, int);
		string print_path(vector<vector <int>>&,int,int);
		string print_visited(list<int>);

		string BFS(int,int);// Con queue
		void BFSaux(int,int,queue<int>&,list<int>&,vector<vector<int>>&);

        bool BFS2(int,vector<int>);
        bool invec(int ,vector<int>);
};

bool Graph::contains(list<int> ls, int node){//Verifica si el nodo está en visitados
		list<int>::iterator it;
		it = find(ls.begin(), ls.end(), node);
		if(it != ls.end()){
			return true;
		}
		else{
			return false;
		}
}

string Graph::print_visited(list<int> q){
	string s;
	s=s+"visited: ";
	while (!q.empty()){
    s=s+to_string(q.front())+ " ";
    q.pop_front();
	}
	return s;
}


string Graph::print_path(vector<vector <int>> &path, int start, int goal){
	stringstream s;
	int node =  path[goal][0];
	stack<int> reverse;
	reverse.push(goal);
	while (node != start) {
		reverse.push(node);
    node = path[node][0];
  }
	reverse.push(start);
	while (!reverse.empty()) {
		if(s.tellp() != 0){
			s<<" ";
		}
		s<<to_string(reverse.top());
		reverse.pop();
  }
  return "path: "+s.str();
}


string Graph::BFS(int a,int b){
	string s;
	queue<int> q;
	list<int> visited;
	vector <vector<int>> paths(nodes, vector<int>(0));
	q.push(a);
	BFSaux(a, b, q, visited, paths);
	s=print_visited(visited)+print_path(paths,a,b);
	return s;
}

void Graph::BFSaux(int current,int goal,queue<int> &q,list<int> &visited,vector<vector<int>> &paths){//
	if(current == goal){
	} else if(q.empty()){
		cout << "Nodo no encontrado";
	}	
	else {//Si no hemos llegado a la meta, sacamos el top, metemos los hijos
		current = q.front();
		q.pop();
		visited.push_back(current);
		for(int  i = 0; i < adjList[current].size(); i++){
			//Metemos los hijos de la lista de adyacencia
			if(!contains(visited, adjList[current][i])){//Siempre y cuando no se hayan visitado ya
				q.push(adjList[current][i]);
				paths[adjList[current][i]].push_back(current);
			}
		}
		BFSaux(current, goal, q, visited, paths);
	}
}

//Primera función de tarea. Cargar la matriz de adyacencia desde el .txt

void Graph::loadGraphList(string fileName, int numNodes, int maxArcos){//Tenemos que editar *adjList a los nodos actualizados
	nodes=numNodes;//Actualizamos cuantos nodos tenemos
	adjList=new vector<int>[numNodes];//Crea un vector por cada nodo que tiene. Donde puede meter los arcos de cada uno ¿¿¿¿¿?????

	string line;
		ifstream lee (fileName);
		int u, v;
		if (lee.is_open()){
			while (getline(lee, line)){
				u = stoi(line.substr(1,1))*10+stoi(line.substr(2,1))-1;
				v = stoi(line.substr(5,1))*10+stoi(line.substr(6,1))-1;//Menos uno porque el ID se lee desde el 1
				addEdgeAdjList(u,v);
			}
			lee.close(); // Closes the file
		} else {
			cout << "Unable to open file";
		}
	for(int i=0;i<nodes;i++){//Falta ordenar uno
		sort(adjList[i].begin(),adjList[i].end());
	}

}

Graph::Graph() {
	nodes = edgesList = 0;
}

Graph::Graph(int n) {
	nodes = n;
	adjList = new vector<int>[nodes];
	edgesList = 0;
}



//Auxiliar para agregar arcos 
void Graph::addEdgeAdjList(int u, int v){
	adjList[u].push_back(v);
	adjList[v].push_back(u);
	edgesList++;
}

string Graph::printAdjList(){
	  stringstream aux;
		for (int i = 0; i < nodes; i++){
	        aux << "vertex "
	             << i << " :";
	        for (int j = 0; j < adjList[i].size(); j ++){
							 aux << " " << adjList[i][j];
					}
	        aux << " ";
    }
		return aux.str();
}




 
bool Graph::BFS2(int start, vector<int> v){
    queue<int> lev1;
    queue<int> lev2;
	list<int> visited;
    int current=start;
	visited.push_back(current);
		for(int  i = 0; i < adjList[current].size(); i++){
			//Metemos los hijos de la lista de adyacencia
			if(!contains(visited, adjList[current][i])){//Siempre y cuando no se hayan visitado ya
				lev1.push(adjList[current][i]);
			}
		}
    while(!lev1.empty()){
        current=lev1.front();
        lev1.pop();
        visited.push_back(current);
        if(invec(current,v)){
            return true;
        }
        for(int  i = 0; i < adjList[current].size(); i++){
			//Metemos los hijos de la lista de adyacencia
			if(!contains(visited, adjList[current][i])){//Siempre y cuando no se hayan visitado ya
				lev2.push(adjList[current][i]);
			}
		}
    }
    while(!lev2.empty()){
        current=lev2.front();
        lev2.pop();
        visited.push_back(current);
        if(invec(current,v)){
            return true;
        }
    }
    return false;
}

bool Graph::invec(int current,vector<int> v){
    vector<int>::iterator ptr;
     for(ptr=v.begin(); ptr < v.end(); ptr++){
        if(*ptr==current){
            return true;
        }
    }
    return false;
}

#endif /* Graph_H_ */
