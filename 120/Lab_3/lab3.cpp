#include <iostream>
#include <cmath>

using namespace std;

int main() {
	float a, b, c;
	const float pi = 3.14159;
	cout << "Enter radius a for the ellipse: " << flush;
	cin >> a;
	cout << "Enter radius b for the ellipse: " << flush;
	cin >> b;

  // Validation
  if (!(a > 0) || !(b > 0)) {
    cout << "\nThe inputs are invalid. Please make sure they're both positive numbers. \nexiting...\n\n" << endl;
    return 0;
  }
  
  if (a == b) {
    cout << "Your ellipse is a circle!" << endl;
    c = 2 * pi * sqrt( (a*a + b*b)/2 );
    cout << "The circumference of the circle is: " << c << "\n\n";
    return 0;
  }

	c = 2 * pi * sqrt( (a*a + b*b)/2 );
	cout << "The circumference of the ellipse is: " << c << "\n\n";
  return 0;
}
