#include "price.h"
#include<iostream>
using namespace std;

price::price(){
	typ=0;
	timespent=0;
}

price::price(int type,int stayingtime){
	typ=type;
	timespent=stayingtime;
}

price::~price(){}

void price::printmoney(){
	int hour;
	if (timespent>=0&&timespent<=30) {hour=0;}
	else if (timespent>30&&timespent<=60) {hour=1;}
	else {hour=(timespent-timespent%60)/60+1;}
	cout<<"Parking fee: ";
	if (typ==1) {cout<<10*hour;}
	else if (typ==2) {cout<<8*hour;}
	else if (typ==3) {cout<<5*hour;}
	else if (typ==4) {cout<<3*hour;}
	else {cout<<"Error";}
	cout<<" RMB"<<endl;
}