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
	int f,i,j,ahr[MAX]={0},amin[MAX]={0},dhr[MAX]={0},dmin[MAX]={0},carnum,cartype[MAX]={0},platenum[MAX][6]={0};
	int ayr=2014,dyr=2014,amon=7,dmon=7,ad=27,dd=27; //for the convenience of programming, we simply simulate the whole procees in one day, i.e. 2014/7/27
	int carperhr,rushhrcar;
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
	cout<<"Enter how many vehicles you want to simulate: ";
	cin>>carnum;
	cout << "How many floors do you want?" << endl;
	cin >> f;
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
	//simulate vehicle types
	for (i=0;i<carnum;i++){
		cartype[i]=rand()%4+1;
	}
	//assign arrival and departure times to the vehicles
	rushhrcar=carnum%24;
	carperhr=(carnum-rushhrcar)/24; //carnum%24 puts in the rush hour
	//0 
	



	for (i=0;i<carperhr;i++) 
	{
		ahr[i]=0;
		amin[i]=rand()%60+0;
		dhr[i]=rand()%24+0;
		dmin[i]=rand()%60+0;
		//we should make sure that departure time is later than arrival time
		while (dhr[i]<ahr[i])
		{
			dhr[i]=rand()%24;
		}
		if (dhr[i]==ahr[i])
		{
			while (amin[i]<=dmin[i]){
				dmin[i]=rand()%60;
			}
		}
	}
	//1 
	for (i=carperhr;i<2*carperhr;i++)
	{
		ahr[i]=1;
		amin[i]=rand()%60;
		dhr[i]=rand()%24;
		dmin[i]=rand()%60;
		while (dhr[i]<ahr[i])
		{
			dhr[i]=rand()%24;
		}
		if (dhr[i]==ahr[i])
		{
			while (amin[i]<=dmin[i]){
				dmin[i]=rand()%60;
			}
		}
	}
	//2 
	for (i=2*carperhr;i<3*carperhr;i++){
		ahr[i]=2;
		amin[i]=rand()%60;
		dhr[i]=rand()%24;
		dmin[i]=rand()%60;
		while (dhr[i]<ahr[i])
		{
			dhr[i]=rand()%24;
		}
		if (dhr[i]==ahr[i])
		{
			while (amin[i]<=dmin[i]){
				dmin[i]=rand()%60;
			}
		}
	}
	//3 
	for (i=3*carperhr;i<4*carperhr;i++){
		ahr[i]=3;
		amin[i]=rand()%60;
		dhr[i]=rand()%24;
		dmin[i]=rand()%60;
		while (dhr[i]<ahr[i])
		{
			dhr[i]=rand()%24;
		}
		if (dhr[i]==ahr[i])
		{
			while (amin[i]<=dmin[i]){
				dmin[i]=rand()%60;
			}
		}
	}
	//4 
	for (i=4*carperhr;i<5*carperhr;i++){
		ahr[i]=4;
		amin[i]=rand()%60;
		dhr[i]=rand()%24;
		dmin[i]=rand()%60;
		while (dhr[i]<ahr[i])
		{
			dhr[i]=rand()%24;
		}
		if (dhr[i]==ahr[i])
		{
			while (amin[i]<=dmin[i]){
				dmin[i]=rand()%60;
			}
		}
	}
	//5
	for (i=5*carperhr;i<6*carperhr;i++){
		ahr[i]=5;
		amin[i]=rand()%60;
		dhr[i]=rand()%24;
		dmin[i]=rand()%60;
		while (dhr[i]<ahr[i])
		{
			dhr[i]=rand()%24;
		}
		if (dhr[i]==ahr[i])
		{
			while (amin[i]<=dmin[i]){
				dmin[i]=rand()%60;
			}
		}
	}
	//6
	for (i=6*carperhr;i<7*carperhr;i++){
		ahr[i]=6;
		amin[i]=rand()%60;
		dhr[i]=rand()%24;
		dmin[i]=rand()%60;
		while (dhr[i]<ahr[i])
		{
			dhr[i]=rand()%24;
		}
		if (dhr[i]==ahr[i])
		{
			while (amin[i]<=dmin[i]){
				dmin[i]=rand()%60;
			}
		}
	}
	//7
	for (i=7*carperhr;i<8*carperhr;i++){
		ahr[i]=7;
		amin[i]=rand()%60;
		dhr[i]=rand()%24;
		dmin[i]=rand()%60;
		while (dhr[i]<ahr[i])
		{
			dhr[i]=rand()%24;
		}
		if (dhr[i]==ahr[i])
		{
			while (amin[i]<=dmin[i]){
				dmin[i]=rand()%60;
			}
		}
	}
	//8
	for (i=8*carperhr;i<9*carperhr;i++){
		ahr[i]=8;
		amin[i]=rand()%60;
		dhr[i]=rand()%24;
		dmin[i]=rand()%60;
		while (dhr[i]<ahr[i])
		{
			dhr[i]=rand()%24;
		}
		if (dhr[i]==ahr[i])
		{
			while (amin[i]<=dmin[i]){
				dmin[i]=rand()%60;
			}
		}
	}
	//9
	//let 9 be the rush hour
	for (i=9*carperhr;i<10*carperhr+rushhrcar;i++){
		ahr[i]=9;
		amin[i]=rand()%60;
		dhr[i]=rand()%24;
		dmin[i]=rand()%60;
		while (dhr[i]<ahr[i])
		{
			dhr[i]=rand()%24;
		}
		if (dhr[i]==ahr[i])
		{
			while (amin[i]<=dmin[i]){
				dmin[i]=rand()%60;
			}
		}
	}
	//10
	for (i=10*carperhr+rushhrcar;i=11*carperhr+rushhrcar;i++){
		ahr[i]=10;
		amin[i]=rand()%60;
		dhr[i]=rand()%24;
		dmin[i]=rand()%60;
		while (dhr[i]<ahr[i])
		{
			dhr[i]=rand()%24;
		}
		if (dhr[i]==ahr[i])
		{
			while (amin[i]<=dmin[i]){
				dmin[i]=rand()%60;
			}
		}
	}
	//11
	for (i=11*carperhr+rushhrcar;i<12*carperhr+rushhrcar;i++){
		ahr[i]=11;
		amin[i]=rand()%60;
		dhr[i]=rand()%24;
		dmin[i]=rand()%60;
		while (dhr[i]<ahr[i])
		{
			dhr[i]=rand()%24;
		}
		if (dhr[i]==ahr[i])
		{
			while (amin[i]<=dmin[i]){
				dmin[i]=rand()%60;
			}
		}
	}
	//12
	for (i=12*carperhr+rushhrcar;i<13*carperhr+rushhrcar;i++){
		ahr[i]=12;
		amin[i]=rand()%60;
		dhr[i]=rand()%24;
		dmin[i]=rand()%60;
		while (dhr[i]<ahr[i])
		{
			dhr[i]=rand()%24;
		}
		if (dhr[i]==ahr[i])
		{
			while (amin[i]<=dmin[i]){
				dmin[i]=rand()%60;
			}
		}
	}
	//13
	for (i=13*carperhr+rushhrcar;i<14*carperhr+rushhrcar;i++){
		ahr[i]=13;
		amin[i]=rand()%60;
		dhr[i]=rand()%24;
		dmin[i]=rand()%60;
		while (dhr[i]<ahr[i])
		{
			dhr[i]=rand()%24;
		}
		if (dhr[i]==ahr[i])
		{
			while (amin[i]<=dmin[i]){
				dmin[i]=rand()%60;
			}
		}
	}
	//14
	for (i=14*carperhr+rushhrcar;i<15*carperhr+rushhrcar;i++){
		ahr[i]=14;
		amin[i]=rand()%60;
		dhr[i]=rand()%24;
		dmin[i]=rand()%60;
		while (dhr[i]<ahr[i])
		{
			dhr[i]=rand()%24;
		}
		if (dhr[i]==ahr[i])
		{
			while (amin[i]<=dmin[i]){
				dmin[i]=rand()%60;
			}
		}
	}//15
	for (i=15*carperhr+rushhrcar;i<16*carperhr+rushhrcar;i++){
		ahr[i]=15;
		amin[i]=rand()%60;
		dhr[i]=rand()%24;
		dmin[i]=rand()%60;
		while (dhr[i]<ahr[i])
		{
			dhr[i]=rand()%24;
		}
		if (dhr[i]==ahr[i])
		{
			while (amin[i]<=dmin[i]){
				dmin[i]=rand()%60;
			}
		}
	}
	//16
	for (i=16*carperhr+rushhrcar;i<17*carperhr+rushhrcar;i++){
		ahr[i]=16;
		amin[i]=rand()%60;
		dhr[i]=rand()%24;
		dmin[i]=rand()%60;
		while (dhr[i]<ahr[i])
		{
			dhr[i]=rand()%24;
		}
		if (dhr[i]==ahr[i])
		{
			while (amin[i]<=dmin[i]){
				dmin[i]=rand()%60;
			}
		}
	}
	//17
	for (i=17*carperhr+rushhrcar;i<18*carperhr+rushhrcar;i++){
		ahr[i]=17;
		amin[i]=rand()%60;
		dhr[i]=rand()%24;
		dmin[i]=rand()%60;
		while (dhr[i]<ahr[i])
		{
			dhr[i]=rand()%24;
		}
		if (dhr[i]==ahr[i])
		{
			while (amin[i]<=dmin[i]){
				dmin[i]=rand()%60;
			}
		}
	}
	//18
	for (i=18*carperhr+rushhrcar;i<19*carperhr+rushhrcar;i++){
		ahr[i]=18;
		amin[i]=rand()%60;
		dhr[i]=rand()%24;
		dmin[i]=rand()%60;
		while (dhr[i]<ahr[i])
		{
			dhr[i]=rand()%24;
		}
		if (dhr[i]==ahr[i])
		{
			while (amin[i]<=dmin[i]){
				dmin[i]=rand()%60;
			}
		}
	}
	//19
	for (i=19*carperhr+rushhrcar;i<20*carperhr+rushhrcar;i++){
		ahr[i]=19;
		amin[i]=rand()%60;
		dhr[i]=rand()%24;
		dmin[i]=rand()%60;
		while (dhr[i]<ahr[i])
		{
			dhr[i]=rand()%24;
		}
		if (dhr[i]==ahr[i])
		{
			while (amin[i]<=dmin[i]){
				dmin[i]=rand()%60;
			}
		}
	}
	//20
	for (i=20*carperhr+rushhrcar;i<21*carperhr+rushhrcar;i++){
		ahr[i]=20;
		amin[i]=rand()%60;
		dhr[i]=rand()%24;
		dmin[i]=rand()%60;
		while (dhr[i]<ahr[i])
		{
			dhr[i]=rand()%24;
		}
		if (dhr[i]==ahr[i])
		{
			while (amin[i]<=dmin[i]){
				dmin[i]=rand()%60;
			}
		}
	}
	//21
	for (i=21*carperhr+rushhrcar;i<22*carperhr+rushhrcar;i++){
		ahr[i]=21;
		amin[i]=rand()%60;
		dhr[i]=rand()%24;
		dmin[i]=rand()%60;
		while (dhr[i]<ahr[i])
		{
			dhr[i]=rand()%24;
		}
		if (dhr[i]==ahr[i])
		{
			while (amin[i]<=dmin[i]){
				dmin[i]=rand()%60;
			}
		}
	}
	//22
	for (i=22*carperhr+rushhrcar;i<23*carperhr+rushhrcar;i++){
		ahr[i]=22;
		amin[i]=rand()%60;
		dhr[i]=rand()%24;
		dmin[i]=rand()%60;
		while (dhr[i]<ahr[i])
		{
			dhr[i]=rand()%24;
		}
		if (dhr[i]==ahr[i])
		{
			while (amin[i]<=dmin[i]){
				dmin[i]=rand()%60;
			}
		}
	}
	//23
	for (i=23*carperhr+rushhrcar;i<24*carperhr+rushhrcar;i++){
		ahr[i]=23;
		amin[i]=rand()%60;
		dhr[i]=rand()%24;
		dmin[i]=rand()%60;
		while (dhr[i]<ahr[i])
		{
			dhr[i]=rand()%24;
		}
		if (dhr[i]==ahr[i])
		{
			while (amin[i]<=dmin[i]){
				dmin[i]=rand()%60;
			}
		}
	}


	//generate the plate numbers
	for (i=0;i<carnum;i++){
		for (j=0;j<6;j++){
			platenum[i][j]=rand()%10;
		}
	}
	//print the tickets
	//print the arrival ticket
	for (i=0;i<carnum;i++){
		cout<<"ARRIVAL TICKET"<<endl;
		cout<<"Plate number: ";
		for (j=0;j<6;j++){
			cout<<platenum[i][j];
		}
		cout<<endl;
		arrivalticket(ayr,amon,ad,ahr[i],amin[i],cartype[i]);
		//print the departure ticket
		cout<<"DEPARTURE TICKET"<<endl;
		cout<<"Plate number: ";
		for (j=0;j<6;j++){
			cout<<platenum[i][j];
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