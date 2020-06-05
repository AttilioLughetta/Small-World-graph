#include "GraphRepresentation.h"
#include <ilcplex/ilocplex.h>
#include <fstream>
#pragma once
typedef IloArray<IloNumVarArray> NumVarMatrix;
typedef IloArray<NumVarMatrix>   NumVar3Matrix;



//template<typename T>
class cplexSolver
{
private:
	GraphRepresentation<int> *g;
	int getN()
	{
		return this->g->getN();
	}

	inline int a(int i, int j)
	{
		return this->g->hasEdge(i - 1, j - 1);
	}

	inline int Deg(int i)
	{
		return this->g->getDegree(i - 1);
	}
	
	void print_solution(const IloCplex& cplex, const IloNumVarArray& x) {
		int n = getN();
		
		cout << "\n\nVerteces:\n ";

		for (auto i = 1; i <= n; ++i) {
			if (cplex.getValue(x[i]) > .5)
				cout << x[i] << " ";

		}


		cout << "\n";
	}
public:
	cplexSolver(GraphRepresentation<int> *graph)
	{
		g = graph;
	}







	vector<int> Solve(double alpha, double lambda, double &time)
	{
		// CPLEX environment. Takes care of everything, including memory management for CPLEX objects.
		IloEnv env;

		// CPLEX model. We put variables and constraints in it!
		IloModel model(env);
		int L = ceil(2 * (lambda)-1);
		// Vertex Number

		int n = getN();
		stringstream name;

		// Variables



		// Create variable x


		IloNumVarArray x(env, n + 1);
		for (int j = 1; j <= n; j++) {
			name << "x_" << j;
			x[j] = IloNumVar(env, 0, 1, IloNumVar::Bool, name.str().c_str());
			name.str(""); // Clean name
		}


		// Create variable w

		NumVar3Matrix w(env, n + 1);
		for (int i = 1; i <= n; i++) {
			w[i] = NumVarMatrix(env, n + 1);
			for (int j = 1; j <= n; j++) {
				w[i][j] = IloNumVarArray(env, L + 1);	cout << "\n";
				for (int l = 1; l <= L; l++) {
					name << "w_" << i << "_" << j << "_" << l;
					w[i][j][l] = IloNumVar(env, 0.0, IloInfinity, ILOFLOAT, name.str().c_str()); // modificare da 0 ad infinito
					name.str("");
					//cout << l;
				}

			}
		}



		// create variable z

		IloArray<IloNumVarArray> z(env, n + 1);
		for (int i = 1; i <= n; i++) {
			int degree = Deg(i); 
			if (degree < 2) degree = 2;
			z[i] = IloNumVarArray(env, degree + 1);
			z[i][1] = IloNumVar(env, 0, 0, ILOFLOAT, name.str().c_str()); // Almeno Grado 2
			for (auto j = 2; j <= degree; j++) {
				name << "x_" << i << "_" << j;
				z[i][j] = IloNumVar(env, 0, IloInfinity, ILOFLOAT, name.str().c_str());
				name.str("");
			}
		}

		IloExpr expr(env);


		//Objective Function

		for (auto i = 1; i <= n; i++)
			expr += x[i];

		IloObjective obj(env, expr, IloObjective::Maximize);

		// Add the objective function to the model
		model.add(obj);

		expr.clear();

		//Constraints


		//Constraint 1a)
		IloArray<IloArray<IloRangeArray>>  ac(env, n + 1);
		for (int i = 1; i <= (n - 1); i++)
		{
			ac[i] = IloArray<IloRangeArray>(env, n + 1);
			for (int j = i + 1; j <= n; j++)
			{
				ac[i][j] = IloRangeArray(env, L + 1);
				for (int l = 1; l <= L; l++)
				{

					expr = w[i][j][l] - w[j][i][l];
					name << "Constraint 1a" << i << "_" << j << "_" << l;
					ac[i][j][l] = IloRange(env, 0, expr, 0, name.str().c_str());
					name.str("");
					expr.clear();
				}

				model.add(ac[i][j]);
			}
		}

		//Constraint 1b)

		//1ba)
		IloArray<IloRangeArray> ba(env, n);
		for (int i = 1; i <= (n - 1); i++)
		{
			ba[i] = IloRangeArray(env, n + 1);
			for (int j = i + 1; j <= n; j++)
			{
				expr = w[i][j][1] - x[i];
				name << "Constraint 1ba" << i << "_" << j << "_1";
				ba[i][j] = IloRange(env, -IloInfinity, expr, 0, name.str().c_str());
				name.str("");
				expr.clear();
			}
			model.add(ba[i]);
		}

		//1bb)
		IloArray<IloRangeArray> bb(env, n);
		for (int i = 1; i <= (n - 1); i++)
		{
			bb[i] = IloRangeArray(env, n + 1);
			for (int j = i + 1; j <= n; j++)
			{

				expr = w[i][j][1] - x[j];
				name << "Constraint 1bb " << i << "_" << j << "_1";
				bb[i][j] = IloRange(env, -IloInfinity, expr, 0, name.str().c_str());
				name.str("");
				expr.clear();
			}
			model.add(bb[i]);
		}



		//1bc)
		IloArray<IloRangeArray> bc(env, n);
		for (int i = 1; i <= (n - 1); i++)
		{
			bc[i] = IloRangeArray(env, n + 1);
			for (int j = i + 1; j <= n; j++)
			{
				int res = a(i,j);
				expr = w[i][j][1] - res;
				name << "Constraint 1bc " << i << "_" << j << "_1";
				bc[i][j] = IloRange(env, -IloInfinity, expr, 0, name.str().c_str());
				name.str("");
				expr.clear();
			}
			model.add(bc[i]);
		}


		//Constraint C
		IloArray<IloRangeArray> c(env, n);
		for (int i = 1; i <= (n - 1); i++)
		{
			c[i] = IloRangeArray(env, n + 1);
			for (int j = i + 1; j <= n; j++)
			{
				int res = a(i,j) - 2;
				expr = w[i][j][1] - x[i] - x[j] - res;
				name << "Constraint 1c" << i << "_" << j << "_1";
				c[i][j] = IloRange(env, 0, expr, IloInfinity, name.str().c_str());
				name.str("");
				expr.clear();
			}
			model.add(c[i]);
		}

		//Constraints D)

		//Da)

		IloArray<IloArray<IloRangeArray>>  da(env, n);
		for (int i = 1; i <= (n - 1); i++)
		{
			da[i] = IloArray<IloRangeArray>(env, n + 1);
			for (int j = i + 1; j <= n; j++)
			{
				da[i][j] = IloRangeArray(env, L + 1);
				for (int l = 2; l <= L; l++)
				{
					expr = w[i][j][l] - x[i];
					name << "Constraint Da" << i << "_" << j << "_" << l;
					da[i][j][l] = IloRange(env, -IloInfinity, expr, 0, name.str().c_str());
					name.str("");
					expr.clear();
				}
				model.add(da[i][j]);
			}
		}

		//Db)

		IloArray<IloArray<IloRangeArray>>  db(env, n);
		for (int i = 1; i <= (n - 1); i++)
		{
			db[i] = IloArray<IloRangeArray>(env, n + 1);
			for (int j = i + 1; j <= n; j++)
			{
				db[i][j] = IloRangeArray(env, L + 1);
				for (int l = 2; l <= L; l++)
				{
					for (int t = 1; t <= n; t++)
					{
						int res = a(i,t);
						expr += res * w[t][j][l - 1];
					}
					expr += w[i][j][l - 1] - w[i][j][l];
					name << "Constraint Db" << i << "_" << j << "_" << l;
					db[i][j][l] = IloRange(env, 0, expr, IloInfinity, name.str().c_str());
					name.str("");
					expr.clear();

				}
				model.add(db[i][j]);
			}
		}


		//Constraint E
		IloArray<IloArray<IloRangeArray>>  e(env, n);
		for (int i = 1; i <= (n - 1); i++)
		{
			e[i] = IloArray<IloRangeArray>(env, n + 1);
			for (int j = i + 1; j <= n; j++)
			{
				e[i][j] = IloRangeArray(env, L + 1);
				for (int l = 2; l <= L; l++)
				{
					for (int t = 1; t <= n; t++)
					{
						int res = a(i,t);
						expr += res * w[t][j][l - 1];

					}
					int degree = Deg(i);
					expr += degree * (x[i] - 1) - degree * w[i][j][l];
					name << "Constraint e" << i << "_" << j << "_" << l;
					e[i][j][l] = IloRange(env, -IloInfinity, expr, 0, name.str().c_str());
					name.str("");
					expr.clear();

				}
				model.add(e[i][j]);
			}
		}


		//Constraint F

		IloRangeArray f = IloRangeArray(env, n + 1);
		for (int i = 1; i <= n; i++)
		{
			int degree = Deg(i);
			for (int j = 2; j <= degree; j++)
				expr += z[i][j];
			expr += -x[i];
			name << "Constraint 1f" << i << "_";
			f[i] = IloRange(env, 0, expr, 0, name.str().c_str());
			name.str("");
			expr.clear();

		}
		model.add(f);

		//Constraint G

		IloRangeArray g = IloRangeArray(env, n + 1);
		for (int i = 1; i <= n; i++)
		{
			int degree = Deg(i);
			for (int j = 2; j <= degree; j++)
				expr += j * z[i][j];
			for (int j = 1; j <= n; j++)
			{
				int res = a(i,j);
				expr += res * -x[j];

			}
			expr += +degree * (1 - x[i]);
			name << "Constraint G" << i << "_";
			g[i] = IloRange(env, 0, expr, IloInfinity, name.str().c_str());
			name.str("");
			expr.clear();

		}
		model.add(g);


		//Constraint 2

		IloArray<IloRangeArray> two(env, n + 1);
		for (int i = 1; i <= (n - 1); i++)
		{
			two[i] = IloRangeArray(env, n + 1);
			for (int j = i + 1; j < n; j++)
			{
				expr = w[i][j][L] - x[i] - x[j] + 1;
				name << "Constraint two" << i << "_" << j << "_1";
				two[i][j] = IloRange(env, 0, expr, IloInfinity, name.str().c_str());
				name.str("");
				expr.clear();
			}
			model.add(two[i]);
		}

		//Constraint 3

		IloRangeArray three = IloRangeArray(env, n + 1);
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (j != i)
				{
					for (int l = 2; l <= L; l++)
						expr += l * (w[i][j][l] - w[i][j][l - 1]);

					expr += w[i][j][1] - lambda * x[j];
				}
			}
			name << "Constraint three" << i;
			three[i] = IloRange(env, -IloInfinity, expr, 0, name.str().c_str());
			name.str("");
			expr.clear();

		}
		model.add(three);
		

		//Constraint 5a

		IloArray<IloArray<IloRangeArray>>  fiveA(env, n);
		for (int i = 1; i <= (n - 1); i++)
		{
			fiveA[i] = IloArray<IloRangeArray>(env, n + 1);
			for (int j = i + 1; j <= n; j++)
			{
				fiveA[i][j] = IloRangeArray(env, L + 1);
				for (int l = 2; l <= L; l++)
				{
					expr = w[i][j][l] - w[i][j][l - 1];
					name << "Constraint 5a" << i << "_" << j << "_" << l;
					fiveA[i][j][l] = IloRange(env, 0, expr, IloInfinity, name.str().c_str());
					name.str("");
					expr.clear();
				}
				model.add(fiveA[i][j]);
			}
		}

		//Constraint 5b

		IloRangeArray fiveB = IloRangeArray(env, n + 1);
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				int res =a(i,j);
				expr += res * x[j];
			}
			expr += -x[i] - x[i];
			name << "Constraint 5b" << i << "_";
			fiveB[i] = IloRange(env, 0, expr, IloInfinity, name.str().c_str());
			name.str("");
			expr.clear();

		}
		model.add(fiveB);


		//Constraint 6

		IloRangeArray six = IloRangeArray(env, n + 1);
		for (int i = 1; i <= n; i++)
		{
			for (int s = 1; s <= n - 1; s++)
			{
				for (int t = s + 1; t <= n; t++)
				{
					int res = a(i,s)*a(i,t);

					expr += res * w[s][t][1];
				}

			}
			int degree = Deg(i);
			for (int d = 2; d <= degree; d++)
			{
				double di = alpha * (d * (d - 1) / 2);
				int a = ceil(di);
				expr += -a * z[i][d];
			}

			name << "Constraint 6" << i << "_";
			six[i] = IloRange(env, 0, expr, IloInfinity, name.str().c_str());
			name.str("");
			expr.clear();

		}
		model.add(six);

		// Free the memory used by expr
		expr.end();

		// Create the solver object
		IloCplex cplex(model);
		// Export model to file (useful for debugging!)
		cplex.exportModel("model.lp");
		
		
		//Setting time limit
		cplex.setParam(IloCplex::TiLim, 3600);
		
		
		bool solved = false;

		
		try {
			// Try to solve with CPLEX 
			IloNum start;
			start = cplex.getTime();
			cplex.getTime();
			solved = cplex.solve();
			time = cplex.getTime() - start;

		}
		catch (const IloException& e) {
			cerr << "\n\nCPLEX Raised an exception:\n";
			cerr << e << "\n";
			env.end();
			throw;
		}

		if (solved) {
			// If CPLEX successfully solved the model, print the results
			cout << "\n\nCplex success!\n";
			cout << "\tStatus: " << cplex.getStatus() << "\n";
			cout << "\tObjective value: " << cplex.getObjValue() << "\n";
			//print_solution(cplex, x);
			//env.end();
			vector<int> s;
			
			for (int i = 1; i <= n; i++)
			{
				if(cplex.getValue(x[i])>0)
					s.push_back(i-1);
			}
			return  s; /*cplex.getBestObjValue();*/

			

		}
		else {
			cerr << "\n\nCplex error!\n";
			cerr << "\tStatus: " << cplex.getStatus() << "\n";
			cerr << "\tSolver status: " << cplex.getCplexStatus() << "\n";

		}

		env.end();




	}





};


