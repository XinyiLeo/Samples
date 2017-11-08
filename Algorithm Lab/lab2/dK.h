#ifndef dK_H_ 
#define dK_H_

typedef unsigned char byte;    

typedef struct node {  
	struct node *parent;  
	int rank;
	int serial;
} node_t;  

typedef struct edge {  
	int weight;
	node_t *father;  
	node_t *son; 
} edge_t;

byte ifexist(int len, int* set, int test) {
	int i;
	for(i = 0; i < len; i++) {
		if(test == *(set+i)) return 1;
	}
	return 0;
}
  
node_t* Getnode(int serial) { 
	node_t *pnode = (node_t*)malloc(sizeof(node_t)); 
	if(pnode!=NULL) {
		pnode->parent = NULL;
		pnode->rank = 0;  
		pnode->serial = serial;
	}
  	return pnode;  
}

edge_t* Getedge(int weight, int father, int son, node_t** no) { 
	edge_t *pedge = (edge_t*)malloc(sizeof(edge_t)); 
	if(pedge!=NULL) {
		pedge-> weight = weight;
		pedge-> father= no[father];  
		pedge-> son = no[son];
	}
  	return pedge;  
}

node_t* find_root(node_t* x) {
	if(x->parent == NULL) return x;
	else {
		if(x->parent->parent != NULL)
			x->parent = find_root(x->parent);
		return x->parent;
	}
} 

void union_root(node_t* x, node_t* y) {
	node_t* x_root;
	node_t* y_root;
	x_root = find_root(x);
	y_root = find_root(y);
	if(x_root->rank > y_root->rank) y_root->parent = x_root;
	else {
		x_root->parent = y_root;
		if(x_root->rank == y_root->rank) y_root->rank++;
	}
}

void sort_ed(edge_t** input, int cnt) {
	edge_t* sw_ed;
	//Bubble Sort
	int i, j;
	for(i = cnt - 1; i >=0; i-- ) {
		for(j = 0; j < i; j++ ) {
			if(input[j]->weight > input[j+1]->weight) {
				sw_ed = input[j];
				input[j] = input[j+1];
				input[j+1] = sw_ed; 
			}
		}
	}
}



#endif  
