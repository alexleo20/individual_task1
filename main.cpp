#include <vector> 
#include <thread> 
#include <stdio.h> 
#include <exception> 
#include <locale.h> 
#include <math.h> 
#include <cilk/cilk.h> 
#include <cilk/reducer_opadd.h> 
#include <iostream>

using namespace std::chrono;
using namespace std;

double f(double x)
{
	return 8.0 /(2.0 + 2*x*x);
}

int main()
{
	srand((unsigned)time(0));
	double a = -1.0;
	double b = 1.0;
	int N = 1e+9;
	double h = (b - a) / N;
	cilk::reducer_opadd <double> I(0.0);
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	cilk_for (int i = 0; i < N; i++)
	{
		I += f(i*h + a) * h;
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> duration = (t2 - t1);
	double Pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825;
	cout << "definite integral is " << I.get_value() << endl;
	cout << "time is " << duration.count() << " seconds" << endl;
	return 0;
}