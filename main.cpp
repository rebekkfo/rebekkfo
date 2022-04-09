//
// This is example code from Chapter 2.2 "The classic first program" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
// 
// keep_window_open() added for TDT4102, excercise 0

// This program outputs the message "Hello, World!" to the monitor

#include "DynamicMemory.h"
#include "Matrix.h"
#include <iostream>
#include "Dummy.h"

//------------------------------------------------------------------------------'

// C++ programs start by executing the function main
int main()
{
	// Oppgave 1
	{
		createFibonacci();
	}

	// Oppgave 2
	{
		Matrix A(4, 2);
		Matrix B(4);

		std::cout << A << '\n';
		std::cout << B << '\n';

		B.set(2, 3, 5.0);
		std::cout << B << '\n';

		std::cout << B.get(2, 3) << '\n';
	}

	//Oppgave 3
	{
		dummyTest();
	}

	// Oppgave 4 og 5
	{
	Matrix A(2), B(2), C(2);
	A.set(0, 0, 1.0);
	A.set(0, 1, 2.0);
	A.set(1, 0, 3.0);
	A.set(1, 1, 4.0);

	B.set(0, 0, 4.0);
	B.set(0, 1, 3.0);
	B.set(1, 0, 2.0);
	B.set(1, 1, 1.0);

	C.set(0, 0, 1.0);
	C.set(0, 1, 3.0);
	C.set(1, 0, 1.5);
	C.set(1, 1, 2.0);

	std::cout << "A = \n" << A << '\n';
	std::cout << "B = \n" << B << '\n';
	std::cout << "C = \n" << C << '\n';

	A += (B + C);
	std::cout << "A + B + C = \n" << A << '\n';
	std::cout << "B = \n" << B << '\n';
	std::cout << "C = \n" << C << '\n';

	Matrix D = A * B;
	C *= C;
	std::cout << "D = A * B\n" << D << '\n';
	std::cout << "A = \n" << A << '\n';
	std::cout << "B = \n" << B << '\n';
	std::cout << "C *= C \n" << C << '\n';
	}
}

//------------------------------------------------------------------------------
