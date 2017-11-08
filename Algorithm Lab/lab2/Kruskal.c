#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dK.h"

#define NODE_NUM 30
#define MAXNODE 40

int main(int argc, char *argv[]) {
	char buf[100];
	char *cmd;
	char* token;
	int i;
	int first_num[100];
	int second_num[100];
	int ed_wei[100];


	FILE *pFile;
	if(!(pFile = fopen("iinput.txt","r"))) {
		puts("Input file Failed\n");
		exit(0);
	}	
	int cnt = 0;
	while(fgets(buf,50, pFile)) {
		buf[strlen(buf)-1] = '\0';
		cmd = buf;
		token = strtok(cmd," ");
		first_num[cnt] = atoi(token);
		token = strtok(NULL," ");
		second_num[cnt] = atoi(token);
		token = strtok(NULL,"\n");
		ed_wei[cnt] = atoi(token);
		cnt++;
	}

	//construct nodes
	int contain[2 * cnt];
	node_t* node_set[MAXNODE];
	int set_length = 0;
	for(i = 0;i < cnt; i++) {
		if(!ifexist(set_length,contain,first_num[i])) {
			contain[set_length] = first_num[i];
			set_length++;
		}
		if(!ifexist(set_length,contain,second_num[i])) {
			contain[set_length] = second_num[i];
			set_length++;
		}
	}
	for(i = 0; i < set_length; i++) {
		node_set[contain[i]] = Getnode(contain[i]); 		
	}	

	//Edge
	edge_t* edge_set[cnt];
	edge_t* edge_set_sorted[cnt];
	edge_t* wanted_edge_set[cnt];
	int wanted = 0;
	
	for(i = 0; i < cnt; i++) {
		edge_set[i] = Getedge(ed_wei[i], first_num[i], second_num[i], node_set);
	}
	sort_ed(edge_set,cnt);
	

	//Begin Kruskal
	for(i = 0; i < cnt; i++) {
		if(find_root(edge_set[i]->father)!=find_root(edge_set[i]->son)) {
			wanted_edge_set[wanted] = edge_set[i];
			wanted ++;
			union_root(edge_set[i]->father,edge_set[i]->son);		
		}
	}
	for(i = 0; i < wanted; i++) {
		printf("Edge %d: Connect nodes %d and %d, the weight is: %d. \n",i + 1, wanted_edge_set[i]->father->serial 
			, wanted_edge_set[i]->son->serial, wanted_edge_set[i]->weight);
	}

	fclose(pFile); 
	return 0;
}
