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

	vector <string> filenames = { "insecta-ant-colony3-day29", "insecta-ant-colony3-day29" /* "insecta-ant-colony2-day35","insecta-ant-colony2-day35",/*,"msc01440","msc01440","bloweybq","bloweybq","as-22july06","as-22july06","netscience","netscience","DSJC250.1","DSJC250.1"/*,  "elt","elt", "queen11","queen11", "G37", "G37",*/ /*"plat1919","plat1919" */};
	vector <int> expectedSolutions = {   10000000,1000000,3000004,100000,10000000,1000000,100000,1000000,100000,1000000 ,1000000 ,1000000,1000000,1000000 ,1000000 ,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000 };
	vector <int> TIMELIMITS = { 10000000,10000000,10000000,6300005,10000000,1000000,100000000,1000000,100000,1000000,1000000,1000000,1000000,1000000 ,1000000 ,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000 };
	bool random = false;
	double alpha = 0.5;
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
	double redCoeff = 0.1;
	int redRule = 0;
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
	
	
	strftime(buffer, 80, "Log\\SoluzioniLimitateATempo.txt", localTime);


	ofstream f;
	f.open(buffer, std::ofstream::out | std::ofstream::app);
	if (!f)
		return -1;
	
	strftime(buffer, 80, "Log\\SoluzioniLimitateATarget.txt", localTime);
	
	ofstream f2;
	f2.open(buffer, std::ofstream::out | std::ofstream::app);
	if (!f2)
		return -1;
	
	
	//TTT PLOT
	
	/*







	lambda = 2.8;
	alpha = 0.4;
	expectedSolution = 15;
	fileName = "rail_5177";
	
	time(&currentTime);
	localTime = localtime(&currentTime);
	strftime(buffer, 80, "%I:%M%p-%d/%m/%Y:     ", localTime);
	
	//Graph Creation
	f << "\n\n";

	GraphT<int> * g = new GraphT<int>(nvertex, false, false);
	g->createFromFile("E:\\Tesi\\Papers\\Network\\" + fileName + ".txt");
	
	
	time(&currentTime);
	
	localTime = localtime(&currentTime);
	strftime(buffer, 80, "%I:%M%p-%d/%m/%Y:     ", localTime);
	f << buffer << "Risultati Idf" << 2 << ":   ";
	
	unordered_set<int> best;
	seconds = TIMELIMITS[0];
	best = idfAlgo<int>(alpha, lambda, g, seconds, 2, expectedSolution);
	GraspSeconds = 3000;
	f << best.size() << "  ::: ";
	for (auto a : best)
		f << a << " ";
	f << " in " << seconds << " seconds";
	f << endl;
	int target = best.size();
	f << "Vettore tempi GRASP" << endl;
	
	f << " x <- (";
	for (int cout = 0; count < 30; count++) {


		best = GRASProcedure(g, alpha, lambda, GraspSeconds, seconds, 2, bestImprovement, valueBased, expectedSolution, sizePercentage);

		if(best.size()>= expectedSolution)
		f << seconds << ", ";

	}

	f << ")"<<endl;
	f << "Vettore tempi SA" << endl;

	f << " x <- (";
	for (int count = 0; count < 30; count++) {
	 best = SAProcedure(g, 3000, seconds, alpha, lambda, 2, 10000000, redCoeff, redRule, 12345, 1000, expectedSolution);
	 if (best.size() >= expectedSolution)
		 f << seconds << ", ";

	}
	 
	 
	 f << ")" << endl;
	 f << "Vettore tempi ILS" << endl;

	 f << " x <- (";
	 for (int count = 0; count < 30; count++) {
		 best = ILSProcedure(g, alpha, lambda, 3000, seconds, 2, bestImprovement, expectedSolution, omega);
	 if (best.size() >= target)
		 f << seconds << ", ";

	}
	
	 f << ")" << endl;
	
	*/



	 // TTTPLOT 3° tipo 
	 

	map<int, double> *IDFm = new map<int, double>();
	map<int, double> *Graspm = new map<int, double>();
	map<int, double> *ILSm = new map<int, double>();
	map<int, double> *SAm = new map<int, double>();
	unordered_set<int> best;

	int limiteDiTempo = 25000;
    lambda = 1.4;
	alpha = 0.6;
	//non serve
	expectedSolution = 34;
	//nome grafo
	fileName = "soc-hamsterster";
	
	
	nvertex = 70;
	double rapporto = 0.75;
	double maxedge = (nvertex * (nvertex - 1)) / 2;
	for (int counting = 0; counting < 30; counting++)

	{
		if (counting == 9)
			limiteDiTempo = 400;
		if (counting == 19)
			limiteDiTempo = 300;

		
		map<int, double> *IDFm = new map<int, double>();
		map<int, double> *Graspm = new map<int, double>();
		map<int, double> *ILSm = new map<int, double>();
		map<int, double> *SAm = new map<int, double>();
		unordered_set<int> best;
		
		
		
		
		nvertex = nvertex + 1;

		//rapporto = rapporto + 0.01;
		
		double totale = rapporto * maxedge;
		nedge = totale;
		//Creazione Grafo
		GraphT<int> * g = new GraphT<int>(nvertex, false, false);
		g->createFromFile("E:\\Tesi\\Papers\\Network\\" + fileName + ".txt");
		//CREAZIONE RANDOM

		//g->randIntPopulate(nedge);

		int edgeNumber = 0;
		for (int a : g->getAllVertices())
			edgeNumber = edgeNumber + g->getDegree(a);

		edgeNumber = edgeNumber / 2;



		f << "Run #" << counting << "  Grafo con vertici : " << nvertex << " e archi : " << nedge << endl;

		//LANCIO ALGORITMI
		best = idfAlgo<int>(alpha, lambda, g, seconds, 2, expectedSolution);
		//best = GRASProcedure(g, alpha, lambda, limiteDiTempo, seconds, 2, bestImprovement, valueBased, expectedSolution, sizePercentage, Graspm);
		//best = SAProcedure(g, limiteDiTempo, seconds, alpha, lambda, 2, 10000000, redCoeff, redRule, 12345, 1000, expectedSolution, SAm);
		//best = ILSProcedure(g, alpha, lambda, limiteDiTempo, seconds, 2, bestImprovement, expectedSolution, omega, ILSm);
		//Ricerca del più piccolo max
		f << "Per ottenere " << expectedSolution << " Idf ha impiegato :" << seconds <<  endl;
		


		   //Si prendono i più grandi
		int bestIdf = 0;
		int bestGrasp = 0;
		int bestILS = 0;
		int bestSA = 0;

		int minore = 0;

		//if (SAm->rbegin() != SAm->rend())
			//bestSA = SAm->rbegin()->first;
		if (IDFm->rbegin() != IDFm->rend())
			bestIdf = IDFm->rbegin()->first;
		//if (ILSm->rbegin() != ILSm->rend())
			//bestILS = ILSm->rbegin()->first;
		//if (Graspm->rbegin() != Graspm->rend())
			bestGrasp = Graspm->rbegin()->first;
		//Si prende il più piccolo
		bestILS = 1000;
		bestSA = 1000;
		bestGrasp = 1000;
		if (bestSA <= bestGrasp && bestSA <= bestILS && bestSA <= bestIdf)
		{
			minore = bestSA;
		}
		else
		{
			if (bestILS <= bestGrasp && bestILS <= bestSA && bestILS <= bestIdf)
				minore = bestILS;
			else
			{
				if (bestIdf <= bestGrasp && bestIdf <= bestSA && bestIdf <= bestILS)
					minore = bestIdf;
				else
					minore = bestGrasp;

			}

		}

		// Si prende il timestamp del primo numero uguale a minore nelle varie mappe

		double Idft, Graspt, ILSt, SAt;


		std::map<int, double>::iterator it = IDFm->begin();
		while (it != IDFm->end())
		{
			if (it->first >= minore)
			{
				Idft = it->second;
				break;
			}
			it++;
		}
		/*
		it = Graspm->begin();

		while (it != Graspm->end())
		{
			if (it->first >= minore)
			{
				Graspt = it->second;
				break;
			}
			it++;
		}


		it = ILSm->begin();

		while (it != ILSm->end())
		{
			if (it->first >= minore)
			{
				ILSt = it->second;
				break;
			}
			it++;
		}
		
		it = SAm->begin();
		while (it != SAm->end())
		{
			if (it->first >= minore)
			{
				SAt = it->second;
				break;
			}
			it++;
		}
		*/
		// Si stampa il timestamp e le migliori soluzioni


		f << " In  " << limiteDiTempo << " l'algoritmo   IDF     ha ottenuto :  " << bestIdf << "L'algoritmo    Gras    ha ottenuto :  " << bestGrasp << "L'algoritmo     SA   ha ottenuto :  " << bestSA << "L'algoritmo    ILS    ha ottenuto :  " << bestILS << endl;
		f << "Per ottenere " << minore << " gli algoritmi hanno impiegato :" << Idft << "    " << Graspt << "     " << SAt << "     " << ILSt << endl;




		delete g;
		delete Graspm;
		delete IDFm;
		delete SAm;
		delete ILSm;

		
	}
	 /*

	//
	alpha = 0.7;
	
	for (int jx = 1; jx <= 5; jx++) {
		alpha = alpha + 0.2;
		lambda = 1.3;

		for (int j = 0; j <= 5; j++) {
			//lambda = lambda - 0.4;


			for (int a = 0; a < filenames.size(); a++)
			{

				expectedSolution = expectedSolutions[a];
				fileName = filenames[a];




				char buffer[80];
				time(&currentTime);
				struct tm *localTime = localtime(&currentTime);
				strftime(buffer, 80, "%I:%M%p-%d/%m/%Y:     ", localTime);
				//Graph Creation
				

				GraphT<int> * g = new GraphT<int>(nvertex, false, false);

				if (random)
					g->randIntPopulate(nedge);
				else
					g->createFromFile("E:\\Tesi\\Papers\\Network\\" + fileName + ".txt");


				g->draw();
				cplexSolver *Solver = new cplexSolver(g);
				int edgeNumber = 0;
				for (int a : g->getAllVertices())
					edgeNumber = edgeNumber + g->getDegree(a);

				edgeNumber = edgeNumber / 2;




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

						unordered_set<int> best;
						seconds = TIMELIMITS[a];

						best = idfAlgo<int>(alpha, lambda, g, seconds, function, expectedSolution);
						


						TIMELIMITS[a] = seconds+2;

						if (a == 0)
						{
							TIMELIMITS[a + 1] = seconds;
							expectedSolutions[a + 1] = best.size();
							f << "\\textit{ " << fileName << "} & " << g->getN() << "  &  " << edgeNumber << "  & " << alpha << " & " << lambda << " & " << best.size() << " & ";

						}
						else {
							if (a % 2 != 1)
							{
								TIMELIMITS[a + 1] = seconds;
								expectedSolutions[a + 1] = best.size();
								
								f << "\\textit{ " << fileName << "} & " << g->getN() << "  &  " << edgeNumber << "  & " << alpha << " & " << lambda << " & " << best.size() << " & ";
							}
							else
								f2 << "\\textit{ " << fileName << "} & " << g->getN() << "  &  " << edgeNumber << "  & " << alpha << " & " << lambda << " & " << seconds << " & ";
						}


						



						if (minSec > seconds)
							minSec = seconds;

					} while (function < 2);
				}
				catch (exception) {
					f << endl;
					f << "Crash Idf" << endl;
				}



				minSec = 200;



				//Grasp

				try {
					int function = 0;
					function++;
					do {
						function++;
						unordered_set<int> bests;

						// Grasp limit (seconds) = idf  seconds
						GraspSeconds = TIMELIMITS[a];



						bests = GRASProcedure(g, alpha, lambda, GraspSeconds, seconds, function, bestImprovement, valueBased, expectedSolution, sizePercentage);


						if ((a % 2 != 1) && (expectedSolutions[a + 1] > bests.size()))
							expectedSolutions[a + 1] = bests.size();


						if (a == 0)
						{

							f << bests.size() << " & ";

						}
						else {
							if (a % 2 != 1)
							{

								
								f << bests.size() << " & ";
							}
							else
								f2 << seconds << " & ";
						}
					} while (function < 2);
				}
				catch (exception_ptr) {
					f << endl;
					f << "Crash Grasp" << endl;
				}

				//Simulated Anealing

				try {
					int function = 1;
					do {
						function++;

						unordered_set<int> bests;
						SAtimelimit = TIMELIMITS[a];
						if (g->getN() > 0)
							bests = SAProcedure(g, SAtimelimit, seconds, alpha, lambda, function, 10000000, redCoeff, redRule, 12345, 1000, expectedSolution);

						if (a == 0)
						{

							f << bests.size() << " & ";

						}
						else {
							if (a % 2 != 1)
							{

								f << bests.size() << " & ";
							}
							else
								
							f2 << seconds << " & ";
						}

						//Setting Expected solution
						if ((a % 2 != 1) && (expectedSolutions[a + 1] - bests.size() < (expectedSolutions[a + 1] * 15 / 100)) && bests.size() > 3)
							expectedSolutions[a + 1] = bests.size();
					} while (function < 2);
				}
				catch (exception_ptr) {
					f << endl;
					f << "Crash Simulated Anealing" << endl;
				}


				//Iterated Local Search

				try {
					int function = 1;

					do {
						function++;
						unordered_set<int> bests;

						// ILS limit (seconds) = idf  seconds
						double ILSSeconds = TIMELIMITS[a];
						if (g->getN() > 0)
							bests = ILSProcedure(g, alpha, lambda, ILSSeconds, seconds, function, bestImprovement, expectedSolution, omega);


						if ((a % 2 != 1) && (expectedSolutions[a + 1] > bests.size()))
							expectedSolutions[a + 1] = bests.size();
						if (a == 0)
						{

							f << bests.size() <<" & "<<GraspSeconds<< " \\\\ \\cline{1-5} "<<endl;

						}
						else {
							if (a % 2 != 1)
							{

								f << bests.size() << " & " << GraspSeconds << " \\\\ \\cline{1-5} "   << endl;
							}
							else
								f2 << seconds << " & " << expectedSolution << " \\\\  \\cline{1-5}" << endl;
								
						}
					} while (function < 2);
				}
				catch (exception_ptr) {
					f << endl;
					f << "Crash ILS" << endl;
				}








				//Cplex_solver
				try {

					vector<int> vec;
					//vec = Solver->Solve(alpha, lambda,seconds);

				}
				catch (exception) {
					f << endl;
					f << "Crash Solver" << endl;
				}


				delete g;
				delete Solver;

				count++;
				nedge += 15;
				int edge_max = (nvertex*(nvertex - 1)) / 2;
				if (nedge >= edge_max)
					nvertex++;


			}

		}

	}*/
}               










