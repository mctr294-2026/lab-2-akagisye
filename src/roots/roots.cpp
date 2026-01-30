#include "roots.hpp"
#include <cmath>

//====================================================================
//Object 1 
//====================================================================

bool bisection(std::function<double(double)> f, double a, double b, double *root) {

    double fa = f(a); //Simplification
    double fb = f(b);

    if (fa * fb >= 0){ //if a and b are on the same side of the horizontal axis, no root
    return false;
    }

    for(int i=0; i<1000000; i++) {
       double c = (a+b)/2; // Find midpoint
        *root = c;

        double fc = f(c);

        if(std::abs(fc) < 1e-6) { // Check if the root is found
            return true;
        }
        
        if(fa*fc > 0){ //replace a with c
            a = c;
            fa = fc;
        }
            else{ //replace b with c
                b = c;
                fb = fc;
            }
        } // for loop

    return false;
    } //bool  
               
//====================================================================
//Object 2 
//====================================================================

bool regula_falsi(std::function<double(double)> f, double a, double b, double *root) {

    double fa = f(a);
    double fb = f(b);

    if(fa * fb > 0){
        return false;
    }

    for(int i=0; i<1000000; i++){

        double c = a - (fa * (b - a))/(fb - fa); //Midpoint
        double fc = f(c);

        *root = c;
            
        if(std::abs(fc) < 1e-6){
        return true;
        }

        if(fa*fc > 0){
            a = c;
            fa = fc;
        }
        if(fb*fc > 0){
            b = c;
            fb= fc;
        }

}//forloop
    return false;
} //bool

//====================================================================
//Object 3 
//====================================================================
bool newton_raphson(std::function<double(double)> f, std::function<double(double)> g, double a, double b, double c, double *root){

*root = c;
if(std::abs(f(c)) < 1e-6) {
    return true;
}

for(int i=0; i<1000000; i++){
    double fx = f(c);
    double gx = g(c); //g is the derivative of f

    if(std::abs(gx) < 1e-6){ //if the derivative is zero return false
        return false;
    }

    double c_new = c - fx/gx;

    *root = c_new;

    if(c_new < a || c_new > b){ //false if cnew is out of bounds
        return false;
    }

    if(std::abs(f(c_new)) < 1e-6){
        return true;
    }

    c = c_new; //Update for next loop
    } //for
return false;

} // bool



//====================================================================
//Object 4 
//====================================================================
bool secant(std::function<double(double)> f, double a, double b, double c, double *root) {

double x0 = c;
double x1 = c + 0.1; //pick a random point to the right of c

if(x1 > b){
    x1 = c - 0.1;
}

for (int i = 0; i < 1000000; i++){

    double f1 = f(x1);
    double f0 = f(x0);

    if(std::abs(f1 - f0) < 1e-6){
        return false;
    }


    double x_new = x1 - f1 * (x1-x0) / (f1-f0);

    *root = x_new;
    if(x_new < a || x_new > b){
    return false;
    }

    if(std::abs(x_new - x1) < 1e-6){ //if difference between the 2 is small
        return true;
    }

    x0 = x1; //recycle values
    x1 = x_new; 

} //for

return false;

    return false;
} //bool