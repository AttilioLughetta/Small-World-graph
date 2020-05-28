

#pragma once
#include <queue>
#include <set>
#include <map>
#include <iostream>
#include<tuple>
#include "GraphRepresentation.h"

//Single triangle

template <typename T>
class triangle {
	unordered_set<T> verteces;

public :
	triangle<T>(T a, T b, T c)
	{
		verteces.insert(a); 
		verteces.insert(b); 
		verteces.insert(c); 
	}

	 unordered_set<T>getVerteces()const
	{
		return verteces;
	}

	 void draw()
	 {
		 cout << "\n";
		 for (T a : getVerteces())
		 {
			 cout << " " << a;
		 }
		
	 }

};

template<typename T>
bool operator == (const triangle<T> & a , const triangle<T> & b)
{
	bool ret = false;
	for (T x : a.getVerteces())
	{
		ret = false;
		for (T y : b.getVerteces())
			if (x == y)
				ret = true;
		if (!ret)
			return false;
	}
	return ret;

}

namespace std
{
	template<typename T>
	struct hash<triangle<T>>
	{
		size_t
			operator()( triangle<T>  obj) const
		{
			int ret = 1;
			for (T a : obj.getVerteces())
				ret = ret * (a + 1);
			return hash<int>()(ret);
		}
	};
}








//Data Structure T  storing triangles



template <typename T>

class Triangles {
private:
	
	
    map<int, unordered_set<triangle<T>>> triangles;
	GraphRepresentation<T> *graph;
	

	map<int, unordered_set<triangle<T>>> naiveAlgo(GraphRepresentation<T> *graph)
	{
		map<int, unordered_set<triangle<T>>> tmp;
		triangle<T> *tri;
		unordered_set<triangle<T>> triangless;
		
		for (T x : graph->getAllVertices())
		{
			for (T y : graph->getNeighbors(x))
				for (T z : graph->getNeighbors(y))
					if (graph->hasEdge(x, z))
					{
						
						int degree = graph->getDegree(x) + graph->getDegree(y) + graph->getDegree(z);
						tri = new triangle<T>(x, y, z);
						triangless = tmp[degree];
						triangless.emplace(*tri);
						tmp[degree] = triangless;

					}

		}

		return tmp;
	}


public:
	Triangles(GraphRepresentation <T> *g)
	{
		graph = g;
		triangles = naiveAlgo(g);
	}

	
	void draw()
	{
		
		for (auto itr = triangles.begin(); itr != triangles.end(); ++itr) {
			cout << "\nGrado :" << itr->first;
				for (auto x : itr->second)
					x.draw();
		}
	}


	triangle<T> pop()
	{
		auto greater =triangles.rbegin() ;
		auto greaterSet = greater->second;
		auto greaterTriangle= greaterSet.begin();


		
		triangle<T> ret = *greaterTriangle;
		greaterSet.erase(greaterTriangle);
		
		
		if ((greaterSet).empty())
			triangles.erase(greater->first);

		else
			triangles[greater->first] = greaterSet;
		
		return ret;

	}


	unordered_set<T> popAsSet()
	{
		auto greater = triangles.rbegin();
		auto greaterSet = greater->second;
		auto greaterTriangle = greaterSet.begin();



		triangle<T> ret = *greaterTriangle;
		greaterSet.erase(greaterTriangle);


		if ((greaterSet).empty())
			triangles.erase(greater->first);

		else
			triangles[greater->first] = greaterSet;

		return ret.getVerteces();

	}





	bool empty()
	{
		return triangles.empty();
	}


	void removeTriangles(unordered_set<triangle<T>> a)
	{
		int key;
		for (triangle<T> t : a)
		{
			key = 0;
			for (T v : t.getVerteces())
				key += graph->getDegree(v);
			
			auto triangleSet= triangles[key];
			triangleSet.erase(t);
			//t.draw();
			if (triangleSet.empty())
				triangles.erase(key);
			else
				triangles[key] = triangleSet;

		}
	}


	unordered_set <triangle<T>> getTriangles()
	{
		unordered_set<triangle<T>> ret;
		for (auto itr = triangles.begin(); itr != triangles.end(); ++itr)
			for (triangle<T> x : itr->second)
				ret.insert(x);
		return ret;
	}


	int count()
	{
		int ret=0;
		for (auto itr = triangles.begin(); itr != triangles.end(); ++itr)
			ret+=itr->second.size();
		return ret;
	}


};


