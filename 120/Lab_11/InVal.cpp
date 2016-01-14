#include "InVal.h"
#include <iostream>
using namespace std;

void InVal::PrintAsBase(int baseout) { // converts from basein to baseout
  int temp_value = value;
  char digits[128];
  for (int i=0; i<128; i++) { digits[i] = -1; } // sets the elements of the array equal to -1
  for (int i=0; temp_value>0; i++){
    digits[i]=temp_value%baseout;
    temp_value/=baseout;
  }

  cout << "     ";
  for (int i=127; i>=0; i--) { // Print out the value of the converted base
    char temp;
    if (digits[i] != -1) {
      if (digits[i] > 9) {
        temp = 'A'+ digits[i] - 10;
        cout << temp;
      } else {
        temp = '0'+ digits[i];
        cout << temp;
      }
    }
  }
  cout << " (base " << baseout << ")" << endl;
}
