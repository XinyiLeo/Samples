/* This homework is finished independely by Xinyi Wu (513309030)
   It's an simple implementation for RSA algorithm
   In the program, there are three functions as well as a main function
   The three functions are: generate, encrtpt_mpz, and decrypt_mpz    
*/

/* How to use the program?
   First type make to compile the program, the application name is H.o
  
   To run H.o, we have several options
   
   --generate 80           
   -g 80
   This generate the public key and security pair, 80 means the security level
   80,112,128,192,256 security level are permissible, if other input is typed
   the default bit 1000 will be the input

   --encrypt 99
   -e 99
   This encrypt the message with power e, 99 is the plain text

   --decrypt 99
   -d 99
   This decrypt the message with power d, 99 is the cipher text

   Sample input
   ./H.o -g 80 -e 44 -d 49


/*

