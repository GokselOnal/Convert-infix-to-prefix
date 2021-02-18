//============================================================================
// Name        : Calculator.h
// Author      : Emre Sefer & Hasan Sozer
// Version     : 1.2
// Copyright   : (c) 2020 Ozyegin University
// Description : Includes the header file of the Calculator class that will be 
//               used as part of the program to be submitted as Homework 2,  
//               which is assigned in the context of the course CS201, 
//				 Data Structures and Algorithms.
//============================================================================

#ifndef __CALCULATOR__
#define __CALCULATOR__

#include <string>
#include "Stack.h"

using namespace std;

class Calculator {
public:
	Calculator(string); // constructor that takes an arithmetic expression in infix representation
	~Calculator(); // destructor
	string getPrefix(); // returns the prefix representation of the arithmetic expression
	int calculate(); // evaluates and returns the result of the arithmetic expression
private:
	Stack *stack; // stack to be used for infix-prefix conversion and evaluation of an arithmetic expression
	string prefixExpression; // keeps a prefix representation of the arithmetic expression
	string infixExpression; // keeps an infix representation of the arithmetic expression
};

 #endif