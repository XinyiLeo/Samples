#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>
#include <iostream>

using namespace std;

void prime(mpz_t p, int len);
void getB(mpz_t x1, mpz_t y1, mpz_t b, mpz_t a, mpz_t p);
string encrypt(string m, mpz_t qx, mpz_t qy, mpz_t px, mpz_t py, mpz_t a, mpz_t p);
string decrypt(string c, mpz_t k, mpz_t a, mpz_t p);
bool miller_rabin(mpz_t n, int k, gmp_randstate_t state);
bool mul(mpz_t qx, mpz_t qy, mpz_t px, mpz_t py, mpz_t d, mpz_t a, mpz_t p);
void add(mpz_t x1, mpz_t y1, mpz_t x2, mpz_t y2, mpz_t x3, mpz_t y3, mpz_t a, bool zero, mpz_t p);
string mpz2str(mpz_t m, bool out);
void str2mpz(mpz_t m, string str, bool in);
void generate(mpz_t p, mpz_t a, mpz_t b, mpz_t gx, mpz_t gy, mpz_t k ,mpz_t qx, mpz_t qy);
char table(char k_c, char m_c, bool encrypt);
string encrypt_v(string m, string k);
string decrypt_v(string c, string k);

int bit_len = 800;
int key_len = 128;
int p_len = 200;
int en_len = 40;

int main(int argc, char** argv){
	mpz_t gx,gy,k,a,b,qx,qy,p;
	string kk;
	mpz_inits(gx,gy,k,a,b,qx,qy,p,NULL);
	if (argc == 2 && strcmp(argv[1],"--generate") == 0) generate(p,a,b,gx,gy,k,qx,qy);
	else if (argc == 5 && strcmp(argv[1],"--encrypt") == 0 && strcmp(argv[3],"--key") == 0){
		string mm = "";
		for (unsigned int i = 0; i < strlen(argv[2]); i++){
			mm += argv[2][i];
		}
		string tmp = "";
		string key = "";
		for (unsigned int i = 0; i < strlen(argv[4]); i++){
			key += argv[4][i];
		}
		size_t pos1,pos2;
		pos1 = key.find(" ",0,1);
		pos2 = 0;
		tmp = key.substr(pos2,pos1-pos2);
		mpz_set_str(qx,tmp.c_str(),10);
		if (pos1 == string::npos){
			cout << "Wrong key!" << endl;
			mpz_clears(gx,gy,k,a,b,qx,qy,p,NULL);
			return 0;
		}
		pos2 = pos1 + 1;
		pos1 = key.find(" ",pos2,1);
		tmp = key.substr(pos2,pos1-pos2);
		mpz_set_str(qy,tmp.c_str(),10);
		if (pos1 == string::npos){
			cout << "Wrong key!" << endl;
			mpz_clears(gx,gy,k,a,b,qx,qy,p,NULL);
			return 0;
		}
		pos2 = pos1 + 1;
		pos1 = key.find(" ",pos2,1);
		tmp = key.substr(pos2,pos1-pos2);
		mpz_set_str(gx,tmp.c_str(),10);
		if (pos1 == string::npos){
			cout << "Wrong key!" << endl;
			mpz_clears(gx,gy,k,a,b,qx,qy,p,NULL);
			return 0;
		}
		pos2 = pos1 + 1;
		pos1 = key.find(" ",pos2,1);
		tmp = key.substr(pos2,pos1-pos2);
		mpz_set_str(gy,tmp.c_str(),10);
		if (pos1 == string::npos){
			cout << "Wrong key!" << endl;
			mpz_clears(gx,gy,k,a,b,qx,qy,p,NULL);
			return 0;
		}
		pos2 = pos1 + 1;
		pos1 = key.find(" ",pos2,1);
		tmp = key.substr(pos2,pos1-pos2);
		mpz_set_str(a,tmp.c_str(),10);
		if (pos1 == string::npos){
			cout << "Wrong key!" << endl;
			mpz_clears(gx,gy,k,a,b,qx,qy,p,NULL);
			return 0;
		}
		pos2 = pos1 + 1;
		pos1 = key.find(" ",pos2,1);
		tmp = key.substr(pos2,pos1-pos2);
		mpz_set_str(p,tmp.c_str(),10);
		if (pos1 == string::npos){
			cout << "Wrong key!" << endl;
			mpz_clears(gx,gy,k,a,b,qx,qy,p,NULL);
			return 0;
		}
		pos2 = pos1 + 1;
		pos1 = key.find(" ",pos2,1);
		tmp = key.substr(pos2,pos1-pos2);
		kk = tmp;
		mm = encrypt(mm,qx,qy,gx,gy,a,p);
		mm = encrypt_v(mm,kk);
	}
	else if (argc == 5 && strcmp(argv[1],"--decrypt") == 0 && strcmp(argv[3],"--key") == 0){
		string cc = "";
		for (unsigned int i = 0; i < strlen(argv[2]); i++){
			cc += argv[2][i];
		}
		string tmp = "";
		string key = "";
		for (unsigned int i = 0; i < strlen(argv[4]); i++){
			key += argv[4][i];
		}
		size_t pos1,pos2;
		pos1 = key.find(" ",0,1);
		pos2 = 0;
		tmp = key.substr(pos2,pos1-pos2);
		mpz_set_str(k,tmp.c_str(),10);
		if (pos1 == string::npos){
			cout << "Wrong key!" << endl;
			mpz_clears(gx,gy,k,a,b,qx,qy,p,NULL);
			return 0;
		}
		pos2 = pos1 + 1;
		pos1 = key.find(" ",pos2,1);
		tmp = key.substr(pos2,pos1-pos2);
		mpz_set_str(a,tmp.c_str(),10);
		if (pos1 == string::npos){
			cout << "Wrong key!" << endl;
			mpz_clears(gx,gy,k,a,b,qx,qy,p,NULL);
			return 0;
		}
		pos2 = pos1 + 1;
		pos1 = key.find(" ",pos2,1);
		tmp = key.substr(pos2,pos1-pos2);
		mpz_set_str(p,tmp.c_str(),10);
		if (pos1 == string::npos){
			cout << "Wrong key!" << endl;
			mpz_clears(gx,gy,k,a,b,qx,qy,p,NULL);
			return 0;
		}
		pos2 = pos1 + 1;
		pos1 = key.find(" ",pos2,1);
		tmp = key.substr(pos2,pos1-pos2);
		kk = tmp;
		cc = decrypt_v(cc,kk);
		cc = decrypt(cc,k,a,p);
	}
	else cout << "Wrong number of arguments!" << endl;
	mpz_clears(gx,gy,k,a,b,qx,qy,p,NULL);
	return 1;
}

void generate(mpz_t p, mpz_t a, mpz_t b, mpz_t gx, mpz_t gy, mpz_t k ,mpz_t qx, mpz_t qy){
	gmp_randstate_t state;
	time_t seed;
	time(&seed);
	gmp_randinit_default(state);    
	gmp_randseed_ui(state, long(seed));
	prime(p,p_len);	
	prime(a,30);   
	getB(gx,gy,b,a,p);
	prime(k,key_len);
	mul(qx,qy,gx,gy,k,a,p);
	srand((int)time(0));
	int len = rand() % 29 + 1;
	string kk = "";
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
		kk += c;
	}
	cout << "Encrypt Key:" << endl;
	gmp_printf("%Zd %Zd %Zd %Zd %Zd %Zd ", qx,qy,gx,gy,a,p);
	cout << kk << endl;
	cout << "Decrypt Key:" << endl;
	gmp_printf("%Zd %Zd %Zd ",k,a,p);
	cout << kk << endl;
	return;
}

void prime(mpz_t p, int len){
        gmp_randstate_t state;
        time_t seed;
        time(&seed);
        gmp_randinit_default(state);
        gmp_randseed_ui(state, long(seed));
	bool composite = true;
	while(composite){
                mpz_urandomb(p, state, len);
                unsigned long int r;
                mpz_t q;
                mpz_init(q);
                r = mpz_fdiv_q_ui(q,p,2);
                mpz_clear(q);
                if (r == 0) mpz_add_ui(p,p,1);
                composite = miller_rabin(p, 30, state);
        }
	return;
}

void getB(mpz_t x1, mpz_t y1, mpz_t b, mpz_t a, mpz_t p){
	mpz_t tmp1,tmp2;
	mpz_inits(tmp1,tmp2,NULL);
	while(1){
		prime(b,40);
		mpz_powm_ui(tmp1,a,3,p);
		mpz_powm_ui(tmp2,b,2,p);
		mpz_mul_ui(tmp1,tmp1,4);
		mpz_addmul_ui(tmp1,tmp2,27);
		mpz_mod(tmp1,tmp1,p);
		if (mpz_cmp_ui(tmp1,0) != 0) break;
	}
	prime(x1,30);
	mpz_powm_ui(tmp1,x1,3,p);
	mpz_addmul(tmp1,a,x1);
	mpz_add(tmp1,tmp1,b);
	mpz_sqrt(y1,tmp1);
	mpz_clears(tmp1,tmp2,NULL);
	return;
}

bool mul(mpz_t qx, mpz_t qy, mpz_t px, mpz_t py, mpz_t d, mpz_t a, mpz_t p){
	mpz_t x1,y1,x2,y2,x3,y3,D;
	mpz_inits(x2,y2,x3,y3,NULL);
	mpz_init_set(x1,px);
	mpz_init_set(y1,py);
	mpz_init_set(D,d);
	bool zero = false;
	unsigned long int r;
	int* bit_ary = new int[bit_len];
	int count = 0;
	while(mpz_cmp_ui(D,0) != 0){
		r = mpz_fdiv_q_ui(D,D,2);
		bit_ary[count] = r;
		count++;
		if (count == bit_len) cout << "Error!" << endl;
	}
	for (int i = 1; i <= count; i++){
        	mpz_set(x2,x1);
		mpz_set(y2,y1);
		add(x1,y1,x2,y2,x3,y3,a,zero,p);
		mpz_set(x1,x3);
		mpz_set(y1,y3);
		if (bit_ary[count-i] == 1){
			mpz_set(x2,px);
			mpz_set(y2,py);
			add(x1,y1,x2,y2,x3,y3,a,zero,p);
			mpz_set(x1,x3);
			mpz_set(y1,y3);
		}
	}
	if (zero){
		return false;
	}
	mpz_set(qx,x3);
	mpz_set(qy,y3);
	mpz_clears(x1,y1,x2,y2,x3,y3,D,NULL);
	return true;
}

void add(mpz_t x1, mpz_t y1, mpz_t x2, mpz_t y2, mpz_t x3, mpz_t y3, mpz_t a, bool zero, mpz_t p){
	mpz_t x2x1,y2y1,k,tmp,tmp2;
	mpz_inits(x2x1,y2y1,k,tmp,tmp2,NULL);
	if (zero){
		mpz_set(x3,x1);
		mpz_set(y3,y1);
		zero = false;
		mpz_clears(x2x1,y2y1,k,tmp,tmp2,NULL);
	}
	mpz_sub(x2x1,x2,x1);
	if (mpz_cmp_ui(x2x1,0) < 0) mpz_add(x2x1,x2x1,p);
	mpz_sub(y2y1,y2,y1);
        if (mpz_cmp_ui(y2y1,0) < 0) mpz_add(y2y1,y2y1,p);
	if (mpz_cmp_ui(x2x1,0) != 0){
		mpz_invert(tmp,x2x1,p);
		mpz_mul(tmp,tmp,y2y1);
		mpz_mod(k,tmp,p);
	}
	else{
		if (mpz_cmp_ui(y2y1,0) == 0){
			mpz_mul_ui(tmp,y1,2);
			mpz_mod(tmp,tmp,p);
			mpz_invert(tmp,tmp,p);
			mpz_mul(tmp2,x1,x1);
			mpz_mul_ui(tmp2,tmp2,3);
			mpz_sub(tmp2,tmp2,a);
			mpz_mul(tmp,tmp,tmp2);
			mpz_mod(k,tmp,p);
		}
		else{
			zero = true;
			mpz_clears(x2x1,y2y1,k,tmp,tmp2,NULL);
		}
	}
	mpz_mul(tmp,k,k);
	mpz_sub(tmp,tmp,x1);
	mpz_sub(tmp,tmp,x2);
	mpz_mod(x3,tmp,p);
	mpz_sub(tmp,x1,x3);
	mpz_mul(tmp,tmp,k);
	mpz_sub(tmp,tmp,y1);
	mpz_mod(y3,tmp,p);
	mpz_clears(x2x1,y2y1,k,tmp,tmp2,NULL);
	return;
}

string encrypt(string m, mpz_t qx, mpz_t qy, mpz_t px, mpz_t py, mpz_t a, mpz_t p){
	string str = "";
	mpz_t mx,my,c1x,c1y,c2x,c2y,r,tmpx,tmpy;
	bool zero = false;
	string cipherx;
	string ciphery;
	string tmp;
	mpz_inits(mx,my,c1x,c1y,c2x,c2y,r,tmpx,tmpy,NULL);
	prime(r,100);
	int freq = m.length()/en_len;
	int res = m.length()%en_len;
	int en_temp = en_len/2;
	for (int i = 0; i < freq; i++){
		tmp = m.substr(i*en_len,en_temp);
		cipherx = tmp+'\0';
		tmp = m.substr((i+0.5)*en_len,en_temp);
		ciphery = tmp+'\0';
		str2mpz(mx,cipherx,true);
		str2mpz(my,ciphery,true);
		mul(c2x,c2y,px,py,r,a,p);
		mul(tmpx,tmpy,qx,qy,r,a,p);
		add(mx,my,tmpx,tmpy,c1x,c1y,a,zero,p);
		tmp = mpz2str(c1x, false);
		str+=tmp;
		tmp = mpz2str(c1y, false);
		str+=tmp;
		tmp = mpz2str(c2x, false);
		str+=tmp;
		tmp = mpz2str(c2y, false);
		str+=tmp;
	}
	if (res > 0){
		if (res <= en_temp){
			tmp = m.substr(freq*en_len,res);
			cipherx = tmp+'\0';
			str2mpz(mx,cipherx,true);
			mpz_set_ui(my,0);
		}
		else{
			tmp = m.substr(freq*en_len,en_temp);
			cipherx = tmp+'\0';
			str2mpz(mx,cipherx,true);
			tmp = m.substr((freq+0.5)*en_len,res);
			ciphery = tmp+'\0';
			str2mpz(my,ciphery,true);
		}
		mul(c2x,c2y,px,py,r,a,p);
		mul(tmpx,tmpy,qx,qy,r,a,p);
		add(mx,my,tmpx,tmpy,c1x,c1y,a,zero,p);
		tmp = mpz2str(c1x, false);
		str+=tmp;
		tmp = mpz2str(c1y, false);
		str+=tmp;
		tmp = mpz2str(c2x, false);
		str+=tmp;
		tmp = mpz2str(c2y, false);
		str+=tmp;
	}
	str = str.substr(0,str.length()-1);
	//cout << str << endl;
	mpz_clears(mx,my,c1x,c1y,c2x,c2y,r,tmpx,tmpy,NULL);
	return str;
}

string decrypt(string c, mpz_t k, mpz_t a, mpz_t p){
	mpz_t c1x,c1y,c2x,c2y,tmpx,tmpy,mx,my;
	mpz_inits(c1x,c1y,c2x,c2y,tmpx,tmpy,mx,my,NULL);
	bool zero = false;
	string cipherx;
	string ciphery;
	string tmp;
	string str = "";
	c += ")";
	int count = 0;
	size_t pos1,pos2;
	pos2 = 0;
	pos1 = c.find(char(41));
	while(1){
		if (count == 0){
		tmp = c.substr(pos2,pos1-pos2);
		cipherx = tmp+'\0';
		str2mpz(c1x,cipherx,false);
		}
		else if (count == 1){
		tmp = c.substr(pos2,pos1-pos2);
		cipherx = tmp+'\0';
		str2mpz(c1y,cipherx,false);
		}
		else if (count == 2){
		tmp = c.substr(pos2,pos1-pos2);
		cipherx = tmp+'\0';
		str2mpz(c2x,cipherx,false);
		}
		else if (count == 3){
		tmp = c.substr(pos2,pos1-pos2);
		cipherx = tmp+'\0';
		str2mpz(c2y,cipherx,false);
		}
		count++;
		count = count % 4;
		pos2 = pos1 + 1;
		pos1 = c.find(")",pos2,1);
		if (count != 0 && pos1 == string::npos){
			cout << endl;
			mpz_clears(c1x,c1y,c2x,c2y,tmpx,tmpy,mx,my,NULL);
			return str;
		}
		if (count == 0){
			mul(tmpx,tmpy,c2x,c2y,k,a,p);
			mpz_neg(tmpy,tmpy);
			add(c1x,c1y,tmpx,tmpy,mx,my,a,zero,p);
			tmp = mpz2str(mx, true);
			str += tmp;
			tmp = mpz2str(my, true);
			str += tmp;
			if (pos1 == string::npos){
				cout << str << endl;
				mpz_clears(c1x,c1y,c2x,c2y,tmpx,tmpy,mx,my,NULL);
				return str;
			}
		}
	}
	mpz_clears(c1x,c1y,c2x,c2y,tmpx,tmpy,mx,my,NULL);
	return str;
}

bool miller_rabin(mpz_t n, int k, gmp_randstate_t state){
	mpz_t m, tmp, a, tmp2, gcd_result, exp;
	mpz_inits(m,tmp,a,tmp2,gcd_result,exp,NULL);
	mpz_sub_ui(m,n,1);
	int s = 1;
	while(1){
		unsigned long int r;
		r = mpz_fdiv_q_ui(tmp,m,2);
		if (r == 1) break;
		else{
			mpz_set(m,tmp);
			s++;
		} 
	}
	for (int i = 0; i < k; i++){
		bool jump = false;
		mpz_sub_ui(tmp2,n,3);
		mpz_urandomm(a,state,tmp2);
		mpz_add_ui(a,a,2);
		mpz_gcd(gcd_result,a,n);
		if (mpz_cmp_ui(gcd_result,1) != 0){
			mpz_clears(a,tmp2,gcd_result,exp,m,tmp,NULL);
			return true;
		}
		mpz_powm(a,a,m,n);
		mpz_sub_ui(tmp2,n,1);
		if ((mpz_cmp_ui(a,1) == 0) || (mpz_cmp(a,tmp2) == 0)) continue;
		for (int j = 1; j < s; j++){
			mpz_powm_ui(a,a,2,n);
			if (mpz_cmp_ui(a,1) == 0){
				mpz_clears(a,tmp2,gcd_result,exp,m,tmp,NULL);
				return true;
			}
			if (mpz_cmp(a,tmp2) == 0){
				jump = true;
				break;
			}
		}
		if (jump) continue;
		mpz_clears(a,tmp2,gcd_result,exp,m,tmp,NULL);
		return true;
	}
	mpz_clears(a,tmp2,gcd_result,exp,m,tmp,NULL);
	return false;
}

string mpz2str(mpz_t m, bool out){
	string str = "";
	char c = char(41);
	if (!out) str += c;
	mpz_t mm;
	mpz_init_set(mm,m);
	unsigned long int r;
	int count = 0;
	while (mpz_cmp_ui(mm,0) != 0){
		if (!out) r = mpz_fdiv_q_ui(mm,mm,68);
		else r = mpz_fdiv_q_ui(mm,mm,69);
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
		str = c+str;
		count++;
	}
	mpz_clear(mm);
	return str;
}

void str2mpz(mpz_t m, string str, bool in){
	mpz_t mm;
	mpz_init(mm);
	unsigned long int r = 0;
	int i = 0;
	while(str[i] != '\0'){
		r = int(str[i]);
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
		if (!in) mpz_mul_ui(mm,mm,68);
		else mpz_mul_ui(mm,mm,69);
		mpz_add_ui(mm,mm,r);
		i++;
	}
	mpz_set(m,mm);
	mpz_clear(mm);
	return;
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

string encrypt_v(string m, string k){
	int k_len = k.length();
	string str = "";
	for (unsigned int i = 0; i < m.length(); i++){
		str += table(k[i%k_len],m[i],true);
	}
	cout << str << endl;
	return str;
}

string decrypt_v(string c, string k){
	int k_len = k.length();
	string str = "";
	for (unsigned int i = 0; i < c.length(); i++){
		str += table(k[i%k_len],c[i],false);
	}
	//cout << str << endl;
	return str;
}
