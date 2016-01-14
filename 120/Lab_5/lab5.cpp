//Name: Alex McNurlin
//Lab: CS120-04
//Lab 5
//Date: Tue Sep 29 14:30:50 PDT 2015
#include <iostream>
using namespace std;

int read_data();
double calc_charge(int,int,int,int,char); 
int print_data(int,int,int,char,double,int,double);

int customer_number, schedule, energy_use, demand_amount;
char discount_char;
double discount_amt, cost, total_cost;



int main() {
  while (read_data()) {
  cost = calc_charge(customer_number, schedule, energy_use, demand_amount, discount_char);
  print_data(customer_number, schedule, energy_use, discount_char, discount_amt, demand_amount, cost);
  cout << "Cost for this customer: " << cost << endl;
  total_cost = total_cost + cost;
  }
  cout << "Total cost is: " << total_cost << endl;
  return 0;
}


int read_data() {
  cout << "Enter Customer Number: ";
  cin >> customer_number;
  if (customer_number == 000000) {
    cout << "Exiting...\n";
    return 0;
  }
  cout << "Enter Schedule Number: ";
  cin >> schedule;
  cout << "Enter Energy Usage: ";
  cin >> energy_use;
  cout << "Enter Demand Amount: ";
  cin >> demand_amount;
  cout << "Does this customer receive a discount? (Y/N)";
  cin >> discount_char;
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
  cout << "Schedule: " << schedule << endl;
  cout << "Energy Use: " << energy_use << endl;
  cout << "Demand Amount: " << demand_amount << endl;
  cout << "Discount: " << discount_char << endl;
  if (discount_char == 'Y') {
    cout << "Discount Amount: " << discount_amt << endl;
  }
}
