#pragma once
#pragma once
#include <queue>
#include <set>
#include <map>
#include <iostream>
#include "GraphRepresentation.h"

template<typename T>
class sortedVerteces
{
	vector<T> verteces;
	GraphRepresentation<T> *graph;
	unordered_map<T, int> degrees;


	bool priorityFunction1(T a, T b)
	{
		if(graph->getDegree(a) > graph->getDegree(b))
			return true;
		else 
		return false;
	}

	bool priorityFunction2(T a, T b)
	{
		int degA = this->degrees.at(a);
		int degB = this->degrees.at(b);
	
		
		if (degA > degB)
			return true;
		else
			return false;
	}






	void sortVertices()
	{
		int i,k;
		int N = verteces.size();
		T temp;
		//Bubble sort
		do {
			k = 0;
			for (i = 0; i < N - 1; i++)
				if (priorityFunction1(verteces[i + 1], verteces[i]))
				{
					temp = verteces[i];
					verteces[i] = verteces[i + 1];
					verteces[i + 1] = temp;
					k = 1;
				}
		} while (k == 1);
	}

	void sortVertices2()
	{
		int i, k;
		int N = verteces.size();
		T temp;
		//Bubble sort
		do {
			k = 0;
			for (i = 0; i < N - 1; i++)
				if (priorityFunction2(verteces[i + 1], verteces[i]))
				{
					temp = verteces[i];
					verteces[i] = verteces[i + 1];
					verteces[i + 1] = temp;
					k = 1;
				}
		} while (k == 1);
	}

private:
public:
	
	~sortedVerteces()
	{
		verteces.clear();
	}
	
	
	sortedVerteces(unordered_set<T> vSet, GraphRepresentation<T> *g )
	{
		graph = g;
		verteces.insert(verteces.end(), vSet.begin(), vSet.end());
		sortVertices();
	}

	sortedVerteces(unordered_set<T> vSet, GraphRepresentation<T> *induced, GraphRepresentation<T> * graph)
	{
		this->graph = induced;
		verteces.insert(verteces.end(), vSet.begin(), vSet.end());
		unordered_map <T, int> tmp;

		for (T v : verteces)
		{
			/*GraphRepresentation<T> *ga = this->graph->vertexInduction(v, graph);
			int deg = ga->getDegree(v);*/
			int deg = 0;
			for (T el : graph->getNeighbors(v))
			{
				if (induced->hasVertex(el))
					deg++;
			}

			tmp[v] = deg;

		}

		this->degrees = tmp;
		sortVertices2();
		//delete ga;
		
	}


	vector<T>getSorted()
	{
		return verteces;
	}

};