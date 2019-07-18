#include <iostream>
#include <iomanip>
#include <cstring>
#include <cassert>
#include <cmath>

using namespace std;

// global variable
const int MAXCITY = 22;
const int WEAPON_COUNT = 3;
const int WARRIOR_COUNT = 5; 
const int WARRIOR_PER_HEADQUARTER = 10000; 
int M, N, R, K, T;
int curtime = 0;
class City;
class Headquarter;
class Warrior;
class Weapon;
class arrow;
class bomb;
class sword;
City* cityMap[MAXCITY];


// database
enum weaponType {SWORD, BOMB, ARROW};
const char* weName[] = {"sword", "bomb", "arrow"};
enum warriorType {DRAGON, NINJA, ICEMAN, LION, WOLF}; 
const char* waName[] = {"dragon", "ninja", "iceman", "lion", "wolf"};
enum headquarterType {RED, BLUE, UNFLAGGED};
const char* hName[] = {"red", "blue", "unflagged"};

struct warrior_t {
	warriorType wType;
	int life;
	int damage;
} warriorDic[WARRIOR_COUNT];

// action functions
bool warriorBorn(Headquarter* H);
bool lionRun(City* C);
bool warriorMove();
bool warriorGetLife(City* C);
bool arrowAttack(Headquarter* rHQ, Headquarter* bHQ);
bool bombExplode();
bool fighting();
bool recordLionLife(Headquarter* H);
bool weaponReport();
bool getWeapon(Warrior* victor, Warrior* killed);

// Warrior
class Warrior {
	City* C = NULL; 
protected:
	int id;
	int life;
	int damage;
	warriorType waType;
	Headquarter* HQ = NULL; 
	arrow* myArrow = NULL;
	bomb* myBomb = NULL;
	sword* mySword = NULL;
public:
	Warrior(int id_, int life_, int damage_);
	bool weaponReport(headquarterType hType);
	virtual ~Warrior();
	friend bool warriorBorn(Headquarter* H);
	friend bool lionRun(City* C);
	friend bool warriorMove();
	friend bool warriorGetLife(City* C);
	friend bool arrowAttack();
	friend bool bombExplode();
	friend bool fighting();
	friend bool recordLionLife(Headquarter* H);
	friend bool getWeapon(Warrior* victor, Warrior* killed);
	virtual bool born() { return false; }
	virtual bool run() { return false; } // used for lion
	virtual bool move() { return false; } // used for iceman
	virtual bool arrowAttack(Warrior* enemy);
	virtual int attack(Warrior* enemy, int cityNumber);
	virtual int counterAttack(Warrior* enemy, int cityNumber);
	virtual bool useBomb(Warrior* enemy);
	virtual bool recordLife(int life_) { return false; }
	virtual int showLife() { return false; }
	virtual bool increaseMorale() { return false; }
	virtual bool decreaseMorale() { return false; }
	virtual bool yell(int cityNumber, headquarterType dragonHQ) { return false; }
	virtual bool decreaseLoyalty() { return false; }
};

class dragon : public Warrior {
	double morale;
public:
	dragon(int id_, int life_, int damage_, double morale_);
	~dragon();
	bool cheer() { }
	bool born() { cout << "Its morale is " << setiosflags(ios::fixed) << setprecision(2) << morale << endl; }
	bool increaseMorale() { morale += 0.2; return true; }
	bool decreaseMorale() { morale -= 0.2; return true; }
	bool yell(int cityNumber, headquarterType dragonHQ) { 
		int minute = curtime % 60;
		int hour = (curtime - minute) / 60;
		if(morale > 0.8) {
			cout << setfill('0') << setw(3) << hour << ":" << setfill('0') << setw(2) << minute << " " ;
			cout << hName[dragonHQ] << " dragon " << id << " yelled in city " << cityNumber << endl;
		}
		return true; 
	}
};

class ninja : public Warrior {
public:
	ninja(int id_, int life_, int damage_);
	~ninja();
};

class iceman : public Warrior {
	bool trade = true; // trade life with attack
public:
	iceman(int id_, int life_, int damage_);
	~iceman();
	bool move() { 
		trade = !trade;
		if(trade) {
			damage += 20;
			if(life > 9)
				life-=9;
			else
				life = 1;	
			return true;			
		}	
		return false;
	}
};

class lion : public Warrior {
	int loyalty;
	int prefightLife = 0;
public:
	lion(int id_, int life_, int damage_, int loyalty_);
	~lion();
	bool born() { cout << "Its loyalty is " << loyalty << endl; }
	bool run() { return loyalty <= 0; }
	bool recordLife(int life_) { if(life_ > 0) prefightLife = life_; else prefightLife = 0; return true; }
	int showLife() { return prefightLife; }
	bool decreaseLoyalty() { loyalty -= K; return true; }
};

class wolf : public Warrior {
public:
	wolf(int id_, int life_, int damage_);
	~wolf();
};

// weapon
class Weapon {
protected: 
	weaponType weType; 
public:
	Weapon();
	virtual ~Weapon();
};

class sword : public Weapon {
	int damage;
public:
	sword(int damage_);
	~sword();
	friend int Warrior::attack(Warrior* enemy, int cityNumber);
	friend int Warrior::counterAttack(Warrior* enemy, int cityNumber);
	friend bool Warrior::useBomb(Warrior* enemy);
	friend bool Warrior::weaponReport(headquarterType hType);
	friend bool getWeapon(Warrior* victor, Warrior* killed);
};

class bomb : public Weapon {
public:
	bomb();
	~bomb();
	friend bool Warrior::weaponReport(headquarterType hType);
	friend bool getWeapon(Warrior* victor, Warrior* killed);
};

class arrow : public Weapon {
	int damage;
	int residueNum = 3;
public:
	arrow(int damage_);
	~arrow();
	friend bool Warrior::arrowAttack(Warrior* enemy);
	friend bool Warrior::weaponReport(headquarterType hType);
	friend bool getWeapon(Warrior* victor, Warrior* killed);
};


// city (headquanter / town)
class City {
	headquarterType consecutiveDirection = UNFLAGGED; 
protected:
	int id = 0;
	int life = 0;
	Warrior* pSet[2] = {NULL, NULL}; // script RED, BLUE
	headquarterType flag = UNFLAGGED; 
public:
	City(int id_);
	virtual ~City();
	bool generateLife() { life += 10; return true; }
	friend bool warriorBorn(Headquarter* H);
	friend bool lionRun(City* C);
	friend bool warriorMove();
	friend bool warriorGetLife(City* C);
	friend bool arrowAttack();
	friend bool bombExplode();
	friend bool fighting();
	friend bool weaponReport();
};


class Headquarter : public City {
	headquarterType hType;
	Warrior* wSet[WARRIOR_PER_HEADQUARTER]; // warrior database
	warriorType seq[WARRIOR_COUNT]; // warrior born sequence
	int curWarrior = -1;
	int WarriorVolume = 0; // number of existing warrior under this headquarter 
public:
	Headquarter(int id_, headquarterType hType_, warriorType seq_[WARRIOR_COUNT]);
	~Headquarter();
	bool reset(int id_, int life_);
	bool reportElements();
	friend bool warriorBorn(Headquarter* H);
	friend bool lionRun(City* C);
	friend bool warriorMove();
	friend bool warriorGetLife(City* C);
	friend bool arrowAttack();
	friend bool Warrior::arrowAttack(Warrior* enemy);
	friend bool Warrior::useBomb(Warrior* enemy);
	friend int Warrior::attack(Warrior* enemy, int cityNumber);
	friend int Warrior::counterAttack(Warrior* enemy, int cityNumber);
	friend bool bombExplode();
	friend bool recordLionLife(Headquarter* H);
	friend bool fighting();
};


// cpp file
// Constructor and Destructor
Weapon::Weapon() { }
sword::sword(int damage_) : Weapon(), damage(damage_) { weType = SWORD; }
bomb::bomb() { weType = BOMB; }
arrow::arrow(int damage_) : Weapon(), damage(damage_) { weType = ARROW; }
Warrior::Warrior(int id_, int life_, int damage_) : id(id_), life(life_), damage(damage_) { }

dragon::dragon(int id_, int life_, int damage_, double morale_) : Warrior(id_, life_, damage_), morale(morale_) {
	switch( id%3 ) {
		case SWORD:
			if(floor(damage/5))
				mySword = new sword(floor(damage/5));
			break;
		case BOMB:
			myBomb = new bomb();
			break;
		case ARROW:
			myArrow = new arrow(R);
			break;
	}
	waType = DRAGON; 
}

ninja::ninja(int id_, int life_, int damage_) : Warrior(id_, life_, damage_) { 
	switch( id%3 ) {
		case SWORD:
			if(floor(damage/5))
				mySword = new sword(floor(damage/5));
			myBomb = new bomb();
			break;
		case BOMB:
			myBomb = new bomb();
			myArrow = new arrow(R);
			break;
		case ARROW:
			myArrow = new arrow(R);
			if(floor(damage/5))
				mySword = new sword(floor(damage/5));
			break;
	}	
	waType = NINJA; 
}

iceman::iceman(int id_, int life_, int damage_) : Warrior(id_, life_, damage_) { 
	switch( id%3 ) {
		case SWORD:
			if(floor(damage/5))
				mySword = new sword(floor(damage/5));
			break;
		case BOMB:
			myBomb = new bomb();
			break;
		case ARROW:
			myArrow = new arrow(R);
			break;
	}
	waType = ICEMAN; 
}

lion::lion(int id_, int life_, int damage_, int loyalty_) : Warrior(id_, life_, damage_), loyalty(loyalty_) { waType = LION; }
wolf::wolf(int id_, int life_, int damage_) : Warrior(id_, life_, damage_) { waType = WOLF; }
City::City(int id_) : id(id_) { };

Headquarter::Headquarter(int id_, headquarterType hType_, warriorType seq_[WARRIOR_COUNT]) : City(id_), hType(hType_) {
	for(int i = 0; i < WARRIOR_PER_HEADQUARTER; i++ ) 
		wSet[i] = NULL;
	for(int i = 0; i < WARRIOR_COUNT; i++)
		seq[i] = seq_[i];
}

Weapon::~Weapon() { }
sword::~sword() { }
bomb::~bomb() { }
arrow::~arrow() { }
Warrior::~Warrior() { delete mySword; delete myArrow; delete myBomb; };
dragon::~dragon() { }
ninja::~ninja() { }
iceman::~iceman() { }
lion::~lion() { }
wolf::~wolf() { }
City::~City() { }
Headquarter::~Headquarter() { for(int i = 0; i < WarriorVolume; i++ ) if(wSet[i]) delete wSet[i]; }


// Methods
bool Warrior::useBomb(Warrior* enemy) {
	int minute = curtime % 60;
	int hour = (curtime - minute) / 60;
	if(!enemy || life <= 0 || enemy->life<=0)
		return false;

	// parameter copy
	int myLife = life;
	int enemyLife = enemy->life;

	// attack
	enemyLife -= damage;
	if(mySword)
		enemyLife -= mySword->damage;
	if(enemyLife <= 0) {
		if(enemy->myBomb) { 
			// print bomb info
			cout << setfill('0') << setw(3) << hour << ":" << setfill('0') << setw(2) << minute << " " ; 
			cout << hName[enemy->HQ->hType] << " " << waName[enemy->waType] << " " << enemy->id << " used a bomb and killed ";
			cout << hName[HQ->hType] << " " << waName[waType] << " " << id << endl;
			return true;
		}
		else return false;
	} 
	else if(enemy->waType != NINJA) {
		// Counter Attack
		myLife -= floor(enemy->damage * 0.5);
		if(enemy->mySword) {
			myLife -= enemy->mySword->damage;
		}
		if(myLife <= 0) {
			if(myBomb) {
				// print bomb info
				cout << setfill('0') << setw(3) << hour << ":" << setfill('0') << setw(2) << minute << " " ; 
				cout << hName[HQ->hType] << " " << waName[waType] << " " << id << " used a bomb and killed ";
				cout << hName[enemy->HQ->hType] << " " << waName[enemy->waType] << " " << enemy->id << endl;
				return true;
			}
			else return false;		
		}
		else return false;
	}
	else return false;		
}

bool Warrior::arrowAttack(Warrior* enemy) {
	int minute = curtime % 60;
	int hour = (curtime - minute) / 60;
	if(!enemy || !myArrow)
		return false;
	myArrow->residueNum--;
	enemy->life -= R;
	if(!myArrow->residueNum) {
		delete myArrow;
		myArrow = NULL;
	}
	cout << setfill('0') << setw(3) << hour << ":" << setfill('0') << setw(2) << minute << " " ; 
	cout << hName[HQ->hType] << " " << waName[waType] << " " << id << " shot" ;
	if(enemy->life <= 0) 
		cout << " and killed " << hName[enemy->HQ->hType] << " " << waName[enemy->waType] << " " << enemy->id;
	cout << endl;
	return true;		
}

int Warrior::attack(Warrior* enemy, int cityNumber) { 
	int minute = curtime % 60;
	int hour = (curtime - minute) / 60;
	// 2: BLUE ARROW KILLED 1: RED WIN 0: N/A -1: BLUE WIN -2: RED ARROW KILLED 3/-3: PREPARE FOR COUNTER ATTACK 
	if(!enemy || (life <= 0 && enemy->life <= 0))
		return 0;
	// killed by arrow
	if(life <= 0 && enemy->life > 0)
		return -2;
	if(life > 0 && enemy->life <= 0)
		return 2;
	// print attack
	cout << setfill('0') << setw(3) << hour << ":" << setfill('0') << setw(2) << minute << " " ; 
	cout << hName[HQ->hType] << " " << waName[waType] << " " << id << " attacked ";
	cout << hName[enemy->HQ->hType] << " " << waName[enemy->waType] << " " << enemy->id;
	cout << " in city " << cityNumber << " with " << life << " elements and force " << damage << endl;

	// start attack
	enemy->life -= damage;
	if(mySword) {
		enemy->life -= mySword->damage;
		mySword->damage = floor(mySword->damage * 0.8);
		if(!mySword->damage) {
			delete mySword;
			mySword = NULL;
		}	
	}
	if(enemy->life <= 0) {
		return 1;
	} 
	else return 3; // start counter attack
}

int Warrior::counterAttack(Warrior* enemy, int cityNumber) {
	int minute = curtime % 60;
	int hour = (curtime - minute) / 60;
	// 2: BLUE ARROW KILLED 1: RED WIN 0: N/A -1: BLUE WIN -2: RED ARROW KILLED 3/-3: PREPARE FOR COUNTER ATTACK 
	if(!enemy)
		return 0;

	// killed by arrow
	if(life <= 0)
		return -2;
	if(enemy->life <= 0)
		return 2;
	// print attack
	cout << setfill('0') << setw(3) << hour << ":" << setfill('0') << setw(2) << minute << " " ; 
	cout << hName[HQ->hType] << " " << waName[waType] << " " << id << " fought back against ";
	cout << hName[enemy->HQ->hType] << " " << waName[enemy->waType] << " " << enemy->id;
	cout << " in city " << cityNumber << endl;

	// start attack
	enemy->life -= floor(damage * 0.5);
	if(mySword) {
		enemy->life -= mySword->damage;
		mySword->damage = floor(mySword->damage * 0.8);
		if(!mySword->damage) {
			delete mySword;
			mySword = NULL;
		}	
	}
	if(enemy->life <= 0) 
		return 1;
	else return 3; 
}

bool Warrior::weaponReport(headquarterType hType) {
	bool hasWeapon = false;
	bool comma = false;
	int minute = curtime % 60;
	int hour = (curtime - minute) / 60;
	cout << setfill('0') << setw(3) << hour << ":" << setfill('0') << setw(2) << minute << " " ;
	cout << hName[hType] << " " << waName[waType] << " " << id << " has ";
	if(myArrow) {
		hasWeapon = true;
		cout << weName[myArrow->weType] << "(" << myArrow->residueNum << ")";
		comma = true;
	}
	if(myBomb) {
		if(comma) cout << ',';
		hasWeapon = true;
		cout << weName[myBomb->weType];
		comma = true;
	}
	if(mySword) {
		if(comma) cout << ',';
		hasWeapon = true;
		cout << weName[mySword->weType] << "(" << mySword->damage << ")";
		comma = true;
	}
	if(!hasWeapon)
		cout << "no weapon";
	cout << endl;
	return true;
}

bool Headquarter::reset(int id_, int life_) { 
	id = id_;
	life = life_;
	pSet[0] = pSet[1] = NULL;
	flag = UNFLAGGED;
	for(int i = 0; i < WARRIOR_PER_HEADQUARTER; i++) {
		wSet[i] = NULL;
	}
	curWarrior = -1;
	WarriorVolume = 0;
	return true;
}

bool Headquarter::reportElements() {
	int minute = curtime % 60;
	int hour = (curtime - minute) / 60;
	cout << setfill('0') << setw(3) << hour << ":" << setfill('0') << setw(2) << minute << " " ;
	cout << life << " elements in " << hName[hType] << " headquarter" << endl;
	return true;
}

bool warriorBorn(Headquarter* H) { 
	warrior_t w;
	w = warriorDic[H->seq[(1 + H->curWarrior) % 5]];
	if(H->life - w.life >= 0) {
		H->life -= w.life;
		H->curWarrior = (1 + H->curWarrior) % 5;
		assert(H->WarriorVolume < WARRIOR_PER_HEADQUARTER);
		switch(H->seq[H->curWarrior]) {
    			case DRAGON : 
				H->wSet[H->WarriorVolume] = new dragon(H->WarriorVolume + 1, w.life, w.damage, (double) H->life / (double) w.life);
            				break;       
    			case NINJA : 
				H->wSet[H->WarriorVolume] = new ninja(H->WarriorVolume + 1, w.life, w.damage);
            				break;       
    			case ICEMAN : 
				H->wSet[H->WarriorVolume] = new iceman(H->WarriorVolume + 1, w.life, w.damage);
            				break;       
    			case LION :
				H->wSet[H->WarriorVolume] = new lion(H->WarriorVolume + 1, w.life, w.damage, H->life);
            				break;       
    			case WOLF : 
				H->wSet[H->WarriorVolume] = new wolf(H->WarriorVolume + 1, w.life, w.damage);
            				break;       
		}
		// Link each other
		H->wSet[H->WarriorVolume]->HQ = H;
		H->wSet[H->WarriorVolume]->C = H;
		if(H->hType == RED) 
			H->pSet[RED] = H->wSet[H->WarriorVolume];
		else if(H->hType == BLUE)
			H->pSet[BLUE] = H->wSet[H->WarriorVolume];
		else return false;
		// Print Result
		int minute = curtime % 60;
		int hour = (curtime - minute) / 60;
		cout << setfill('0') << setw(3) << hour << ":" << setfill('0') << setw(2) << minute << " " ;
		cout << hName[H->hType] << " " << waName[H->wSet[H->WarriorVolume]->waType] << " " << H->wSet[H->WarriorVolume]->id << " born" << endl;
		H->wSet[H->WarriorVolume]->born();

		// Upadte Volume
		H->WarriorVolume++;
		return true;
	}
	return false;
}

bool lionRun(City* C) { 	
	int minute = curtime % 60;
	int hour = (curtime - minute) / 60;
	bool flag = false;
	for(int i = 0; i < 2; i++ ) {
		if(C->pSet[i] && C->pSet[i]->waType == LION && C->pSet[i]->run()) {
			cout << setfill('0') << setw(3) << hour << ":" << setfill('0') << setw(2) << minute << " " ;
			cout << hName[C->pSet[i]->HQ->hType] << " lion " << C->pSet[i]->id << " ran away" << endl;
			C->pSet[i] = NULL;
			flag = true;
		}
	}
	return flag;
}

bool warriorMove() {
	bool redReachHQ = false;
	bool blueReachHQ = false;
	bool redHQhasBlueWarrior = cityMap[0]->pSet[BLUE];
	bool blueHQhasRedWarrior = cityMap[N+1]->pSet[RED];
	bool endGame = false;

	int minute = curtime % 60;
	int hour = (curtime - minute) / 60;
	Warrior* current;
	// red warrior 
	for(int i = N; i >= 0; i--) {
		if(cityMap[i]->pSet[RED]) {
			cityMap[i]->pSet[RED]->move();
			cityMap[i+1]->pSet[RED] = cityMap[i]->pSet[RED];
			cityMap[i]->pSet[RED]->C = cityMap[i+1];
			cityMap[i]->pSet[RED] = NULL;
			if(i == N)
				redReachHQ = true;
		}
	}

	// blue warrior
	for(int i = 1; i < N+2; i++) {
		if(cityMap[i]->pSet[BLUE]) {
			cityMap[i]->pSet[BLUE]->move();
			cityMap[i-1]->pSet[BLUE] = cityMap[i]->pSet[BLUE];
			cityMap[i]->pSet[BLUE]->C = cityMap[i-1];
			cityMap[i]->pSet[BLUE] = NULL;
			if(i == 1)
				blueReachHQ = true;
		}
	}

	// Blue reach headquarter
	if(blueReachHQ) {
		cout << setfill('0') << setw(3) << hour << ":" << setfill('0') << setw(2) << minute << " " ;
		cout << "blue " << waName[cityMap[0]->pSet[BLUE]->waType] << " " << cityMap[0]->pSet[BLUE]->id << " ";
		cout << "reached red headquarter with " << cityMap[0]->pSet[BLUE]->life << " elements and force " << cityMap[0]->pSet[BLUE]->damage << endl;
		blueReachHQ = true;
	}


	// march
	for(int i = 1; i < N+1; i++) {
		current = cityMap[i]->pSet[RED];
		if(current) {
			cout << setfill('0') << setw(3) << hour << ":" << setfill('0') << setw(2) << minute << " " ;
			cout << hName[current->HQ->hType] << " " << waName[current->waType] << " " << current->id << " ";
			cout << "marched to city " << i << " with " << current->life << " elements and force " << current->damage << endl;
		}
		current = cityMap[i]->pSet[BLUE];
		if(current) {
			cout << setfill('0') << setw(3) << hour << ":" << setfill('0') << setw(2) << minute << " " ;
			cout << hName[current->HQ->hType] << " " << waName[current->waType] << " " << current->id << " ";
			cout << "marched to city " << i << " with " << current->life << " elements and force " << current->damage << endl;		
		}
	}

	// Red reach headquarter
	if(redReachHQ) {
		cout << setfill('0') << setw(3) << hour << ":" << setfill('0') << setw(2) << minute << " " ;
		cout << "red " << waName[cityMap[N+1]->pSet[RED]->waType] << " " << cityMap[N+1]->pSet[RED]->id << " ";
		cout << "reached blue headquarter with " << cityMap[N+1]->pSet[RED]->life << " elements and force " << cityMap[N+1]->pSet[RED]->damage << endl;
		redReachHQ = true;
	}

	// Headqusrter Taken
	if(blueReachHQ && redHQhasBlueWarrior) {
		cout << setfill('0') << setw(3) << hour << ":" << setfill('0') << setw(2) << minute << " " ;
		cout << "red headquarter was taken" << endl;
		endGame = true;
	}
	if(redReachHQ && blueHQhasRedWarrior) {
		cout << setfill('0') << setw(3) << hour << ":" << setfill('0') << setw(2) << minute << " " ;
		cout << "blue headquarter was taken" << endl;
		endGame = true;
	}
	return endGame; 
}

bool warriorGetLife(City* C) { 

	int minute = curtime % 60;
	int hour = (curtime - minute) / 60;

	if(C->pSet[RED] && !C->pSet[BLUE]) {
		cout << setfill('0') << setw(3) << hour << ":" << setfill('0') << setw(2) << minute << " " ;
		cout << hName[C->pSet[RED]->HQ->hType] << " " << waName[C->pSet[RED]->waType] << " " << C->pSet[RED]->id << " ";
		cout << "earned " << C->life << " elements for his headquarter" << endl;	
		C->pSet[RED]->HQ->life += C->life;
		C->life = 0;
	}
	if(C->pSet[BLUE] && !C->pSet[RED]) {
		cout << setfill('0') << setw(3) << hour << ":" << setfill('0') << setw(2) << minute << " " ;
		cout << hName[C->pSet[BLUE]->HQ->hType] << " " << waName[C->pSet[BLUE]->waType] << " " << C->pSet[BLUE]->id << " ";
		cout << "earned " << C->life << " elements for his headquarter" << endl;	
		C->pSet[BLUE]->HQ->life += C->life;
		C->life = 0;
	}	
	return true; 
}

bool arrowAttack() {
	// attack, no enemy in headquarter
	for(int i = 1; i < N+1; i++) {
		if(cityMap[i]->pSet[RED])
			cityMap[i]->pSet[RED]->arrowAttack(cityMap[i+1]->pSet[BLUE]); 
		if(cityMap[i]->pSet[BLUE])
			cityMap[i]->pSet[BLUE]->arrowAttack(cityMap[i-1]->pSet[RED]);

	}
	return true;
}

bool bombExplode() {
	int minute = curtime % 60;
	int hour = (curtime - minute) / 60;
	bool ifBomb;
	for(int i = 1; i < N+1; i++) {
		ifBomb = false;
		if(((cityMap[i]->flag == UNFLAGGED && i % 2 == 1) || cityMap[i]->flag == RED ) && cityMap[i]->pSet[RED])
			ifBomb = cityMap[i]->pSet[RED]->useBomb(cityMap[i]->pSet[BLUE]);
		else if(cityMap[i]->pSet[BLUE])
			ifBomb = cityMap[i]->pSet[BLUE]->useBomb(cityMap[i]->pSet[RED]);			
		if(ifBomb) {
			cityMap[i]->pSet[RED] = NULL;
			cityMap[i]->pSet[BLUE] = NULL;
		}
	}		
	return true;
}

bool recordLionLife(Headquarter* H) {
	for(int i = 0; i < H->WarriorVolume; i++) {
		if(H->wSet[i] && H->wSet[i]->waType == LION)
			H->wSet[i]->recordLife(H->wSet[i]->life);
	}
	return true;
}

bool fighting() {
	int minute = curtime % 60;
	int hour = (curtime - minute) / 60;
	int result = 0; // 2: BLUE ARROW KILLED 1: RED WIN 0: N/A -1: BLUE WIN -2: RED ARROW KILLED 3/-3: PREPARE FOR COUNTER ATTACK 
	
	headquarterType attacker;
	headquarterType killed;
	headquarterType victor;

	for(int i = 1; i < N+1; i++) {
		result = 0;
		// Attack
		if(((cityMap[i]->flag == UNFLAGGED && i % 2 == 1) || cityMap[i]->flag == RED) && cityMap[i]->pSet[RED]) {
			attacker = RED;
			result = cityMap[i]->pSet[RED]->attack(cityMap[i]->pSet[BLUE], i);
		}
		else if(cityMap[i]->pSet[BLUE]) {
			attacker = BLUE;
			result = -cityMap[i]->pSet[BLUE]->attack(cityMap[i]->pSet[RED], i);			
		}			

		// Counter Attack: for those +3/-3
		if(result == 3 && cityMap[i]->pSet[BLUE]->waType != NINJA) // blue counter
			result = -cityMap[i]->pSet[BLUE]->counterAttack(cityMap[i]->pSet[RED], i);
		else if(result == -3 && cityMap[i]->pSet[RED]->waType != NINJA)
			result = cityMap[i]->pSet[RED]->counterAttack(cityMap[i]->pSet[BLUE], i);			
	
		
		// Warrior Killed
		if(result == 1 || result == 2) {
			victor = RED;
			killed = BLUE;
		}
		if(result == -1 || result == -2) {
			victor = BLUE;
			killed = RED;
		}
		if(result == 1 || result == -1) {
			cout << setfill('0') << setw(3) << hour << ":" << setfill('0') << setw(2) << minute << " " ;
			cout << hName[cityMap[i]->pSet[killed]->HQ->hType] << " " << waName[cityMap[i]->pSet[killed]->waType] << " " << cityMap[i]->pSet[killed]->id;
			cout << " was killed in city " << i << endl;
		}
		if(result == 1 || result == -1 || result == 2 || result == -2) {
			if(cityMap[i]->pSet[killed]->waType == LION)
				cityMap[i]->pSet[victor]->life += cityMap[i]->pSet[killed]->showLife();
			// dragon morale
			if(cityMap[i]->pSet[victor]->waType == DRAGON) {
				cityMap[i]->pSet[victor]->increaseMorale();
			}
			// wolf get weapon
			if(cityMap[i]->pSet[victor]->waType == WOLF) {
				getWeapon(cityMap[i]->pSet[victor], cityMap[i]->pSet[killed]);
			}
			cityMap[i]->pSet[killed] = NULL;
		}
		if(!result) { // warrior killed by arrow but no enemy
			if(cityMap[i]->pSet[RED] && cityMap[i]->pSet[RED]->life <= 0 )
				cityMap[i]->pSet[RED] = NULL;
			if(cityMap[i]->pSet[BLUE] && cityMap[i]->pSet[BLUE]->life <= 0 )
				cityMap[i]->pSet[BLUE] = NULL;
		}

		if(result == 3 || result == -3) {
			if( cityMap[i]->pSet[RED]->waType == DRAGON ) 
				cityMap[i]->pSet[RED]->decreaseMorale();
			if( cityMap[i]->pSet[BLUE]->waType == DRAGON ) 
				cityMap[i]->pSet[BLUE]->decreaseMorale();
			if( cityMap[i]->pSet[RED]->waType == LION ) 
				cityMap[i]->pSet[RED]->decreaseLoyalty();
			if( cityMap[i]->pSet[BLUE]->waType == LION ) 
				cityMap[i]->pSet[BLUE]->decreaseLoyalty();
			cityMap[i]->consecutiveDirection = UNFLAGGED;
		}	

		// Dragon yelled
		if( result && cityMap[i]->pSet[attacker] && cityMap[i]->pSet[attacker]->waType == DRAGON )
			cityMap[i]->pSet[attacker]->yell(i, cityMap[i]->pSet[attacker]->HQ->hType);	
	
		// Warrior get life from headquarters
		if( result == 1 || result == 2 ) {
			// reward life
			if( cityMap[i]->pSet[RED]->HQ->life > 8 ) {
				cityMap[i]->pSet[RED]->HQ->life -= 8;
				cityMap[i]->pSet[RED]->life += 8;
			}
			cout << setfill('0') << setw(3) << hour << ":" << setfill('0') << setw(2) << minute << " " ;
			cout << hName[cityMap[i]->pSet[RED]->HQ->hType] << " " << waName[cityMap[i]->pSet[RED]->waType] << " " << cityMap[i]->pSet[RED]->id;
			cout << " earned " << cityMap[i]->life << " elements for his headquarter" << endl;	
			cityMap[i]->pSet[RED]->HQ->life += cityMap[i]->life;
			cityMap[i]->life = 0;
		}	
		if( result == -1 || result == -2) {
			if( cityMap[i]->pSet[BLUE]->HQ->life > 8 ) {
				cityMap[i]->pSet[BLUE]->HQ->life -= 8;
				cityMap[i]->pSet[BLUE]->life += 8;
			}
			cout << setfill('0') << setw(3) << hour << ":" << setfill('0') << setw(2) << minute << " " ;
			cout << hName[cityMap[i]->pSet[BLUE]->HQ->hType] << " " << waName[cityMap[i]->pSet[BLUE]->waType] << " " << cityMap[i]->pSet[BLUE]->id;
			cout << " earned " << cityMap[i]->life << " elements for his headquarter" << endl;	
			cityMap[i]->pSet[BLUE]->HQ->life += cityMap[i]->life;
			cityMap[i]->life = 0;
		}

		// Setting flag
		// cout << "city " << i << endl;
		// cout << "flag " << hName[cityMap[i]->flag] << endl;
		// cout << "direction" << hName[cityMap[i]->consecutiveDirection] << endl;
		
		if( result == 1 || result == 2 ) {
			// red win
			if( cityMap[i]->flag != RED && cityMap[i]->consecutiveDirection == RED ) {
				cityMap[i]->flag = RED;
				cityMap[i]->consecutiveDirection = UNFLAGGED;
				cout << setfill('0') << setw(3) << hour << ":" << setfill('0') << setw(2) << minute << " " ;
				cout << "red flag raised in city " << i << endl;
			}
			else
				cityMap[i]->consecutiveDirection = RED;
		}
		if( result == -1 || result == -2 ) {
			// blue win
			if( cityMap[i]->flag != BLUE && cityMap[i]->consecutiveDirection == BLUE) {
				cityMap[i]->flag = BLUE;
				cityMap[i]->consecutiveDirection = UNFLAGGED;
				cout << setfill('0') << setw(3) << hour << ":" << setfill('0') << setw(2) << minute << " " ;
				cout << "blue flag raised in city " << i << endl;
			}
			else
				cityMap[i]->consecutiveDirection = BLUE;
		}

	}	
	return true;
}

bool weaponReport() {
	for(int i = 0; i < N + 2; i++) {
		if(cityMap[i]->pSet[RED])
			cityMap[i]->pSet[RED]->weaponReport(RED);
	}
	for(int i = 0; i < N + 2; i++) {
		if(cityMap[i]->pSet[BLUE])
			cityMap[i]->pSet[BLUE]->weaponReport(BLUE);
	}
	return true;
}

bool getWeapon(Warrior* victor, Warrior* killed) {
	if(!victor->myArrow && killed->myArrow) {
		victor->myArrow = killed->myArrow;
		killed->myArrow = NULL;
	}
	if(!victor->myBomb && killed->myBomb) {
		victor->myBomb = killed->myBomb;
		killed->myBomb = NULL;
	}
	if(!victor->mySword && killed->mySword) {
		victor->mySword = killed->mySword;
		killed->mySword = NULL;
	}
	return true; 
}

// main function
int main() {
	// Setting
	int round;
	warriorType redSeq[WARRIOR_COUNT] = {ICEMAN, LION, WOLF, NINJA, DRAGON};
	warriorType blueSeq[WARRIOR_COUNT] = {LION, DRAGON, NINJA, ICEMAN, WOLF};
	Headquarter* rHQ = new Headquarter(0, RED, redSeq);
	Headquarter* bHQ = new Headquarter(0, BLUE, blueSeq);
	for(int i = 0; i < MAXCITY; i++)
		cityMap[i] = NULL;

	// Input and Initialization	
	cin >> round;
	for(int i = 0; i < round; i++ ) {
		cout << "Case " << i + 1 << ":" << endl;
		// Get input
		cin >> M >> N >> R >> K >> T;
		
		for(int j = 0; j < WARRIOR_COUNT; j++) {
			warriorDic[j].wType = static_cast<warriorType>(j);
			cin >> warriorDic[j].life;
		}
		for(int j = 0; j < WARRIOR_COUNT; j++)
			cin >> warriorDic[j].damage;
		
		// Environment Reset
		rHQ -> reset(0, M);
		bHQ -> reset(N + 1, M);
		cityMap[0] = rHQ;
		cityMap[N + 1] = bHQ;
		for(int j = 1; j < N + 1; j++)
			cityMap[j] = new City(j);
		curtime = -5;
		
		while(curtime <= T) {	
			// 0: Warrior Born 
			curtime += 5;
			if(curtime > T) break;
			warriorBorn(rHQ);
			warriorBorn(bHQ);			

			// 1: Lion Run
			curtime += 5;
			if(curtime > T) break;
			for(int j = 0; j < N + 2; j++)
				lionRun(cityMap[j]);

			// 2: Warrior Move
			// 12: Warrior Reach Headquarter 13: Headquarter Was Taken
			curtime += 5;
			if(curtime > T) break;
			if(warriorMove()) break;
			// cout << curtime << endl;

			// 3: Generate life
			curtime += 10;
			if(curtime > T) break;
			for(int j = 1; j < N + 1; j++)
				cityMap[j]-> generateLife();
			// cout << curtime << endl;
		
			// 4: Warrior Get life
			curtime += 10;
			if(curtime > T) break;
			for(int j = 1; j < N + 1; j++)
				warriorGetLife(cityMap[j]);	
			// cout << curtime << endl;

			// 5: Warrior Arrow Shoot
			curtime += 5;
			if(curtime > T) break;
			arrowAttack();
			// cout << curtime << endl;

			// 6: Warrior Use Bomb (no prediction)
			curtime += 3;
			if(curtime > T) break;
			bombExplode();
			// cout << curtime << endl;

			// 7: Attack 8: Counter Attack 9: Killed
			// 10: Get Elements 11: Flag Raise 
			recordLionLife(rHQ);
			recordLionLife(bHQ);
			curtime += 2;
			if(curtime > T) break;
			fighting();
			// cout << curtime << endl;

			// 14: Headquarter Report elements
			curtime+=10;
			if(curtime > T) break;
			rHQ -> reportElements();
			bHQ -> reportElements();
			// cout << curtime << endl;

			// 15: Warrior Report Weapon
			curtime+=5;
			if(curtime > T) break;
			weaponReport();		
		}

		// End this round
		for(int j = 1; j < N + 1; j++) 
			delete cityMap[j];

		for(int j = 0; j < MAXCITY; j++) 
			cityMap[j] = NULL;
		
	}

	// End and delete
	delete rHQ;
	delete bHQ;

	return 0;
}
