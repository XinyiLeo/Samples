#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODE 100
#define INFINITY 10000

typedef unsigned char byte;   
byte ifexist(int len, int* set, int test) {
	int i;
	for(i = 0; i < len; i++) {
		if(test == *(set+i)) return 1;
	}
	return 0;
}

int main() {
	char buf[MAX_NODE];
	char *cmd;
	char* token;
	int i;
	int first_num[MAX_NODE];
	int second_num[MAX_NODE];
	int ed_wei[MAX_NODE];
	FILE *pFile;
	if(!(pFile = fopen("iinput.txt","r"))) {
		puts("Input file Failed\n");
		exit(0);
	}	
	int real_num_set[MAX_NODE];
	int real_num = 0;
	int cnt = 0;
	int flag = 0;
	while(fgets(buf,50, pFile)) {
		buf[strlen(buf)-1] = '\0';
		cmd = buf;
		token = strtok(cmd," ");
		first_num[cnt] = atoi(token);
		token = strtok(NULL," ");
		second_num[cnt] = atoi(token);
		token = strtok(NULL,"\n");
		ed_wei[cnt] = atoi(token);
		if(!ifexist(real_num, real_num_set, first_num[cnt])) {
			real_num_set[real_num] = first_num[cnt];
			real_num++;
		}  
		if(!ifexist(real_num, real_num_set, second_num[cnt])) {
			real_num_set[real_num] = second_num[cnt];
			real_num++;
		}  
		cnt++;
	}

	int j = 0;
	int edge_matrix[real_num+1][real_num+1];
	for(i = 0; i < real_num +1; i++) {
		for(j = 0; j < real_num+1; j++) {
			edge_matrix[i][j] = INFINITY;		
		}	
	}
	
	for(i = 0; i < cnt; i++) {
		edge_matrix[second_num[i]][first_num[i]] = ed_wei[i];
		edge_matrix[first_num[i]][second_num[i]] = ed_wei[i];
	}
	
	int Dist[real_num + 1];
	for(i = 0; i < real_num +1 ; i++) {
		Dist[i] = INFINITY;
	}
	int T_set[real_num];
	for(j = 0; j < real_num; j++) {
		T_set[j] = 0;
	}

	int parent[real_num + 1];
	int edge_set[cnt];
	int k;
	int smallest_node;
	int smallest_value = INFINITY;
		
	smallest_node = 0;
	Dist[real_num_set[smallest_node]] = 0;
	
	for(j = 0; j < real_num; j++ ) {
		smallest_value = INFINITY;
		//Put the node into T set
		T_set[j] = real_num_set[smallest_node];
		//Delete node in T' Set
		real_num_set[smallest_node] = 0;

		for(k = 0; k < real_num; k++) {
			//Check each nodes
			if(real_num_set[k] != 0) {
				if(edge_matrix[T_set[j]][real_num_set[k]] < Dist[real_num_set[k]]) {
					Dist[real_num_set[k]] = edge_matrix[T_set[j]][real_num_set[k]];
					parent[real_num_set[k]] = T_set[j];
				}
			}
			if(Dist[real_num_set[k]] < smallest_value) {
				smallest_value = Dist[real_num_set[k]];
				smallest_node = k;		
			}
		}
	}
	//Print out
	for(j = 1; j < real_num; j++ ) {
		printf("Edge %d: Connect nodes %d and %d, the weight is: %d. \n", j
			, T_set[j], parent[T_set[j]], edge_matrix[T_set[j]][parent[T_set[j]]]);
	}



	fclose(pFile); 
	return 0;
}



