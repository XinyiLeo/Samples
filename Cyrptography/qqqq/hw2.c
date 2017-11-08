#define HW2
#ifdef HW2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int i;
	unsigned char hexa[16];
	unsigned char square[4][4];
	int m,n,tmp;
	char input[33];
	if(argc == 3) {
		if(!strcmp(argv[2],"default"))
			strcpy(input,"acbd946219944bef39738184bdc1ae5b");
		else {
			printf("Error!\n");
			return 0;			
		}
	}
	else {
		printf("Please print the 32 digit hexadecimal value: \n");
		if (!fgets(input, 64, stdin)) {printf("\n");return 0;}
		input[strlen(input)-1] = '\0';
	}
	
	printf("The default input is : \n");
	printf("%s\n",input);
	for(i = 0; i < 32; i++) {
		switch (input[i]){
        		case '1':
				tmp = 1;
				break;
			case '2':
				tmp = 2;
				break;
			case '3':
				tmp = 3;
				break;
			case '4':
				tmp = 4;
				break;
			case '5':
				tmp = 5;
				break;
			case '6':
				tmp = 6;
				break;
			case '7':
				tmp = 7;
				break;
			case '8':
				tmp = 8;
				break;
			case '9':
				tmp = 9;
				break;
			case 'a':
				tmp = 10;
				break;
			case 'b':
				tmp = 11;
				break;
			case 'c':
				tmp = 12;
				break;
			case 'd':
				tmp = 13;
				break;
			case 'e':
				tmp = 14;
				break;
			case 'f':
				tmp = 15;
				break;
			case '0':
				tmp = 0;
				break;
        		default:
				printf("error\n");
				break;
    		}
		if(i%2 == 0) m = tmp;
		else {
			n = tmp;
			tmp = m*16 + n;
			hexa[(i-1)/2] = tmp;
		}	
	}
	int tmpp;
	int j;
	for(i = 0; i < 16; i++ ) {
		tmpp = i % 4;
		square[(i-tmpp)/4][tmpp] = hexa[i];	
	}
	printf("\n");
	//ShiftRows Layer
	if(!(strcmp(argv[1],"1"))) {
		printf("Choose the ShiftRows Layer: The encrypted message is: \n");
		unsigned char tmppp[4][4];
		for(i = 0; i < 4; i++) {
			for(j = 0; j < 4; j++) {
				tmppp[i][j] = square[(i+j) % 4][j];
			}
		}

	
		for(i = 0; i < 4; i++) {
			for(j = 0; j < 4; j++) {
				square[i][j] = tmppp[i][j];
				printf("%x", square[i][j]);	
			}		
		}
	}
	//Subbytes
	else if(!(strcmp(argv[1],"2"))) {
		int SBox[16][16];
		i = 0;
		SBox[i][0] =   99;
		SBox[i][1] =   202;
		SBox[i][2] =   183;
		SBox[i][3] =   4;	
		SBox[i][4] =   9;
		SBox[i][5] =   83;
		SBox[i][6] =   208;
		SBox[i][7] =   81;
		SBox[i][8] =   205;
		SBox[i][9] =   96;
		SBox[i][10] =   224;
		SBox[i][11] =  231 ;	
		SBox[i][12] =   186;
		SBox[i][13] =   112;
		SBox[i][14] =  225 ;
		SBox[i][15] =   140;
	
		i = 1;
		SBox[i][0] =   124;
		SBox[i][1] =   130;
		SBox[i][2] =   253;
		SBox[i][3] =   199;	
		SBox[i][4] =   131;
		SBox[i][5] =   209;
		SBox[i][6] =   239;
		SBox[i][7] =   163;
		SBox[i][8] =   12 ;
		SBox[i][9] =   129;
		SBox[i][10] =  50 ;
		SBox[i][11] =  200;	
		SBox[i][12] =  120;
		SBox[i][13] =  62 ;
		SBox[i][14] =  248;
		SBox[i][15] =  161;

		i = 2;
		SBox[i][0] =   119;
		SBox[i][1] =   201;
		SBox[i][2] =   147;
		SBox[i][3] =   35 ;	
		SBox[i][4] =   44 ;
		SBox[i][5] =   0  ;
		SBox[i][6] =   170;
		SBox[i][7] =   64 ;
		SBox[i][8] =   19 ;
		SBox[i][9] =   79 ;
		SBox[i][10] =  58 ;
		SBox[i][11] =  55 ;	
		SBox[i][12] =  37 ;
		SBox[i][13] =  181;
		SBox[i][14] =  152;
		SBox[i][15] =  137;

		i = 3;
		SBox[i][0] =   123;
		SBox[i][1] =   125;
		SBox[i][2] =   38 ;
		SBox[i][3] =   195;	
		SBox[i][4] =   26;
		SBox[i][5] =   237;
		SBox[i][6] =   251;
		SBox[i][7] =   143;
		SBox[i][8] =   236;
		SBox[i][9] =   220;
		SBox[i][10] =  10 ;
		SBox[i][11] =  109;	
		SBox[i][12] =  46 ;
		SBox[i][13] =  102;
		SBox[i][14] =  17 ;
		SBox[i][15] =  13 ;

		i = 4;
		SBox[i][0] =   242;
		SBox[i][1] =   250;
		SBox[i][2] =   54 ;
		SBox[i][3] =   24;	
		SBox[i][4] =   27 ;
		SBox[i][5] =   32 ;
		SBox[i][6] =   67 ;
		SBox[i][7] =   146;
		SBox[i][8] =   95 ;
		SBox[i][9] =   34 ;
		SBox[i][10] =  73 ;
		SBox[i][11] =  141;	
		SBox[i][12] =  28 ;
		SBox[i][13] =  72 ;
		SBox[i][14] =  105;
		SBox[i][15] =  191;

		i = 5;
		SBox[i][0] =   107;
		SBox[i][1] =   89 ;
		SBox[i][2] =   63 ;
		SBox[i][3] =   150;	
		SBox[i][4] =   110;
		SBox[i][5] =   252;
		SBox[i][6] =   77 ;
		SBox[i][7] =   157;
		SBox[i][8] =   151;
		SBox[i][9] =   42 ;
		SBox[i][10] =  6  ;
		SBox[i][11] =  213;	
		SBox[i][12] =  166;
		SBox[i][13] =  3  ;
		SBox[i][14] =  217;
		SBox[i][15] =  230;
	
		i = 6;
		SBox[i][0] =   111;
		SBox[i][1] =   71 ;
		SBox[i][2] =   247;
		SBox[i][3] =   5  ;	
		SBox[i][4] =   90 ;
		SBox[i][5] =   177;
		SBox[i][6] =   51 ;
		SBox[i][7] =   56 ;
		SBox[i][8] =   68 ;
		SBox[i][9] =   144;
		SBox[i][10] =  36 ;
		SBox[i][11] =  78 ;	
		SBox[i][12] =  180;
		SBox[i][13] =  246;
		SBox[i][14] =  142;
		SBox[i][15] =  66 ;

		i = 7;
		SBox[i][0] =   197;
		SBox[i][1] =   240;
		SBox[i][2] =   204;
		SBox[i][3] =   154;	
		SBox[i][4] =   160;
		SBox[i][5] =   91 ;
		SBox[i][6] =   133;
		SBox[i][7] =   245;
		SBox[i][8] =   23 ;
		SBox[i][9] =   136;
		SBox[i][10] =  92 ;
		SBox[i][11] =  169;	
		SBox[i][12] =  198;
		SBox[i][13] =  14 ;
		SBox[i][14] =  148;
		SBox[i][15] =  104;

		i = 8;
		SBox[i][0] =   48 ;
		SBox[i][1] =   173;
		SBox[i][2] =   52 ;
		SBox[i][3] =   7  ;	
		SBox[i][4] =   82 ;
		SBox[i][5] =   106;
		SBox[i][6] =   69 ;
		SBox[i][7] =   188;
		SBox[i][8] =   196;
		SBox[i][9] =   70 ;
		SBox[i][10] =  194;
		SBox[i][11] =  108;	
		SBox[i][12] =  232;
		SBox[i][13] =  97 ;
		SBox[i][14] =  155;
		SBox[i][15] =  65 ;

		i = 9;
		SBox[i][0] =   1  ;
		SBox[i][1] =   212;
		SBox[i][2] =   165;
		SBox[i][3] =   18 ;	
		SBox[i][4] =   59 ;
		SBox[i][5] =   203;
		SBox[i][6] =   249;
		SBox[i][7] =   182;
		SBox[i][8] =   167;
		SBox[i][9] =   238;
		SBox[i][10] =  211;
		SBox[i][11] =  86 ;	
		SBox[i][12] =  221;
		SBox[i][13] =  53 ;
		SBox[i][14] =  30 ;
		SBox[i][15] =  153;
		
		i = 10;
		SBox[i][0] =   103;
		SBox[i][1] =   162;
		SBox[i][2] =   229;
		SBox[i][3] =   128;	
		SBox[i][4] =   214;
		SBox[i][5] =   190;
		SBox[i][6] =   2  ;
		SBox[i][7] =   218;
		SBox[i][8] =   126;
		SBox[i][9] =   184;
		SBox[i][10] =  172;
		SBox[i][11] =  244;	
		SBox[i][12] =  116;
		SBox[i][13] =  87 ;
		SBox[i][14] =  135;
		SBox[i][15] =  45 ;

		i = 11;
		SBox[i][0] =   43 ;
		SBox[i][1] =   175;
		SBox[i][2] =   241;
		SBox[i][3] =   226;	
		SBox[i][4] =   179;
		SBox[i][5] =   57 ;
		SBox[i][6] =   127;
		SBox[i][7] =   33 ;
		SBox[i][8] =   61 ;
		SBox[i][9] =   20 ;
		SBox[i][10] =  98 ;
		SBox[i][11] =  234;	
		SBox[i][12] =  31;
		SBox[i][13] =  185;
		SBox[i][14] =  233;
		SBox[i][15] =  15;

		i = 12;
		SBox[i][0] =   254;
		SBox[i][1] =   156;
		SBox[i][2] =   113;
		SBox[i][3] =   235;	
		SBox[i][4] =   41 ;
		SBox[i][5] =   74 ;
		SBox[i][6] =   80 ;
		SBox[i][7] =   16 ;
		SBox[i][8] =   100;
		SBox[i][9] =   222;
		SBox[i][10] =  145;
		SBox[i][11] =  101;	
		SBox[i][12] =  75 ;
		SBox[i][13] =  134;
		SBox[i][14] =  206;
		SBox[i][15] =  176;
		
		i = 13;
		SBox[i][0] =   215;
		SBox[i][1] =   164;
		SBox[i][2] =   216;
		SBox[i][3] =   39 ;	
		SBox[i][4] =   227 ;
		SBox[i][5] =   76 ;
		SBox[i][6] =   60;
		SBox[i][7] =   255;
		SBox[i][8] =   93 ;
		SBox[i][9] =   94;
		SBox[i][10] =  149;
		SBox[i][11] =  122;	
		SBox[i][12] =  189;
		SBox[i][13] =  193;
		SBox[i][14] =  85 ;
		SBox[i][15] =  84 ;

		i = 14;
		SBox[i][0] =   171;
		SBox[i][1] =   114;
		SBox[i][2] =   49 ;
		SBox[i][3] =   178;	
		SBox[i][4] =   47 ;
		SBox[i][5] =   88 ;
		SBox[i][6] =   159;
		SBox[i][7] =   243;
		SBox[i][8] =   25 ;
		SBox[i][9] =   11 ;
		SBox[i][10] =  228;
		SBox[i][11] =  174;	
		SBox[i][12] =  139;
		SBox[i][13] =  29 ;
		SBox[i][14] =  40 ;
		SBox[i][15] =  187;

		i = 15;
		SBox[i][0] =   118;
		SBox[i][1] =   192;
		SBox[i][2] =   21 ;
		SBox[i][3] =   117;	
		SBox[i][4] =   132;
		SBox[i][5] =   107;
		SBox[i][6] =   168;
		SBox[i][7] =   210;
		SBox[i][8] =   115;
		SBox[i][9] =   219;
		SBox[i][10] =  121;
		SBox[i][11] =  8  ;	
		SBox[i][12] =  138;
		SBox[i][13] =  158;
		SBox[i][14] =  223;
		SBox[i][15] =  22 ;

		int Sm, Sn;int k;
		
		printf("The subbyte method is chosen: The encrypted message is: \n");
		for(k = 0; k < 4; k++) {
			for(j = 0; j < 4; j++) {
				Sm = square[k][j] % 16;
				Sn = (square[k][j]-Sm)/16;
				square[k][j] = SBox[Sn][Sm];
				printf("%x", square[k][j]);	
			}		
		}
	}
	else ;
	
	printf("\n");

	return 0;
}

#endif
