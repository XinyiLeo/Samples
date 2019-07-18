#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

// Test Case
/*
1
20
3 4 5 6 7
*/
enum weapon_t { sword, bomb, arrow };


// Warriors 
class City;
class Warrior {
	char name[20];
	int life = 0;
public:
	char* weapons[3] = {(char*) "sword", (char*) "bomb", (char*) "arrow"};
	Warrior(char* name_);
	void setLife(int life_);
	int getLife();
	virtual void setInfo(int time_, int life_) { };
	virtual void printState() { };
	friend class City;
};

class dragon : public Warrior {
	double morale;
	weapon_t weapon;
	void printState();
	void setInfo(int time_, int life_);
public:
	dragon(char* name_);
};

class ninja : public Warrior {
	weapon_t weapon[2];
	void printState();
	void setInfo(int time_, int life_);
public:
	ninja(char* name_);
};

class iceman : public Warrior {
	weapon_t weapon;
	void printState();
	void setInfo(int time_, int life_);
public:
	iceman(char* name_);
};

class lion : public Warrior {
	int loyalty;
	void printState();
	void setInfo(int time_, int life_);
public:
	lion(char* name_);
};

class wolf : public Warrior {
	void setInfo(int time_, int life_);
	void printState();
public:
	wolf(char* name_);
};

dragon::dragon(char* name_) : Warrior( name_ ) { }

void dragon::printState() {
	cout << "It has a " << weapons[weapon] << ",and it's morale is " << setiosflags(ios::fixed) << setprecision(2) << morale << endl;
}

void dragon::setInfo( int time_, int life_ ) {
	weapon = static_cast<weapon_t> (time_ % 3);
	morale = (double) life_ / (double) getLife(); 
}

ninja::ninja(char* name_) : Warrior( name_ ) { }

void ninja::setInfo( int time_, int life_ ) {
	weapon[0] = static_cast<weapon_t> (time_ % 3);
	weapon[1] = static_cast<weapon_t> (( time_ + 1 ) % 3);
}

void ninja::printState() {
	cout << "It has a " << weapons[weapon[0]] << " and a " << weapons[weapon[1]] << endl; 
}

iceman::iceman(char* name_) : Warrior( name_ ) { }

void iceman::setInfo( int time_, int life_ ) {
	weapon = static_cast<weapon_t> (time_ % 3);
}

void iceman::printState() {
	cout << "It has a " << weapons[weapon] << endl; 
}

lion::lion(char* name_) : Warrior( name_ ) { }

void lion::printState() {
	cout << "It's loyalty is " << loyalty << endl;
}

void lion::setInfo( int time_, int life_ ) {
	loyalty = static_cast<weapon_t> (life_);
}

wolf::wolf(char* name_) : Warrior( name_ ) { }

void wolf::printState() { }

void wolf::setInfo( int time_, int life_ ) { }

Warrior::Warrior(char* name_) {
	strcpy(name, name_);
};

void Warrior::setLife(int life_) {
	life = life_;
}

int Warrior::getLife() {
	return life;
}

// Implementation of City
class City {
	char name[20];
	bool active = true;
	int life = 0;
	int curWarrior = -1;
	Warrior *p[5];
	int Ccnt[5] = {0,0,0,0,0};
	public:
		City(char* name_, int seq_[5], Warrior *pWarrior[5]);
		void setLife(int life_);
		int findNextWarrior();
		bool isActive();
		void reset();
		void deactivate(int time);
		void printState(int time);
};

City::City(char* name_, int seq_[5], Warrior *pWarrior_[5]) {
	strcpy(name, name_);
	int i;
	for(i = 0; i < 5; i++) {
		p[i] = pWarrior_[seq_[i]];
	}
};

void City::setLife(int life_) {
	life = life_;
}

int City::findNextWarrior() {
	// If none, return -1
	int cnt, lastCnt;
	Warrior* w;
	lastCnt = 6;
	for(cnt = 1; cnt < lastCnt; cnt++) {
		w = p[(cnt + curWarrior) % 5];
		if(life - w->life >= 0) {
			life -= w->life;
			curWarrior = (cnt + curWarrior) % 5;
			Ccnt[curWarrior] += 1;
			return curWarrior;
		} 
	}
	return -1;
}

bool City::isActive() {
	return active;
}

void City::reset() {
	active = true;
	life = 0;
	curWarrior = -1;
	int i;
	for(i = 0; i < 5; i++) {
		Ccnt[i] = 0;
	}
}

void City::deactivate(int time) {
	active = false;
	cout << setfill('0') << setw(3) << time << " ";
	cout << name << " ";
	cout << "headquarter stops making warriors" << endl;
}

void City::printState(int time) {
	cout << setfill('0') << setw(3) << time << " ";
	time++; // id equals to time + 1
	cout << name << " ";
	cout << p[curWarrior]->name << " ";
	cout << time << " ";
	cout << "born with strength " << p[curWarrior]->life << ",";
	cout << Ccnt[curWarrior] << " " << p[curWarrior]->name << " in " << name << " headquarter" << endl;
	p[curWarrior]->setInfo(time, life);
	p[curWarrior]->printState();
}

// Main Function
int main() {
	int i, j, round, Clife, Wlife, next, activeNum = 2;
	cin >> round;
	// Warrior Init
	enum warrior_t {DRAGON, NINJA, ICEMAN, LION, WOLF}; 	
	Warrior *pWarrior[5] = {new dragon((char *)"dragon"), new ninja((char *)"ninja"), 
		new iceman((char *)"iceman"), new lion((char *)"lion"), new wolf((char *)"wolf")};

	// City Init
	enum city_t {RED, BLUE}; 	
	int redSeq[5] = {ICEMAN, LION, WOLF, NINJA, DRAGON};
	int blueSeq[5] = {LION, DRAGON, NINJA, ICEMAN, WOLF};
	City *pCity[2] = {new City((char *)"red", redSeq, pWarrior), new City((char *)"blue", blueSeq, pWarrior)};
	int time = 0;

	for(i = 0; i < round; i++ ) {
		cout << "Case:" << i + 1 << endl;
		time = 0;
		activeNum = 2;
		pCity[0]->reset();
		pCity[1]->reset();
			
		// Operate in the for loop
		cin >> Clife;
		pCity[0]->setLife(Clife);
		pCity[1]->setLife(Clife);
		// Input the initial life of the warriors
		for(j = 0; j < 5; j++) {
			cin >> Wlife;
			pWarrior[j]->setLife(Wlife);
		}
		// Start to print while loop
		while (activeNum > 0) {
			for(j = 0; j < 2; j++) {
				if(pCity[j]->isActive()) {
					//find next warrior
					next = pCity[j]->findNextWarrior();
					if(next == -1) {
						pCity[j]->deactivate(time);
						activeNum -= 1;
					}
					else {
						pCity[j]->printState(time);
					}
				}
			}
			time += 1;
		}
	}

	// Deconstruction
	for(i = 0; i < 5; i++) {
		delete pWarrior[i];
	}
	for(i = 0; i < 2; i++) {
		delete pCity[i];
	}
}











