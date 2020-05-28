/*
#include "cplexSolver.h"
#include "GraphRepresentation.h"
typedef IloArray<IloNumVarArray> NumVarMatrix;
typedef IloArray<NumVarMatrix>   NumVar3Matrix;
// Model:
//
// BINARY VARIABLE x[i][j]    For all i,j = 0, ..., n - 1
//    x[i][j] == 1            If arc (i,j) is selected
//    x[i][j] == 0            Otherwise
//
// INTEGER VARIABLE t[i]      For all i = 0, ..., n - 1
//    t[i] == k               Iff node i is the k-th node in the tour
//    t[0] == 1
//    t[i] in [2, ..., n]     For all i = 1, ... n - 1
//
// OBJECTIVE FUNCTION
//    max sum x[i] For all i
//
// CONSTRAINTS
//		1a) w[i][j][l] = w[j][i][l]				 For  i,j in V, l=1...L
//	    1) sum(j, x[j][i]) == 1                    For all i
//    2) sum(j, x[i][j]) == 1                    For all i
//    3) t[i] - t[j] + 1 <= n * (1 - x[i][j])    For all i,j = 1, ..., n - 1
//       Can be written as:
//       t[i] - t[j] + n * x[i][j] <= n - 1

int getN()
{

}


void Solve(double alpha, double lambda)
{
	// CPLEX environment. Takes care of everything, including memory management for CPLEX objects.
	IloEnv env;

	// CPLEX model. We put variables and constraints in it!
	IloModel model(env);
	double L = 2 * (lambda - 1);
	// Vertex Number

	int n = getN();

	stringstream name;
					
														// Variables

	
	
	// Create variable x


	IloNumVarArray x(env, n);	
	for (auto j = 1; j <= n; ++j) {
		name << "x_"  << j;
		x[j] = IloNumVar(env, 0, 1, IloNumVar::Bool, name.str().c_str());
		name.str(""); // Clean name
	}


	// Create variable w

	NumVar3Matrix w(env, n);
	for (int i = 1; i <= n; i++) {
		w[i] = NumVarMatrix(env, n);
		for (int j = 1; j <= n; j++) {
			w[i][j] = IloNumVarArray(env, L);
			for (int l = 1; l <= L; l++) {
				name << "w_" << i << "_" << j << "_" << l;
				w[i][j][l] = IloNumVar(env, 0.0, IloInfinity, ILOFLOAT, name.str().c_str()); // modificare da 0 ad infinito
				name.str("");
			}
		}
	}



	// create variable z

	IloArray<IloNumVarArray> z(env, n);
	for (auto i = 1; i <= n; ++i) {
		z[i] = IloNumVarArray(env, n);
		for (auto j = 1; j <= n; ++j) {
			name << "x_" << i << "_" << j;
			z[i][j] = IloNumVar(env, 0, IloInfinity, ILOFLOAT, name.str().c_str()); // modificare da 0 ad infinito
			name.str(""); 
		}
	}

	IloExpr expr(env);


											//Objective Function

	for (auto i = 1; i <= n; ++i) 
			expr += x[i];

	IloObjective obj(env, expr, IloObjective::Maximize);

	// Add the objective function to the model
	model.add(obj);

	expr.clear();

												//Constraints


	//Constraint 1a)
	IloArray<IloRangeArray>  a(env, n); 
	for (int i = 1; i <= (n - 1); i++)
	{
		a[i]= IloRangeArray(env, n);
		for (int l = 1; l <= L; l++)
		{
			int j = i + 1;
			expr = w[i][j][l] - w[i][j][l];
			name << "Constraint 1a" << i << "_" << j<<"_" << l;
			a[i][l] = IloRange(env, 0, expr, 0, name.str().c_str());
			name.str(""); 
			expr.clear();
			model.add(a[i][l]);
		}
	}

	//Constraint 1b)

	//1ba)
	IloRangeArray ba (env, n);
	for (int i = 1; i <= (n - 1); i++)
	{
		int j = i + 1;
		expr = w[i][j][1] - x[i];
		name << "Constraint 1ba" << i << "_" << j << "_1" ;
		ba[i] = IloRange(env, -IloInfinity, expr, 0, name.str().c_str());
		name.str("");
		expr.clear();
		model.add(ba[i]);
	}
	
	//1bb)
	IloRangeArray bb(env, n);
	for (int i = 1; i <= (n - 1); i++)
	{
		int j = i + 1;
		expr = w[i][j][1] - x[j];
		name << "Constraint 1bb" << i << "_" << j << "_1";
		bb[i] = IloRange(env, -IloInfinity, expr, 0, name.str().c_str());
		name.str("");
		expr.clear();
		model.add(bb[i]);
	}

	int ar[100][100];
	
	//1bc)
	IloRangeArray bc(env, n);
	for (int i = 1; i <= (n - 1); i++)
	{
		int j = i + 1;
		expr = w[i][j][1];
		name << "Constraint 1bc" << i << "_" << j << "_1";
		ba[i] = IloRange(env, -IloInfinity, expr, this->g.hasEdge(i+1,j+1), name.str().c_str());
		name.str("");
		expr.clear();
		model.add(ba[i]);
	}







}



*/