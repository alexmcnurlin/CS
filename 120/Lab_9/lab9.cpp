// Name:  Alex McNurlin
// Date:  Wed Oct 28 17:32:49 PDT 2015
// Class: CS120-04 Lab
// Lab:   Lab 9
#include <iostream>
#include <curses.h>  // include the curses library
#include <stdlib.h>
using namespace std;

const int NUMCOLS = 70;
const int NUMROWS = 20;

void setup(); // function prototype
void move_robot(char,char); // function to move the robot
int is_valid(int,int);

class Robot {
  private:
    int name;
    int last_position[2];
  public:
    int position[2];
    int Rmove(char); // The name is Rmove to avoid conflict with the cursese function
    Robot(int x,int y){
      position[0] = x;
      position[1] = y;
    };
};

int Robot::Rmove(char d) {
  switch(d) {
    case 'n':
    case 'N':
      move(position[0], position[1]);
      if (!is_valid(position[0]-1, position[1])){
        break;
      }
      delch();
      insch(' ');
      position[0] -= 1;
      move(position[0], position[1]);
      delch();
      insch('R');
      break;

    case 'e':
    case 'E':
      move(position[0], position[1]);
      if (!is_valid(position[0], position[1]+1)){
        break;
      }
      delch();
      insch(' ');
      position[1] += 1;
      move(position[0], position[1]);
      delch();
      insch('R');
      break;

    case 's':
    case 'S':
      move(position[0], position[1]);
      if (!is_valid(position[0]+1, position[1])){
        break;
      }
      delch();
      insch(' ');
      position[0] += 1;
      move(position[0], position[1]);
      delch();
      insch('R');
      break;

    case 'w':
    case 'W':
      move(position[0], position[1]);
      if (!is_valid(position[0], position[1]-1)){
        break;
      }
      delch();
      insch(' ');
      position[1] -= 1;
      move(position[0], position[1]);
      delch();
      insch('R');
      break;
  }
  refresh();
}

Robot r_0(1,1);
Robot r_1(1,NUMCOLS-2);
Robot r_2(NUMROWS-2,NUMCOLS-2);
Robot r_3(NUMROWS-2,1);

int main() {
  char c, d;
  WINDOW *wnd;

  //uses curses library function to initialize the curses window
  wnd = initscr();
  // use curses library function to clear the window
  clear();
  // use curses library function to update the window
  refresh();
  // draw room with 4 robots

  setup();
  
  // wait until user presses 'q' key
  while (1) {
    cin >> c;
    if (c== 'q')
      break;
    cin >> d;
    if (d== 'q')
      break;
    move_robot(c,d);
  }
  // use curses library function to free the screen for normal use
  endwin();
}

int is_valid(int x,int y) {
  if (x == 0 || y == NUMCOLS-1 || y == 0 || x == NUMROWS-1 
      || (r_0.position[0] == x
      && r_0.position[1] == y)
      || (r_1.position[0] == x
      && r_1.position[1] == y)
      || (r_2.position[0] == x
      && r_2.position[1] == y)
      || (r_3.position[0] == x
      && r_3.position[1] == y)
     ) {
    return 0;
  } else {
    return 1;
  }
}

void move_robot(char c, char d) {
  switch(c) {
    case '0':
      r_0.Rmove(d);
      break;
    case '1':
      r_1.Rmove(d);
      break;
    case '2':
      r_2.Rmove(d);
      break;
    case '3':
      r_3.Rmove(d);
      break;
    default:
      endwin();
      cout << "Invalid command entered. Exiting..." << endl;
      exit(1);
  }
}

// Draw a 70x20 room containing a robot in each corner
void setup() {
  int i;

  // draw north and south walls
  for (i=0; i<NUMCOLS; i++) {
    move(0,i);
    delch();
    insch('-');
    move(NUMROWS-1, i);
    delch();
    insch('-');
  }

  // draw east and west walls
  for (i=0; i<NUMROWS; i++) {
    move(i, 0);
    delch();
    insch('|');
    move(i, NUMCOLS-1);
    delch();
    insch('|');
  }

  // draw robot 0
  move(1,1);
  delch();
  insch('R');

  // draw robot 1
  move(1,NUMCOLS-2);
  delch();
  insch('R');

  // draw robot 2
  move(NUMROWS-2,NUMCOLS-2);
  delch();
  insch('R');
  
  // draw robot 3
  move(NUMROWS-2,1);
  delch();
  insch('R');

refresh();
}
