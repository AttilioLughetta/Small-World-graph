#pragma once
#include <queue>
#include <set>
#include <iostream>
#include<tuple>
#include "GraphRepresentation.h"






template <typename T>struct Compare
{
public:
	bool operator() (const pair<set<T>, int>&  a, const pair<set<T>, int>& b)const
	{
		

		return a.first > b.first;

		
		
	}
};




template <typename T>
class Triangle {
private:
	set< pair<set<T>, int>, Compare<T>> t;
	GraphRepresentation<T> *graph;
	set<T> s;
	set< pair<set<T>, int>, Compare<T>> naiveAlgo(GraphRepresentation<T> *graph)
	{
		set< pair<set<T>, int>, Compare<T>> tmp;
		for (T x : graph->getAllVertices())
		{
			for (T y : graph->getNeighbors(x))
				for (T z : graph->getNeighbors(y))
					if (graph->hasEdge(x, z))
					{
						int degree = graph->getDegree(x) + graph->getDegree(y) + graph->getDegree(z);
						s.insert(x); 
						s.insert(y);
						s.insert(z);
						tmp.emplace(make_pair(s, degree));
						s.clear();

					}

		}

		return tmp;
	}


public:


	Triangle(GraphRepresentation <T> *g)
	{
		graph = g;
		t = naiveAlgo(g);
	}
	
	void draw()
	{
		for (pair<set<T>, int> aa : t)
		{
			cout << "\n";
			for (T bb : aa.first)
				cout << " " << bb;
			cout<< " con  grado :" << aa.second;
		}
	}


	
};


