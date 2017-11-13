#include "vehicletime.h"
#include <iostream>
using namespace std;

vtime::vtime(){
	ayr=amon=ad=ahr=amin=dyr=dmon=dd=dhr=dmin=stayingtime=0;
}

vtime::vtime(int ayear,int amonth,int aday, int ahour,int aminute,int dyear,int dmonth,int dday,int dhour,int dminute){
	ayr=ayear;amon=amonth;ad=aday;ahr=ahour;amin=aminute;dyr=dyear;dmon=dmonth;dd=dday;dhr=dhour;dmin=dminute;
	stayingtime=0;
}

vtime::~vtime(){}

void vtime::printarrival(){
	cout<<"Arrival time: "<<ayr<<"/"<<amon<<"/"<<ad<<" ";
	if (ahr>=0&&ahr<10) {cout<<"0";} //format
	cout<<ahr<<":";
	if (amin>=0&&amin<10) {cout<<"0";} //format
	cout<<amin<<endl;
}

void vtime::printdeparture(){
	cout<<"Departure time:"<<dyr<<"/"<<dmon<<"/"<<dd<<" ";
	if (dhr>=0&&dhr<10) {cout<<"0";}
	cout<<dhr<<":";
	if (dmin>=0&&dmin<10) {cout<<"0";}
	cout<<dmin<<endl;
}

int vtime::staytime(){
	stayingtime=(dd-ad)*24*60-dhr*60+dmin-ahr*60-amin; //does not consider arriving and leaving in different months
	return stayingtime;
}

void vtime::printtime(){
	cout<<"Time spent in the parking lot: "<<stayingtime<<" minutes"<<endl;
}