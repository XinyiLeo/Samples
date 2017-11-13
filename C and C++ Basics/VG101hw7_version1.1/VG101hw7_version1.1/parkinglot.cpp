#include <iostream>
#include <string>
#include <iomanip>
#include <time.h>
#include "price.h"
#include "vehicletime.h"
using namespace std;
#define MAX 10000 //simulate at most 10000 vehicles

/*This program allows users to input the number of floor and how many vans(a), cars(b), motorbikes(c) and bicycles(d) are there in  each floor*/

class Vehicle{
public: virtual void printtype(){cout<<"Vehicle type:"<<endl;}
};
class Van:public Vehicle{
public:void printtype() {cout<<"Vehicle type: Van"<<endl;}
};
class Car:public Vehicle{
public:void printtype() {cout<<"Vehicle type: Car"<<endl;}
};
class Motor:public Vehicle{
public:void printtype() {cout<<"Vehicle type: Motorbike"<<endl;}
};
class Bike:public Vehicle{
public:void printtype() {cout<<"Vehicle type: Bicycle"<<endl;}
};



int main(){
	void arrivalticket(int ayr,int amon,int ad,int ahr,int amin,int cartype);
	void departureticket(int ayr,int amon,int ad,int ahr,int amin,int dyr,int dmon,int dd,int dhr,int dmin,int cartype);
	int f, i, j, ahr[MAX] = { 0 }, amin[MAX] = { 0 }, dhr[MAX] = { 0 }, dmin[MAX] = { 0 }, carnum;
	int	cartype[MAX] = { 0 }, platenum[MAX][6] = { 0 },aminute[MAX],dminute[MAX];
	char plateletter[MAX][6] = { 0 };
	int ayr=2014,dyr=2014,amon=7,dmon=7,ad=27,dd=27; //for the convenience of programming, we simply simulate the whole procees in one day, i.e. 2014/7/27
	int carperhr,rushhrcar;
	/* 
	string *s = new string[20];
	s[0] = "first";
	s[1] = "second";
	s[2] = "third";
	s[3] = "fourth";
	s[4] = "fifth";
	s[5] = "sixth";
	s[6] = "seventh";
	s[7] = "eighth";
	s[8] = "ninth";
	s[9] = "tenth";
	s[10] = "eleventh";
	s[11] = "twelveth";
	s[12] = "thirteenth";
	s[13] = "fourteenth";
	s[14] = "fifteenth";
	s[15] = "sixteenth";
	s[16] = "seventeenth";
	s[17] = "eighteenth";
	s[18] = "ninteenth";
	s[19] = "twentieth";
	srand((unsigned)time(NULL));
	*/
	cout<<"Enter how many vehicles you want to simulate: ";
	cin>>carnum;
	/*
	cout << "How many floors do you want?" << endl;
	cin >> f;
	while (f > 20)
	{
		cout << "The gloor number should be greater than 20,please input again:";
			cin >>  f;
	}
	int*a = new int[f];
	int*b = new int[f];
	int*c = new int[f];
	int*d = new int[f];
	for (i = 0; i < f; i++)
	{
		cout << "How many vans do you want on the "<<s[i] <<" floor?" << endl;
		cin >> a[i];
		cout << "How many cars do you want on the " << s[i] << " floor?" << endl;
		cin >> b[i];
		cout << "How many motorbikes do you want on the " << s[i] << " floor?" << endl;
		cin >> c[i];
		cout << "How many bicycles do you want on the " << s[i] << " floor?" << endl;
		cin >> d[i];
    }
	cout << "                      vans(a)      cars(b)     motorbikes(c)     bicycles(d)" << endl;
	for (i = 0; i < f; i++)
	{
		cout.fill(' ');
		cout << s[i] << " floor" << setw(8) << a[i] << setw(8) << b[i] << setw(8) << c[i] << setw(8) << d[i] << endl;
		cout << "\n";
	}
	*/
	//simulate vehicle types
	for (i=0;i<carnum;i++){
		cartype[i]=rand()%4+1;
	}
	//assign arrival and departure times to the vehicles
	
	rushhrcar=carnum%24;
	carperhr=(carnum-rushhrcar)/24; //carnum%24 puts in the rush hour
	

	if (carperhr != 0)
	{
		for (j = 0; j < 9; j++)
		{
			for (i = carperhr*j; i < carperhr*(j + 1); i++)
			{
				aminute[i] = rand() % 60 + 60 * j;
				dminute[i] = rand() % 1440;
				while (dminute[i] <= aminute[i])
				{
					dminute[i] = rand() % 1440;
				}
				amin[i] = aminute[i] % 60;
				dmin[i] = dminute[i] % 60;
				ahr[i] = (aminute[i] - ahr[i]) / 60;
				dhr[i] = (dminute[i] - dhr[i]) / 60;
			}
		}

		//let 9 be the rush hour
		

			for (i = (9 * carperhr); i < ((10 * carperhr) + rushhrcar); i++){
				aminute[i] = rand() % 60 + 60 * j;
				dminute[i] = rand() % 1440;
				while (dminute[i] <= aminute[i])
				{
					dminute[i] = rand() % 1440;
				}
				amin[i] = aminute[i] % 60;
				dmin[i] = dminute[i] % 60;
				ahr[i] = (aminute[i] - ahr[i]) / 60;
				dhr[i] = (dminute[i] - dhr[i]) / 60;
			}
		     
	    
		
	for (j = 10; j < 24; j++)
	{
		for (i = j * carperhr + rushhrcar; i < (j + 1) * carperhr + rushhrcar; i++){
			aminute[i] = rand() % 60 + 60 * j;
			dminute[i] = rand() % 1440;
			if (aminute[i] == 1439)
			{
				aminute[i]--;
			}
			while (dminute[i] <= aminute[i])
			{
				dminute[i] = rand() % 1440;
			}
			amin[i] = aminute[i] % 60;
			dmin[i] = dminute[i] % 60;
			ahr[i] = (aminute[i] - ahr[i]) / 60;
			dhr[i] = (dminute[i] - dhr[i]) / 60;
		}
     }
}
	
	if (carperhr == 0)
	{
			for (i = 0; i < rushhrcar; i++){
				aminute[i] = rand() % 60 + 60 * j;
				dminute[i] = rand() % 1440;
				if (aminute[i] == 1439)
				{
					aminute[i]--;
				}
				while (dminute[i] <= aminute[i])
				{
					dminute[i] = rand() % 1440;
				}
				amin[i] = aminute[i] % 60;
				dmin[i] = dminute[i] % 60;
				ahr[i] = (aminute[i] - ahr[i]) / 60;
				dhr[i] = (dminute[i] - dhr[i]) / 60;
			}
	}
	



	//generate the plate numbers
	for (i=0;i<carnum;i++){
		for (j = 0; j < 2; j++)
		{
			platenum[i][j] = rand() % 26 + 65;
			plateletter[i][j] = (char)(platenum[i][j]);
		}
		for (j=2;j<6;j++){
			platenum[i][j]=rand()%10;
		}
	}
	//print the tickets
	//print the arrival ticket
	for (i=0;i<carnum;i++){
		cout<<"ARRIVAL TICKET"<<endl;
		cout<<"Plate number: ";
		for (j = 0; j < 2; j++)
		{
			cout << plateletter[i][j];
		}
		for (j=2;j<6;j++){
			cout<<platenum[i][j];
		}
		cout<<endl;
		arrivalticket(ayr,amon,ad,ahr[i],amin[i],cartype[i]);
		//print the departure ticket
		cout<<"DEPARTURE TICKET"<<endl;
		cout<<"Plate number: ";
		for (j = 0; j < 2; j++)
		{
			cout << plateletter[i][j];
		}
		for (j = 2; j<6; j++){
			cout << platenum[i][j];
		}
		cout<<endl;
		departureticket(ayr,amon,ad,ahr[i],amin[i],dyr,dmon,dd,dhr[i],dmin[i],cartype[i]);
		cout<<endl;
	}
	return 0;
}

void arrivalticket(int ayr,int amon,int ad,int ahr,int amin,int cartype){
	Van v;Car c;Motor m;Bike b;
	switch (cartype){
	case 1:v.printtype();break;
	case 2:c.printtype();break;
	case 3:m.printtype();break;
	case 4:b.printtype();break;
	default:cout<<"Error";break;
	}
	vtime vt(ayr,amon,ad,ahr,amin,0,0,0,0,0);
	vt.printarrival();
} //the arrival ticket fuction does not contain the hint where you can find an empty place to park

void departureticket(int ayr,int amon,int ad,int ahr,int amin,int dyr,int dmon,int dd,int dhr,int dmin,int cartype){
	int stayingtime;
	Van v;Car c;Motor m;Bike b;
	switch (cartype){
	case 1:v.printtype();break;
	case 2:c.printtype();break;
	case 3:m.printtype();break;
	case 4:b.printtype();break;
	default:cout<<"Error";break;
	}
	vtime vt(ayr,amon,ad,ahr,amin,dyr,dmon,dd,dhr,dmin);
	vt.printdeparture();
	vt.printtime();
	stayingtime=vt.staytime();
	price p(cartype,stayingtime);
	p.printmoney();
}