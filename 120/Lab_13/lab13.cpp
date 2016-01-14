//Name : Alex McNurlin
//Class: CS120-04
//Lab  : Lab 13
//Date : Tue Dec  1 12:36:23 PST 2015
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;



struct robot {
  public: 
    char type;
    int quadrant;
    int id;
    int num_deployments;
    char manufacturer[64];
    int status; // 0 for in holding, 1 for deployed
    robot *next;
    robot(){};
    robot(int RobotNumber, char RobotType, char* RobotManufacturer) {
      type = RobotType;
      quadrant = 0;
      id = RobotNumber;
      num_deployments = 0;
      strcpy( manufacturer, RobotManufacturer );
      next = NULL;
    };
};



void add(robot*,int,char,char*);
int dispatch(robot*,char,int);
int retrieve(robot*,char,int);
int info(robot*,robot*,int);
int count_hold(robot*);
int count_dep(robot*);



int main() {
  robot *scout_list = NULL, *miner_list = NULL;

  // Opening File
  ifstream somefile;
  string filename;
  cout << "Please enter file to load data from: ";
  cin >> filename;
  cout << endl;
  somefile.open(filename.c_str());
  if (somefile.fail()) {
    cout << "Error opening file" << endl << "Exiting..." << endl;
    exit(1);
  }


  // Reading File
  int rnum; char rtype; char rman[64];
  while (somefile >> rnum >> rtype >> rman) {
    switch(rtype) {
      case 'S':
        if (scout_list == NULL) {
          scout_list = new robot(rnum, rtype, rman);
          break;
        }
        add(scout_list, rnum, rtype, rman);
        break;
      case 'M':
        if (miner_list == NULL) {
          miner_list = new robot(rnum, rtype, rman);
          break;
        }
        add(miner_list, rnum, rtype, rman);
        break;
    }
  }
  cout << filename << " loaded" << endl;


  // Peinding command
  cout << "Please enter a command" << endl;
  char c; int arg;


  // Handling inputs
  while (1) { 
    cin.clear();
    fflush(stdin);
    cin >> c;
    switch (c){
      case 'D':                                        // Dispach Scout
        cin >> arg;
        if (!cin) {
          cout << "invalid command" << endl;
          break;
        }
        if (arg > 4 | arg < 1) {
          cout << "Invalid quadrant number" << endl;
          break;
        }
        dispatch(scout_list, 'S', arg);
        break;

      case 'd':                                        // Dispach Miner
        cin >> arg;
        if (!cin) {
          cout << "invalid command" << endl;
          break;
        }
        if (arg > 4 | arg < 1) {
          cout << "Invalid quadrant number" << endl;
          break;
        }
        dispatch(miner_list, 'M', arg);
        break;

      case 'R':                                        // Retrieve Scout
        cin >> arg;
        if (!cin) {
          cout << "invalid command" << endl;
          break;
        }
        retrieve(scout_list, 'S', arg);
        break;

      case 'r':                                        // Retrieve Miner
        cin >> arg;
        if (!cin) {
          cout << "invalid command" << endl;
          break;
        }
        retrieve(miner_list, 'M', arg);
        break;

      case '?':                                        // Get info on robot
        cin >> arg;
        if (!cin) {
          cout << "invalid command" << endl;
          break;
        }
        info(scout_list,miner_list,arg);
        break;

      case 'q':                                        // Exit program
        cout << "Exiting..." << endl;
        exit(0);

      case 'm':                                        // # of deployed miners
        count_dep(miner_list);
        break;

      case 'M':                                        // # of miners in holding
        count_hold(miner_list);
        break;

      case 's':
        count_dep(scout_list);
        break;

      case 'S':
        count_hold(scout_list);
        break;

      default:                                         // Unrecognized command
        cout << "invalid command" << endl;
        break;
    }
  }



  return 0;
}




void add(robot *robots, int RobotNumber, char RobotType, char* RobotManufacturer) {
  robot *r;
  r = robots;
  while (r->next != NULL) {
    r = r->next;
  }

  r->next = new robot(RobotNumber, RobotType, RobotManufacturer);
}



int dispatch(robot *robots, char type, int quadrant) {
  robot *r;
  r = robots;

  while (r->next != NULL) {
    if (r->type == type && r->status == 0) {
      r->status = 1;
      r->num_deployments += 1;
      r->quadrant = quadrant;
      cout << "Robot " << r->id << " deployed to quadrant " << r->quadrant << "." << endl;
      return 0;
    }

    r = r->next;
  }
  switch(type) {
    case 'S':
      cout << "There are no scouts to fufill your request" << endl;
      break;
    case 'M':
      cout << "There are no miners to fufill your request" << endl;
      break;
  }
}



int retrieve(robot *robots, char type, int id) {
  robot *r;
  r = robots;

  while (r->next != NULL) {
    if (r->type == type && r->id == id && r->status == 1) {
      r->status = 0;
      cout << "Robot " << r->id << " retrieved from quadrant " << r->quadrant << "." << endl;
      return 0;
    } else if (r->type == type && r->id == id && r-> status == 0) {
      switch(type) {
        case 'S':
          cout << "Scout number " << id << " is not deployed"  << endl;
          break;
        case 'M':
          cout << "Miner number " << id << " is not deployed"  << endl;
          break;
      }
      return 1;
    }

    r = r->next;
  }
  switch(type) {
    case 'S':
      cout << "Scout number " << id << " is invalid"  << endl;
      break;
    case 'M':
      cout << "Miner number " << id << " is invalid"  << endl;
      break;
  }
}



int info(robot* scout_list, robot* miner_list, int id) {
  robot *r;

  r = scout_list;
  string status;
  while (r->next != NULL) {
    if (r->id == id) {

      if (r->status) {
        status = "Deployed in quadrant ";
      } else {
        status = "In scout holding bay";
      }
      string type;
      type = "Scout";

     cout << "Robot " << r->id << endl;
       cout << "\ttype: " << type << endl;
       cout << "\tstatus: " << status;
       if (r->status) {
         cout << r->quadrant;
       }
       cout << endl;
       cout << "\tnum-deployments: " << r->num_deployments << endl;
       cout << "\tmanufacturer: " << r->manufacturer << endl;
    return 0;
    }
    r = r->next;
  }

  r = miner_list;
  while (r->next != NULL) {
    if (r->id == id) {

      if (r->status) {
        status = "Deployed in quadrant ";
      } else {
        status = "In miner holding bay";
      }

      string type;
      type = "Miner";

     cout << "Robot " << r->id << endl;
       cout << "\ttype: " << type << endl;
       cout << "\tstatus: " << status;
       if (r->status) {
         cout << r->quadrant;
       }
       cout << endl;
       cout << "\tnum-deployments: " << r->num_deployments << endl;
       cout << "\tmanufacturer: " << r->manufacturer << endl;
    return 0;
    }
    r = r->next;
  }
  
 cout << "Invalid robot number " << id << endl;
}



int count_dep(robot* robots) {
  robot *r;
  r=robots;
  int i=0;
  for(; r->next!=NULL; r=r->next) {
    if( r->status ) {
      i++;
    }
  }

  switch(r->type) {
    case 'S':
      cout << "Scouts deployed: " << i << endl;
      break;
    case 'M':
      cout << "Miners deployed: " << i << endl;
      break;
  }
  return 0;
}



int count_hold(robot* robots) {
  robot *r;
  r=robots;
  int i=0;
  for(; r->next!=NULL; r=r->next) {
    if( !r->status ) {
      i++;
    }
  }

  switch(r->type) {
    case 'S':
      cout << "Scouts in holding bay: " << i << endl;
      break;
    case 'M':
      cout << "Miners in holding bay: " << i << endl;
      break;
  }
  return 0;
}
