#pragma once
#include"GraphRepresentation.h"
#include"floydWarshall.h"
#include <unordered_set>
#include<unordered_map>
#include <ctime>

template<typename T>
class GraphT : public GraphRepresentation<T>
{
	private: bool selfLoop;

	public:
	  unordered_map<T, unordered_set<T>> str;
	
	void setSelfLoop(bool s)
	{
		selfLoop = s;
	}
	
	GraphT(int nvertex, bool isOriented, bool selfLoop)
	{
		GraphRepresentation<T>::setParam(nvertex, isOriented, selfLoop);
		
		
		

	}

bool newEdge(T source, T destination)
	{
		
		
		unordered_set<T> v = getAllVertices();
		bool ret = true;
		unordered_set<T> tmp;
		int sou = source;
		int des = destination;

			for(auto sr : v)
			{
				sou--;
				if (sou == 0)
				{
					source = sr;
					break;
				}

			}
			for (auto ds :v)
			{
				des--;
				if (des == 0)
				{
					destination = ds;
					break;
				}
			}

			tmp = str.at(source);
			
			//This edge already exist!
			if (tmp.find(destination) != tmp.end()||source == destination)
				return false;

			tmp.insert(destination);
			
			str.erase(source);
			str.emplace(pair<T, unordered_set<T>>(source, tmp));
			tmp.clear();


		if (!(GraphRepresentation<T> ::isOriented()))
		{
			
				tmp = str.at(destination);
				tmp.insert(source);

				str.erase(destination);
				str.emplace(pair<T, unordered_set<T>>(destination, tmp));
			


		}
		
		return ret;
		}

	
	void randIntPopulate(int m)
	{
		int counter = 0;
		srand(time(NULL));
		int n = GraphRepresentation<T> :: getN();
		for (int i = 0; i < n; i++)
			this->str.emplace(pair<T, unordered_set<T>>(i, NULL));


		while (counter < m)
		{
			int s = rand() % n;
			int d = rand() % n;
			if(s!=d|| this->selfLoop)
				if (newEdge(s,d))
					counter++;

			
		}

		
	}


	 GraphT<T>* inductionV(unordered_set<T> vertices, T vertex)
	{
		vertices.insert(vertex);
		return induction(vertices);
	}




	void draw()
	{
		for (std::pair<T, unordered_set<T>> element : str)
		{
			cout << "\n(" << element.first << ")";
			for (T d : element.second)
				cout << "->" << d;

		}
	}
	
	
	int hasEdge(T s, T d) const
	{
		if (str.find(s) == str.end())
			return 0;
		if (str.at(s).find(d) != str.at(s).end())
			return 1;
		return 0;
	 }

	int getDegree(T i) const
	{
		return str.at(i).size();
	}
	unordered_set<T> getNeighbors(T i)const 
	{
		return str.at(i);

	}
	
	unordered_set<T> getAllVertices() const 
	{
		unordered_set<T> s;
		for (std::pair<T, unordered_set<T>> element : str)
		{
			s.insert(element.first);
		}

	  return s;
	
	}



	 bool addEdge(T source ,T destination)override
	{
		
		bool ret = true;
		
		if(this->str.find(source)==str.end())
			str.emplace(pair <T, unordered_set<T>>(source, NULL));
		
		if(str.find(destination)==str.end())
			this->str.emplace(std::pair<T, unordered_set<T>>(destination, NULL));
		
		
		unordered_set <T> tmp = str.at(source);

		//This edge already exist!
		if (tmp.find(destination) != tmp.end() || source == destination)
			return false;

		tmp.insert(destination);

		str.erase(source);
		str.emplace(pair<T, unordered_set<T>>(source, tmp));
		tmp.clear();


		if (!(GraphRepresentation<T> ::isOriented()))
		{

			tmp = str.at(destination);
			tmp.insert(source);

			str.erase(destination);
			str.emplace(pair<T, unordered_set<T>>(destination, tmp));


		}

		return ret;
	}


	 GraphT<T> * induction(unordered_set<T> vertices) override
	 {
		 GraphT<T> * g = new GraphT<T>(vertices.size(), this->isOriented(), this->haveSelfLoop());
		 for (T s : vertices)
		 {
			// add verteces
			 g->str.emplace(pair<T, unordered_set<T>>(s, NULL));
			// add edges 
			for (T d : vertices)
			 {
				 if (this->hasEdge(s, d))
					 g->addEdge(s, d);
			 }
		 }

		 return g;
	 }




	 };

