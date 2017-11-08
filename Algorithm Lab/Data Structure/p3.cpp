#define P3
#ifdef P3

#include <iostream> 
#include <map> 
#include <queue>
#include <string>
#include <sstream>
#include <set>



using namespace std; 

 	struct order
    	{
        	int ID_number;
        	int timestamp;
        	string client;
        	string equity;
        	string buy_sell;
        	int price;
        	int quantity;
        	int duration;
	};

       

	struct compare_t
	{
		bool operator () (order* a, order* b) const
		{
			if(a->buy_sell == "SELL") {
                		if(a->price > b->price) {
 					return true;
				}
				else if(a->price == b->price) {
				 	if (a->ID_number > b->ID_number) return true;
					else return false;				
				}
				else return false;
			}
			else {
				if(a->price < b->price) {
 					return true;
				}
				else if(a->price == b->price) {
				 	if (a->ID_number > b->ID_number) return true;
					else return false;				
				}
				else return false;			
			}
		}
	};

	struct time_compare
	{
		bool operator()(order* a, order* b) const
		{	
			if(a->duration == -1) {
				if(b->duration == -1) {
					 if(a->ID_number > b-> ID_number) return true;
					 	else return false;
				}
				else return true;
			}
			else if(b->duration == -1) return false;
			else if ((a->timestamp + a->duration) > (b->timestamp + b->duration)) return true;
			else if ((a->timestamp + a->duration) == (b->timestamp + b->duration)) {
				if(a->ID_number > b-> ID_number) return true;
				else return false;	
			}
			else return false;				
		}
	};
   
	struct equity 
	{ 
        	string name;
		priority_queue<order*, vector<order*>, compare_t> *e_buy;
   		priority_queue<order*, vector<order*>, compare_t> *e_sell;
	}; 

	//The first is buyer, the second is seller
	void transact(order* &buyer, order* &seller) {
		if(buyer->price >= seller->price) {
			if(buyer->ID_number > seller->ID_number) {
				if(buyer->quantity >= seller->quantity) {
					cout << buyer->client << " purchased " << seller->quantity << " shares of " 
					     << buyer->equity << " from " << seller->client << " for $" << seller->price << "/share" << endl;
					seller -> quantity = 0;  buyer->quantity = buyer->quantity - seller -> quantity;	
				}
				else {
					cout << buyer->client << " purchased " << seller->quantity << " shares of " 
					     << buyer->equity << " from " << seller->client << " for $" << seller->price << "/share" << endl;
					buyer -> quantity = 0;  seller->quantity = seller->quantity - buyer -> quantity;
				}
			}
			else {
				if(buyer->quantity >= seller->quantity) {
					cout << buyer->client << " purchased " << seller->quantity << " shares of " 
					     << buyer->equity << " from " << seller->client << " for $" << buyer->price << "/share" << endl;
					seller -> quantity = 0;  buyer->quantity = buyer->quantity - seller -> quantity;	
				}
				else {
					cout << buyer->client << " purchased " << seller->quantity << " shares of " 
					     << buyer->equity << " from " << seller->client << " for $" << buyer->price << "/share" << endl;
					buyer -> quantity = 0;  seller->quantity = seller->quantity - buyer -> quantity;
				}			
			}		
		}
	}

	int main(int argc, char *argv[]) {
		string temp_str;
		map<string,   equity*> equity_map; 
      		map<string,   equity*>::iterator map_it;
                priority_queue<order*, vector<order*>, time_compare> *t_comp = new priority_queue<order*, vector<order*>,time_compare>;	   			set<int> Deleted_ID;
 		set<int> ::iterator it;
		queue<order*> *To_Del = new queue<order*>;
		order* qq;

     		char victim;
     		int i = 0;
     		int a = 0;
		int current_stamp = 0;
     		while(cin >> a) {
        	//Start input
        		order* temp = new order;
        		temp->ID_number = i;
        		temp-> timestamp = a;
        		cin >> temp-> client;
			cin >> temp-> buy_sell;
       			cin >> temp-> equity;
        		cin >> victim;
        		cin >> temp-> price;
        		cin >> victim;
        		cin >> temp-> quantity;
        		cin >> temp-> duration;
                 
		//Delete the expired one
			if(!t_comp->empty()) {
				if(current_stamp != temp-> timestamp) {
					current_stamp = temp-> timestamp;
					while(t_comp->top()->timestamp+t_comp->top()->duration == current_stamp) {
						To_Del->push(t_comp->top());
						Deleted_ID.insert(t_comp->top()->ID_number);	
						t_comp->pop();			
					}
				}
			}
			
		//Begin to assign queue into the map, create a new equity enter if needed.
  			map_it = equity_map.find(temp-> equity);
			if(map_it == equity_map.end()) {
				equity* temp_eq = new equity;
				temp_eq-> name = temp-> equity;
			        temp_eq-> e_buy = new priority_queue<order*, vector<order*>, compare_t>;
				temp_eq-> e_sell= new priority_queue<order*, vector<order*>, compare_t>;
				equity_map.insert(make_pair(temp-> equity, temp_eq));
			}
		 //Execution
		  	map_it = equity_map.find(temp-> equity);
                        if(temp->buy_sell == "BUY") {
				while((!map_it->second ->e_sell->empty()) && temp -> quantity > 0) {
					it = Deleted_ID.find(map_it->second ->e_sell->top()->ID_number);
					if(it != Deleted_ID.end()) {
						map_it->second ->e_sell->pop();	
						continue;	
					}	
					/*qq = map_it->second->e_sell->top();
					transact(temp, qq);
					map_it->second ->e_sell->pop(); 
					map_it->second ->e_sell->push(qq);	
			    		if(map_it->second ->e_sell->top()->quantity == 0) {
						To_Del->push(t_comp->top());
					        Deleted_ID.insert(map_it->second ->e_sell->top()->ID_number);
						map_it->second ->e_sell->pop();		       				
					}	*/	
					break;
				}
				if(temp->quantity == 0) delete temp;	
			}
			if(temp->buy_sell == "SELL") {
				while((!map_it->second ->e_buy->empty()) && temp -> quantity > 0) {
					it = Deleted_ID.find(map_it->second ->e_buy->top()->ID_number);
					if(it != Deleted_ID.end()) {
						map_it->second ->e_buy->pop();	
						continue;	
					}	
					//Further Excecution	
					//qq = const_cast <order*> (map_it->second->e_sell->top());
					/*transact(qq,temp);	
					map_it->second ->e_buy->pop(); 
					map_it->second ->e_buy->push(qq);
					if(map_it->second ->e_buy->top()->quantity == 0) {
						To_Del->push(t_comp->top());
					        Deleted_ID.insert(map_it->second ->e_buy->top()->ID_number);
						map_it->second ->e_buy->pop();		       				
					}		*/
					break;
				}
				if(temp->quantity == 0) delete temp;	
			}

			//Push to Queue
			if(temp->duration == 0) {
				delete temp;			
			}
			else {
		        	map_it = equity_map.find(temp-> equity);
				t_comp ->push(temp);
				if(temp-> buy_sell == "BUY") {
					map_it-> second -> e_buy -> push(temp);
				}
				else if (temp-> buy_sell == "SELL") {
					map_it-> second -> e_sell -> push(temp);
				} 
			}			
        		i++;
   		 } 
		 
			

	//Output
		 for(map<string,   equity*>::iterator j = equity_map.begin();  j != equity_map.end(); j++) 
            	 { 
                        cout<< j->first << endl; 
            	 } 
                 cout << " " << endl;
   		 cout << "All the buyers: " << endl;
		 for(map<string,   equity*>::iterator j = equity_map.begin();  j != equity_map.end(); j++) 
            	 { 
   		 	while(!j->second->e_buy->empty()) {
       		 	order* tempp;
        	 	tempp = j->second->e_buy->top();
       		 cout << "ID number: " <<   tempp->ID_number << "   Timestamp: " << tempp-> timestamp << "  Client: " << tempp-> client 
             		<< "   Equity:"     << tempp-> equity << "   Buy or Sell: " 
            		<< tempp-> buy_sell << "   Price: " << tempp-> price << "   Quantity: " << tempp-> quantity 
             		<< "   Duration: " << tempp-> duration 
             		<< endl;
        		j->second->e_buy->pop();
    		 	}
			delete j->second->e_buy;
		 }

                 cout << " " << endl;
		 cout << "All the sellers: " << endl;
   		 for(map<string,   equity*>::iterator j = equity_map.begin();  j != equity_map.end(); j++) 
            	 { 
   		 	while(!j->second->e_sell->empty()) {
       		 	order* tempp;
        	 	tempp = j->second->e_sell->top();
       		 cout << "ID number: " <<   tempp->ID_number << "   Timestamp: " << tempp-> timestamp << "  Client: " << tempp-> client 
             		<< "   Equity:"     << tempp-> equity << "   Buy or Sell: " 
            		<< tempp-> buy_sell << "   Price: " << tempp-> price << "   Quantity: " << tempp-> quantity 
             		<< "   Duration: " << tempp-> duration 
             		<< endl;
        		j->second->e_sell->pop();
    		 	}
			delete j->second->e_sell;
		 }
		 for(map<string,   equity*>::iterator j = equity_map.begin();  j != equity_map.end(); j++) 
            	 { 
                        delete j->second;
            	 } 
		
		 cout << " " << endl;
		 cout << "All the stuffs" << endl;
		 while(!t_comp->empty()) {
		 	order* tempp;
			tempp = t_comp->top();
       		 cout << "ID number: " <<   tempp->ID_number << "   Timestamp: " << tempp-> timestamp << "  Client: " << tempp-> client 
             		<< "   Equity:"     << tempp-> equity << "   Buy or Sell: " 
            		<< tempp-> buy_sell << "   Price: " << tempp-> price << "   Quantity: " << tempp-> quantity 
             		<< "   Duration: " << tempp-> duration 
             		<< endl;
        		t_comp->pop();
			delete tempp;
		 } 
		
		 while(!To_Del->empty()) {
		 	order* bb = To_Del->front();
			To_Del->pop();
			delete bb;
		 }

		 delete t_comp;
		 delete To_Del;
    		 return 0;
	}
#endif /*End For P3*/






















