#pragma once
#include <queue>
#include <set>
#include <map>
#include <iostream>
#include "GraphRepresentation.h"
#include <ctime>


template<typename T>
class RCL
{
	vector<T> verteces;
	GraphRepresentation<T> *graph;
	unordered_map<T, int> degrees;


	bool priorityFunction1(T a, T b)
	{
		if (graph->getDegree(a) > graph->getDegree(b))
			return true;
		else
			return false;
	}

	bool priorityFunction2(T a, T b)
	{
		int degA = this->degrees.at(a);
		int degB = this->degrees.at(b);


		if (degA > degB)
			return true;
		else
			return false;
	}






	void sortVertices()
	{
		int i, k;
		int N = verteces.size();
		T temp;
		//Bubble sort
		do {
			k = 0;
			for (i = 0; i < N - 1; i++)
				if (priorityFunction1(verteces[i + 1], verteces[i]))
				{
					temp = verteces[i];
					verteces[i] = verteces[i + 1];
					verteces[i + 1] = temp;
					k = 1;
				}
		} while (k == 1);
	}

	void sortVertices2()
	{
		int i, k;
		int N = verteces.size();
		T temp;
		//Bubble sort
		do {
			k = 0;
			for (i = 0; i < N - 1; i++)
				if (priorityFunction2(verteces[i + 1], verteces[i]))
				{
					temp = verteces[i];
					verteces[i] = verteces[i + 1];
					verteces[i + 1] = temp;
					k = 1;
				}
		} while (k == 1);
	}

private:
public:

	~RCL()
	{
		verteces.clear();
		degrees.clear();
	}

	//1° priority function
	RCL(unordered_set<T> CurrentSolutionSet, GraphRepresentation<T> *g, double alpha, double lambda, bool & full,float sizePercentage)
	{
		full = false;
		graph = g;
		verteces.clear();
		GraphRepresentation<T> *currSolution = g->induction(CurrentSolutionSet);
		cout << currSolution->getAllVertices().size() << endl;

		for (T element : g->getNeighborsFromVertices(CurrentSolutionSet))
		{
			currSolution = g->inductionV(CurrentSolutionSet, element);// togliere deleteVertex e vertex induction
			//currSolution = currSolution->vertexInduction(element, g);
			double mLAD = maxLocalAverageDistance(currSolution);
			double mLC = minimumLocalCluster(currSolution);
			//cout << currSolution->getAllVertices().size()<<" mLad e mlc : "<<mLAD<<"  "<<mLC <<" "<<currSolution->getN()<< endl;
			//currSolution->deleteVertex(element);
			//cout << currSolution->getAllVertices().size() << endl;
			
			if ((mLAD <= lambda) && (mLC >= alpha))
				verteces.push_back(element);
		}
		
		if (verteces.size() == 0)
		{
			
			full = true;
			return ;
		}
		
		sortVertices();
		int newsize = (sizePercentage * verteces.size()) / 100;
		if (newsize > 0)
			 this->verteces.resize(newsize);

		
		


	}
	//2° priority function
	RCL(unordered_set<T> CurrentSolutionSet, GraphRepresentation<T> * graph,  double alpha, double lambda, bool & full,float sizePercentage, int function)
	{
		
		full = false;
		verteces.clear();
		GraphRepresentation<T> *currSolution = graph->induction(CurrentSolutionSet);
		cout << currSolution->getAllVertices().size() << endl;
		unordered_map <T, int> tmp;

		for (T element : graph->getNeighborsFromVertices(CurrentSolutionSet))
		{
			currSolution = graph->inductionV(CurrentSolutionSet, element);// togliere deleteVertex e vertex induction
			//currSolution = currSolution->vertexInduction(element, g);
			double mLAD = maxLocalAverageDistance(currSolution);
			double mLC = minimumLocalCluster(currSolution);
			//cout << currSolution->getAllVertices().size()<<" mLad e mlc : "<<mLAD<<"  "<<mLC <<" "<<currSolution->getN()<< endl;
			//currSolution->deleteVertex(element);
			//cout << currSolution->getAllVertices().size() << endl;

			if ((mLAD <= lambda) && (mLC >= alpha))
			{
				verteces.push_back(element);
				int deg = currSolution->getDegree(element);
				tmp[element] = deg;
			}
		}

		if (verteces.size() == 0)
		{

			full = true;
			return;
		}

		this->degrees = tmp;
		sortVertices2();

		int newsize = (sizePercentage * verteces.size()) / 100;
		if (newsize > 0)
			this->verteces.resize(newsize);

		

	}


	vector<T>getSorted()
	{
		return verteces;
	}



	T selectAtRandom()
	{

		srand(time(NULL));
		int size = verteces.size();
		int randIndex = rand() % size;
		return verteces[randIndex];

	}
};