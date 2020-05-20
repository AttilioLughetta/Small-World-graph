/*#pragma once
#include <vector>
#include<unordered_set>
#include <iostream>
#include "GraphRepresentation.h"
using namespace std;

#define T int
template <class T>
class Graph :public GraphRepresentation<T> {
private:
	int n;        // numero di vertici
	vector<unordered_set<int>> vertex;
	bool oriented;
	const  int selfLoop = 0;
	unordered_map<T, unordered_map<T, int>> dist ;
	

public:
	Graph(int m, bool oriented);
	bool newEdge(int source, int destination);
	void randPopulate(int m);
	void draw();
	int hasEdge(T a, T b);
	int getDegree(T i);
	 unordered_set<T> getNeighbors(T i);
	 unordered_set<T> getAllVertices();
	void deleteGrapgh ();
	
	
	
};

*/