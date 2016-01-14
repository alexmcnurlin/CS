#include <cstdlib>
class InVal {
  public:
    void PrintAsBase(int base);
    InVal(){};
    InVal(int base_10) {
      value = base_10;
    };
  public:
    int value;
};
