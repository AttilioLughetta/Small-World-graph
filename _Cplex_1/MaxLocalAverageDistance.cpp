#include"MaxLocalAverageDistance.h"
#include "GraphRepresentation.h"
#include<vector>
using namespace std;

//localAverageDistance
template <typename T>
int lad(GraphRepresentation<T> *g, T vertex)
{
	unordered_map < T<unordered_map<T, int>> a = g->getDist<T>();
	unordered_map<T, int> tmp = g.getDist(T); 
	for (auto i=tmp.begin(); i !=tmp.end(); i++)
	{
		if (i.first != vertex)
			count += i.second;
	}
	return count / (g.getN() - 1);
}

//maxLocalAvarageDistance
template <typename T>
int maxLocalAverageDistance(GraphRepresentation<T>  *g)
{
	
	int max = 0;
	int c;
	
	unordered_set<T> tmp = g.getAllVertices();
	for (auto i =tmp.begin() ; i != tmp.end(); i++)
	{
		c = lad(g, i);
		
		max = c > max ? c : max;
	}
	return max;
}