#include<stdio.h>
#include<math.h>
typedef enum Boolean{FALSE,TRUE} bool;
FILE *fp;
int n,i;

struct TreeNode {
	int data;
	struct TreeNode *left;
	struct TreeNode *right;
};

typedef struct TreeNode Node;

Node *root;

Node *newNode(int data){
	Node *node = (Node*) malloc(sizeof(Node));
	node->data = data;
	node->left = node->right = NULL;
	return (node); 
}

Node *insertLevelOrder(int arr[], Node *root, int i, int n){
	if (i < n){ 
		if(arr[i] == NULL);
		Node *temp = newNode(arr[i]); 
		root = temp;
		root->left = insertLevelOrder(arr, root->left, 2*i+1, n); 
		root->right = insertLevelOrder(arr, root->right, 2*i+2, n); 
	} 
	return root; 
}

int load(char inputFile[]){
	fp = fopen(inputFile, "r");
	if(fp == NULL){
		printf("[!] \"%s\" file not found...\n", inputFile);
		return 1;
	}
	int data, c;
	n = 1;
	fscanf(fp,"[");
	while(TRUE){
		c = fgetc(fp);
		if(c==',') n++;
		else if(c==']') break;
	}
	int arr[n],i=0;
	rewind(fp);
	fscanf(fp,"[");
	while(TRUE){
		if(fscanf(fp,"%d",&data)>0) arr[i] = data;
		else{
			c = fgetc(fp);
			if(c==']') break;
			else if(c=='n'){
				arr[i] = -1;
				for(int i = -1; 3 > ++i;)
					fgetc(fp);
			}
		}
		i++;
	}
	fclose(fp);
	root = insertLevelOrder(arr, root, 0, n);
	return 0;
}

void postOrder(Node* root){ 
	if(root != NULL){
		postOrder(root->left);
		postOrder(root->right);
		root->data = 2;
	}
}



int main(){
	load("test1.txt");
	return 0;
}