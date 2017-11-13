#define  RECOVERY 
#ifdef 	RECOVERY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <inttypes.h>
#pragma pack(push, 1)
struct BootEntry {
	uint8_t BS_jmpBoot[3];		/* Assembly instruction to jump to boot code        */
	uint8_t BS_OEMName[8];		/* OEM Name in ASCII                                */
	uint16_t BPB_BytsPerSec; 	/* Bytes per sector. Allowed values include 512, 
					   1024, 2048, and 4096                             */
	uint8_t BPB_SecPerClus; 	/* Sectors per cluster (data unit). Allowed values
					   are powers of 2, but the cluster size must be 
					   32KB or smaller                                  */
	uint16_t BPB_RsvdSecCnt; 	/* Size in sectors of the reserved area             */
	uint8_t BPB_NumFATs;		/* Number of FATs 				    */
	uint16_t BPB_RootEntCnt; 	/* Maximum number of files in the root directory
 					   for FAT12 and FAT16. This is 0 for FAT32 	    */
	uint16_t BPB_TotSec16;		/* 16-bit value of number of sectors in file system */
	uint8_t BPB_Media;		/* Media type 					    */
	uint16_t BPB_FATSz16;		/* 16-bit size in sectors of each FAT for FAT12 and
					   FAT16. For FAT32, this field is 0		    */
	uint16_t BPB_SecPerTrk; 	/* Sectors per track of storage device 		    */
	uint16_t BPB_NumHeads;		/* Number of heads in storage device 		    */
	uint32_t BPB_HiddSec;           /* Number of sectors before the start of partition  */
	uint32_t BPB_TotSec32; 		/* 32-bit value of number of sectors in file system.
					   Either this value or the 16-bit value above must
					   be 0 					    */
	uint32_t BPB_FATSz32;		/* 32-bit size in sectors of one FAT 		    */
	uint16_t BPB_ExtFlags;		/* A flag for FAT				    */
	uint16_t BPB_FSVer;		/* The major and minor version number   	    */
	uint32_t BPB_RootClus;		/* Cluster where the root directory can be found    */
	uint16_t BPB_FSInfo;		/* Sector where FSINFO structure can be found       */
	uint16_t BPB_BkBootSec;		/* Sector where backup copy of boot sector is 
					   located  				 	    */
	uint8_t BPB_Reserved[12]; 	/* Reserved					    */
	uint8_t BS_DrvNum;		/* BIOS INT13h drive number 			    */
	uint8_t BS_Reserved1;		/* Not used 					    */
	uint8_t BS_BootSig;		/* Extended boot signature to identify if the next
					   three values are valid 			    */
	uint32_t BS_VolID;		/* Volume serial number				    */
	uint8_t BS_VolLab[11];		/* Volume label in ASCII. User defines when 
					   creating the file system 			    */
	uint8_t BS_FilSysType[8]; 	/* File system type label in ASCII 		    */
};
#pragma pack(pop)

static int trig;
static int if_dot;


	
#pragma pack(push, 1)
struct DirEntry {
	uint8_t DIR_Name[11];		/* File name */
	uint8_t DIR_Attr;		/* File attributes */
	uint8_t DIR_NTRes;		/* Reserved */
	uint8_t DIR_CrtTimeTenth;	/* Created time (tenths of second) */
	uint16_t DIR_CrtTime;		/* Created time (hours, minutes, seconds) */
	uint16_t DIR_CrtDate;		/* Created day */
	uint16_t DIR_LstAccDate;	/* Accessed day */
	uint16_t DIR_FstClusHI;		/* High 2 bytes of the first cluster address */
	uint16_t DIR_WrtTime;		/* Written time (hours, minutes, seconds */
	uint16_t DIR_WrtDate;		/* Written day */
	uint16_t DIR_FstClusLO;		/* Low 2 bytes of the first cluster address */
	uint32_t DIR_FileSize;		/* File size in bytes. (0 for directories) */
};
#pragma pack(pop)


void print_hint(char* c) {
	printf("Usage: %s -d [device filename] [other arguments]\n", c);
	printf("-i                   Print file system information\n");
	printf("-l                   List of the root directory\n");
	printf("-r target -o dest    Recover the target deleted file\n");
	printf("-x target            Cleanse the target deleted file\n");
	trig = 1;
}

int char_valid_test(char k) {
	if(((int)k > 64 && (int)k < 91) || ((int)k > 47 && (int)k < 58)) return 1;
	else {
		if((int)k == '$' || (int)k == '%' || (int)k == '-' || (int)k == '.' 
		|| (int)k == '{' || (int)k == '}' || (int)k == '~' || (int)k == '!' || (int)k == '#' 
		|| (int)k == '(' || (int)k == ')' || (int)k == '&' || (int)k == '_' || (int)k == '^' 
		 )	return 1;
		else return 0;
	}
}

int filename_valid_test(char *c) {
	char current_char;
	current_char = *c;
	int cnt = 0;
	if_dot = 0;

	while(cnt < strlen(c)) {
		//printf("The current char is %c\n", current_char);	
		if(!char_valid_test(current_char)) return 0;
		if(current_char == '.') {
			if(if_dot == 1) return 0;
			else {
				if_dot = 1;
				if(cnt == 0 || cnt > 8 || strlen(c)-cnt < 2 || strlen(c)-cnt > 4) return 0;
			}		
		}
		cnt++;
		current_char = *(c+cnt);
	}
	
	return 1;
}

int main(int argc, char *argv[]) {
	int iflag = 0;
	int lflag = 0;
	int rflag = 0;
	int oflag = 0;
  	char *rvalue = NULL;
	char *ovalue = NULL;
	char *xvalue = NULL;
  	int c;
	trig = 0;
  	opterr = 0;
	
		

	//Open a file to write
	FILE *fp;

	while ((c = getopt (argc, argv, "ilr:o:x:d:")) != -1) {
    		switch (c) {
      			case 'i':
        			iflag = 1;
        			break;
      			case 'l':
        			lflag = 1;
        			break;
      			case 'r':
        			rvalue = optarg;
				rflag = 1;
        			break;
			case 'o':
        			ovalue = optarg;
				oflag = 1;
        			break;
			case 'd':
        			break;
			case 'x':
        			xvalue = optarg;
        			break;
      			case '?':
        			print_hint(argv[0]);
        			return 1;
      			default:
        			abort ();
      		}
	}
  	
	if(argc < 3) {print_hint(argv[0]); return 0; }
  	else if(argc > optind || strcmp(argv[1],"-d") || oflag != rflag) {
		print_hint(argv[0]);
		return 0; 
	}
	
	if(!trig) {
		//Read the file
		if( (fp = fopen(argv[2], "r+")) == NULL ) {
				perror(argv[2]);
				exit(1);
			}
		struct BootEntry boot_entry;
		fread(&boot_entry, 1, sizeof(struct BootEntry), fp);
	
		int tmp = boot_entry.BPB_BytsPerSec * (boot_entry.BPB_RsvdSecCnt
				+ boot_entry.BPB_FATSz32 *   boot_entry.BPB_NumFATs);
		if(iflag == 1) {
			printf("Number of FATs = %d\n", boot_entry.BPB_NumFATs);
			printf("Number of bytes per sector = %d\n", boot_entry.BPB_BytsPerSec);	
			printf("Number of sectors per cluster = %d\n", boot_entry.BPB_SecPerClus );
			printf("Number of reserved sectors = %d\n", boot_entry.BPB_RsvdSecCnt);
			printf("First FAT starts at byte = %d\n", boot_entry.BPB_BytsPerSec * boot_entry.BPB_RsvdSecCnt);
			printf("Data area starts at byte = %d\n", tmp);	
			
		} 
		
		if(lflag == 1) {
			int cnnt = 1;
			struct DirEntry dir_entry;
			fseek(fp, tmp  ,SEEK_SET);
			while(1) {
				fread(&dir_entry, 1 , sizeof(struct DirEntry), fp);
				if(dir_entry.DIR_Attr == 0 || dir_entry.DIR_Attr > 63) break;
				else {
					if(dir_entry.DIR_Name[0] == 0xe5)
						dir_entry.DIR_Name[0] = 0x3f;
					if(dir_entry.DIR_Attr == 15) 
						printf("%d, LFN entry\n", cnnt);	
					else if(dir_entry.DIR_Attr == 16) {
						uint8_t A[9]; int i = 0;
						for(i = 0; i < 8; i++) {
							if(dir_entry.DIR_Name[i] == 0x20) A[i] = '\0'; 								else 
							A[i] = dir_entry.DIR_Name[i];						
						}
						printf("%d, %s/, %d, %d\n", cnnt, 
							A, dir_entry.DIR_FileSize
							, 0x100 * dir_entry.DIR_FstClusHI+					       								dir_entry.DIR_FstClusLO);
					}
					else {
						int i; int trig_dot = 0;
						uint8_t A[9],B[3];
						for(i = 0; i < 8; i++) {
							if(dir_entry.DIR_Name[i] == 0x20) A[i] = '\0'; 								else 
							A[i] = dir_entry.DIR_Name[i];						
						}				
						for(i = 0; i < 3; i++) {
							if(dir_entry.DIR_Name[i+8] == 0x20) {
								if(i == 0) trig_dot = 1;
								B[i] = '\0'; 
							}
							else 
							B[i] = dir_entry.DIR_Name[i+8];						
						}	
	
						if(trig_dot == 0)
						printf("%d, %s.%s, %d, %d\n", cnnt, 
							A,B
							, dir_entry.DIR_FileSize
							, 0x100 * dir_entry.DIR_FstClusHI+					       								dir_entry.DIR_FstClusLO);
						else
						printf("%d, %s, %d, %d\n", cnnt, 
							A
							, dir_entry.DIR_FileSize
							, 0x100 * dir_entry.DIR_FstClusHI+					       								dir_entry.DIR_FstClusLO);
					}			
				}
				cnnt++;
			}
		}	

		if(rvalue != NULL || xvalue != NULL) {
			char* value;
			if(rvalue != NULL ) value = rvalue;
			else if(xvalue != NULL) value = xvalue;
			//Find the possible goal
			int if_find = 0;
			int name_co =1, dot_pos = 0;
			fseek(fp, tmp  ,SEEK_SET);
			struct DirEntry buf_tmp; int i;
			while(1) {
				name_co =1; dot_pos = 0;if_find = 0;
				fread(&buf_tmp, 1 , sizeof(struct DirEntry), fp);
				if(buf_tmp.DIR_Attr == 0 || buf_tmp.DIR_Attr > 63) break;
				if(buf_tmp.DIR_Attr == 16 || buf_tmp.DIR_Attr == 15 || buf_tmp.DIR_Name[0] != 0xe5 ) continue;
				for(i = 1; i < 8; i++) {
					if(buf_tmp.DIR_Name[i] == 0x20) {
						if(value[i] == '\0') {
							name_co = 0; 
							if_find = 1;
						}
						else if(value[i] == '.')  dot_pos = i;
						else name_co = 0;
						break; 						
					}
					else if(value[i] != buf_tmp.DIR_Name[i]) { 
						name_co = 0;
						break;
					}				
				}
				if(name_co == 1) {
					for(i = 0; i < 3; i++) {
						if(buf_tmp.DIR_Name[8 + i] == 0x20) {
							if(value[dot_pos + 1 + i] == '\0') if_find = 1;
							break; 						
						}
						else if(value[dot_pos + 1 + i] != buf_tmp.DIR_Name[8 + i]) {
							break;
						}	
						if(i == 2) if_find = 1;			
					}
				}	
				if(if_find == 1) break;	
			}
			

			if(if_find == 1) {
				char* Buf_write = malloc (512*sizeof(char));
				fseek(fp, tmp + boot_entry.BPB_BytsPerSec * boot_entry.BPB_SecPerClus *
					(0x100 * buf_tmp.DIR_FstClusHI + buf_tmp.DIR_FstClusLO - 2) , SEEK_SET);
				if(rvalue != NULL) {
					fread(Buf_write,  1 , buf_tmp.DIR_FileSize  , fp );
					FILE *dp;
					if( (dp = fopen(ovalue, "w+")) == NULL ) {
						printf("[%s]: error - fail to open\n", ovalue);	
						exit(1);
					}	
					fwrite(Buf_write, 1, buf_tmp.DIR_FileSize ,dp);
					printf("[%s] : recovered\n",value);
					fclose(dp);
				}
				else if(xvalue != NULL) {
					fseek(fp, tmp + boot_entry.BPB_BytsPerSec * boot_entry.BPB_SecPerClus *
					(0x100 * buf_tmp.DIR_FstClusHI + buf_tmp.DIR_FstClusLO - 2) , SEEK_SET);
					memset(Buf_write, 0, sizeof(*Buf_write) ); 
					fwrite(Buf_write,  1 , buf_tmp.DIR_FileSize  , fp );	
					printf("[%s] : cleansed\n",value);		
				}
				free(Buf_write);
				
			}
			else {
				printf("[%s]: error - fail to recover\n", value);			
			}
			
		}
	}


	
 	fclose(fp);
	
	return 0;
}
#endif /* RECOVERY */
