/*
#include "GraphRepresentation.h"
#include<vector>

//localAverageDistance
template <typename T>
double lad(GraphRepresentation<T> *g, T vertex)
{
	int count = 0;
	unordered_map<T, int> tmp = (g->getDist<T>()).at(vertex);
	for (pair <T, int> i : tmp)
	{
		if (i.first != vertex)
			count = count + i.second;


	}
	return count / (g->getN() - 1);
}

//maxLocalAvarageDistance
template <typename T>
double maxLocalAverageDistance(GraphRepresentation<T> *g)
{

	double max = 0;
	double c;
	unordered_set<T> tmp = g->getAllVertices();
	for (T i : tmp)
	{
		c = lad<T>(g, i);
		max = c > max ? c : max;
	}
	return max;
}*/