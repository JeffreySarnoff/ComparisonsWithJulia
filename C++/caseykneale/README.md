## Numerical Type System Example:
The Julia programming language is often touted as being easy to read, performant, extensible, and geared for numerical computation. There are many reasons why that is most often the case but, sometimes the message gets clouded by nuances of specific examples. The example provided here-in is a tactical comparison between two similar implementations of the same theme in both Julia and C++. 

The Julia implementation uses only Base Julia (no imports). Similarly, the C++ example uses minimal external libraries. The julia implementation and its output can be found in the file ending with the extension `*.jl` or begining with the word `Julia`. The focus here is not on performance, but instead on readibility, flexibility, and convenience.

## Goal
Our goal is to write a simple program that can simultaenously return both the positive and negative roots for the pythagorean theorem, and the solutions of the quadratic equation. Our user-base is composed of lay people. They can open an IDE, and type numbers into pre-written scripts, but lack knowledge of topics in computer science like type systems. For example, the difference between an integer and a floating point number is to be treated how spreadsheet soft-ware treats them.

## Defining the Plus Or Minus Operator
There are two cases we need to handle. The first is when we have a scalar input (`X = sqrt(Y)`), and the second is when the plus or minus operator performs both operations, (`X=Y + sqrt(Z)`). In Julia and C++ this is easily accomplished by overloading the namespace of the function. As in,

### C++
```cpp
template <class T> T* plusMinus (T a) {...}

template <class T> T* plusMinus (T a, T b) {...}
```
### Julia
```Julia
±(a::Number) = ...
±(a::Number,b::Number) = ...
```
Notice how, in Julia we are given unicode support so we can actually define the `plusMinus` function to read as it does in mathematics. More interestingly, this type of operator can be written, thanks to syntactic sugar, in the following way `X = Y ± sqrt(Z)`. This is superficial of course, but, consider the type system at play.

In order to get similar behaviour to Julia, C++ has required us to make a template function. Julia's `Number` type encompases, integers, floats, complex numbers, etc. C++ can give us similar behaviour but, it's via an abstraction that we have to write, and consider. Julia's type system cleverly handles these common abstractions by promoting types at the operator level. Two items worth mentioning that result from this,

1. In the 2-parameter `±` function `a` and `b` need not be the same type. The C++ code
### C++
```cpp
template <class T> T* plusMinus (T a, T b) {
  T* result = new T[2];
  result[0] = a + b;
  result[1] = a - b;
  return result;
}
```
would require a little thought and a change to implement this. 

2. We can add onto the type system provided by Julia and even introduce our own promotion rules for new types. So just like C++ we are not confined to any single treatment of objects. In our case, we don't need to go there but, it's worth mentioning that no one is forced to live or die by the types provided in Base. 

## Pythagorean theorem
If we compare the two implementations for the pythagorean theorem we see effectively the same math happening. Worth noting is how the syntactic sugar(`±()`, `√()` functions) work with the type dispatching to bring the julia code to be a closer representation of the intended mathematics.

### Julia
```Julia
pythogorean_theorem( a::Number, b::Number ) = ±√(a^2 + b^2)
```

### C++
```cpp
double* pythagoreanTheorem(double b, double c) {
    double* result = plusMinus<double>( sqrt(pow(b,2.0) + pow(c,2.0)) );
    // A common alternative way to write the same function - slightly more readable.
    //double* result = plusMinus<double>( sqrt((b*b) + (c*c)) ); 
    return result;
}

double* pythagoreanTheorem(int b, int c) {
    double b_dbl = static_cast<double>(b), 
            c_dbl = static_cast<double>(c);
    double* result = pythagoreanTheorem(b_dbl, c_dbl);
    return result;
}

```
One can begin to see that multidispatch isn't about saving lines of code, sure that's nice, but it's about maintenance and extensibility to other use cases. For example, boiler plate casting code is removed from us when we introduce complex numbers to our system. Meanwhile, in C++, that requires more code to be written, our current abstraction to change, etc. We are free from writing wrappers that convert ints to doubles. We still can choose to do this, for performance we may opt too, but instead, we can opt rely on promotion rules and get things done quickly.

## Quadratic Equation
Let's start our discussion of the quadratic equation implementations by looking at the code first.

### C++
```cpp
double* quadraticEquation(double a, double b, double c) {    
    double* result = plusMinus<double>(-b, sqrt(pow(b, 2.0) - (4.0*a*c)) );
    //Alternative.
    //double* result = plusMinus<double>(-b, sqrt((b*b) - (4.0*a*c)) ); 
    result[0] /= 2.0 * a;
    result[1] /= 2.0 * a;
    return result;
}

double* quadraticEquation(int a, int b, int c) {
    double a_dbl = static_cast<double>(a), 
            b_dbl = static_cast<double>(b), 
            c_dbl = static_cast<double>(c);
    double* result = quadraticEquation(a_dbl, b_dbl, c_dbl);
    return result;
}
```

The C++ code has a few things going on. Sure we can get over the `pow` function, it's really not a big deal, but look at how we have to perform elementwise division of our output vector(created by `plusMinus()`) by a scalar(`2.0 * A`). Either we write a loop, make a function to handle this, call a library and cast to a new type/make a design change, or manually divide both entries. At some point we have to ask ourselves "hasn't someone already solved this problem?" For someone interested in just doing the math, the Julia approach is intriguing,

### Julia
```Julia
quadratic_equation( a::Number, b::Number, c::Number ) = ( -b ± √(b^2.0 - 4.0a*c) ) ./ 2.0a
```
We have again made use of some syntactic sugar, but, we've also used a new operator. Notice the `./`. The "dot"(`.`) is called the broadcast operator. It tells the compiler that we intend to repeat the operation over all available dimensions of an array/collection. So we can do `./`, `.+`, `.-`, `.*`, `.^`, `.!`, `.&`, `.==`, etc. The broadcast operator is part of the language. If we define our own functions, we can broadcast them by affixing this dot at the end of the name, ie: turning `myfunction(a)` into `myfunction.(a)`.

Some broadcasting examples, 
* Retrieve the last element of each list in a list of lists: 
```Julia
last.(list_of_list_instance)
```
* Multiplying a vector by every element in another vector to recieve a matrix: 
```Julia
a = [1,2,3]
b = ones(3)#same as [1,1,1]
c = a .* transpose(b)
``` 

## Wrapping up

The broadcast operator is something like a hero. It lets us avoid writing loops when we want highly legible code, and allows us to make quick progress without making goofy mistakes. This is similar to the benefit of having multidispatch in the language. We want generic and concise operations in a programming language, so they can be leveraged all over. 

Type systems shouldn't be a chore. The reason they were invented in the first place was to serve us. In the Julia source code, you'll see an example where integer, double, and complex double's are used in the same function call,

```Julia
println("(C++ variant does not support this)\ninteger, float, and complex inputs: ")
roots = quadratic_equation( a, b_dbl, c_cmplx )
```
The way the current C++ code is written this can't be done. We would be required to do a bit of work. We could call an API which supports these, but now we need to concern ourselves with a makefile, versioning, mashup between API's. At the end of the day we likely still will be casting between some operations.

I think of it this way: Python, R, and Julia are great for data science because they show the operator the mechanics and mathematics of whats done and conceals the data until it's called for. This is the opposite of spreadsheet software, which shows the operator a ton of data and conceals the mechanics until they are called for. Julia abstracts the type system so the operator can focus on the mechanics and mathematics of what needs to be done until it is called for. This is the opposite of how C++ brings the type system forward and will not let us perform mechanics/mathematics until it is dealt with.

I once lost 2 weeks of my life chasing a bug due to casting a double to an int without rounding in C++. In my defense when printed it appeared as a whole number more often then not and was burried in >3k lines of heavy physics code. Let's not go into it, was a bad time. That said, Julia, doesn't let you make that mistake. It throws an error when we lose precision without casting.

The Julia language is there to support your efforts of quickly building performant code to solve really hard problems. More importantly, when you show your PI, boss, friend, or even future self, the code you stand a good chance of it being quickly understood. Those quick understandings prevent bugs, and reduce technical debt, by providing clearer direction of what is actually happening.

