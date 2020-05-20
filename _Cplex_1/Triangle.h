#pragma once
#include <queue>
#include <set>
#include <iostream>
#include<tuple>
#include "GraphRepresentation.h"






template <typename T>struct Compare
{
public:
	bool operator() (const pair<tuple<T, T, T>, int>&  a, const pair<tuple<T, T, T>, int>& b)const
	{
		if ((a.second > b.second)||(a.second==b.second&& ((get<0>(a.first)+1)*(get<1>(a.first)+1)*(get<2>(a.first)+1) > (get<0>(b.first)+1)*(get<1>(b.first)+1)*(get<2>(b.first)+1)) ))
			return true;
		else
		{
			return false;
			
			
			
			/*if (a.second == b.second)
			{
				if (get<0>(a.first) > get<0>(b.first))
					return true;
				else
				{
					if (get<1>(a.first) > get<1>(b.first))
						return true;
					else
					{
						if (get<2>(a.first) > get<2>(b.first))
							return true;
					}
				}
			}*/

			return  false;
		}
	}
};




template <typename T>
class Triangle {
private:
	set< pair<tuple<T, T, T>, int>,   Compare<T>> t;
	GraphRepresentation<T> *graph;
	set< pair<tuple<T, T, T>, int>, Compare<T>>  naiveAlgo(GraphRepresentation<T> *graph)
	{
		set< pair<tuple<T, T, T>, int>, Compare<T>>  tmp;
		for (T x : graph->getAllVertices())
		{
			for (T y : graph->getNeighbors(x))
				for (T z : graph->getNeighbors(y))
					if (graph->hasEdge(x, z))
					{
						int degree = graph->getDegree(x) + graph->getDegree(y) + graph->getDegree(z);
						tmp.emplace(make_pair(make_tuple(x, y, z), degree));


					}

		}

		return tmp;
	}


public :

	
	Triangle(GraphRepresentation <T> *g)
	{
		graph = g;
		t = naiveAlgo(g);
	}
	
	void draw()
	{
		for (pair<tuple<T, T, T>, int> aa : t)
		{
			cout << "\n" << get<0>(aa.first) << " " << get<1>(aa.first) << "  " << get<2>(aa.first) << " con  grado :" << aa.second;
		}
	}
	


};


