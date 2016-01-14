// Name: Alex McNurlin
// Class: CS120-04
// Lab:   7
// Date: Tue Oct 13 12:31:15 PDT 2015
#include <iostream>
using namespace std;

int main() {
  int nums[10];
  float sum=0;
  float ave;
  cout << "Enter 10 integers for the array: " << endl;
  for(int i=0; i<10; i++) {
    cin >> nums[i];
  }
  for(int i=0; i<10; i++) {
    cout << nums[i] << " ";
    sum += nums[i];
  }
  ave = sum/10;

  cout << endl << "The sum of the numbers is: " << sum << endl;
  cout << "The average of the numbers is: " << ave << endl;
}
