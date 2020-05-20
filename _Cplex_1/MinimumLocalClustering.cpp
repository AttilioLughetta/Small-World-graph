#include "GraphRepresentation.h"
#include <vector>
#include <unordered_set>
using namespace std;


template< typename T > double localClusterCoefficient(GraphRepresentation <T> g, T vertex)
{
	int count = 0;
	int nn = g.getDegree(vertex);
	unordered_set <T> n1 = g.getNeighbors(vertex);
	
	for (auto x = n1.begin(); x != n1.end(); ++x)
	{
		unordered_set <T> n2 = g.getNeighbors(n1);
		for (auto y = n2.begin(); y != n2.end(); ++y)
		{
				if (g.hasEdge(y,vertex))
					count ++;
		}
	}

	if (!g.isOriented())
		return  (count) / (nn*(nn - 1));
	else
		return (count) / ((nn*(nn - 1)) / 2);

}



template< typename T > double TminimumLocalCluster(GraphRepresentation <T> g, unordered_set<T> vertices)
{
	double min = 1;
	double c = 0;
	for (auto itr = vertices.begin(); itr != vertices.end(); ++itr) 
		{
			c= localClusterCoefficient(g, itr);
			min = c < min ? c : min;
		}
}
