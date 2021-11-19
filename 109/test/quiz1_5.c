#include <stdio.h>
char list[] = "abc";
void swap(char a, char b){
	int i=0, j=0;
	for(int k=0; k<strlen(list); k++){
		if(a == list[k]) i = k; else
		if(b == list[k]) j = k;
		if(i && j) break;
	}
	char tmp = list[i];
	list[i] = list[j];
	list[j] = tmp;
}
void P(char *list, int i){
	size_t length = strlen(list); //get the size of list
	if (i == length){ //printf("#");
		for (int i = 0; i < length; i++) printf("%c", list[i]);
		printf("\n");
	}
	else{ //printf("for(int j=%d; j<%d; j++) ",i,length);
		for(int j = i; j < /*(a)*/length; j++){
			swap(list[i], list[j]); // The swap function will exchange the element of parameter.
			P(/*(b)*/list, i+1);
			swap(list[i], list[j]);
		}
	}
}
void main(){
	// Assume list has been initialized and the size of list is n.
	P(&list, 0);
}