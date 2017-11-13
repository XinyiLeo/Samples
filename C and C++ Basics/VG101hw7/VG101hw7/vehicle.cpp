#include "vehicle.h"
#include<iostream>
using namespace std;
vehicle::vehicle(){
	typ=1;
}

vehicle::vehicle(int type){
	typ=type;
}
vehicle::~vehicle(){}

void vehicle::printtype(){
	cout<<"Vehicle type: ";
	switch (typ){
		case 1:cout<<"Van"<<endl;break;
		case 2:cout<<"Car"<<endl;break;
		case 3:cout<<"Motorbike"<<endl;break;
		case 4:cout<<"Bicycle"<<endl;break;
		default:cout<<"Error"<<endl;break;
	}
}
