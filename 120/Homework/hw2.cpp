// Author: Alex McNurlin
// Date: Fri Sep 18 16:45:56 PDT 2015
// Class: CS120-04
// Homework 2


#include <iostream>
#include <iomanip>
using namespace std;

int main() {
  // Getting user input
  float inner_diameter, outer_diameter, thickness, density, material_cost;
  int quantity;
  cout << "Inner diameter (in centimeters): ";
  cin >> inner_diameter;
  cout << "Outer diameter (in centimeters): ";
  cin >> outer_diameter;
  cout << "Thickness (in centimeters): ";
  cin >> thickness;
  cout << "Material density (in grams per cubic centimeter): ";
  cin >> density;
  cout << "Material cost (in cents per gram): ";
  cin >> material_cost;
  cout << "Quantity in current batch: ";
  cin >> quantity;

  // Validating inputs
  if (!(inner_diameter > 0) || !(outer_diameter > 0) || !(thickness > 0) || !(density > 0) || !(material_cost > 0) || !(quantity > 0)) {
    cout << "\nYour inputs are invalid! Please enter valid floating point numbers!\nexiting..." << endl;
    return 0;
  }
  // Calculating weight
  float surface_area, weight;
  float pi = 3.14159;
  surface_area = (pi * (outer_diameter*outer_diameter/4) - pi * (inner_diameter*inner_diameter/4));
  weight = surface_area * thickness * density * quantity;

  // Calculating cost
  float cost;
  cost = weight * material_cost / 100;

  cout << "Expected weight: " << weight << " grams" << endl;
   
  // Sets decimal precision for dollars
  cout.precision(2);
  cout.setf(ios::fixed);
  cout << "Expected cost: $"  << cost << endl;

  return 0;
}
