#include<stdio.h>

/* Sparse_matrix Create(max_row, max_col) ::= */ 

#define MAX_TERMS 101 /* maximum number of terms +1*/

typedef struct {
	int col;
	int row;
	int value;
} term;
term a [MAX_TERMS]

void transpose (term a[], term b[]){
/* b is set to the transpose of a */
	int n, i, j, currentb;
	n = a[0].value; /* total number of elements */
	b[0].row = a[0].col; /* rows in b = columns in a */
	b[0].col = a[0].row; /*columns in b = rows in a */
	b[0].value = n;
	if (n > 0){ /*non zero matrix */
		currentb = 1;
		for (i = 0; i < a[0].col; i++)
		/* transpose by columns in a */
		for( j = 1; j <= n; j++)
		/* find elements from the current column */
		if (a[j].col == i) {
			/* element is in current column, add it to b */
			CHAPTER 2 67
			b[currentb].row = a[j].col;
			b[currentb].col = a[j].row;
			b[currentb].value = a[j].value;
			currentb++
		}
	}
}

int main(){
	printf("############# Program start #############");
	printf("################## End ##################");
	system("PAUSE");
	return 0;
}

