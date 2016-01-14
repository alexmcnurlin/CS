//Name : Alex McNurlin
//Date : Tue Sep 22 13:13:27 PDT 2015
//Class: CS120-4
//Lab  : 4

#include <iostream>
using namespace std;

int main() {
 cout << "\t0\t1\t2\t3\t4\t5\t6\t7\t8\t9" << endl;
  for (int i=40; i<=110; i+=10) {
    cout << i;
    for (int j=0; j<10; j++) {
      char k = j + i;
      cout << "\t" << k;
    }
    cout << endl;
  }

  return 0;
}
