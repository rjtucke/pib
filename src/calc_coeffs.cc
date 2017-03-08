#include "../include/util.h"
#include <cstdlib>   // exit
#include <vector>
#include <cmath>     // sin
#include <complex>   // to handle time part
#include <iostream>
#include <iomanip> // for setprecision
using namespace std;

const size_t N_MAX =  30; // fourier coefficients to calculate
const double L = 1.0;     // box width (in Angstroms)
const size_t X_RESOLUTION = 100; // how many x values across box (not used in integration!!!)

double psi_0(double x) { // example psi_0: triangle wave
    const double N = sqrt(12./pow(L,3)); // normalization
    if (x<L/2) {
        return N*x;
    } else {
        return N*(L-x);
    }
}

// numerical fourier coefficient calculator
const unsigned int MAX_ITERATIONS = 100;
typedef double (*func_t)(double);         // streamline function pointer syntax
double trapzd(func_t f, int iter, unsigned int order) {
    double x, sum, delta_x;
    static double result;            // the integral (I hope!)
    int it, j;

    if (iter == 1) {
        return (result=L*f(0.5*L)*sin(order*M_PI/2)); // save state (static variable!)
    } else {
        for (it=1,j=1 ; j<iter-1; j++)  // I think this just means it = 2^(number_of_slices-1)
            it <<= 1;
        delta_x = L/it;                 // slice width
        x   = 0.5*delta_x;                  // initial x is middle of first slice
        for (sum=0,j=1 ; j<=it ; j++,x+=delta_x) // j is slice number, x points to middle of current slice
            sum += f(x)*sin(order*M_PI*x/L);
        result = 0.5*(result+sum*delta_x);             // 
        return result;
    }
}

double qtrap(func_t f, unsigned int order) {
    double old_result = -1.0e30;
    const double EPSILON = 1.0e-5;
    for (unsigned int iter=1 ; iter<=MAX_ITERATIONS ; iter++) {
        double result = trapzd(f, iter, order);
        if (iter > 5)
            if (fabs(result-old_result) < EPSILON*fabs(old_result) or (fabs(result) < EPSILON*EPSILON and fabs(old_result) < EPSILON*EPSILON))
                return result;
        old_result = result;
    }
    return 0.0;
}

/*
// calculate f(x) data using fourier coefficients
void calc_func(vector<double> c) {
    for (double x=0; x<=L; x+=L/X_RESOLUTION) {
        double y = 0;
        for (unsigned int n=1; n<=N_MAX; ++n) {
            y += c[n]*sin(n*M_PI*x/L);
        }
        cout << x << " " << y << endl;
    }
}
*/

int main() {
    vector<double> c(N_MAX+1, 0.0);
    for (unsigned int n=1; n<=N_MAX; ++n) {
        c[n] = qtrap(psi_0, n);
        cout << fixed << setprecision(4) << "c["<<n<<"] = "<<c[n]<<endl;
    }

    //calc_func(c);

    return EXIT_SUCCESS;
}

