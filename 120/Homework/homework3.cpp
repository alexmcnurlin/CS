// Name: Alex McNurlin
// Class: CS120-04
// Date: Mon Oct  5 19:14:58 PDT 2015

#include <iostream>
#include <iomanip>
using namespace std;

void prompt_command();

float running_sum = 0;
bool loop_continue = true;

int main() {
  // Getting user input
  float inner_diameter, outer_diameter, thickness, density, material_cost, surface_area, weight, cost;
  const float pi = 3.14159;
  int quantity;
  char command;

  while (loop_continue){
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
    cout << endl;

    // Validating inputs
    if (!(inner_diameter > 0) || !(outer_diameter > 0) || !(thickness > 0) || !(density > 0) || !(material_cost > 0) || !(quantity > 0)) {
      cout << "\nYour inputs are invalid! Please enter valid floating point numbers!" << endl;
      prompt_command();
    }
    // Calculating weight
    surface_area = (pi * (outer_diameter*outer_diameter/4) - pi * (inner_diameter*inner_diameter/4));
    weight = surface_area * thickness * density * quantity;

    // Calculating cost
    cost = weight * material_cost / 100;

    cout << "Expected weight: " << weight << " grams" << endl;
     
    // Sets decimal precision for dollars
    cout.precision(2);
    cout.setf(ios::fixed);
    cout << "Expected cost: $"  << cost << endl;
    running_sum += cost;
    cout << "Expected total: $" << cost << endl;

    prompt_command();
  }

  return 0;
}


void prompt_command() {
  char command;
  cout << endl << "Please enter a command:" << endl;
  cout << "    B: Compute the expected weight and cost of another batch of washers" << endl;
  cout << "    ?: Display the total cost of all washers computed so far in the current session" << endl;
  cout << "    X: Exit the program" << endl;
  cin >> command;

  switch(command){
    case 'B':
    case 'b':
      loop_continue = true;
      break;
    case '?':
      cout << "The running total is: " << running_sum;
      prompt_command();
      break;
    case 'X':
    case 'x':
      loop_continue = false;
      cout << "The total will be: $" << running_sum << endl << "exiting...";
      break;
    default:
      cout << "Invalid command, please try again" << endl;
      prompt_command();
  }
}
