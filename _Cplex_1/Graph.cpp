/*#include "floydWarshall.h"
#include "Graph.h"
#include <ctime>
using namespace std;


#define T int


	//template<typename T>
	Graph<T>::Graph(int m, bool o)
	{
		n = m;
		this->vertex.resize(m);
		oriented = o;
		unordered_map<T, unordered_map<T, int>> dist ;
	}

	template<>
	bool Graph<T>::newEdge(int source, int destination)
	{
		if (!this->oriented)
			return (this->vertex.at(source).insert(destination).second && this->vertex.at(destination).insert(source).second);
		else
			return this->vertex.at(source).insert(destination).second;
	}

	template<>
	 void Graph<T>::randPopulate(int m)
	{
		int counter = 0;
		srand(time(NULL));
		int n = getN();
		while (counter < m)
		{
			int s = rand() % n;
			int d = rand() % n;
			if (this->selfLoop == 1 || s != d)
			{
				if (newEdge(s, d))
					counter++;

			}
		}

	}

	template<>
	void Graph<T>::draw()
	{
		for (int i = 0; i < n; i++)
		{
			cout << "\n(" << i << ")";
			for (auto it = begin(vertex.at(i)); it != end(this->vertex.at(i)); it++)
				cout << "->" << *it;

		}
	}

	template<>
	int Graph<T>::hasEdge(T a, T b)
	{
		//return !(this.vertex.at(d).find(s) == this.vertex.at(d).end());
		return 0;
	}

	template<>
	int Graph<T>::getDegree(T i)
	{
		return 0;
	}

	template<>
	unordered_set<T> Graph<T>::getNeighbors(T i)
	{
		return unordered_set<T>();
	}






	template<>
	unordered_set<T> Graph<T>::getAllVertices()
	{
		return unordered_set<T>();
	}


		//TODO : delete Graph method
	/*
	template<>
	unordered_map<T, unordered_map<T, int>> Graph<T>::computeDistance()
	{
		this->dist = unweightedFloydWarshall(this);
	}

	*/
