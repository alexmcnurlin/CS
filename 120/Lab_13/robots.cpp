#include "robots.h"

void robot::add(int RobotNumber, char RobotType, char* RobotManufacturer) {
  type = RobotType;
  id = RobotNumber;
  strcpy( manufacturer, RobotManufacturer );
  next = NULL;
}
