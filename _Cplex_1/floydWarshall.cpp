/*//
#include"floydWarshall.h"
#include "GraphRepresentation.h"
#include<limits>
using namespace std;
//typedef T;

// O(n^3)

int** unweightedFloydWarshall(GraphRepresentation<T> g)
{
	int n = g.getN();
	int i, j, k;
	int** dist = new int*[n];

	for (i = 0; i < n; i++)
		dist[i] = new int[n];

	//Putting in dist direct edge's Graph
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			if (g.hasEdge(i, j))
				dist[i][j] = 1;
			else
				dist[i][j] = std::numeric_limits<int>::max();
		}

	//Updaditing shortest paths
	for (k = 0; k < n; k++)
	{
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}

	return dist;
}
*/
/*
template< typename T > unordered_map<T, unordered_map<T, int>> unweightedFloydWarshall(GraphRepresentation<T> g)
{
	
	unordered_map<T, unordered_map<T, int>> dist;
	unordered_set <T> vertices=	g.getAllVertices();
	

	
	for (auto itr = vertices.begin(); itr != vertices.end(); ++itr)
	{
		//Putting in dist direct edge's Graph
		for (auto nei= vertices.begin(); nei != vertices.end(); ++nei)
		{
			if (g.hasEdge(itr, nei))
				
				dist.insert(itr, pair <T,int> ( nei, 1));
			else
				dist.insert(itr, pair <T, int>(nei, std::numeric_limits<int>::max()));		
		}
		
	}
	//Updaditing shortest paths
	
	for (auto k = vertices.begin(); k != vertices.end(); k++)
	{
		for (auto i = vertices.begin(); i != vertices.end(); i++)
		{
			for (auto j = vertices.begin(); j != vertices.end(); j++)
			{
				if (dist.at(i).at(k) + dist.at(k).at(j) < dist.at(i).at(j))
				{
					int tmp = dist.at(i).at(k) + dist.at(k).at(j);
					dist.insert(i, pair <T, int>(j, tmp));
				}

			}

		}
	}
	return dist;
}

*/