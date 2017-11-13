class vtime{
public:
	vtime();
	vtime(int ayear,int amonth,int aday, int ahour,int aminute,int dyear,int dmonth,int dday,int dhour,int dminute);
	~vtime();
	void printarrival();
	void printdeparture();
	int staytime();
	void printtime();
private:
	int ayr,amon,ad,ahr,amin,dyr,dmon,dd,dhr,dmin,stayingtime;
};