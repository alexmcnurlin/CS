// Name : Alex McNurlin
// Class: CS120-04
// Lab  : Lab 11
// Date : Tue Nov 10 12:25:27 PST 2015

#include <iostream>
#include "InVal.h"
#include <cstdlib>
#include <string>
#include <cmath>
using namespace std;

void read_int(void);
int  to_dec(int,int);
int toBase10(int[],int,int);

int main() {
  read_int();
  return 0;
}



void read_int(void) {
  int outbase[128];
  
  int inbase;
  string inval;

  cin >> inbase;
  if (inbase < 2 || inbase > 16) {
    cout << "Invalid inbase " << inbase << ".\nprogram terminating.";
    exit(1);
  }

  cin >> inval;
  int digits[inval.length()];
  for(int i=0; i<inval.length(); i++) {
    if(inval[i] >= 'A') {                   // This makes an array of ints 
                                            // representing each digit of the input
      digits[i] = ((inval[i]-'A') + 10);
    } else {
      digits[i] = inval[i] - '0';
    }
    if(digits[i] >= inbase) { // the `-'0'` is to convert the char to its
                                 // respective int.
      cout << "Invalid digit " << inval[i] << ".\nprogram terminating." << endl;
      exit(1);
    }
  }
  int digits_length=sizeof(digits)/sizeof(digits[0]);

  InVal input = InVal(toBase10(digits,digits_length,inbase));

  
  for (int i=0; i<128; i++) {
    outbase[i]=0;
    cin >> outbase[i];
    if (outbase[i] < 2 || outbase[i] > 16) {
      //outbase[i] = 0;
      break;
    }
  }

  cout << inval << " (base " << inbase << ") is..." << endl;
  for (int i=0; outbase[i]!=0; i++) {
    input.PrintAsBase(outbase[i]);
  }
}




int toBase10(int digits[],int digits_length,int base) {
  char temp;
  int output=0;
  for (int i=1; i<=digits_length; i++) {
    temp = digits[digits_length-i];
    output+=(temp*pow(base,i-1));
  }
  return output;
}
