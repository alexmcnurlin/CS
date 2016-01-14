#include <string.h>
struct robot {
  private: 
    char type;
    int quadrant;
    int id;
    int num_deployments;
    char manufacturer[64];
    robot *next;
  public:
    robot(){};
    robot(int RobotNumber, char RobotType, char* RobotManufacturer) {
      type = RobotType;
      id = RobotNumber;
      strcpy( manufacturer, RobotManufacturer );
      next = NULL;
    }

};
