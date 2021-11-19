#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef enum Boolean{ FALSE, TRUE } bool;

char inputFile[] = "test.txt", **map;
int
	i, j, **mark,
	rear = -1, front = -1, shortest = 0,
	er, ec, dir[4][2]={
		/*n*/{-1,0}, /*e*/{0, 1},
		/*s*/{ 1,0}, /*w*/{0,-1}
	};
unsigned short mapSize;

typedef struct e* Element;
typedef struct q* Queue;

Element start, final;
Queue q;

struct e{
    short r, c, d;
};

struct q{
    int _cap;
    int _rear;
    int _len;
    int _front;
    Element* list;
    Element (*delQ)();
    void (*addQ)(Element);
    int (*isEmpty)();
    void (*printQ)();
};

void addQ(Element e){
	// printf("addQ <%d,%d>\n", e->r, e->c);
    if((q->_len + 1) == (q->_cap)){
        int newCap = q->_cap << 1;
        Element* newList = malloc(sizeof(*newList) * newCap);
        int i;
        for(i=0; i<q->_len; i++)
            newList[i] = q->list[(q->_rear + i) % q->_cap];
        q->list = newList;
        q->_front = q->_len;
        q->_rear = 0;
        q->_cap = newCap;
    }
    q->list[q->_front] = e;
    q->_front = (q->_front + 1) % q->_cap;
    q->_len++;
}

void printQ(){
    int i;
    Element e;
    for(i=0; i < q->_len; i++){
        e = q->list[(q->_rear + i) % q->_cap];
        printf("<%d,%d> -> ", e->r, e->c);
    }
    printf("NULL\n");
}

Element delQ(){
    if(q->isEmpty(q)){
        fprintf(stderr, "[!] Queue empty\n");
		printQ(q);
        exit(1);
    }
    Element tmp = q->list[q->_rear];
    q->_rear = (q->_rear + 1) % q->_cap;
    q->_len--;
    return tmp;
}

int isEmpty(){
    return q->_len == 0;
}

Queue newQueue(){
    q = malloc(sizeof(*q));
    q->_cap = 8;
    q->_len = 0;
    q->_rear = 0;
    q->_front = 0;
    q->list = malloc(sizeof(*(q->list)));
    q->addQ = addQ;
    q->delQ = delQ;
    q->isEmpty = isEmpty;
    q->printQ = printQ;
    return q;
}

Element element(short r, short c, short d){
    Element e = malloc(sizeof(*e));
    e->r = r;
    e->c = c;
    e->d = d;
    return e;
}

bool bfs(Element e){
	int d = e->d + 1;
	for(i=0; i<4; i++){
		// printf("dir: %d, %d\n", dir[i][0], dir[i][1]);
		er = e->r + dir[i][0]; ec = e->c + dir[i][1];
		if(er<0 || er >= mapSize || ec<0 || ec >= mapSize){
			// printf("(%d, %d) continue occurs", er, ec);
			continue;
		}
		else if(mark[er][ec] == -1){
			mark[er][ec] = d;
			final->d = d;
			q->addQ(final);
			// for(i=0; i<mapSize; i++){
			// 	for(j=0; j<mapSize; j++){
			// 		printf("%3d ", mark[i][j]);
			// 	}
			// 	printf("\n");
			// }
			shortest = d;
			return TRUE;
		}
		else if(mark[er][ec]>d){
			mark[er][ec] = d;
			q->addQ(element(er,ec,d));
		}
	}

	// for(i=-1;mapSize>++i;){
	// 	for(j=-1;mapSize>++j;){
	// 		printf("%3d ", mark[i][j]);
	// 	}
	// 	printf("\n");
	// }

	return FALSE;
}
int main(){
	// Load file
	FILE *fp; fp = fopen(inputFile,"r");
	if(fp == NULL){
		printf("[!] \"%s\" file not found...\n", inputFile);
		return 1;
	}
	// global 2-D array "map","mark" memory allocation
	fscanf(fp,"%d\n", &mapSize);
	map = malloc(mapSize*sizeof(char *));
	mark = malloc(mapSize*sizeof(int *));
	for(i=-1;mapSize>++i;){
		map[i] = malloc(mapSize*sizeof(char));
		mark[i] = malloc(mapSize*sizeof(int));
	}
	// Scan characters, build "map" and "mark"
	char tmp;
	for(i=-1;mapSize>++i;) for(j=-1;mapSize>++j;){
		fscanf(fp,"%c ", &tmp);
		switch (tmp){
		case 'O':
			map[i][j] = tmp;
			mark[i][j] = mapSize*mapSize;
			break;
		case 'X':
			map[i][j] = tmp;
			mark[i][j] = 0;
			break;
		case 'S':
			map[i][j] = tmp;
			mark[i][j] = 0;
			start = element(i,j,0);
			break;
		case 'F':
			map[i][j] = tmp;
			mark[i][j] = -1;
			final = element(i,j,0);
			break;
		default: break;
		}
	}
	fclose(fp);

	// for(i=0; i<mapSize; i++){
	// 	for(j=0; j<mapSize; j++){
	// 		printf("%3d ", mark[i][j]);
	// 	}
	// 	printf("\n");
	// }
	// printf("\n");
	// printf("----------start!!!-------------\n");

	// Output a path via the map if such a path exists
	q = newQueue();
	q->addQ(start);

	int stop = FALSE;
	while(!stop && !q->isEmpty()){
		// printf("----------------- %d -------------------\n", e->d);
		// printf("step on <%d, %d>\n", e->r, e->c);
		stop = bfs(q->delQ());
		// printf("------------- %s, %s --------------\n",
		//	(!stop)?"TRUE":"FALSE", (!q->isEmpty())?"TRUE":"FALSE");
	}
	if(shortest){
		char output[mapSize][mapSize];
		for(i=-1;mapSize>++i;){
			for(j=-1;mapSize>++j;)
				output[i][j] = map[i][j];
			// 	printf("%c", output[i][j]);
			// printf("\n");
		}
		// go back to start position
		stop = FALSE;
		output[final->r][final->c] = '*';
		j = final->d;
		while(!stop){
			j--;
			for(i=4;-1<--i;){
				// printf("dir: %d, %d\n", dir[i][0], dir[i][1]);
				er = final->r + dir[i][0]; ec = final->c + dir[i][1];
				if(er == start->r && ec == start->c){
					output[er][ec] = '*';
					stop++;
					break;
				}
				else if(mark[er][ec] == j && j != 0){
					output[er][ec] = '*';
					final = element(er,ec,final->d);
					break;
				}
				else continue;
			}
			// int m, n;
			// for(m=-1;mapSize>++m;){
			// 	for(n=-1;mapSize>++n;) printf("%c", output[m][n]);
			// 	printf("\n");
			// }
		}
		for(i=-1;mapSize>++i;){
			for(j=-1;mapSize>++j;)
				printf("%c", output[i][j]);
			printf("\n");
		}
		printf("Path Length: %d\n\n", shortest);
	}
	else printf("The path doesn't exist.\n");
	return 0;
}