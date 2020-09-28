#pragma once
#include <queue>
#include <set>
#include <map>
#include <iostream>
#include "GraphRepresentation.h"
#include "priorityFunction.h"

template< typename T > unordered_set <T> oneFilp(unordered_set<T> currentSolution, GraphRepresentation<T> *g,double alpha,double lambda,int priorityFunction, bool bestImprovement)
{
	unordered_set<T> best = currentSolution;

	for (T component : currentSolution)
	{
		unordered_set<T> adjacentSolution = currentSolution;
		adjacentSolution.erase(component);
		adjacentSolution = solutionReconstruction(adjacentSolution, g, alpha, lambda, priorityFunction,component);

		if (adjacentSolution.size() > best.size())
		{
			best = adjacentSolution;
			adjacentSolution.clear();
			if (!bestImprovement)
				return best;


		}
		 adjacentSolution.clear();
	}
	
	return best;

}



/*
template< typename T > unordered_set <T> solutionReconstruction(unordered_set<T> S1, GraphRepresentation<T> *g, double alpha, double lambda, int priorityFunction)
{

	unordered_set <T> S;
	while (S.size() < S1.size())
	{
		S = S1;
		GraphRepresentation<T> *induced = g->induction(S);
		sortedVerteces<T> *sv;
		if (priorityFunction == 2)
			sv = new sortedVerteces<T>(g->getNeighborsFromVertices(S), induced, g);
		else
			sv = new sortedVerteces<T>(g->getNeighborsFromVertices(S), g);

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
				break;
			}
		}
		delete sv;
		delete induced;
		

	}
	
	 S.clear();
	return S1;
}*/



template< typename T > unordered_set <T> solutionReconstruction(unordered_set<T> S1, GraphRepresentation<T> *g, double alpha, double lambda, int priorityFunction, T toEsxclude)
{

	bool addable = false;
	unordered_set <T> S;
	while (S.size() < S1.size())
	{
		S = S1;
		GraphRepresentation<T> *induced = g->induction(S);
		sortedVerteces<T> *sv;
		unordered_set<T> ver = g->getNeighborsFromVertices(S);
		
		if (!addable)
			ver.erase(toEsxclude);
		
		if (priorityFunction == 2)
			sv = new sortedVerteces<T>(ver, induced, g);
		else
			sv = new sortedVerteces<T>(ver, g);

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
				addable = true;
				break;
			}
		}
		delete sv;
		delete induced;


	}

	S.clear();
	return S1;
}



template< typename T > unordered_set <T> randNeighbor(unordered_set<T> currentSolution, GraphRepresentation<T> *g, double alpha, double lambda, int priorityFunction, int seed)
{
	

	//Generating random number
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<> dist(0, RAND_MAX);
	int random = dist(rng);

	// random element from solution
	auto r = random % currentSolution.size(); 
	auto it = std::begin(currentSolution);
	advance(it, r);

	unordered_set<T> adjacentSolution = currentSolution;
	adjacentSolution.erase(*it);
	adjacentSolution = solutionReconstruction(adjacentSolution, g, alpha, lambda, priorityFunction, *it);

	return adjacentSolution;

}
