#pragma once
#include <vector>
#include <stdio.h>
#include <iostream>
#include "GraphT.h"
//#include"floydWarshall.h"
#include <set>
#include "Triangless.h"
#include"priorityFunction.h"
#include <time.h>
#include "OneFlip.h"
#include <math.h> 


template<typename T>
unordered_set<T> ILSProcedure(GraphRepresentation<T> *Graph, double alpha, double lambda, double timelimit, double &endtime, int priorityFunction, bool bestImprovement, int expectedValue, double omega)
{
	time_t start = time(NULL);


	endtime = difftime(time(NULL), start);

	unordered_set<T> bestSolution;
	unordered_set<T> currentSolution;
	unordered_set<T> toExclude;
	//Seed
	//bestSolution = Triangles<T>::getSingleTriangle(Graph);
	//Best Greedy Seed
	bestSolution = Triangles<T>(Graph).popAsSet();

	currentSolution = bestSolution;

	while (timelimit > endtime && (bestSolution.size() < expectedValue))
	{
		currentSolution = oneFilp(currentSolution, Graph, alpha, lambda, priorityFunction, bestImprovement, toExclude);
		if (currentSolution.size() > bestSolution.size())
			bestSolution = currentSolution;
		currentSolution = perturbationFunction(currentSolution, omega, toExclude);
		endtime = difftime(time(NULL), start);
	}

	return bestSolution;

}


template<typename T>
unordered_set<T> ILSProcedure(GraphRepresentation<T> *Graph, double alpha, double lambda, double timelimit, double &endtime, int priorityFunction, bool bestImprovement, int expectedValue, double omega, map<int, double>* map)
{
	time_t start = time(NULL);


	endtime = difftime(time(NULL), start);

	unordered_set<T> bestSolution;
	unordered_set<T> currentSolution;
	unordered_set<T> toExclude;
	//Seed
	//bestSolution = Triangles<T>::getSingleTriangle(Graph);
	//Best Greedy Seed
	bestSolution = Triangles<T>(Graph).popAsSet();

	currentSolution = bestSolution;
	(*map)[currentSolution.size()] = difftime(time(NULL), start);
	while (timelimit > endtime && (bestSolution.size() < expectedValue))
	{
		currentSolution = oneFilp(currentSolution, Graph, alpha, lambda, priorityFunction, bestImprovement, toExclude);
		if (currentSolution.size() > bestSolution.size())
		{
			(*map)[currentSolution.size()] = difftime(time(NULL), start);
			bestSolution = currentSolution;

		}
		currentSolution = perturbationFunction(currentSolution, omega, toExclude);

		if (currentSolution.size() > bestSolution.size())
			(*map)[currentSolution.size()] = difftime(time(NULL), start);

		endtime = difftime(time(NULL), start);
	}

	return bestSolution;

}



template<typename T>
unordered_set<T>perturbationFunction(unordered_set <T> currentSolution, double omega, unordered_set<T> &toExclude)
{
	int n = ceil(currentSolution.size() * omega);
	toExclude.clear();
	//Generating random number
	for (int m = 0; m < n; m++)
	{
		std::mt19937 rng(std::random_device{}());
		std::uniform_int_distribution<> dist(0, RAND_MAX);
		int random = dist(rng);

		// random element from solution
		auto r = random % currentSolution.size();
		auto it = std::begin(currentSolution);
		advance(it, r);
		currentSolution.erase(*it);
		toExclude.insert(*it);

	}

	return currentSolution;
}