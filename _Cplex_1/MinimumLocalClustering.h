
#include "GraphRepresentation.h"
#include <vector>
#include <unordered_set>
using namespace std;


template< typename T > double localClusterCoefficient(GraphRepresentation <T> *g, T vertex)
{
	double count = 0;
	double nn = g->getDegree(vertex);
	unordered_set <T> n1 = g->getNeighbors(vertex);

	for (T x :n1)
	{
		unordered_set <T> n2 = g->getNeighbors(x);
		for (T y : n2)
		{
			if (g->hasEdge(y, vertex))
				count++;
		}
	}

	if (!g->isOriented())
		return  (count) / (nn*(nn - 1));
	else
		return (count) / ((nn*(nn - 1)) / 2);

}



template< typename T > double minimumLocalCluster(GraphRepresentation <T> *g)
{
	double min = 1;
	double c = 0.0;
	unordered_set<T> vertices = g->getAllVertices();

	for (T itr : vertices)
	{
		c = localClusterCoefficient<T>(g, itr);
		min = c < min ? c : min;
	}

	return min;
}
