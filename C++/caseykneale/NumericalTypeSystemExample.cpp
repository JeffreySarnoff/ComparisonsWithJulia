/* 
 * File:   main.cpp
 * Author: caseykneale
 *
 * Created on November 25, 2020, 9:19 PM
 */
#include <cstdlib>
#include <math.h>
#include <functional>
#include <iostream>
using namespace std;

//Display the first 2 elements of an array of any type.
template <class T> void showFirstTwo (T* a) {
    cout << "[ " << a[0] << ", \t" << a[1] << " ]" << endl;
}

/*
 * Performs: +/- A
 * Returns the result as 2 dimensional array.
 * Warning: this will break for unsigned types.
 */
template <class T> T* plusMinus (T a) {
  T* result = new T[2];
  result[0] = a;
  result[1] = static_cast<T>(-1) * a;
  return result;
}

/*
 * Performs: A +/- B
 * Provided A is the same type as B.
 * Returns the result as 2 dimensional array.
 */
template <class T> T* plusMinus (T a, T b) {
  T* result = new T[2];
  result[0] = a + b;
  result[1] = a - b;
  return result;
}

/*
 * Solve: AX^2 + BX + C = 0 for X
 * Accepting double precision floating point numbers for B and C.
 * Returns the positive and negative roots as a 2 dimensional double array.
 */
double* quadraticEquation(double a, double b, double c) {    
    double* result = plusMinus<double>(-b, sqrt(pow(b, 2.0) - (4.0*a*c)) );
    //Alternative.
    //double* result = plusMinus<double>(-b, sqrt((b*b) - (4.0*a*c)) ); 
    result[0] /= 2.0 * a;
    result[1] /= 2.0 * a;
    return result;
}

/*
 * Solve: AX^2 + BX + C = 0 for X
 * Accepting integer numbers for A, B and C.
 * Returns the positive and negative roots as a 2 dimensional double array.
 */
double* quadraticEquation(int a, int b, int c) {
    double a_dbl = static_cast<double>(a), 
            b_dbl = static_cast<double>(b), 
            c_dbl = static_cast<double>(c);
    double* result = quadraticEquation(a_dbl, b_dbl, c_dbl);
    return result;
}

/*
 * Solve the A^2 = B^2 + C^2 for A
 * Accepting double precision floating point numbers for B and C.
 * Returns the positive and negative roots as a 2 dimensional double array.
 */
double* pythagoreanTheorem(double b, double c) {
    double* result = plusMinus<double>( sqrt(pow(b,2.0) + pow(c,2.0)) );
    // A common alternative way to write the same function - slightly more readable.
    //double* result = plusMinus<double>( sqrt((b*b) + (c*c)) ); 
    return result;
}

/*
 * Solve the A^2 = B^2 + C^2 for A
 * Accepting integers for B and C.
 * Returns the positive and negative roots as a 2 dimensional double array.
 */
double* pythagoreanTheorem(int b, int c) {
    double b_dbl = static_cast<double>(b), 
            c_dbl = static_cast<double>(c);
    double* result = pythagoreanTheorem(b_dbl, c_dbl);
    return result;
}

int main () {
  int a_int = 2, b_int = 5, c_int = -3;
  double a_dbl = 2.0, b_dbl = 5.0, c_dbl = -3.0;
  
  cout << "Solve C^2 = 2^2 + 5^2, for C." << endl;
  cout << "Integer inputs: " << endl;
  double* x = pythagoreanTheorem(a_int,b_int);
  showFirstTwo(x);
  cout << "Double precision float inputs: " << endl;  
  x = pythagoreanTheorem(a_dbl,b_dbl);
  showFirstTwo(x);
  
  cout << "\nSolve 0 = 2X^2 + 5X - 3, for X." << endl;
  cout << "Integer inputs: " << endl;
  x = quadraticEquation(a_int,b_int,c_int);
  showFirstTwo(x);
  cout << "Double precision float inputs: " << endl;  
  x = quadraticEquation(a_dbl,b_dbl,c_dbl);
  showFirstTwo(x);
  return 0;
}
