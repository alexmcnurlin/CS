// Name: Alex McNurlin
// Date: Tue Oct 20 13:10:30 PDT 2015
// Lab : CS120-04
// Lab#: Lab 8
#include <curses.h>

using namespace std; // Include the curses library

const int maxx = 40; // maximum size of the room
const int maxy = 20;

void setup(char[][maxy], int x, int y); // room setup
void print(char room[maxx][maxy]);// print room to screen

int main() {


  int c;
  WINDOW *wnd;
  char room[maxx][maxy];  // stores the room
  int x = maxx/2, y = maxy/2;

  wnd = initscr();        // 'initializes' the window
  clear();                // clears the window
  refresh();              // reprints the window

  setup(room,x,y);        // setup room with the robot

  print(room);            // write this function!!

  while ((c = getch()) != 'q'); // wait for user to press 'q' key

  endwin();               // frees the screen for normal use


}


/* Sets up the room, adding walls, and the robot */
void setup(char r[][maxy], int x, int y) {


  for(int i = 0; i < maxx; i++) {
    for(int j = 0; j < maxy; j++) {
      r[i][j] = ' ';      // empty the room
    }
  }

  for(int i = 0; i < maxy; i++) {
    r[0][i] = '|';        // left wall
    r[maxx-1][i] = '|';   // right wall
  }

  for(int i = 0; i < maxx; i++) {
    r[i][0] = '-';        // top wall
    r[i][maxy-1] = '-';   // bottom wall
  }

  r[x][y] = 'R'; // place the robot



}


void print(char room[maxx][maxy]) {
  for (int c=0; c < maxx; c++) {
    for (int r=0; r < maxy; r++) {
      move(r,c);
      insch(room[c][r]);
    }
  }
  refresh();
}
