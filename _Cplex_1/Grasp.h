#pragma once
#include <vector>
#include"RestrictedCandidateList.h"
#include <stdio.h>
#include <iostream>
#include "GraphT.h"
//#include"floydWarshall.h"
#include <set>
#include "Triangless.h"
#include"priorityFunction.h"
#include <time.h>
#include "OneFlip.h"

using namespace std;

template<typename T>
unordered_set<T> ConstructGreedyRandomizedSolution(GraphRepresentation<T> *Graph, unordered_set<T> seed, double alpha, double lambda, int priorityFunction)
{
	
	float sizePercentage=30;
	bool isCompleteSolution = false;
	unordered_set<T>  currentSolution = seed;
	cout << seed.size() << endl;
	RCL <T> * restrCandidateList;
	if(priorityFunction==1)
		restrCandidateList = new RCL<T> (currentSolution, Graph, alpha, lambda, isCompleteSolution, sizePercentage);
	else 
		 restrCandidateList = new RCL<T>(currentSolution, Graph, alpha, lambda, isCompleteSolution, sizePercentage,priorityFunction);
	
	
	
	while (isCompleteSolution==false)
	{
		currentSolution.insert(restrCandidateList->selectAtRandom());
		if (priorityFunction == 1)
			restrCandidateList = new RCL<T>(currentSolution, Graph, alpha, lambda, isCompleteSolution,sizePercentage);
		else 
			restrCandidateList = new RCL<T>(currentSolution, Graph, alpha, lambda, isCompleteSolution, sizePercentage,priorityFunction);
	}

	delete restrCandidateList;
	return currentSolution;
	
}

template<typename T>
unordered_set<T> GRASProcedure(GraphRepresentation<T> *Graph,  double alpha, double lambda, double timelimit, double &endtime,int priorityFunction)
{
	time_t start = time(NULL);
	unordered_set<T> bestSolution;
	unordered_set<T> currentSolution;
	Triangles<T> *t = new Triangles<T>(Graph);
	unordered_set<T> seeds = t->popAsSet();
	bestSolution = seeds;
	 endtime = difftime(time(NULL), start);

	while (timelimit>endtime&& seeds.size()>0)
	
	{
		currentSolution = ConstructGreedyRandomizedSolution(Graph, seeds, alpha, lambda,priorityFunction);
		currentSolution = oneFilp(currentSolution, Graph, alpha, lambda, priorityFunction);
		endtime = difftime(time(NULL), start);
		if (currentSolution.size() > bestSolution.size())
			bestSolution = currentSolution;
		 currentSolution.clear();
		seeds.clear();
		if (!t->empty())
			seeds = t->popAsSet();
		else
			break;
		

		
	}

	 currentSolution.clear();
	delete t;
	 seeds.clear();

	 endtime = difftime(time(NULL), start);
	return bestSolution;

}