#include<stdio.h>

/* Sparse_matrix Create(max_row, max_col) ::= */ 

#define MAX_TERMS 101 /* maximum number of terms +1*/

typedef struct {
	int col;
	int row;
	int value;
} term a [MAX_TERMS]; 

void fast_transpose(term a[ ], term b[ ]){
/* the transpose of a is placed in b */
	int row_terms[MAX_COL], starting_pos[MAX_COL];
	int i, j, num_cols = a[0].col, num_terms = a[0].value;
	b[0].row = num_cols; b[0].col = a[0].row;
	b[0].value = num_terms;
	if (num_terms > 0){ /*nonzero matrix*/
		for (i = 0; i < num_cols; i++)
			row_terms[i] = 0;
		for (i = 1; i <= num_terms; i++) /*計算 row_terms的值*/
			row_term [a[i].col]++
		starting_pos[0] = 1;
		for (i =1; i < num_cols; i++)
		starting_pos[i]=starting_pos[i-1] +row_terms [i-1];
			/*計算 starting_pos的值*/ 
		for (i=1; i <= num_terms, i++) {
			j = starting_pos[a[i].col]++;
			b[j].row = a[i].col;
			b[j].col = a[i].row;
			b[j].value = a[i].value;
		}
	}
}

void mmult (term a[ ], term b[ ], term d[ ] ){
/* multiply two sparse matrices */
	int i, j, column, totalb = b[].value, totald = 0;
	int rows_a = a[0].row, cols_a = a[0].col,
	totala = a[0].value; int cols_b = b[0].col,
	int row_begin = 1, row = a[1].row, sum =0;
	int new_b[MAX_TERMS][3];
	if (cols_a != b[0].row){
	/*compare the row of a and the col of b*/
		fprintf (stderr, "Incompatible matrices\n");
		exit (1);
	}
	
	fast_transpose(b, new_b); /* the transpose of b is placed in new_b */
	/* set boundary condition */
	a[totala+1].row = rows_a; /* a[0].row*/
	new_b[totalb+1].row = cols_b;
	new_b[totalb+1].col = 0;
	for (i = 1; i <= totala; ) {/* a[0].val */
		column = new_b[1].row; /* b[1].col*/
		for (j = 1; j <= totalb+1;) { /*b[0].val*/
		/* mutiply row of a by column of b */
			if (a[i].row != row) { /* a[1].row */
				storesum(d, &totald, row, column, &sum);
				i = row_begin;
				for (; new_b[j].row == column; j++)
					continue;
				column =new_b[j].row; /* next col */
			}
			else switch (COMPARE (a[i].col, new_b[j].col)) {
				case -1: /* go to next term in a */
					i++; break;
				case 0: /* add terms, go to next term in a and b */
					sum += (a[i++].value * new_b[j++].value);
					break;
				case 1: /* advance to next term in b*/
					j++;
			}
		} /* end of for j <= totalb+1 */
		for (; a[i].row == row; i++)
			continue;
		row_begin = i; row = a[i].row;
	} /* end of for i <=totala */
	d[0].row = rows_a; /* a[0].row*/
	d[0].col = cols_b; /* b[0].cols*/
	d[0].value = totald;
} 

void storesum(term d[ ], int *totald, int row, int column,
int *sum){
	/* if *sum != 0, then it along with its row and column
	position is stored as the *totald+1 entry in d */
	if (*sum && *totald < MAX_TERMS) {
			d[++*totald].row = row;
			d[*totald].col = column;
			d[*totald].value = *sum;
	}
	else {
		fprintf(stderr, "Numbers of terms in product exceed %d\n", MAX_TERMS);
		exit(1);
	}
}

int main(){
	printf("############# Program start #############");
	printf("################## End ##################");
	system("PAUSE");
	return 0;
}

