#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <glob.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/wait.h>

#define ARGNUM 10

static char cwd[PATH_MAX+1];
static char input[255];
static char *cmd;
static char *token;
static glob_t globbuf;

static int str_valid_test(char* tmp, int t) {
	if(t == 0) {
		if(strchr(tmp,' ')== NULL && strchr(tmp,'	')== NULL && strchr(tmp,62)== NULL && strchr(tmp,60)== NULL &&
			strchr(tmp,124)== NULL && strchr(tmp,42)== NULL && strchr(tmp,33)== NULL && strchr(tmp,96)== NULL 				&& strchr(tmp,39)== NULL && strchr(tmp,34)== NULL) return 1;
		else return 0;		
	}
	else {
		if(strchr(tmp,' ')== NULL && strchr(tmp,'	')== NULL && strchr(tmp,62)== NULL && strchr(tmp,60)== NULL &&
			strchr(tmp,124)== NULL && strchr(tmp,33)== NULL && strchr(tmp,96)== NULL && strchr(tmp,39)== NULL
			 && strchr(tmp,34)== NULL) return 1;
		else return 0;		
	}
}

static int split (char* cmd, char** argList) {
	int iter = 0;
	token = strtok(cmd," ");
	while(token != NULL && iter < ARGNUM){
			strcpy(argList[iter],token);
			token = strtok(NULL," ");
		iter++;	
	}
	//printf("%d\n",iter);
	return iter;
}

static int find_wildcard(char* cmd) {
	char* find;
	find = strchr(cmd,'*');
	//printf("%s\n",find);
	if(find == NULL) return 0;
	else return 1;
}

static int input_dealing(char* cmd, char** argList){
	char** temp = (char**) malloc(sizeof(char*) * ARGNUM); 
	/* Build-in Command Exit */
	//printf("%s\n",cmd);
	int m,k,g;
	g = find_wildcard(cmd); 
	k = split(cmd, argList);
	for(m = 0; m < k; m++) {
		temp[m] = argList[m];
		if(!str_valid_test(temp[m],m)) {
			free(temp);
			return 0;		
		}
	}
	temp[k] = NULL;
	
	/* Build-in command change directory */
	if(k != 0) {
		if(!strcmp(temp[0], "exit")) {
			if(temp[1] == NULL) {			
				free(temp);
				return 1;
			}
			else {
				printf("exit: wrong number of arguments\n");			
			}
		}
		else if(!strcmp(temp[0],"cd")) {
			if (!strcmp(argList[1], " ") || strcmp(argList[2], " ")) {
 				fprintf(stderr, "cd: wrong number of arguments\n");
  			} 
			else if (chdir(argList[1]) != 0) {
      				fprintf(stderr, "[arg]: cannot change directory\n");
  			}
		}
		else {
			if(g == 0) {
    				if(!fork()){               //Child
					signal(SIGINT,SIG_DFL);
					signal(SIGQUIT,SIG_DFL);
					signal(SIGTERM,SIG_DFL);
					signal(SIGTSTP,SIG_DFL);
        		 		execvp(*temp,temp);
			 		if(errno == ENOENT) printf("%s: command not found\n",cmd);
					else {
			 			printf("%s: unknown error\n",cmd);
			 		}
        		 		free(temp);
			 		return 1;
				}
				else{                    //Parent
        				wait(NULL);
    				}
			}	
			else {
				if(k >= 2) {
					if(!fork()){ 
						signal(SIGINT,SIG_DFL);
						signal(SIGQUIT,SIG_DFL);
						signal(SIGTERM,SIG_DFL);
						signal(SIGTSTP,SIG_DFL);  
						glob(temp[1], GLOB_DOOFFS | GLOB_NOCHECK, NULL, &globbuf);	
						for(m = 2; m < k; m++ ) {
						glob(temp[m], GLOB_DOOFFS | GLOB_NOCHECK | GLOB_APPEND , NULL, &globbuf);                    
						}
						globbuf.gl_pathv[0] = temp[0];	
						execvp(globbuf.gl_pathv[0], globbuf.gl_pathv);	
						if(errno == ENOENT) printf("%s: command not found\n",cmd);
						else {
			 				printf("%s: unknown error\n",cmd);
			 			}
        		 			free(temp);
			 			return 1;
					}
					else{                    //Parent
        					wait(NULL);
    					}	
				}				
			}
		}
	}
	free(temp);
	return 0;
}

int main(int argc, char *argv[]){
	/* preparation */
	int j;
	setenv("PATH","/bin:usr/bin:.",1);
	globbuf.gl_offs = 1;
	signal(SIGINT,SIG_IGN);
	signal(SIGQUIT,SIG_IGN);
	signal(SIGTERM,SIG_IGN);
	signal(SIGTSTP,SIG_IGN);
	

	char** argList = (char**) malloc(sizeof(char*) * ARGNUM); 
	for(j = 0; j < ARGNUM; j++ ) {
		argList[j] = (char*) malloc(sizeof(char) * 10);	strcpy(argList[j], " ");
	}

	while(1) {
		for(j = 0; j < ARGNUM - 1; j++ ) {
			strcpy(argList[j], " ");
		}
		/* Print the command prompt */
		printf("[3150 shell:");
		if(getcwd(cwd,PATH_MAX+1) != NULL) {
			printf("%s",cwd);	
		}
		else{
			printf("Error Occured!");	
		}
		printf("]$ ");

		/* Read a command line */
		if (!fgets(input, 255, stdin)) {printf("\n");return 0;}
		input[strlen(input)-1] = '\0';
		cmd = input;
		

		/* Deal with the signal*/
		int ooo = input_dealing(cmd, argList);
		//printf("ooo = %d, mypid_is %d\n",ooo, getpid());
		if(ooo==1) break;
	} 
	
	/* Start to free the memory */
	for(j = 0; j < ARGNUM; j++ ) {
		free(argList[j]);	
	}
	free(argList);
	return 0;
} 
