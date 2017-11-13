#include <stdio.h>    //Include standard in and out.
#include <stdlib.h>   //Include standard library.
#include <time.h>     //Include seed according to time.
#define SWAP(a,b) { a ^= b; b ^= a; a ^= b; }    //A function that can swap two element a and b.
//#define TEST           //Choose to give the computer test or not.

unsigned long int karatsuba(unsigned long int a, unsigned long int b);  //Include the subfunction "Karastuba".

int main()
{
	unsigned long int a, b;  //Define the type of a,b: unsigned long int.
	srand(time(NULL));    //Produce a seed for random number according to time.
#ifndef TEST            //If we didn't define TEST(Test succeed).
		a = rand();     //Produce random number. 
		b = rand();     //Produce another random number
	printf("%ld*%ld=%ld\n", a, b, karatsuba(a, b)); //Express the formula.
#endif
#ifdef TEST   //Begin a test of the accuracy (If all the value are the same).
	for(int i=0; i< 1000000; i++)   //Test 100 times to confirm the accuracy.
	{  
		a=rand();    
		b=rand();  //Two random numbers.
		if(karatsuba(a,b)!=a*b)    // Error condition.
		{ 
			fprintf(stderr,"Error: a=%ld, b=%ld\n",a,b); exit(-1);   //Print error content.
		}
	}
#endif 
}

	unsigned long int karatsuba(unsigned long int a, unsigned long int b)  //Because the karatsuba algorithm. 
	{
		int i, n, N;	 //Define three integers.
		unsigned long int x0, y0;  
		unsigned long int z0, z1, z2;  //Define five unsigned long integer.
		if (a<b) SWAP(a, b);     // Always let a>b.       
		if (b == 0)
			return 0;  //If i\in N, i*0=0 (This is crucial when calculating till the endof the recursion);
		for (n = -1, i = 1; i <= b; i <<= 1, n++);   //b_2 =(1......) : (n-1)*(.)                   /* not optimal */  
		for (N = n; i <= a; i <<= 1, N++);    //Keep adding the digit to a_2=(1...........): (N-1)*.
		y0 = b&((1 << n) - 1);  //The exact number of the last n-1 digit.
		x0 = a&((1 << N) - 1);  // The exact number of last N-1 digit.
		z2 = 1 << (N - n);  //equal to *2^(N-n) in decimalism.
		z1 = karatsuba(z2, y0) + x0;  //certain part of addition
		z0 = karatsuba(x0, y0);  //certiain part of addition
		return (z2 << (2 * n)) + (z1 << n) + z0;  //sum
	}