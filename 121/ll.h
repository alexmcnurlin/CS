class ll {
  public:
    ll();
    ll(int n);

    int  getNode();
    void addNode(int n);
    void deleteNode();
    void printNode();
    bool IsEmpty();


  private:
    struct node {
      int value;
      node *next;
      node *prev;
    };

    typedef struct node * nodeptr;
    nodeptr start;
    nodeptr end;
    int count; // The number of nodes in the list

};

typedef ll LL;
