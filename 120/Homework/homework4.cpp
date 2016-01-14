// Name:        Alex McNurlin
// Section:     CS120-04
// Assignment:  Homework 4
// Date:        Mon Oct 12 22:41:35 PDT 2015
#include <iostream>
#include <cstdlib>
using namespace std;

int enter_command();
int hunt_for_zombies();

char command;
int low, high;

int main() {
  while (true) {
    enter_command();
  }

  return 0;
}

int enter_command() {
  cout << "Enter a command:\n\tZ: Hunt for zombie numbers\n\tX: Exit the program" << endl;
  cin >> command;
  switch (command) {
    case 'Z':
      hunt_for_zombies();
      break;
    case 'X':
      cout << "Exiting...";
      exit(0);
      break;
    default:
      cout << "Unrecognized command." << endl;
      enter_command();
  }
  
}

int hunt_for_zombies() {
  int a,b,c,d,e;
  cout << "Enter search range: "; 
  cin >> low; // An infinite loop is created if you enter a char. I'll try and resubmit once I think of a fix.
  cin >> high;// An infinite loop is created if you enter a char. I'll try and resubmit once I think of a fix.
  if (!(low < high) || high > 10000 || low <= 0) {
    cout << "Invalid search range specified." << endl;
    hunt_for_zombies();
    return 0;
  }
  cout << "searching range [" << low << "," << high << "]..." << endl;
  
  for (int i = low; i <= high; i++) {
    int temp;
    temp = i;
    int j = 0;
    do {
      a = temp % 10;
      b = temp / 10 % 10;
      c = temp / 100 % 10;
      d = temp / 1000 % 10;
      e = temp / 10000 % 10;

      temp = a*a + b*b + c*c + d*d + e*e;

      if (temp == 1) {
        cout << i << " is a zombie order " << j << endl;
        break;
      } else if (j > 100) {
        break;
      }
      j++;
    } while (true); // The loop should break on its own when temp is equal to
                    // 1 or j is over 100
  }
  return 0;
}

