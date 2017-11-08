#define HW5
#ifdef HW5

#include <iostream> 
#include <string>
#include<gmpxx.h>
#include <time.h>
#include <math.h>
#include <getopt.h>

using namespace std;

static mpz_t stat;


void encrypt_mpz(mpz_t &plaintext, mpz_t &e, mpz_t &n) {
	mpz_init(stat);  
	cout << "The plaintext is: " << plaintext << endl;	
	mpz_powm(stat, plaintext, e, n);
	cout << "The ciphertext is: " << stat << endl;
}

void decrypt_mpz(mpz_t &encrypttext, mpz_t &d, mpz_t &n) {
	mpz_init(stat);  
	cout << "The ciphertext is: " << encrypttext << endl;
	mpz_powm(stat, encrypttext, d, n);
	cout << "The plaintext is: " << stat << endl;
}

void generate(mpz_t &n,mpz_t &e,mpz_t &d) {
	cout << "The public key pair (n,e) is: (" << n << "," << e << ")" << endl;
	cout << "The private key pair (n,d) is: (" << n << "," << d << ")" << endl;
}


/* Flag set by ‘--verbose’. */
static int verbose_flag;

int main (int argc, char **argv)
{
  int c;
  int gg = 0;
  int dd = 0;
  int ee = 0;
  string ggg;
  string ddd;
  string eee;

  while (1)
    {
      static struct option long_options[] =
        {
          /* These options don’t set a flag.
             We distinguish them by their indices. */
          {"generate",  required_argument, 0, 'g'},
          {"encrypt",  required_argument, 0, 'e'},
          {"decrypt",    required_argument, 0, 'd'},
          {0, 0, 0, 0}
        };
      /* getopt_long stores the option index here. */
      int option_index = 0;

      c = getopt_long (argc, argv, "g:e:d:",
                       long_options, &option_index);

      /* Detect the end of the options. */
      if (c == -1)
        break;

      switch (c)
        {
        case 0:
          /* If this option set a flag, do nothing else now. */
          if (long_options[option_index].flag != 0)
            break;
          printf ("option %s", long_options[option_index].name);
          if (optarg)
            printf (" with arg %s", optarg);
          printf ("\n");
          break;

        case 'g':
		gg = 1;
          	ggg = optarg;
          break;

        case 'e':
		ee = 1;
         	eee = optarg;
          break;

        case 'd':
		dd = 1;
         	ddd = optarg;
          break;

        case '?':
          /* getopt_long already printed an error message. */
          break;

        default:
          abort ();
        }
    }

  /* Print any remaining command line arguments (not options). */
  if (optind < argc)
    {
      printf ("non-option ARGV-elements: ");
      while (optind < argc)
        printf ("%s ", argv[optind++]);
      putchar ('\n');
    }
	
//Start to execute the program
	int b,rr;
	if(gg == 1) {
		b = atoi(ggg.c_str());
		switch(b) {
			case 80: 
				rr=1024;
				break;	
			case 112: 
				rr=2048;
				break;	
			case 128: 
				rr=3072;
				break;	
			case 192: 
				rr=7680;
				break;	
			case 256: 
				rr=15360;
				break;	
			default:
				rr=1000;
				break;
		}
	}
	else rr = 1000;
	mpz_t p,q,n,Euler,gcd_tmp,e,d,t,g,plaintext,ciphertext, Enc, Dec;  
   	time_t seed;  
    	gmp_randstate_t state;  
      
    	time(&seed);  
    	mpz_init(p);  
	mpz_init(q);  
	mpz_init(n);  
	mpz_init(Euler); 
	mpz_init(gcd_tmp);
	mpz_init(e);
	mpz_init(d);  
	mpz_init(t);  
    	mpz_init(g);  
	mpz_init(plaintext);   
	mpz_init(ciphertext);   
	mpz_init(Enc);  
	mpz_init(Dec);      
    	gmp_randinit_default(state);  
    	gmp_randseed_ui(state, long(seed));  
      
	do{  
		mpz_urandomb(p, state, floor(sqrt(rr))); 
	}while(0 == mpz_probab_prime_p(p,50));  
	
	gmp_randseed_ui(state, long(seed+1));  
	do{  
        	mpz_urandomb(q, state, floor(sqrt(rr))); 
	}while(0 == mpz_probab_prime_p(q,50));  

	mpz_mul(n, p, q);//n = p * q  
      	mpz_sub_ui(p, p, 1);//p = p - 1  
    	mpz_sub_ui(q, q, 1);//q = q - 1  
    	mpz_mul(Euler, p, q);//eln = p * q      	

	//Get the public key e
	gmp_randseed_ui(state, long(seed+2));  
	mpz_urandomm(e, state, Euler); 
	mpz_gcd(gcd_tmp,e,Euler); 
	int i =2;
	while(mpz_cmp_ui(gcd_tmp,1)!=0|| mpz_cmp_ui(e,1)==0 || mpz_cmp_ui(e,0)==0 ) {
		i ++;
		gmp_randseed_ui(state, long(seed+i));  
		mpz_urandomm(e, state, Euler); 
		mpz_gcd(gcd_tmp,e,Euler); 
	}

	//Get the private key d
	mpz_invert(d,e,Euler);

	if(gg == 1) {
		generate(n,e,d);	
	}
	
	int encry;
	if(ee == 1) { 
		encry = atoi(eee.c_str());
		mpz_add_ui(Dec, Dec, encry);
		encrypt_mpz(Dec,e,n);
	}
	
	int decry;
	if(dd == 1) {
		decry = atoi(ddd.c_str());
		mpz_add_ui(Enc, Enc, decry);
		decrypt_mpz(Enc,d,n);
	}


	return 0;
}



#endif
