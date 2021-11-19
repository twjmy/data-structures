#include<stdio.h>
#include<stdlib.h>
typedef struct list_node *link;
typedef struct list_node {
	int data;
	link next;
} list_node;

#define IS_FULL(ptr) (!(ptr))
#define IS_EMPTY(node) (!(node))

/* insert a new node with data = 50 into the list ptr after node */
void insert(link *ptr, link node){
	link temp;
	temp = (link) (sizeof(link));
	if(IS_FULL(temp)){
		fprintf(stderr, "The memory is full\n");
		exit(1);
	}
	temp->data = 50;
	if(*ptr) { //noempty list
		temp->next = node ->next;
		node->next = temp;
	}else { //empty list
		temp->next = NULL;
		*ptr = temp;
	}
	free(temp);
}

/* delete node from the list, trail is the preceding node ptr is the head of the list */
void delete(link *ptr, link trail, link node){
	if (trail) trail->next = node->next;
	else *ptr = node->next; //head
	free(node);
}

void print_list(link ptr){
	printf("The list ocntains: ");
	for(; ptr; ptr = ptr->next)
		printf("%4d\n", ptr->data);
	printf("\n");
}

int main(){
	printf("break point");
    link list[3];
    list[0] -> data = 1,
	printf("%d", list[0] -> data);
	list[0] -> next = list[1];
    list[1] -> data = 2;
    list[1] -> next = list[2];
    list[2] -> data = 3;
    list[2] -> next = NULL;
    print_list(*list);
	return 0;
}
