#include<iostream>
#include<string>
#include<cstdlib>
#include<cassert>
#include"dlist.h"
#include "dlist.cpp"
using namespace std;

//The structure of a member of the Airline
struct member
{
    int memberID;
    int calltime;
    string Name;
    string membership;
    int duration;
    int AnsweringTime;
};


int main()
{
    Dlist<member> platinum;
    Dlist<member> gold;
    Dlist<member> silver;
    Dlist<member> regular;
    Dlist<member> Serviced;
    int round = 0;
    int people;
    int peopleremain;
    cin >> people;
    peopleremain = people;
    member all[people]; 
    for(int i = 0; i < people; i++) {
        cin >> all[i].calltime;
        cin >> all[i].Name;
        cin >> all[i].membership;
        cin >> all[i].duration;
        all[i].AnsweringTime = -all[i].duration-1;
        all[i].memberID = i;
    }
    bool busy = false;
    while(peopleremain != 0) {
        //Judging if this time is busy
        for(int i = 0; i < people; i++) {
            if(round < all[i].AnsweringTime + all[i].duration) { busy = true; break;}
            if(i == people - 1) {busy = false;}
        }
        cout << "Starting tick #" << round << endl;    
        //Finding if there are any calls and output them
        for(int i = 0; i < people; i++) { 
            if(all[i].calltime == round) {
                if(all[i].membership == "platinum")  { member *pla = new member(all[i]); platinum.insertFront(pla);}
                else if(all[i].membership == "gold")   { member *gol = new member(all[i]); gold.insertFront(gol);}
                else if(all[i].membership == "silver") { member *sil = new member(all[i]); silver.insertFront(sil);}
                else if(all[i].membership == "regular")  { member *reg = new member(all[i]); regular.insertFront(reg);}
                cout << "Call from " << all[i].Name << " a " << all[i].membership << " member" <<endl;
            }
        }
        //Answering the calls
        if(!platinum.isEmpty() && busy == false) {
            member* o = platinum.removeBack(); 
            all[o->memberID].AnsweringTime = round;    
            cout << "Answering call from " << o->Name << endl;
            Serviced.insertFront(o);
            busy = true;   
            peopleremain = peopleremain - 1;
        }
        if(!gold.isEmpty() && busy == false) {
            member* o = gold.removeBack(); 
            all[o->memberID].AnsweringTime = round;    
            cout << "Answering call from " << o->Name << endl;
            Serviced.insertFront(o);
            busy = true;   
            peopleremain = peopleremain - 1;
        }
        if(!silver.isEmpty() && busy == false) {
            member *o = silver.removeBack(); 
            all[o->memberID].AnsweringTime = round;    
            cout << "Answering call from " << o->Name << endl;
            Serviced.insertFront(o);
            busy = true;   
            peopleremain = peopleremain - 1;
        }
        if(!regular.isEmpty() && busy == false) {
            member* o = regular.removeBack(); 
            all[o->memberID].AnsweringTime = round;    
            cout << "Answering call from " << o->Name << endl;
            Serviced.insertFront(o);
            busy = true;   
            peopleremain = peopleremain - 1;
        }
        round++; 
    }
    cout << "Starting tick #" << round << endl;    
}

