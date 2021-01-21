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
unordered_set<T> ConstructGreedyRandomizedSolution(GraphRepresentation<T> *Graph, unordered_set<T> seed, double alpha, double lambda, int priorityFunction, bool valueBased, float sizePercentage)
{

	bool isCompleteSolution = false;
	unordered_set<T>  currentSolution = seed;
	cout << seed.size() << endl;
	RCL <T>  restrCandidateList;
	if (priorityFunction == 1)
		restrCandidateList =  RCL<T>(currentSolution, Graph, alpha, lambda, isCompleteSolution, sizePercentage, valueBased);
	else
		restrCandidateList =  RCL<T>(currentSolution, Graph, alpha, lambda, isCompleteSolution, sizePercentage, priorityFunction, valueBased);

	while (isCompleteSolution == false)
	{
		currentSolution.insert(restrCandidateList.selectAtRandom());
		
		if (priorityFunction == 1)
			restrCandidateList =  RCL<T>(currentSolution, Graph, alpha, lambda, isCompleteSolution, sizePercentage, valueBased);
		else
			restrCandidateList =  RCL<T>(currentSolution, Graph, alpha, lambda, isCompleteSolution, sizePercentage, priorityFunction, valueBased);
	}

	//delete restrCandidateList;
	return currentSolution;

}

template<typename T>
unordered_set<T> GRASProcedure(GraphRepresentation<T> *Graph, double alpha, double lambda, double timelimit, double &endtime, int priorityFunction, bool bestImprovement, bool valueBased, int expectedValue, float sizePercentage, map<int,double> * map)
{
	time_t start = time(NULL);
	unordered_set<T> bestSolution;
	unordered_set<T> currentSolution;
	//Choosing a triangle as a seed
	Triangles<T> *t = new Triangles<T>(Graph);
	unordered_set<T> seeds = t->popAsSet();
	bestSolution = seeds;
	endtime = difftime(time(NULL), start);
	(*map)[bestSolution.size()] = difftime(time(NULL), start);



	while (timelimit > endtime&& seeds.size() > 0 && (bestSolution.size() < expectedValue))

	{
		//Building a solution
		currentSolution = ConstructGreedyRandomizedSolution(Graph, seeds, alpha, lambda, priorityFunction, valueBased, sizePercentage);
		//Local Search
		currentSolution = oneFilp(currentSolution, Graph, alpha, lambda, priorityFunction, bestImprovement);
		endtime = difftime(time(NULL), start);
		//Updating the best solution
		if (currentSolution.size() > bestSolution.size())
		{
			bestSolution = currentSolution;
			(*map)[bestSolution.size()] = difftime(time(NULL), start);
		}

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


template<typename T>
unordered_set<T> GRASProcedure(GraphRepresentation<T> *Graph, double alpha, double lambda, double timelimit, double &endtime, int priorityFunction, bool bestImprovement, bool valueBased, int expectedValue, float sizePercentage )
{
	time_t start = time(NULL);
	unordered_set<T> bestSolution;
	unordered_set<T> currentSolution;
	//Choosing a triangle as a seed
	Triangles<T> *t = new Triangles<T>(Graph);
	unordered_set<T> seeds = t->popAsSet();
	bestSolution = seeds;
	endtime = difftime(time(NULL), start);
	



	while (timelimit > endtime&& seeds.size() > 0 && (bestSolution.size() < expectedValue))

	{
		//Building a solution
		currentSolution = ConstructGreedyRandomizedSolution(Graph, seeds, alpha, lambda, priorityFunction, valueBased, sizePercentage);
		//Local Search
		currentSolution = oneFilp(currentSolution, Graph, alpha, lambda, priorityFunction, bestImprovement);
		endtime = difftime(time(NULL), start);
		//Updating the best solution
		if (currentSolution.size() > bestSolution.size())
		{
			bestSolution = currentSolution;
		}

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