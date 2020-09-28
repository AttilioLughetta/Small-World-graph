#pragma once
#include <vector>
#include <math.h> 
#include"RestrictedCandidateList.h"
#include <stdio.h>
#include <iostream>
#include "GraphT.h"
#include <set>
#include "Triangless.h"
#include"priorityFunction.h"
#include <time.h>
#include "OneFlip.h"
#include <random>


//Aggiungere seed per il random, il ciclo
template<typename T>
unordered_set<T> SAProcedure(GraphRepresentation<T> *Graph, double timelimit, double &endtime, double alpha, double lambda, int priorityFunction, double t0, double tReductionCostant, int reductionRule, int seed, int maxIteration,int expectedValue)
{
	time_t start = time(NULL);
	unordered_set<T> bestSolution;
	unordered_set<T> currentSolution;
	unordered_set<T> neighborSolution;
	Triangles<T> *triangle = new Triangles<T>(Graph);
	double t = t0;
	int currIteration = 0;
	endtime = difftime(time(NULL), start);

	//
	bestSolution = triangle->popAsSet();
	currentSolution = bestSolution;
	double random;
	
	//Simulated Annealing Loop
	while (timelimit > endtime&& t > 0 && (bestSolution.size() < expectedValue) && currIteration < maxIteration)
	{
		//Local Search
		neighborSolution = randNeighbor(currentSolution, Graph, alpha, lambda, priorityFunction, seed);
		//Updating the best solution
		if (neighborSolution.size() > currentSolution.size())
			currentSolution = neighborSolution;
		else
		{
			// Random number generator
			std::mt19937 rng(std::random_device{}());
			std::uniform_int_distribution<> dist(0, RAND_MAX);
			double random = dist(rng);
			random =  random / ((double)RAND_MAX + 1.0);
		
			//Probability check
			cout << "\nProbabilità : " << probabilityOfAcceptance(currentSolution.size(), neighborSolution.size(), t);
			if (probabilityOfAcceptance(currentSolution.size(), neighborSolution.size(), t) > random)
				currentSolution = neighborSolution;
		}
		

		if (currentSolution.size() > bestSolution.size())
			bestSolution = currentSolution;
		t = tReductionRule(reductionRule, t, tReductionCostant);
		currIteration++;
		endtime = difftime(time(NULL), start);
	}

	
	return bestSolution;
}



double tReductionRule(int rule, double t, double alpha)
{
	
	
	if (rule == 0)
		//linear reduction rule
		t = t - alpha;
	else
		//Geometric reduction rule
		t = t * alpha;
	return t;

}



double probabilityOfAcceptance(int best, int curr, double t)
{
	constexpr double e = 2.71828182846;
	double d = - ( ( (double) best -  (double) curr) / t ) ;
	return pow(e, d);


}