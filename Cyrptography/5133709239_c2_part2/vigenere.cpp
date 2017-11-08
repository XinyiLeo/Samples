#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <time.h>

using namespace std;

char table(char k_c, char m_c, bool encrypt);
void generate();
void encrypt(string m, string k);
void decrypt(string c, string k);

int main(int argc, char** argv){
	if (argc == 2 && strcmp(argv[1],"--generate") == 0) generate();
	else if (argc == 5 && strcmp(argv[1],"--encrypt") == 0 && strcmp(argv[3],"--key") == 0){
		string m = "";
		for (unsigned int i = 0; i < strlen(argv[2]); i++){
			m += argv[2][i];
		}
		string k = "";
		for (unsigned int i = 0; i < strlen(argv[4]); i++){
			k += argv[4][i];
		}
		encrypt(m,k);
	}
	else if (argc == 5 && strcmp(argv[1],"--decrypt") == 0 && strcmp(argv[3],"--key") == 0){
		string c = "";
		for (unsigned int i = 0; i < strlen(argv[2]); i++){
			c += argv[2][i];
		}
		string k = "";
		for (unsigned int i = 0; i < strlen(argv[4]); i++){
			k += argv[4][i];
		}
		decrypt(c,k);		
	}
	else cout << "Wrong number of arguments!" << endl;
	return 1;
}

char table(char k_c, char m_c, bool encrypt){
	int k_r = (int)k_c;
	int m_r = (int)m_c;
	int r = k_r;
	if (r >= 48 && r <= 57) r-=48;
		else if (r >= 97 && r <= 122) r-=87;
		else if (r >= 65 && r <= 90) r-=29;
		else if (r == 44) r = 62;
		else if (r == 46) r = 63;
		else if (r == 59) r = 64;
		else if (r == 63) r = 65;
		else if (r == 33) r = 66;
		else if (r == 40) r = 67;
		else r = 68;
	k_r = r;
	r = m_r;
	if (r >= 48 && r <= 57) r-=48;
		else if (r >= 97 && r <= 122) r-=87;
		else if (r >= 65 && r <= 90) r-=29;
		else if (r == 44) r = 62;
		else if (r == 46) r = 63;
		else if (r == 59) r = 64;
		else if (r == 63) r = 65;
		else if (r == 33) r = 66;
		else if (r == 40) r = 67;
		else r = 68;
	m_r = r;
	if (encrypt) r = (k_r+m_r)%69;
	else r = (m_r-k_r)%69;
	if (r < 0) r += 69;
	char c;
	if (r <= 9) c = char(r+48);
		else if (r <= 35) c = char(r+87);
		else if (r <= 61) c = char(r+29);
		else if (r == 62) c = char(44);
		else if (r == 63) c = char(46);
		else if (r == 64) c = char(59);
		else if (r == 65) c = char(63);
		else if (r == 66) c = char(33);
		else if (r == 67) c = char(40);
		else c = char(41);
	return c;
}

void generate(){
	srand((int)time(0));
	int len = rand() % 29 + 1;
	string k = "";
	char c;
	for (int i = 0; i < len; i++){
		int r = rand() % 69;
		if (r <= 9) c = char(r+48);
		else if (r <= 35) c = char(r+87);
		else if (r <= 61) c = char(r+29);
		else if (r == 62) c = char(44);
		else if (r == 63) c = char(46);
		else if (r == 64) c = char(59);
		else if (r == 65) c = char(63);
		else if (r == 66) c = char(33);
		else if (r == 67) c = char(40);
		else c = char(41);
		k += c;
	}
	cout << "k = " << k << endl;
	return;
}

void encrypt(string m, string k){
	int k_len = k.length();
	string str = "";
	for (unsigned int i = 0; i < m.length(); i++){
		str += table(k[i%k_len],m[i],true);
	}
	cout << str << endl;
	return;
}

void decrypt(string c, string k){
	int k_len = k.length();
	string str = "";
	for (unsigned int i = 0; i < c.length(); i++){
		str += table(k[i%k_len],c[i],false);
	}
	cout << str << endl;
	return;
}
