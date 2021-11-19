#include<stdio.h>
#define MAX_STACK_SIZE 20*20 // maximum stack size
#define TRUE 1
#define FALSE 0

int i, j, top = -1;
typedef enum DirectEnum {n,e,w,s} Direct;
const Direct d;

typedef struct ElementStruct{
	short r, c;
	Direct d;
} Element;

Element pos, errorKey, stack[MAX_STACK_SIZE];

Element push(Element item){
	if(top>=MAX_STACK_SIZE-1){
		printf("[!] Stack is full, cannot add element\n");
		return errorKey;
	}
	stack[++top] = item;
	return item;
}

Element pop(){
	if(top==-1){
		printf("[!] Stack is empty, cannot delete element\n");
		return errorKey;
	}
	return stack[top--];
}

int main(){
	// printf("Load file, build map...\n");
	char inputFile[] = "test.txt";
	FILE *fp; fp = fopen(inputFile,"r");
	if(fp == NULL){
		printf("[!] \"%s\" file not found...\n", inputFile);
		return 1;
	}
	unsigned short int mapSize, EXIT_ROW, EXIT_COL;
	fscanf(fp,"%d\n", &mapSize);
	// printf("Map size = %d\n", mapSize);
	char
		map[mapSize][mapSize],
		mark[mapSize][mapSize],
		output[mapSize][mapSize],
		tmp;
	for(i=-1; mapSize>++i;) for(j=-1; mapSize>++j;){
		fscanf(fp,"%c ", &tmp);
		map[i][j] = tmp;
		if(tmp=='S'){ pos.r = i; pos.c = j;}
		if(tmp=='F'){ EXIT_ROW = i; EXIT_COL = j;}
	}

	// printf("Output map mark initialize...\n");
	memcpy(mark, map, sizeof(map));
	// for(i=-1; mapSize>++i;){
	// 	for(j=-1; mapSize>++j;) printf("%c", map[i][j]);
	// 	printf("\n");
	// }

	// printf("Dirrect element initialize...\n");
	Element	mv[4]; // array of moves for each direction
	mv[n].r=-1;	mv[n].c= 0;	// nextRow = row + mv[dir].r;
	mv[e].r= 0;	mv[e].c= 1;	// nextCol = col + mv[dir].c;
	mv[w].r= 0;	mv[w].c=-1;
	mv[s].r= 1;	mv[s].c= 0;
	// for(i=-1; ++i<s+1;) printf("mv[%d].<r,c> = <%d,%d>;\n", i, mv[i].r, mv[i].c);

	// printf("Output a path via the map if such a path exists...\n");
	int
		row, col,
		nextRow, nextCol,
		shortLength = 0;
	Direct dir;
	pos.d = n;
	push(pos);
	mark[pos.r][pos.c] = '*';
	// for(i=-1; mapSize>++i;){
	// 	for(j=-1; mapSize>++j;) printf("%c", mark[i][j]);
	// 	printf("\n");
	// }
	while (top > -1) {
		// printf("Move to pos at top of stack\n");
		pos = pop();
		row = pos.r; col = pos.c; dir = pos.d;
		// printf("<row,col,dir>=<%d,%d,%d>\n", row, col, dir);
		while (dir < (Direct)4) {
			// printf("Move in direction dir, coordinates of next move\n");
			nextRow = row + mv[dir].r;
			nextCol = col + mv[dir].c;
			if (nextRow < 0 || nextCol < 0 || // Edge judge
			  nextRow > mapSize || nextCol > mapSize)
				++dir;
			else if (map[nextRow][nextCol] == 'F' &&
			  (shortLength > top+2 || !shortLength)) {
				/* found a path shorter than before */
				// printf("Find an exit path:\n");
				pos.r = row; pos.c = col; pos.d = dir+1;
				push(pos);
				pos.r = EXIT_ROW; pos.c = EXIT_COL;
				push(pos);
				shortLength = top;
				// build output map
				memcpy(output, map, sizeof(map));
				for (i = 0; i <= top; i++)
					output[stack[i].r][stack[i].c] = '*';
				// print it
				// for(i=-1; mapSize>++i;){
				// 	for(j=-1; mapSize>++j;) printf("%c", output[i][j]);
				// 	printf("\n");
				// }
				// printf("Path Length: %d\n\n", top);
				row = nextRow; col = nextCol; dir = (Direct)0;
				mark[nextRow][nextCol] = 'F';
				pop(); pop(); ++dir;
			}
			else if (map[nextRow][nextCol] != 'X' &&
			  mark[nextRow][nextCol] != '*') {
				// printf("Legal move and haven't been there\n");
				mark[nextRow][nextCol] = '*';
				pos.r = row; pos.c = col; pos.d = ++dir;
				// printf("Save current pos and direction: <%d,%d,%d>\n",
				// 	row, col, dir);
				push(pos);
				row = nextRow; col = nextCol; dir = (Direct)0;
				// for(i=-1; mapSize>++i;){
				// 	for(j=-1; mapSize>++j;) printf("%c", mark[i][j]);
				// 	printf("\n");
				// }
				// printf("Path Length: %d\n\n", top);
			}
			else ++dir;
			// printf("<row,col,dir,top>= <%d,%d,%d>\n", row, col, dir, top);
		}
	}
	if (shortLength) {
		for(i=-1; mapSize>++i;){
			for(j=-1; mapSize>++j;) printf("%c", output[i][j]);
			printf("\n");
		}
		printf("Path Length: %d\n\n", shortLength);
	}
	else printf("The map does not have a path\n");
	return 0;
}