"""
Performs: +/- A
Returns the result as 2 dimensional array.
"""
±(a::Number) = [ a, -a ]

"""
Performs: A +/- B
A and B can be different types
Returns the result as 2 dimensional array.
"""
±(a::Number,b::Number) = [ a + b, a - b ]

"""
Solve: AX^2 + BX + C = 0 for X
Accepting any Number type inputs for A, B and C.
Returns the positive and negative roots as a 2 dimensional array.
"""
quadratic_equation( a::Number, b::Number, c::Number ) = ( -b ± √(b^2.0 - 4.0a*c) ) ./ 2.0a

"""
Solve the A^2 = B^2 + C^2 for A
Accepting any Number type inputs for B and C.
Returns the positive and negative roots as a 2 dimensional double array.
"""
pythogorean_theorem( a::Number, b::Number ) = ±√(a^2.0 + b^2.0)

function main()
    a, b, c = 2, 5, -3
    a_dbl, b_dbl, c_dbl = 2.0, 5.0, -3.0
    a_cmplx, b_cmplx, c_cmplx = 2.0+0.0im, 5.0+0.0im, -3.0+0.0im

    println("Solve C^2 = 2^2 + 5^2, for C.")
    println("Integer inputs: ")
    roots = pythogorean_theorem( a, b )
    println(roots)
    println("Double precision float inputs: ")
    roots = pythogorean_theorem( a_dbl, b_dbl )
    println(roots)
    println("(C++ variant does not support this)\nDouble precision complex float inputs: ")
    roots = pythogorean_theorem( a_cmplx, b_cmplx )
    println(roots)
    
    println("\nSolve 0 = 2X^2 + 5X - 3, for X.")
    println("Integer inputs: ")
    roots = quadratic_equation( a, b, c )
    println(roots)
    println("Double precision float inputs: ")
    roots = quadratic_equation( a_dbl, b_dbl, c_dbl )
    println(roots)
    println("(C++ variant does not support this)\ninteger, float, and complex inputs: ")
    roots = quadratic_equation( a, b_dbl, c_cmplx )
end

main()
