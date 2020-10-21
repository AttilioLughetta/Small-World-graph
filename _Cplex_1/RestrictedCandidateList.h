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
	unordered_map<T, int> degrees;


	bool priorityFunction1(T a, T b, GraphRepresentation<T> *graph)
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






	void sortVertices(GraphRepresentation<T>* graph)
	{
		int i, k;
		int N = verteces.size();
		T temp;
		//Bubble sort
		do {
			k = 0;
			for (i = 0; i < N - 1; i++)
				if (priorityFunction1(verteces[i + 1], verteces[i], graph))
				{
					temp = verteces[i];
					verteces[i] = verteces[i + 1];
					verteces[i + 1] = temp;
					k = 1;
				}
		} while (k == 1);
	}

	void sortVertices2(GraphRepresentation<T>* graph)
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
		vector<T>().swap( verteces);
		unordered_map<T, int>().swap( degrees);
		verteces.clear();
		degrees.clear();

	}
	RCL()
	{
	}
	//1° priority function
	RCL(unordered_set<T> CurrentSolutionSet, GraphRepresentation<T> *g, double alpha, double lambda, bool & full,float sizePercentage, bool valueBased)
	{
		full = false;
		verteces.clear();
		GraphRepresentation<T> *currSolution = g->induction(CurrentSolutionSet);
		cout << currSolution->getAllVertices().size() << endl;
		delete currSolution;
		for (T element : g->getNeighborsFromVertices(CurrentSolutionSet))
		{
			currSolution = g->inductionV(CurrentSolutionSet, element);// togliere deleteVertex e vertex induction
			double mLAD = maxLocalAverageDistance(currSolution);
			double mLC = minimumLocalCluster(currSolution);

			delete currSolution;
			if ((mLAD <= lambda) && (mLC >= alpha))
				verteces.push_back(element);
		}
		
		//Full solution
		if (verteces.size() == 0)
		{
			
			full = true;
			return ;
		}
		
		sortVertices(g);

		int newsize;
		if(! valueBased)
			newsize = (sizePercentage * verteces.size()) / 100;
		else
		{
			sizePercentage = sizePercentage / 100;
			
			float valueMin = g->getDegree( this->verteces[0]) - (sizePercentage * (g->getDegree(this->verteces[0]) - g->getDegree(this->verteces[verteces.size()-1]) ) );
			newsize = 0;
			for (T a : verteces)
			{
				if (g->getDegree(a)<valueMin)
					break;
				newsize++;
			}
		}
		cout << "Rcl size : " << newsize << endl;
		if (newsize > 0)
			 this->verteces.resize(newsize);

	}


	//2° priority function
	RCL(unordered_set<T> CurrentSolutionSet, GraphRepresentation<T> * graph,  double alpha, double lambda, bool & full,float sizePercentage, int function, bool valueBased)
	{
		
		full = false;
		verteces.clear();
		GraphRepresentation<T> *currSolution = graph->induction(CurrentSolutionSet);
		cout << currSolution->getAllVertices().size() << endl;
		unordered_map <T, int> tmp;
		delete currSolution;
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
			delete currSolution;
		}

		if (verteces.size() == 0)
		{

			full = true;
			return;
		}

		this->degrees = tmp;
		sortVertices2(graph);

		int newsize;
		if (!valueBased)
			newsize = (sizePercentage * verteces.size()) / 100;
		else
		{
			sizePercentage = sizePercentage / 100;

			float valueMin = degrees[this->verteces[0]] - (sizePercentage * (degrees[this->verteces[0]] - degrees[this->verteces[verteces.size() - 1]]));
			newsize = 0;
			for (T a : verteces)
			{
				if (degrees[a] < valueMin)
					break;
				newsize++;
			}
		}
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