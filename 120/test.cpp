#include <iostream>
#include <string>
using namespace std;

void hello(char*);


int main() {
  char world[] = "Hello World";
  hello(world);

  return 0;
}

void hello(char* world) {
  cout << world << endl;
}
