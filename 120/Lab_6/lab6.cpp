//Name: Alex McNurlin
//Lab: CS120-04
//Lab 6
//Date: Mon Oct 12 18:29:10 PDT 2015
#include <cstdlib>    // This is used for the exit(0) function
#include <iostream>   // Standard iostream
#include <fstream>    // To read files
#include <sstream>    // Usage explained in the read_data_from_file function
using namespace std;

int read_data_from_file(ifstream&);
double calc_charge(int,int,int,int,char); 
int print_data(int,int,int,char,double,int,double);
int enter_filename();

int schedule, energy_use, demand_amount, read_type;
int customer_number;
char discount_char;
double discount_amt, cost, total_cost;
char file_to_read[128], filename[128]; // Character strings with arbitrarily large sizes
char write_to_file;
bool fout;
ofstream file_to_write;


int main() {
  ifstream somefile;
  cout << "Enter filename to read from: ";
  cin >> file_to_read;
  cout << endl << "Would you like to write program output to file? (Y/n)";
  cin >> write_to_file;
  switch(write_to_file) {
      case 'y':
      case 'Y': 
        fout = 1;
        break;
      case 'n':
      case 'N':
        fout = 0;
        break;
  }
  if (fout) {
    enter_filename();
  }

  somefile.open(file_to_read);
  if (somefile.fail()) {
    cout << "Error reading file '" << file_to_read << "'" << endl << "Exiting...";
    exit(1);
  }
  while (read_data_from_file(somefile)) {
    cost = calc_charge(customer_number, schedule, energy_use, demand_amount, discount_char);
    print_data(customer_number, schedule, energy_use, discount_char, discount_amt, demand_amount, cost);
    cout << "Cost for this customer: $" << cost << endl;
    if(fout){file_to_write << "Cost for this customer: $" << cost << endl;};
    total_cost = total_cost + cost;
  }
  cout << "Total cost is: " << total_cost << endl;
  if(fout){file_to_write << "Total cost is: " << total_cost << endl;};
  somefile.close();
  return 0;
}

int enter_filename() {
  cout << endl << "Enter filename to write to: ";
  if(fout){file_to_write << endl << "Enter filename to write to: ";};
  cin >> filename;
  file_to_write.open(filename);
  if (file_to_write.fail()) {
    cout << "Could not open file. Please try again" << endl;
    if(fout){file_to_write << "Could not open file. Please try again" << endl;};
    enter_filename();
  }
}

int read_data_from_input() {
  cout << "Enter Customer Number: ";
  if(fout){file_to_write << "Enter Customer Number: ";};
  cin >> customer_number;
  if (customer_number == 000000) {
    cout << "Exiting...\n";
    if(fout){file_to_write << "Exiting...\n";};
    return 0;
  }
  cout << "Enter Schedule Number: ";
  if(fout){file_to_write << "Enter Schedule Number: ";};
  cin >> schedule;
  cout << "Enter Energy Usage: ";
  if(fout){file_to_write << "Enter Energy Usage: ";};
  cin >> energy_use;
  cout << "Enter Demand Amount: ";
  if(fout){file_to_write << "Enter Demand Amount: ";};
  cin >> demand_amount;
  cout << "Does this customer receive a discount? (Y/N)";
  if(fout){file_to_write << "Does this customer receive a discount? (Y/N)";};
  cin >> discount_char;
  return 1;
}


int read_data_from_file(ifstream& infile) {
  // I couldn't figure out how to read line by line using fstream. Various Google
  // searches suggested using the stringstream class and the getline() function
  // to parse lines one by one, rather using the '>>' operator on an instance of 
  // ifstream
  string next_line;
  getline(infile,next_line);
  stringstream linestream(next_line);

  linestream >> customer_number;
  if (customer_number == 000000) {
    cout << "Customer number 000000 reached" << endl;
    if(fout){file_to_write << "Customer number 000000 reached" << endl;};
    return 0;
  }
  linestream >> schedule;
  linestream >> energy_use;
  linestream >> demand_amount;
  linestream >> discount_char;
  return 1;
}


double calc_charge(int customer_number, int schedule, int energy_use, int demand_amount, char discount_char) {
  int basic;
  double energy_rate; // Energy rate initial, and energy rate over
  double demand_rate; // Demand rate initial, and Demand rate over
  float voltage_discount;
  switch (schedule) {
    case 1:
      basic = 3;
      if (energy_use < 600) {
        energy_rate = .05255; // First 600 kWh
      } else if (energy_use > 600) {
        energy_rate = .06156; // Over 600 kWh
      }
      demand_rate = 0;
      voltage_discount = 0;
      break;
    case 11:
      basic = 5;
        energy_rate = .07971;
      if (demand_amount < 20) {
        demand_rate = 0;      // Under 20 kW
      } else if (demand_amount > 20) {
        demand_rate = 3.5;    // Over 20 kW
      }
      voltage_discount = 0;
      break;
    case 12:
      basic = 6;
      energy_rate = .07719; 
      if (demand_amount < 20) {
        demand_rate = 0;      // First 20 kW
      } else if (demand_amount > 20) {
        demand_rate = 3.0;    // Over 20 kW
      }
      if (discount_char == 'Y') {
        voltage_discount = .2;
      } else {
        voltage_discount = 0;
      }
      break;
    case 21:
      basic = 0;
      energy_rate = .05022;
      if (demand_amount <= 50) {
        demand_rate = 225/demand_amount; // Up to 50 kW (fixed rate)
                                         // This will be multiplied by demand 
                                         // amount later
      } else if (demand_amount > 50) {
        demand_rate = 2.75;    // Over 50 kW (per kW)
      }
      if (discount_char == 'Y') {
        voltage_discount = .2;
      } else {
        voltage_discount = 0;
      }
      break;
  }
  //double cost;
  cost = basic + energy_rate * energy_use + (demand_rate * demand_amount) * (1 + voltage_discount);
  return cost;
}


int print_data(int customer_number,int schedule,int energy_use,char discount_char,double discount_amt,int demand_amount,double cost) {
  cout << "Customer Number: " << customer_number << endl;
  if(fout){file_to_write << "Customer Number: " << customer_number << endl;};
  cout << "Schedule: " << schedule << endl;
  if(fout){file_to_write << "Schedule: " << schedule << endl;};
  cout << "Energy Use: " << energy_use << endl;
  if(fout){file_to_write << "Energy Use: " << energy_use << endl;};
  cout << "Demand Amount: " << demand_amount << endl;
  if(fout){file_to_write << "Demand Amount: " << demand_amount << endl;};
  cout << "Discount: " << discount_char << endl;
  if(fout){file_to_write << "Discount: " << discount_char << endl;};
  if (discount_char == 'Y') {
    cout << "Discount Amount: " << discount_amt << endl;
  if(fout){file_to_write << "Discount Amount: " << discount_amt << endl;};
  }
}
