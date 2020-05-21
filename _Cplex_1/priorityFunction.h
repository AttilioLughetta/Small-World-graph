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

	bool priorityFunction(T a, T b)
	{
		if(graph->getDegree(a) > graph->getDegree(b))
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
				if (priorityFunction(verteces[i + 1], verteces[i]))
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
	sortedVerteces(unordered_set<T> vSet, GraphRepresentation<T> *g )
	{
		graph = g;
		verteces.insert(verteces.end(), vSet.begin(), vSet.end());
		sortVertices();
	}


	vector<T>getSorted()
	{
		return verteces;
	}

};