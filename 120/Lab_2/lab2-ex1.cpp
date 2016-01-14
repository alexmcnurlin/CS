#include <iostream>

using namespace std;

int main() {
	float x, y;
	float sum = 0, average;
	cout << "Please enter a number: " << flush;
	cin >> x;
	cout << "Please enter another number: " << flush;
	cin >> y; 
	sum = x + y;
	cout << "The sum of " << x << " plus " << y;
	cout << " is " << sum << ".";

	average = sum/2;
	cout << "The average of your numbers is ";
	cout << average << "." << endl;
	
	return 0;
}
