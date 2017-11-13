#include <iostream>
#include <iomanip>
using namespace std;
int judgedigit(double a);

int main()
{
	char a; double b, c, d, k = 0; int t,cnt=0;
	cout << "RMBtoUSD(R)"<<endl;
	cout << "USDtoRMB(U)"<<endl;
	cout << "Choose Your Conversion :"<<endl;
	cin >> a;
	if (a == 'R')
	{
		cout << "Amount:\n";
		cin >> b;
		cout << "Precision:"<<endl;
		cin >> c;
		d = b / 6.20350;
		while (k <= d)
		{
			k += c/2;
			cnt++;
		}
		if (cnt % 2 == 1)
		{
			d = k - c / 2;
		}
		else
		{
			d = k;
		}
		t = judgedigit(c);
		std::cout.precision(t);
		std::cout << std::fixed;
		std::cout << "USD:" << d;
	}
	if (a == 'U')
	{
		cout << "Amount:\n";
		cin >> b;
		cout << "Precision:\n";
		cin >> c;
		d = b * 6.20350;
		while (k <= d)
		{
			k += c / 2;
			cnt++;
		}
		if (cnt % 2 == 1)
		{
			d = k - c / 2;
		}
		else
		{
			d = k;
		}
		t = judgedigit(c);
		std::cout.precision(t);
		std::cout << std::fixed;
		std::cout << "RMB:" << d;
	}
}
int judgedigit(double a)
{
	int r;
	if (a>=0.00001 && a < 0.0001)
		r = 5;
	if (0.0001 <= a && a < 0.001)
		r = 4;
	if (0.001 <= a && a < 0.01)
		r = 3;
	if (0.01 <= a && a < 0.1)
		r = 2;
	if (0.1 <= a && a < 1)
		r = 1;
	return r;
}