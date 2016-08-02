#include <iostream>
using namespace std;
#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "link.h"
#include <assert.h>

class Stack {
  public:
    Stack();
    ~Stack();

    void Push(int n);
    int Pop();
    int IsEmpty();
    void Print();

  private:
    LinkedList topPtr;
};

Stack::Stack() {
}

Stack::~Stack() {
  while( !IsEmpty()  ) {
    int n = topPtr.FirstNode();
    topPtr.DeleteNode( n  );
  }
}

int main() {
}
