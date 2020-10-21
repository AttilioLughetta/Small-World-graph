#pragma once
#include <unordered_set>
#include <unordered_map>
#include "floydWarshall.h"
#include <algorithm>
using namespace std;
template <typename T>
class GraphRepresentation 
{
private:
	int n;
	unordered_map<T, unordered_map<T, int>> dist ;
	bool oriented;
	bool selfLoop;

public: 
	virtual int hasEdge(T s, T d)const = 0 ;
	virtual int getN() { return n; }
	virtual int hasVertex(T s )const = 0;
	virtual int getDegree(T i)const = 0;
	virtual unordered_set<T> getNeighbors(T i)const = 0;
	virtual unordered_set<T> getAllVertices()const = 0;
	virtual GraphRepresentation<T>* induction(unordered_set<T> vertices) = 0;
	virtual GraphRepresentation<T>* inductionV(unordered_set<T> vertices, T vertex) = 0;
	virtual GraphRepresentation<T>* vertexInduction( T s, GraphRepresentation<T> * graph) = 0;
	virtual void deleteVertex(T v) = 0;
	virtual void draw() = 0;
	 bool newEdge(T a, T b);
	 virtual  bool addEdge(T a, T b) { return false; };


	 virtual ~GraphRepresentation<T>()
	 {


		 if (!dist.empty())
		 {
			 unordered_map<T, unordered_map<T, int>>().swap(dist);
			 dist.clear();

		 }
	 }
	 void setParam(int e, bool o, bool sl)
	{
		n = e;
		oriented = 0;
		
	}

	 void setN(int num)
	 {
		 n = num;
	 }
	 void npp()
	 {
		 n = n + 1;
	 }
	 void nmm()
	 {
		 n = n - 1;
	 }

	bool isOriented()const { return oriented; }

	

	bool haveSelfLoop() { return selfLoop; }


	template <typename T>void setDist(unordered_map<T, unordered_map<T, int>> a)
	{
		this->dist = a;
	}

	template<typename T>unordered_map<T, unordered_map<T, int>> getDist(bool update )
	{
		if (this->dist.empty()||update)
		{ 
			unordered_map<T,unordered_map<T,int>> tmp =  computeDistance<T>();
			setDist<T>(tmp);
			this->setDist(tmp);
		}
			
		return this->dist;
	}
	
	template<typename T> unordered_map<T, unordered_map<T, int>> computeDistance() const
	{
		return GraphRepresentation<T>:: template unweightedFloydWarshall<T>();
	}


	
	template<typename T>  unordered_map<T, unordered_map<T, int>> unweightedFloydWarshall(/*GraphRepresentation<T> g*/)const
	{

		unordered_map<T, unordered_map<T, int>> dist;
		unordered_set <T> vertices = getAllVertices();
		
		for (auto itr : vertices)
		{
			//Putting in dist direct edge's Graph
			unordered_map  <T, int> m;
			m.clear();
			
			for (auto nei : vertices)
			{
				if (hasEdge(itr, nei)) dist[itr][nei] = 1;
					
				else dist[itr][nei] = vertices.size()*vertices.size();
					
			}
		}
		
		for (auto k : vertices)
		{
			for (auto i : vertices)
			{
				for (auto j : vertices)
				{
					int x = dist[i][k]; 
					int y = dist[k][j];
					int z = dist[i][j];
					if ((x + y) < z)
						dist[i][j] = x+y;
				}

			}
		}
		return dist;
	}


	 template<typename T>  unordered_set <T> getNeighborsFromVertices(unordered_set <T> S)
	{
		unordered_set <T> result;
		for (T v : S)
		{
			unordered_set <T> tmp = this->getNeighbors(v);
			result.insert(tmp.begin(), tmp.end());
		}
		
		for (T x : S)
		{
				result.erase(x);
		}
		
		return result;
	}
	


	

	
};

