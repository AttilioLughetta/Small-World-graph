#include <stdio.h>
#include <ilcplex/ilocplex.h>
#include <iostream>
#include "GraphT.h"
#include <ilcplex/ilocplex.h>
#include"floydWarshall.h"
#include <set>
#include "Triangless.h"
#include"idfAlgorithm.h"
#include "cplexSolver.h"
#include <fstream>
#include<ctime>
#include "Grasp.h"
#include "SimulatedAnnealing.h"
#include "IteratedLocalSearch.h"
using namespace std;



int main(int argc, char *argv[])
{

	vector <string> filenames = {/* "fb-pages-tvshow", "soc-hamsterster","anna", "G56", "socfb-Caltech36" , "airfoil1"*/"anna", "delaunay_n12","D_9","G37"/*, "jean", "anna","dolphins","david", "queen8","adjnoun"*/};
	vector <int> expectedSolutions = { 16,4,5,10,100000,10000,10000,10000,10000,100000,10000000,1000000,1000000,1000000,100000,1000000};
	double endtime;
	 //prova(350, endtime, 100000, 0.75) ;
	cout<<endl<<endtime;
	bool random = false;
	double alpha = 0.7;
	double lambda = 1.7;
	int nvertex=138;
	int nedge=493;
	//Grasp Parameter
	int GraspSeconds = 300;
	float sizePercentage = 60;
	bool bestImprovement = true;
	bool valueBased = false;
	//Simulated Annealing Parameter
	int SAtimelimit = 3;
	double redCoeff = 0.75;
	int redRule = 1;
	//Iterated Local Search
	double omega = 0.3;
	
	
	
	int expectedSolution = 10;
	string fileName = "queen";
	double seconds = 0;
	int count=0 ;
	vector <int> result;
	time_t currentTime;
	time(&currentTime);
	char buffer[80];
	struct tm *localTime = localtime(&currentTime);
	
	
	strftime(buffer, 80, "Log\\Migliorativi.txt", localTime);


	ofstream f;
	f.open(buffer, std::ofstream::out | std::ofstream::app);
	if (!f)
		return -1;


	
	for(int a=0;a<filenames.size();a++ )
	{
		
		expectedSolution = expectedSolutions[a];
		fileName = filenames[a];
		
		char buffer[80];
		time(&currentTime);
		struct tm *localTime = localtime(&currentTime);
		strftime(buffer, 80, "%I:%M%p-%d/%m/%Y:     ", localTime);
		//Graph Creation
		f << "\n\n";

		GraphT<int> * g = new GraphT<int>(nvertex, false, false);
		
		if (random)
			g->randIntPopulate(nedge);
		else
			g->createFromFile("E:\\Tesi\\Papers\\Network\\"+fileName+".txt");
		
		
		g->draw();
		cplexSolver *Solver = new cplexSolver(g);
		int edgeNumber = 0;
		for (int a : g->getAllVertices())
			edgeNumber = edgeNumber + g->getDegree(a);

		edgeNumber = edgeNumber / 2;



		f << "Graph created" << endl;
		if (random)
			f << buffer << "Run n# " << count << " with nvertex:" << g->getN() << " and nedge :" << nedge << endl;
		else
			f << buffer << "Run n# " << count << " on " << fileName <<"( V = "<<g->getN()<<" , E = "<<edgeNumber<<" )"<< " Dataset - alpha: "<<alpha<<" lambda: "<<lambda << endl;


		double minSec = 100000;

		//Idf algo
		try {
			int function = 1;
			do {
				function++;
				time(&currentTime);
				char buffer[80];
				struct tm *localTime = localtime(&currentTime);
				strftime(buffer, 80, "%I:%M%p-%d/%m/%Y:     ", localTime);
				f << buffer << "Risultati Idf" << function << ":   ";
				unordered_set<int> best;

				best = idfAlgo<int>(alpha, lambda, g, seconds, function, expectedSolution);
				f << best.size() << "  ::: ";
				for (auto a : best)
					f << a << " ";
				f << " in " << seconds << " seconds";
				f << endl;
				if (minSec > seconds)
					minSec = seconds;
				
			} while (function < 2);
		}
		catch (exception) {
			f << endl;
			f << "Crash Idf" << endl;
		}


	
		//minSec = 10;
		
		

		//Grasp
		
		try {
			int function = 0;
				function++;
			do {
				function++;
				unordered_set<int> bests;

				// Grasp limit (seconds) = idf  seconds
				GraspSeconds = minSec;


				if(g->getN()>0)
					bests = GRASProcedure(g, alpha, lambda, GraspSeconds, seconds,function,bestImprovement,valueBased, expectedSolution, sizePercentage);
			
				time(&currentTime);
				struct tm *localTime = localtime(&currentTime);
				strftime(buffer, 80, "%I:%M%p-%d/%m/%Y:     ", localTime);
				f << buffer << "Risultati Grasp" << function << ":  " << bests.size() << "  ::: ";
				for (auto a : bests)
					f << a << " ";
				f<< " in " << seconds << " seconds con TL a: " << GraspSeconds << endl;
			} while (function < 2);
		}catch(exception_ptr){
			f << endl;
			f << "Crash Grasp" << endl;
		}

		//Simulated Anealing

		try {
			int function = 0;
			do {
				function++;
				unordered_set<int> bests;
				SAtimelimit = minSec;
				if (g->getN() > 0)
					bests = SAProcedure(g, SAtimelimit, seconds, alpha, lambda, function, 100000, redCoeff, redRule, 12345, 1000, expectedSolution);
					
				time(&currentTime);
				struct tm *localTime = localtime(&currentTime);
				strftime(buffer, 80, "%I:%M%p-%d/%m/%Y:     ", localTime);
				f << buffer << "Risultati Simulated Anealing" << function << ":  " << bests.size() << "  ::: ";
				for (auto a : bests)
					f << a << " ";
				f << " in " << seconds << " seconds con TL a: " << SAtimelimit <<" e Coefficente di riduzione : "<<redCoeff << endl;
			} while (function < 2);
		}
		catch (exception_ptr) {
			f << endl;
			f << "Crash Simulated Anealing" << endl;
		}


		//Iterated Local Search

		try {
			int function = 0;
			
			do {
				function++;
				unordered_set<int> bests;

				// ILS limit (seconds) = idf  seconds
				double ILSSeconds = minSec;


				if (g->getN() > 0)
					bests = ILSProcedure(g, alpha, lambda, ILSSeconds, seconds, function, bestImprovement, expectedSolution, omega);
					
				time(&currentTime);
				struct tm *localTime = localtime(&currentTime);
				strftime(buffer, 80, "%I:%M%p-%d/%m/%Y:     ", localTime);
				f << buffer << "Risultati IteratedLocalSearch" << function << ":  " << bests.size() << "  ::: ";
				for (auto a : bests)
					f << a << " ";
				f << " in " << seconds << " seconds con TL a: " << ILSSeconds << endl;
			} while (function < 2);
		}
		catch (exception_ptr) {
			f << endl;
			f << "Crash ILS" << endl;
		}








		//Cplex_solver
		try {
			char buffer[80];
			time(&currentTime);
			struct tm *localTime = localtime(&currentTime);
			strftime(buffer, 80, "%I:%M%p-%d/%m/%Y:     ", localTime);			

			f <<buffer<< "Risultati Solver: ";
			vector<int> vec;
			 //vec = Solver->Solve(alpha, lambda,seconds);
			f << vec.size() << "  ::: ";
			for(auto a : vec)
			f<<a<<" ";
			f << " in " << seconds << " seconds";
			f << endl;
		}
		catch(exception){
			f << endl;
			f << "Crash Solver" << endl;
		}
		
		//Deleting Object
		delete g;
		delete Solver;
		
		count++;
		nedge += 15;
		int edge_max = (nvertex*(nvertex - 1)) / 2;
		if (nedge>= edge_max)
			nvertex++;



	} 
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*
	
	
	int nvertex =50;
	int nedge = 800;
	GraphT<int> * g = new GraphT<int>(nvertex, false, false);
	g->randIntPopulate(nedge);
	cout << "\nIl grafo è stato Creato con successo\n";
	cplexSolver Solver = cplexSolver(g);
	Solver.Solve(0.7,1.7);

	
	g->draw();
	double alpha = 0.7;
	double lambda = 1.7;
	unordered_set<int> best = idfAlgo <int>(alpha, lambda, g);
	
	cout <<"\nLa grandezza dell'insieme con queste caratteristiche è"<< best.size()<<"\n";
	for (int a : best)
		cout << a << " ";
	*/
	
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