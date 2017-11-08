/*
#include <iostream> 
#include <map> 
using namespace std; 
	typedef struct itemstruct 
	{ 
   	   int   a; 
	   char   b[20]; 
	}itemS; 

        itemS   s[4]   =   {{102,"what"}, 
                          {33,   "hello"}, 
                          {198,"world"}, 
                          {45,   "c++"} 
                      };
  
  
  int     main() 
  { 
            map<string,   itemS>     mymap; 
            string   str[4]   =   {"1st","2nd","3rd","4th"}; 
            for(int   i   =   0;   i<4;   i++) 
            { 
                 mymap.insert(make_pair(str[i],   s[i])); 
            } 

            map<string,itemS>::iterator   it; 
            for(it=mymap.begin();   it!=mymap.end(); it++) 
            { 
               if(it->second.a >100){ 
                  //i=mymap.erase(it);  //----->正确
                  mymap.erase(it);     //----->it失效..
                }
            }
  //first是Key, second是value;
            for(it = mymap.begin();  it!=mymap.end(); it++) 
            { 
                          cout<<it->first<<"   "<<it->second.a<<"   "<<it->second.b<<endl; 
            } 
          //system("pause"); 
          return   0; 
  }
*/

#include <iostream> 
#include <string>
#include <map> 
using namespace std; 

struct student{  
 string name;  
 int age;  
 string city;  
 string phone;  
};  
  
int main()  
{  
     using namespace std;  
  
     student s[]={  
      {"童进",23,"武汉","XXX"},  
      {"老大",23,"武汉","XXX"},  
      {"饺子",23,"武汉","XXX"},  
      {"王老虎",23,"武汉","XXX"},  
      {"周润发",23,"武汉","XXX"},  
      {"周星星",23,"武汉","XXX"}  
     };  
      pair<int,student> p1(4,s[0]);  
      pair<int,student> p2(2,s[1]);  
      pair<int,student> p3(3,s[2]);  
      pair<int,student> p4(4,s[3]);  //键值key与p1相同  
      pair<int,student> p5(5,s[4]);  
      pair<int,student> p6(6,s[5]);  
      multimap<int,student> a; 
      a.insert(p1);  
      a.insert(p2);  
      a.insert(p3);  
      a.insert(p4);  
      a.insert(p5);  
      a.insert(p6);  
     typedef multimap<int,student>::iterator int_multimap;  
     pair<int_multimap,int_multimap> p = a.equal_range(4);  
     int_multimap i = a.find(4);  
     //cout << i << endl;
     cout<<"班上key值为"<< i->first<<"的学生有："<<a.count(4)<<"名,"<<"   他们是:"<<endl;  
     for(int_multimap k = p.first; k != p.second; k++)  
     {  
        cout<<k->second.name<<endl;  
     }  
     cout<<"删除重复键值的同学"<<endl;  
     a.erase(i);  
     cout<<"现在班上总人数为："<<a.size()<<".   人员如下："<<endl;  
     for(multimap<int,student>::iterator j=a.begin(); j != a.end(); j++)  
     {        
          cout<<"The name: "<<j->second.name<<"      "<<"age: "<<j->second.age<<"   "  
           <<"city: "<<j->second.city<<"      "<<"phone: "<<j->second.phone<<endl;  
     }  
  
     return 0;  
}  













 
