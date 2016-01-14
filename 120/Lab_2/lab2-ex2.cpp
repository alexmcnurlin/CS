#include <iostream>
#include <cmath>

using namespace std;

int main() {
	float a, b, c;
	const float pi = 3.14159;
	cout << "Enter diameter a for the ellipse: " << flush;
	cin >> a;
	cout << "Enter diameter b for the ellipse: " << flush;
	cin >> b;

	c = 2 * pi * sqrt( (a*a + b*b)/2 );
	cout << "The circumference of the ellipse is: " << c << endl;
}
