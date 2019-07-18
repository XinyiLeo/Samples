#include <iostream>
#include <iomanip>
#include <cstring>
#include <cassert>

using namespace std;

// global variable
const int MAXCITY = 22;
const int WNUM = 5; 
const int WARRIOR_PER_CITY = 30; 
int N;
enum weaponType {SWORD, BOMB, ARROW};
enum warriorType {DRAGON, NINJA, ICEMAN, LION, WOLF}; 
enum headquarterType {RED, BLUE};

struct warrior_t {
	warriorType wType;
	int life;
	int damage;
} warriorDic[WNUM];
int curtime = 0;

// class header
class City;
class Headquarter;
class Warrior;
bool WarriorBorn(Headquarter* H);
bool LionRun(Headquarter* H);
bool linkWarrior2Headquarter(Warrior* W, Headquarter* H); 
bool linkWarriorCity(Warrior* W, City* C);
bool WarriorMove(Headquarter* rHQ, Headquarter* bHQ);
bool WarriorGetLife(City* C);
City* cityMap[MAXCITY];

// Weapon
class Weapon {
protected: 
	weaponType weType; 
};

class sword : public Weapon {
	int damage;
};

class bomb : public Weapon {

};

class arrow : public Weapon {
	int damage;
	int residueNum;
};

// City (Head Quanter / Town)
class City {
	int id = 0;
protected:
	int life = 0;
	Warrior* Pset[2]; // The Warriors it now has, 0 is red, 1 is blue
	int WarriorVol = 0; // Current Number of Warrior
public:
	City(int id_);
	virtual bool reset(int id_, int life_ = 0);
	virtual ~City();
	friend bool WarriorBorn(Headquarter* H);
	friend bool LionRun(Headquarter* H);
	friend bool linkWarriorCity(Warrior* W, City* C);
	friend bool WarriorMove(Headquarter* rHQ, Headquarter* bHQ);
	friend bool WarriorGetLife(City* C);
	bool generateLife();
};

class Headquarter : public City {
	Warrior* Wset[WARRIOR_PER_CITY]; // The Warriors it belongs to
	headquarterType hType;
	char name[20];
	warriorType seq[WNUM]; // Construction Sequence
	int curWarrior = -1;
	bool active = true; // Still making warriors?
	int occupied = 0; // Number of occupation warrior by enemy
public:
	Headquarter(int id_, char* name_, warriorType seq_[WNUM]);
	bool reset(int id_, int life_ = 0);
	bool WarriorBorn();
	bool LionRun();
	~Headquarter();
	friend bool WarriorBorn(Headquarter* H);
	friend bool LionRun(Headquarter* H);
	friend bool linkWarriorCity(Warrior* W, City* C);
	friend bool WarriorMove(Headquarter* rHQ, Headquarter* bHQ);
	friend bool WarriorGetLife(City* C);
};

// Warrior
class Warrior {
	int id;
	int life;
	int damage;	
	Headquarter* HQ = NULL; // Which headquarter it belongs to
	City* curPlace = NULL; // Where it is
protected:
	warriorType waType;
public:
	Warrior(int id_, int life_, int damage_);
	virtual ~Warrior();
	virtual bool printState() = 0;
	virtual int getLoyalty() {return 1;};
	friend bool WarriorBorn(Headquarter* H);
	friend bool LionRun(Headquarter* H);
	friend bool linkWarrior2Headquarter(Warrior* W, Headquarter* H);
	friend bool linkWarriorCity(Warrior* W, City* C);
	friend bool WarriorMove(Headquarter* rHQ, Headquarter* bHQ);
	friend bool WarriorGetLife(City* C);
};

class dragon : public Warrior {
	double morale;
	weaponType weapon;
public:
	dragon(int id_, int life_, int damage_, double morale_);
	~dragon();
	bool printState();
};

class ninja : public Warrior {
	weaponType weapon[2];
public:
	ninja(int id_, int life_, int damage_);
	~ninja();
	bool printState();
};

class iceman : public Warrior {
	weaponType weapon;
public:
	iceman(int id_, int life_, int damage_);
	~iceman();
	bool printState();
};

class lion : public Warrior {
	int loyalty;
public:
	lion(int id_, int life_, int damage_, int loyalty_);
	~lion();
	bool printState();
	int getLoyalty();
};

class wolf : public Warrior {
public:
	wolf(int id_, int life_, int damage_);
	~wolf();
	bool printState();
};

// Cpp File
Warrior::Warrior(int id_, int life_, int damage_) : id(id_), life(life_), damage(damage_) { };
dragon::dragon(int id_, int life_, int damage_, double morale_) : Warrior(id_, life_, damage_), morale(morale_) { waType = DRAGON; };
ninja::ninja(int id_, int life_, int damage_) : Warrior(id_, life_, damage_) { waType = NINJA; };
iceman::iceman(int id_, int life_, int damage_) : Warrior(id_, life_, damage_) { waType = ICEMAN; };
lion::lion(int id_, int life_, int damage_, int loyalty_) : Warrior(id_, life_, damage_), loyalty(loyalty_) { waType = LION; };
wolf::wolf(int id_, int life_, int damage_) : Warrior(id_, life_, damage_) { waType = WOLF; };

Warrior::~Warrior() {};
dragon::~dragon() {};
ninja::~ninja() {};
iceman::~iceman() {};
lion::~lion() {};
wolf::~wolf() {};

bool dragon::printState() {
	cout << "Its morale is " << setiosflags(ios::fixed) << setprecision(2) << morale << endl;
	return true;
};

bool ninja::printState() { };

bool iceman::printState() { };

bool lion::printState() {
	cout << "It's loyalty is " << loyalty << endl;
};

int lion::getLoyalty() {
	return loyalty;
};

bool wolf::printState() { };

City::City(int id_) : id(id_) { 
	for(int i = 0; i < 2; i++ ) {
		Pset[i] = NULL;
	}
};
City::~City() {};
Headquarter::~Headquarter() {};
Headquarter::Headquarter(int id_, char* name_, warriorType seq_[WNUM]) : City(id_) {
	for(int i = 0; i < WARRIOR_PER_CITY; i++ ) {
		Wset[i] = NULL;
	}
	strcpy(name, name_);
	for(int i = 0; i < WNUM; i++)
		seq[i] = seq_[i];
	
}

bool City::reset(int id_, int life_) {
	id = id_;
	life = life_;
	WarriorVol = 0;
	for(int i = 0; i < 2; i++) {
		if(Pset[i])
			delete Pset[i];
		Pset[i] = NULL;
	}
	return true;
}

bool City::generateLife() {
	life += 10;
	return true;
}

bool Headquarter::reset(int id_, int life_) {
	City::reset(id_, life_);
	for(int i = 0; i < WarriorVol; i++) {
		if(Wset[i])
			delete Wset[i];
		Wset[i] = NULL;
	}
	occupied = 0;
	return true;
}

bool LionRun(Headquarter* H) {
	int hour = curtime % 60;
	int minute = curtime - hour * 60;
	bool flag = false;
	for(int i = 0; i < H->WarriorVol; i++ ) {
		if(H->Wset[i] && H->waType == LION && H->Wset[i]->getLoyalty() <= 0) {
			flag = true;
			cout << setfill('0') << setw(3) << hour << ":" << setfill('0') << setw(2) << minute << " " ;
			// cout << name << " " << Wset[WarriorVol-1]->getName() << " " << Wset[WarriorVol-1]->getId() << " ran away" << endl;
			delete H->Wset[i];
			H->Wset[i] = NULL;
		}
	}
	return flag;
}

bool WarriorBorn(Headquarter* H) {
	warrior_t w;
	for(int cnt = 1; cnt < WNUM + 1; cnt++) {
		w = warriorDic[seq[(cnt + H->curWarrior) % 5]];
		if(H->life - w.life >= 0) {
			H->life -= w.life;
			H->curWarrior = (cnt + H->curWarrior) % 5;
			assert(H->WarriorVol < WARRIOR_PER_CITY);
			switch(H->seq[H->curWarrior]) {
    				case DRAGON : 
					H->Wset[H->WarriorVol] = new dragon(H->WarriorVol+1, w.life, w.damage, (double) H->life / (double) w.life);
             				break;       
    				case NINJA : 
					H->Wset[H->WarriorVol] = new ninja(H->WarriorVol+1, w.life, w.damage);
             				break;       
    				case ICEMAN : 
					H->Wset[H->WarriorVol] = new iceman(H->WarriorVol+1, w.life, w.damage);
             				break;       
    				case LION :
					H->Wset[H->WarriorVol] = new lion(H->WarriorVol+1, w.life, w.damage, H->life);
             				break;       
    				case WOLF : 
					H->Wset[H->WarriorVol] = new wolf(H->WarriorVol+1, w.life, w.damage);
             				break;       
			}
			// Link each other
			H->Wset[H->WarriorVol]->HQ = H;
			H->Wset[H->WarriorVol]->curPlace = H;
			if(H->hType == RED) 
				H->Pset[RED] = H->Wset[H->WarriorVol];
			else if(H->hType == BLUE)
				H->Pset[BLUE] = H->Wset[H->WarriorVol];
			else return false;

			WarriorVol++;

			// Print Result
			int minute = curtime % 60;
			int hour = (curtime - minute) / 60;
			cout << setfill('0') << setw(3) << hour << ":" << setfill('0') << setw(2) << minute << " " ;
			// cout << name << " " << Wset[WarriorVol-1]->getName() << " " << Wset[WarriorVol-1]->getId() << " born" << endl;
			// Wset[WarriorVol-1] -> printState();
			return true;
		}
	}
	return false;
}

bool WarriorMove() {
	// First perform move, then perform print
	// Red should process from right to left, blue left to right, or it will override
	int minute = curtime % 60;
	int hour = (curtime - minute) / 60;
	


	return true;
}

bool linkWarriorCity(Warrior* W, City* C) {
	W->curPlace = C;
	if(W->HQ->hType == RED) {
		C->Pset[RED] = W;
	}
	else if(W->HQ->hType == BLUE) {
		C->Pset[BLUE] = W;
	}
	else {
		return false;
	}
	return true;
}

bool linkWarrior2Headquarter(Warrior* W, Headquarter* H) {
	W->HQ = H;
	return true;
}

bool WarriorGetLife(City* C) {
	if(C->Pset[RED] && !C->Pset[BLUE]) {
		C->Pset[RED]->HQ->life += C->life;
		C->life = 0;
		return true;
	}	
	if(C->Pset[BLUE] && !C->Pset[RED]) {
		C->Pset[BLUE]->HQ->life += C->life;
		C->life = 0;
		return true;
	}	
	return false;
}


// Main File
int main() {
	// Setting
	int round;
	int M, R, K, T; // N is global
	warriorType redSeq[WNUM] = {ICEMAN, LION, WOLF, NINJA, DRAGON};
	warriorType blueSeq[WNUM] = {LION, DRAGON, NINJA, ICEMAN, WOLF};
	Headquarter* rHQ = new Headquarter(0, (char *)"red", redSeq);
	Headquarter* bHQ = new Headquarter(0, (char *)"blue", blueSeq);
	for(int i = 0; i < MAXCITY; i++)
		cityMap[i] = NULL;

	// Input and Initialization	
	cin >> round;
	for(int i = 0; i < round; i++ ) {
		cout << "Case:" << i + 1 << endl;
		// Get input
		cin >> M >> N >> R >> K >> T;
		
		for(int j = 0; j < WNUM; j++) {
			warriorDic[j].wType = static_cast<warriorType>(j);
			cin >> warriorDic[j].life;
		}
		for(int j = 0; j < WNUM; j++)
			cin >> warriorDic[j].damage;
		
		// Environment Reset
		curtime = 0;
		rHQ -> reset(0, M);
		bHQ -> reset(N + 1, M);
		cityMap[0] = rHQ;
		cityMap[N + 1] = bHQ;
		for(int j = 1; j < N + 1; j++)
			cityMap[j] = new City(j);
		curtime = -5;
				
		// 0: Warrior Born 
		curtime += 5;
		// rHQ->WarriorBorn();
		// bHQ->WarriorBorn();

		// 1: Lion Run
		curtime += 5;
		// rHQ->LionRun();
		// bHQ->LionRun();		

		// 2: Warrior Move
		curtime += 5;
		WarriorMove(rHQ, bHQ);

		// 3: Generate life
		curtime += 10;
		for(int j = 0; j < N + 2; j++)
			cityMap[j]-> generateLife();
		
		// 4: Warrior Get life
		curtime += 10;
		for(int j = 0; j < N + 2; j++)
			WarriorGetLife(cityMap[j]);	

		// 5: Warrior Arrow Shoot
		

		// End this round
		for(int j = 1; j < N + 1; j++) {
			cityMap[j]->reset(0, 0);
			delete cityMap[j];
		}
	}

	// End and delete
	delete rHQ;
	delete bHQ;

	return 0;
}
