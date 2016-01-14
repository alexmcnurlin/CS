// Name : Alex McNurlin
// Class: CS120-4
// Lab  : Lab 10
// Date : Tue Nov  3 12:29:41 PST 2015
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
using namespace std;

class studentype {
  private:
    char char_grade;
    float id,t1,t2,t3,num_grade;

  public:
    studentype(){};
    void add_grades(int read_id,float read_t1,float read_t2,float read_t3){
      id = read_id;
      t1 = read_t1;
      t2 = read_t2;
      t3 = read_t3;
    };
    void PrintGrade(float,float);  // Calculates and prints the letter grade
    float mean();         // Figures and returns the average number grade
    int is_null();      // Returns true if the student id is 0, IE it doesn't exist
};
const int max_stud = 128;
studentype students[max_stud];

void studentype::PrintGrade(float mean, float std_dev) {  // Calculates and prints the letter grade
  if (num_grade > (mean + 1.5*std_dev)) {
    cout << "A" << endl;
  } else if (num_grade > (mean + 0.5*std_dev)) {
    cout << "B" << endl;
  } else if (num_grade > (mean - 0.5*std_dev)) {
    cout << "C" << endl;
  } else if (num_grade > (mean - 1.5*std_dev)) {
    cout << "D" << endl;
  } else {
    cout << "F" << endl;
  }
}

float studentype::mean() {  // Figures and returns the average number grade
  num_grade = (t1+t2+t3)/3;
  return num_grade;
}

int studentype::is_null() {  // Returns true if the student id is 0
  if (id==0) {
    return 1;
  } else {
    return 0;
  }
}

void read_data(ifstream& f);
float find_mean();
float find_std_dev(float,int);
int num_stud;


//#############################################################################
int main() {
  char fstring[128];  // The file to open
  ifstream f;         // The file object
  float mean, std_dev;

  cout << "Please enter a file to input from: ";
  cin >> fstring;
  f.open(fstring);
  if (f.fail()) {
    cout << "Error reading file '" << fstring << "'" << endl << "Exiting...";
    exit(1);
  }
  read_data(f);
  mean = find_mean();
  std_dev = find_std_dev(mean,num_stud);
  for (int i=0; i<num_stud; i++) {
    students[i].PrintGrade(mean, std_dev);
  }
  
  return 0;
}



void read_data(ifstream& f) {
  int id;
  float t1,t2,t3;
  for (int i=0;i<128;i++) {
    id = 0;
    f >> id;
    f >> t1;
    f >> t2;
    f >> t3;
    if (id == 0) {          // Checks if the id wasn't assigned. AKA the file is done reading.
      break;
    }

    students[i].add_grades(id,t1,t2,t3);
  }
}

float find_mean() {
  float sum=0;
  for (int i=0;i<max_stud;i++) {
    
    sum += students[i].mean();
    if (students[i].is_null()) {
      num_stud = i;
      break;
    }
  }
  return sum/num_stud;
}

float find_std_dev(float mean, int num_stud) {
  double diff,sum=0,dev=0;
  for (int i=0;i<num_stud;i++) {
    diff = students[i].mean() - mean;
    sum += diff*diff;
  }
  dev = sqrt(sum/num_stud);   
  return dev;
} 
