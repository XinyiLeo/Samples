#define HW1
#ifdef HW1

#include <iostream> 
#include <string>
#include<gmpxx.h>
#include <time.h>
using namespace std;

void f(mpz_t &x, mpz_t &n) {
	mpz_pow_ui(x,x,2);
	mpz_add_ui(x,x,1);
	mpz_mod(x,x,n);
}

int main() {	
	mpz_t n,a,b,d,c;
	mpz_init(n); 
	mpz_init(c); 
	mpz_init_set_ui(d,1); 
	mpz_init_set_ui(a,2); 
	mpz_init_set_ui(b,2); 
	cout << "Please input the number to be factored: " << endl;
	cin >> n ;
	
	while(mpz_cmp_ui(d,1)==0) {
		f(a,n);
		f(b,n);
		f(b,n);
		mpz_sub(c, a, b);
		mpz_gcd(d, c, n); 
	}
	if(mpz_cmp(d,n)==0) cout << "Can't Factorize! " << endl;
	else cout << "One of the factor is: " << d << endl;	














	return 0;
}

#endif
