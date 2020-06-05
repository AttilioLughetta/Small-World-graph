

#pragma once
#include <queue>
#include <set>
#include <map>
#include <iostream>
#include<tuple>
#include "GraphRepresentation.h"

//Single triangle


class triangle {
	set<int> verteces;

public:
	triangle(int a, int b, int c)
	{
		verteces.insert(a);
		verteces.insert(b);
		verteces.insert(c);
	}
	set<int> getV()const
	{
		return verteces;
	}

	unordered_set<int> getVerteces()const
	{
		
		unordered_set <int> tmp;
		for (int a : verteces)
			tmp.insert(a);
		return tmp;
	}

	void draw()
	{
		cout << "\n";
		for (int a : getVerteces())
		{
			cout << " " << a;
		}

	}

};


bool operator < (const triangle & a, const triangle & b)
{

	for (int x : a.getV())
	{
		for (int y : b.getV())
			if (x != y)
				return (x < y);

	}
}

bool operator == (const triangle & a, const triangle & b)
{
	bool ret = false;
	for (int x : a.getVerteces())
	{
		ret = false;
		for (int y : b.getVerteces())
			if (x == y)
				ret = true;
		if (!ret)
			return false;
	}
	return ret;

}
/*
namespace std
{
	
	struct hash<triangle>
	{
		size_t
			operator()(triangle  obj) const
		{
			int ret = 1;
			for (int a : obj.getVerteces())
				ret = ret * (a + 1);
			return hash<int>()(ret);
		}
	};
}

*/


//Data Structure T  storing triangles





class Triangles {
private:


	map<int, set<triangle>> triangles;
	GraphRepresentation<int> *graph;


	map<int, set<triangle>> naiveAlgo(GraphRepresentation<int> *graph)
	{
		map<int, set<triangle>> tmp;
		triangle *tri;
		set<triangle> triangless;

		for (int x : graph->getAllVertices())
		{
			for (int y : graph->getNeighbors(x))
				for ( int z : graph->getNeighbors(y))
					if (graph->hasEdge(x, z))
					{

						int degree = graph->getDegree(x) + graph->getDegree(y) + graph->getDegree(z);
						tri = new triangle(x, y, z);
						triangless = tmp[degree];
						triangless.emplace(*tri);
						tmp[degree] = triangless;

					}

		}

		return tmp;
	}


public:
	Triangles(GraphRepresentation <int> *g)
	{
		graph = g;
		triangles = naiveAlgo(g);
	}

	~Triangles() {
		this->triangles.clear();

	}



	void draw()
	{

		for (auto itr = triangles.begin(); itr != triangles.end(); ++itr) {
			cout << "\nGrado :" << itr->first;
			for (auto x : itr->second)
				x.draw();
		}
	}


	triangle pop()
	{
		auto greater = triangles.rbegin();
		auto greaterSet = greater->second;
		auto greaterTriangle = greaterSet.begin();



		triangle ret = *greaterTriangle;
		greaterSet.erase(greaterTriangle);


		if ((greaterSet).empty())
			triangles.erase(greater->first);

		else
			triangles[greater->first] = greaterSet;

		return ret;

	}


	unordered_set<int> popAsSet()
	{
		auto greater = triangles.rbegin();
		auto greaterSet = greater->second;
		auto greaterTriangle = greaterSet.begin();



		triangle ret = *greaterTriangle;
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


	void removeTriangles(set<triangle> a)
	{
		int key;
		for (triangle t : a)
		{
			key = 0;
			for (int v : t.getVerteces())
				key += graph->getDegree(v);

			auto triangleSet = triangles[key];
			triangleSet.erase(t);
			
			if (triangleSet.empty())
				triangles.erase(key);
			else
				triangles[key] = triangleSet;

		}
	}


	set <triangle> getTriangles()
	{
		set<triangle> ret;
		for (auto itr = triangles.begin(); itr != triangles.end(); ++itr)
			for (triangle x : itr->second)
				ret.insert(x);
		return ret;
	}


	int count()
	{
		int ret = 0;
		for (auto itr = triangles.begin(); itr != triangles.end(); ++itr)
			ret += itr->second.size();
		return ret;
	}


};


