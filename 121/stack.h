/*
 * stack.h
 */

class Stack {
  public:
    Stack() {
      top = NULL;
    }

    void Push( char c  );
    char Pop();

    bool IsEmpty();

    void Print();
  private:
    struct stackNode {
      char info;
      struct stackNode* next;
    };

    typedef struct stackNode StackNode;
    typedef StackNode *StackNodePtr;

    StackNodePtr top;
};
