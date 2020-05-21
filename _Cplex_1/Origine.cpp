#include <stdio.h>
#include <iostream>
#include "GraphT.h"
//#include"MaxLocalAverageDistance.h"
#include <ilcplex/ilocplex.h>
#include"floydWarshall.h"
//#include "MinimumLocalClustering.h"
#include <set>
#include "Triangless.h"
#include"idfAlgorithm.h"
using namespace std;

ILOSTLBEGIN

int main()
{
	int nvertex = 379;
	int nedge = 914;
	GraphT<int> * g = new GraphT<int>(nvertex, false, false);

	g->randIntPopulate(nedge);
	g->draw();
	double alpha = 0.7;
	double lambda = 1.7;
	unordered_set<int> best = idfAlgo <int>(alpha, lambda, g);
	
	cout <<"\nLa grandezza dell'insieme con queste caratteristiche è"<< best.size()<<"\n";
	for (int a : best)
		cout << a << " ";
	
	
	/*
	cout<<"\n "<<maxLocalAverageDistance<int>(g);
	cout << "\n" << minimumLocalCluster<int>(g);
	Triangles<int> *t = new Triangles<int>(g);
	t->draw();
	cout << "\t\t\t\t\t\t\t" << t->count();
	cout << "\n\n\n\n altro :";
	
	unordered_set <int> us;
	us.insert(1); us.insert(2); us.insert(3); us.insert(4); us.insert(5); us.insert(6);
	
	
	GraphT<int> * h = g->induction(us);

	h->draw();



	cout << "\n\n\n\n altro :";
	Triangles<int> *tr = new Triangles<int>(h);
	tr->draw();
	cout << "\t\t\t\t\t\t\t" << tr->count();
	cout << "\nprova";
	t->removeTriangles(tr->getTriangles());
	t->draw();

	cout << "\t\t\t\t\t\t\t" << t->count();

	




	/**
	unordered_set<int> a;
	int s, d=0;	
	cout << "\n\nInserisci nel Grafoi vertici da indurre : ";
	cin >> s;
	a.insert(s);	cout << "\n\nInserisci nel Grafoi vertici da indurre : ";
	cin >> s;
	a.insert(s);	cout << "\n\nInserisci nel Grafoi vertici da indurre : ";
	cin >> s;
	a.insert(s);

	GraphT<int> *b = g->inductionV(a,2);
	b->draw();
	*//*
	unordered_set <unordered_set <int>> z;
	unordered_set<int>i;
		//i.insert ({ 1,2,3 });
		unordered_set<int> o;
		//o.insert ({ 1,2,3 });
	
	z.insert(i);
	z.insert(o);*/
	//cout << z.size();
	//g->draw();



}               











/* STAMPA DISTANZE

unordered_set<int>	 x = g->getAllVertices();
for (int a : x)
{
	for (int b :x)
	{
		int z = y.at(a).at(b);
		cout<< "\nDa " << a << "Ad " << b << "  " << z;
	}
}*/