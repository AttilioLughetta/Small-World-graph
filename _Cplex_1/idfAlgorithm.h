#include <stdio.h>
#include <iostream>
#include "GraphT.h"
#include"MaxLocalAverageDistance.h"
#include <ilcplex/ilocplex.h>
#include"floydWarshall.h"
#include "MinimumLocalClustering.h"
#include <set>
#include "Triangless.h"
#include"priorityFunction.h"
#include <time.h>
using namespace std;


template<typename T>
unordered_set<T> idfAlgo(double alpha, double lambda, GraphRepresentation<T> *g, double & endtime, int function) {
	
	time_t start = time(NULL);

	//All triangles in g  sorted in the deacreasing order of sum of degrees
	Triangles<T> *t = new Triangles<T>(g);	unordered_set<T> best;
	while (!t->empty())
	{
		//Pick the first Triangle in T
		unordered_set<T> S1 = t->popAsSet();
		unordered_set<T> S;
		S.clear();
	
		while (S.size() < S1.size())
		{
			S = S1;
			GraphRepresentation<T> *induced = g->induction(S);
			sortedVerteces<T> *sv;
			if(function == 2)
				sv = new sortedVerteces<T>( g->getNeighborsFromVertices(S),induced, g);
			else 
				sv = new sortedVerteces<T>(g->getNeighborsFromVertices(S),  g);

			for (T v : sv->getSorted())
			{
				induced = g->inductionV(S, v);
				//induced->vertexInduction(g, v);
				double mLAD = maxLocalAverageDistance(induced);
				double mLC = minimumLocalCluster(induced);
				//induced->deleteVertex(v);
				
				if ((mLAD <= lambda) && (mLC >= alpha))
				{
					S1.insert(v);
					delete sv;
					delete induced;
					break;
				}
			}

		}

		//removing  all triangles in the currend G[S] from the set T
		GraphRepresentation<T> * h = g->induction(S);
		Triangles<T> *tr = new Triangles<T>(h);
		t->removeTriangles(tr->getTriangles());
		delete tr;
		//Updating the best
		if (S.size() > best.size())
			best = S;


	}

	endtime = difftime(time(NULL), start);

	delete t;
	return best;
}

