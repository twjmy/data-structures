#include<stdio.h>

/* Sparse_matrix Create(max_row, max_col) ::= */ 

#define MAX_TERMS 101 /* maximum number of terms +1*/

typedef struct {
	int col;
	int row;
	int value;
} term;
term a[MAX_TERMS];

void fast_transpose(term a[ ], term b[ ]){
/* the transpose of a is placed in b */
	int row_terms[MAX_COL], starting_pos[MAX_COL];
	int i, j, num_cols = a[0].col, num_terms = a[0].value;
	b[0].row = num_cols; b[0].col = a[0].row;
	b[0].value = num_terms;
	if (num_terms > 0){ /*nonzero matrix*/
		for (i = 0; i < num_cols; i++)
			row_terms[i] = 0;
		for (i = 1; i <= num_terms; i++) /*�p�� row_terms����*/
			row_term [a[i].col]++
		starting_pos[0] = 1;
		for (i =1; i < num_cols; i++)
		starting_pos[i]=starting_pos[i-1] +row_terms [i-1];
			/*�p�� starting_pos����*/ 
		for (i=1; i <= num_terms, i++) {
			j = starting_pos[a[i].col]++;
			b[j].row = a[i].col;
			b[j].col = a[i].row;
			b[j].value = a[i].value;
		}
	}
}

int main(){
	printf("############# Program start #############");
	printf("################## End ##################");
	system("PAUSE");
	return 0;
}

