#include <iostream>
using namespace std;

int main()
{
	int x,y,z,r;
	cout << "Current Year:\n";
	cin >> x;
	cout << "Your Age:" << "\n" ;
	cin >> y;
	cout << "Another Year:" << "\n";
	cin >> z;
	cout << "Your age:" << "\n";
	r = y + z - x;
	cout << r;
	cout << "\n";
}