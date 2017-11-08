
#include <iostream>
#include <set>
#include <map>
#include <queue>
using namespace std;

/*
int main(int argc, char *argv[]) {
    priority_queue<int, vector<int>, less <int> > *q1 = new priority_queue<int, vector<int>, less<int> >;
    for(int i=9;i>=0;i--)   
        q1->push(i);  
    while(!q1->empty()){  
        cout<<q1->top()<< endl;  
        q1->pop();  
    }  
    return 0;      
} // cout 9 8 7 6 5 4 3 2 1 0
*/

struct Node{  
    int x, y;  
}node;  
 
bool operator < ( Node a, Node b){  
    if(a.x == b.x) return a.y < b.y;  
    return a.x < b.x;  
}  

 int main(){  
    priority_queue<Node> q;  
    for(int i=0;i<10;i++){  
        node.x=i;  
        node.y=10-i/2;  
        q.push(node);  
    }     
    while(!q.empty()){  
        cout<<q.top().x <<' '<<q.top().y<<endl;  
        q.pop();  
    }  
    return 0;  
} 





