#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <conio.h>

using namespace std;



void print_vector(const vector<double>& vec) {
	for (double val : vec) {
		cout << val << endl;
	}
	cout << endl;
}

// Jacobi Iterative Method
vector<double> jacobi(const vector<vector<double>>& A, const vector<double>& B, vector<double> x, double epsilon) {
	int n = A.size();
	vector<double> x_old(n, 0.0);
	bool converged = false;
	int iteration = 0;

	while (!converged) {
		converged = true;
		for (int i = 0; i < n; ++i) {
			double sum = 0.0;
			for (int j = 0; j < n; ++j) {
				if (i != j) {
					sum += A[i][j] * x_old[j];
				}
			}
			x[i] = (B[i] - sum) / A[i][i];
		}

		// Check convergence
		for (int i = 0; i < n; ++i) {
			if (fabs(x[i] - x_old[i]) > epsilon) {
				converged = false;
				break;
			}
		}

		x_old = x;
		iteration++;

		// Prevent infinite loop
		if (iteration > 10000) {
			cout << "Jacobi method did not converge after 10000 iterations." << endl;
			break;
		}
	}

	cout << "Jacobi Iterations: " << iteration << endl;
	return x;
}

// Gauss-Seidel Iterative Method
vector<double> gauss_seidel(const vector<vector<double>>& A, const vector<double>& B, vector<double> x, double epsilon) {
	int n = A.size();
	bool converged = false;
	int iteration = 0;

	while (!converged) {
		converged = true;
		vector<double> x_old = x;

		for (int i = 0; i < n; ++i) {
			double sum = 0.0;
			for (int j = 0; j < n; ++j) {
				if (i != j) {
					sum += A[i][j] * x[j];
				}
			}
			x[i] = (B[i] - sum) / A[i][i];
		}

		// Check convergence
		for (int i = 0; i < n; ++i) {
			if (fabs(x[i] - x_old[i]) > epsilon) {
				converged = false;
				break;
			}
		}

		iteration++;

		// Prevent infinite loop
		if (iteration > 10000) {
			cout << "Gauss-Seidel method did not converge after 10000 iterations." << endl;
			break;
		}
	}

	cout << "Gauss-Seidel Iterations: " << iteration << endl;
	return x;
}

// SOR Iterative Method
vector<double> sor(const vector<vector<double>>& A, const vector<double>& B, vector<double> x, double omega, double epsilon) {
	int n = A.size();
	bool converged = false;
	int iteration = 0;

	while (!converged) {
		converged = true;
		vector<double> x_old = x;

		for (int i = 0; i < n; ++i) {
			double sum = 0.0;
			for (int j = 0; j < n; ++j) {
				if (i != j) {
					sum += A[i][j] * x[j];
				}
			}
			x[i] = (1 - omega) * x[i] + omega * (B[i] - sum) / A[i][i];
		}

		// Check convergence
		for (int i = 0; i < n; ++i) {
			if (fabs(x[i] - x_old[i]) > epsilon) {
				converged = false;
				break;
			}
		}

		iteration++;

		// Prevent infinite loop
		if (iteration > 10000) {
			cout << "SOR method did not converge after 10000 iterations." << endl;
			break;
		}
	}

	cout << "SOR Iterations: " << iteration << " with omega: " << omega << endl;
	return x;
}
const vector<vector<vector<double>>> A = { {
		{4, 2, -3, -1, 2, 1, 0, 0, 0, 0},
		{8, 6, -5, -3, 6, 5, 0, 1, 0, 0},
		{4, 2, -2, -1, 3, 2, -1, 0, 3, 1},
		{0, -2, 1, 5, -1, 3, -1, 1, 9, 4},
		{-4, 2, 5, 6, 7, -3, 3, 2, 3, 0},
		{8, 6, -8, 5, 7, 17, 2, 6, -3, 5},
		{0, 2, -1, 3, -4, 2, 5, 3, 0, 1},
		{16, 10, -11, -9, 17, 34, 2, -1, 2, 2},
		{4, 6, 2, -7, 13, 9, 2, 0, 12, 4},
		{0, 0, -1, 8, -3, -24, -8, 6, -3, 1},},
		{{4, 2, -4, 0, 2, 4, 0, 0},
		{2, 2, -1, -2, 1, 3, 2, 0},
		{-4, -1, 14, 1, -8, -3, 5, 6}, 
		{0, -2, 1, 6, -1, -4, -3, 3},
		{2, 1, -8, -1, 22, 4, -10, -3},
		{4, 3, -3, -4, 4, 11, 1, -4},
		{0, 2, 5, -3, -10, 1, 14, 2},
		{0, 0, 6, 3, -3, -4, 2, 19}},
		{{4, -1, 0, 0, 0, 0, 0, 0, 0, 0},
		{-1, 4, -1, 0, 0, 0, 0, 0, 0, 0},
		{0, -1, 4, -1, 0, 0, 0, 0, 0, 0,},
		{0, 0, -1, 4, -1, 0, 0, 0, 0, 0,},
		{0, 0, 0, -1, 4, -1, 0, 0, 0, 0,},
		{0, 0, 0, 0, -1, 4, -1, 0, 0, 0,},
		{0, 0, 0, 0, 0, -1, 4, -1, 0, 0,},
		{0, 0, 0, 0, 0, 0, -1, 4, -1, 0,},
		{0, 0, 0, 0, 0, 0, 0, -1, 4, -1,},
		{0, 0, 0, 0, 0, 0, 0, 0, -1, 4,}}
};


const vector<vector<double>> B = { { 5, 12, 3, 2, 3, 46, 13, 38, 19, -21 } ,
							{ 0,-6,6,23,11,-22,-15,45 },
							{ 7,5,-13,2,6 ,-12,14,-4,5,-5 }};
const double EPSILON[3] = { 1e-3,1e-4,1e-5 };
const double OMEGA[5] = { 0.8,0.9,1,1.1,1.2 };
int Select_Equation()
{
	std::cout << "Please Select Equati\n";
	std::cout << "1. 线性方程组\n";
	std::cout << "2. 对称正定线性方程组\n";
	std::cout << "3. 三对角(严格对角占优)线性方程组\n";
	int n;
	std::cin >> n;
	return n;
}
int Select_Epsilon()
{
	std::cout << "Please Select Epsilon\n";
	std::cout << "1. 1e-3  2. 1e-4  3. 1e-5\n";
	int n;
	std::cin >> n;
	return n;
}

int Select_Omega()
{
	std::cout << "Please Select Omega\n";
	std::cout << "1. 0.8  2. 0.9  3. 1  4. 1.1  5. 1.2\n";
	int n;
	std::cin >> n;
	return n;
}
int main()
{

	vector<double> x_initial1 = { 2,0,2,2,6,2,2,3,2,0 }; // Initial vector with zeros
	vector<double> x_initial2 = { 2,0,2,2,6,2,2,3 };
	while (true)
	 {
		 std::cout << "Please choose which method to use\n";
		 std::cout << "1.Jacobi迭代法\n";
		 std::cout << "2.Gauss-Seidel迭代法\n";
		 std::cout << "3.SOR迭代法\n";
		 std::cout << "4.Exit\n";
		 int n;
		 int m, e, o;
		 std::cin >> n;
		 vector<double> x_jacobi, x_gauss_seidel, x_sor;
		 switch (n)
		 {
			 case 1:
				 m = Select_Equation();
				 e = Select_Epsilon();
				 x_jacobi = jacobi(A[m-1], B[m-1], x_initial1,EPSILON[e-1]);
				 cout << "Solution using Jacobi method: \n";
				 print_vector(x_jacobi);
				 break;
			 case 2:
				 m = Select_Equation();
				 e = Select_Epsilon();
				 x_gauss_seidel = gauss_seidel(A[m - 1], B[m - 1], x_initial2, EPSILON[e - 1]);
				 cout << "Solution using Gauss-Seidel method: \n";
				 print_vector(x_gauss_seidel);
				 break;
			 case 3:
				 m = Select_Equation();
				 e = Select_Epsilon();
				 o = Select_Omega();
				 x_sor = sor(A[m - 1], B[m - 1], x_initial1,OMEGA[o-1], EPSILON[e - 1]);
				 cout << "Solution using SOR method with omega = " << OMEGA[o - 1] << ": \n";
				 print_vector(x_sor);
				 break;
			 case 4:
				 exit(0);
			 default:
				 break;
		 }
		 _getch();
		 system("cls");
	 }
	 return 0;
}