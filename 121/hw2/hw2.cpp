// Alex McNurlin
// hw2.cpp
// CS121
// Programming Assignment #2 (RPN calculator)
// 2/26/16


#include <iostream>
#include <string>
// Used as part of code from stackoverflow.com. Credit and better explanation 
// are given below. 
#include <vector>
// Also used for the code from stackoverflow
#include <sstream>
// Used for the sqrt() function
#include <math.h>
#include "ll.h"
#include "stack.h"
using namespace std;


void parse_input( const std::string &input, Stack &stack );
// Functions for each of the mathematical functions given.
int add(Stack &stack);
int subtract(Stack &stack);
int multiply(Stack &stack);
int divide(Stack &stack);
int square(Stack &stack);
int square_root(Stack &stack);
int duplicate(Stack &stack);
int swap(Stack &stack);
int printstack(Stack &stack);


int main() {
  cout << "RPN Calculator v1.0 by Alex McNurlin" << endl;
  string s;
  Stack stack;

  while (1) {

    // Statusline to prompt a new command
    if ( stack.IsEmpty() ){
      cout << "RPN " << "(empty)" << " > ";
    } else {
      double top = stack.Top();
      cout << "RPN " << top << " > ";
    }

    // Reads user input. Exits on error (including user hitting ctrl-D)
    if (!getline(cin,s)) {
      exit(0);
    }


    // Thanks to http://stackoverflow.com/questions/236129/split-a-string-in-c
    // Credit to user 'kev' -> http://stackoverflow.com/users/348785/kev
    // Takes the input line and parses it with space delimiters (word by word)
    string buf;            // Have a buffer string
    stringstream ss(s);    // Insert the string into a stream
    vector<string> tokens; // Create vector to hold our words
    while (ss >> buf) {
      tokens.push_back(buf);
    }
    // End stackoverflow code.


    // Loops over each of the input commands
    for (int i=0; i< tokens.size(); i++) {
      // This is where the bulk of the processing is.
      parse_input( tokens[i], stack );
    }
  }

  return 0;
}


void parse_input( const std::string &input, Stack &stack ) {
  char* p;

  // Converts input to a double and stores it in input_number. If the string
  // contains non-numbers, then `p` stores everything past the last number
  double input_number = strtod( input.c_str(), &p);
  if ( *p ) { // If the given string was not a number, run the command given

    string oper(p); // A temporary string with the same contents as *p
    
    if ( oper == "-") {
      subtract(stack);
    } else if ( oper == "+") {
      add(stack);
    } else if ( oper == "*") {
      multiply(stack);
    } else if ( oper == "/") {
      divide(stack);
    } else if ( oper == "sq") {
      square(stack);
    } else if ( oper == "sqrt") {
      square_root(stack);
    } else if ( oper == "dup") {
      duplicate(stack);
    } else if ( oper == "swap") {
      swap(stack);
    } else if ( oper == "ps") {
      printstack(stack);
    } else if ( oper == "quit" ) {
      exit(0);
    } else {
      cout << "'" << oper << "' is not a valid operation" << endl;
    }

  } else {  // If the string was a number, push to stack

    stack.Push(input_number);

  }
}


int add(Stack &stack) {
  double temp = stack.Pop();

  // Checks if the stack has enough values.
  if ( stack.IsEmpty() ) {
    cout << "Not enough values in the stack!" << endl;
    if (temp) stack.Push(temp);
    return 1;
  }

  // Adds values
  double temp2 = stack.Pop();
  double out = temp2 + temp;

  // Pushes output
  stack.Push( out );
}


int subtract(Stack &stack) {
  double temp = stack.Pop();

  // Checks if the stack has enough values.
  if ( stack.IsEmpty() ) {
    cout << "Not enough values in the stack!" << endl;
    if (temp) stack.Push(temp);
    return 1;
  }

  // Subtracts
  double temp2 = stack.Pop();
  double out = temp2 - temp;

  stack.Push( out );
}


int multiply(Stack &stack) {
  double temp = stack.Pop();

  // Checks if the stack has enough values.
  if ( stack.IsEmpty() ) {
    cout << "Not enough values in the stack!" << endl;
    if (temp) stack.Push(temp);
    return 1;
  }

  // Multiplies
  double temp2 = stack.Pop();
  double out = temp2 * temp;

  stack.Push( out );
}


int divide(Stack &stack) {
  // Avoids dividing by 0
  if ( stack.Top() == 0 ) {
    cout << "Cannot divide by zero!" << endl;
    return 1;
  }

  double temp = stack.Pop();

  // Checks if the stack has enough values.
  if ( stack.IsEmpty() ) {
    cout << "Not enough values in the stack!" << endl;
    if (temp) stack.Push(temp);
    return 1;
  } 

  // Divides
  double temp2 = stack.Pop();
  double out = temp2 / temp;

  stack.Push( out );
}


int square(Stack &stack) {
  // Checks if the stack has enough values.
  if ( stack.IsEmpty() ) {
    cout << "Not enough values in the stack!" << endl;
    return 1;
  }

  double temp = stack.Pop();
  double out = temp * temp;

  stack.Push( out );
}


int square_root(Stack &stack) {
  // Checks if operand is negative
  if ( stack.Top() < 0 ) {
    cout << "Cannot get square root of negative number!" << endl;
    return 1;
  }

  // Checks if the stack has enough values.
  if ( stack.IsEmpty() ) {
    cout << "Not enough values in the stack!" << endl;
    return 1;
  }

  double temp = stack.Pop();
  double out = sqrt(temp);

  stack.Push( out );
}


int duplicate(Stack &stack) {
  // Checks if the stack has enough values.
  if ( stack.IsEmpty() ) {
    cout << "Not enough values in the stack!" << endl;
    return 1;
  }

  double temp = stack.Pop();

  stack.Push( temp );
  stack.Push( temp );
}


int swap(Stack &stack) {
  double temp = stack.Pop();

  // Checks if the stack has enough values.
  if ( stack.IsEmpty() ) {
    cout << "Not enough values in the stack!" << endl;
    if (temp) stack.Push(temp);
    return 1;
  }

  
  double temp2 = stack.Pop();

  // Swaps the top two values
  stack.Push( temp );
  stack.Push( temp2 );
}


int printstack(Stack &stack) {
  // Prints the stack
  if ( stack.IsEmpty() ) {
    cout << "Stack is empty" << endl;
  } else {
    cout << "Stack contents: " << stack.PrintStack() << endl;
  }
}
