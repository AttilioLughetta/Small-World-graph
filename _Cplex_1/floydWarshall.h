/*
#pragma once
#include "GraphRepresentation.h"
#include <unordered_map>
using namespace std;

template<typename T>  
unordered_map<T, unordered_map<T, int>> unweightedFloydWarshall <T> (GraphRepresentation <T> :: GraphRepresentation <T> g)
{
	
	unordered_map<T, unordered_map<T, int>> dist;
	unordered_set <T> vertices = g.getAllVertices();



	for (auto itr = vertices.begin(); itr != vertices.end(); ++itr)
	{
		//Putting in dist direct edge's Graph
		for (auto nei = vertices.begin(); nei != vertices.end(); ++nei)
		{
			if (g.hasEdge(itr, nei))

				dist.insert(itr, pair <T, int>(nei, 1));
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
};
*/