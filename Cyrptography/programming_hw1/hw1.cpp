#define HW3
#ifdef HW3

#include <iostream> 
#include <string>
#include<gmpxx.h>
#include <time.h>
using namespace std;

int main() {	
	mpz_t p,a,b;  
	time_t seed;  
	gmp_randstate_t state;  
  
	//Generate random number a and b
	time(&seed);  
	mpz_init(p);  
	gmp_randinit_default(state);  
	gmp_randseed_ui(state, long(seed)); 
	mpz_urandomb(p, state, 4096);
	mpz_init_set(a,p);
	mpz_urandomb(p, state, 4096);
	mpz_urandomb(p, state, 4096);
	mpz_init_set(b,p);

	//Begin gcd
	mpz_t q,tmp;
	mpz_t r[2],s[2],t[2];
	mpz_init_set(r[0],b); mpz_init_set(r[1],a);  		//r0 = b, r1 = a
	mpz_init_set_si(s[0],0); mpz_init_set_si(s[1],1);	//s0 = 0, s1 = 1
	mpz_init_set_si(t[0],1); mpz_init_set_si(t[1],0);	//t0 = 1, t1 = 0
	mpz_init(q);  
    	mpz_init(tmp); 
	
	
	while(mpz_cmp_ui(r[0], 0) != 0) { //When r0 != 0
		mpz_set(tmp, r[0]);  			//tmp = r0
		mpz_fdiv_qr(q, r[0], r[1], r[0]);  	//q = t / r0, r0 = r1 % r0  
		mpz_set(r[1], tmp);  			//r1 = tmp

		//cout << "r0: " << r[0] << "   r1: " << r[1] << endl;

		mpz_set(tmp, s[1]);  			//tmp = s1
		mpz_set(s[1], s[0]);			//s1 = s0
		mpz_mul(s[0], q, s[0]);  	
       		mpz_sub(s[0], tmp, s[0]);  		//s0 = s1(tmp) - q * s0  	

		mpz_set(tmp, t[1]);  			//tmp = t1
		mpz_set(t[1], t[0]);			//t1 = t0
		mpz_mul(t[0], q, t[0]);  	
       		mpz_sub(t[0], tmp, t[0]);  		//t0 = t1(tmp) - q * t0  
	
	}
	//The result from the  
	mpz_gcd(tmp,a,b); 
 
	cout << "The first number: " << endl;
	cout << a << endl;
	cout << endl;
	cout << "The second number: " << endl;
	cout << b << endl;
	cout << endl;
	cout << "There greatest common factor calculated by Eucilidean algorithm: " << endl;
	cout << r[1] << endl;
	cout << endl;
	cout << "There greatest common factor calculated by embeded function " << endl;
	cout << tmp << endl;
	cout << endl;
	
	return 0;
}

#endif
