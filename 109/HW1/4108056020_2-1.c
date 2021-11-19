#include<stdio.h>
#include<stdlib.h>
typedef enum Boolean { FALSE, TRUE } bool;
bool frist = TRUE;
FILE* fp;
short **mark[6];
char inputFile[13], **map[6], **output[6], tmp;
int i, j, k, s, floo, ef, er, ec, shf=455,
	size = 0, shortest = 0,
	dir[4][2]={
		/*n*/{-1, 0}, /*e*/{ 0, 1},
		/*s*/{ 1, 0}, /*w*/{ 0,-1},
	};
unsigned short mapSize;

typedef struct e* Element;
typedef struct q* Queue;
typedef struct w* Way;

Element start, up;
Queue q;

struct e{
	short f, r, c, d;
};

struct q{
    int _cap;
    int _rear;
    int _len;
    int _front;
    Element* list;
    Element (*delQ)();
    Element (*addQ)(Element);
    int (*isEmpty)();
    void (*printQ)();
};

Element addQ(Element e){
	printf("addQ <%d,%d,%d>\n", e->f, e->r, e->c);
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
	return e;
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
        printf("[!] Queue empty\n");
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

Element element(short f, short r, short c, short d){
    Element e = malloc(sizeof(*e));
	e->f = f;
    e->r = r;
    e->c = c;
    e->d = d;
    return e;
}

void mapMark(int f, int r, int c){
	switch (tmp){
	case 'S':
		start = element(f,r,c,0);
	case 'X':
		mark[f][r][c] = 0;
		break;
	default: 
		mark[f][r][c] = 455;
		break;
	}
}

int sizef(int f){
	switch (f){
	case 5: return 13;
	case 4: return 11;
	case 3: return 9;
	case 2: return 7;
	case 1: return 5;
	case 0: return 3;
	default: exit(1);
	}
}

bool fileScan(){
	size = 0;
	while(fscanf(fp,"%c ", &tmp)>0) size++;
	switch(size){
	// 1+3*3=10, 10+5*5=35, 35+7*7=84,
	// 84+9*9=165, 165+11*11=286, 286+13*13=455.
		case 455: size=13; floo=5; break;
		case 286: size=11; floo=4; break;
		case 165: size=9; floo=3; break;
		case 84: size=7; floo=2; break;
		case 35: size=5; floo=1; break;
		case 10: size=3; floo=0; break;
	}
	if(frist){
		s=13;
		for(i=6;-1<--i;s-=2){
			map[i] = malloc((s+1)*sizeof(char *));
			output[i] = malloc((s+1)*sizeof(char *));
			mark[i] = malloc((s+1)*sizeof(short *));
			for(j=-1;s>++j;){
				map[i][j] = malloc((s+1)*sizeof(char));
				output[i][j] = malloc((s+1)*sizeof(char));
				mark[i][j] = malloc((s+1)*sizeof(short));
			}
		}
		frist = FALSE;
	}
	if(size > 1){
		rewind(fp);
		s = size;
		printf("s=%d\n",s);
		for(i=floo+1;-1<--i;s-=2){
			for(j=-1;s>++j;){
				for(k=-1;s>++k;){
					fscanf(fp,"%c ", &tmp);
					map[i][j][k] = tmp;
					output[i][j][k] = tmp;
					mapMark(i,j,k);
					printf("%c ", map[i][j][k]);
				}
				printf("\n");
			}
		}
	}else{
		printf("Path length: 0\n");
		printf("=====outMaze=====\n");
		printf("*\n");
		fclose(fp);
		return FALSE;
	}
	s = size;
	printf("s=%d\n",s);
	for(i=floo+1;-1<--i;s-=2){
		for(j=-1;s>++j;){
			for(k=-1;s>++k;)
				printf("%3d ",mark[i][j][k]);
			printf("\n");
		}
	}
	fclose(fp);
	return TRUE;
}

bool bfs(Element e){
	int d = e->d + 1;
	ef = e-> f;
	s = sizef(ef);
	for(i=-1; 4>++i;){
		er = e->r + dir[i][0]; ec = e->c + dir[i][1];
		printf("s = %2d, dir: %2d, %2d,  <ef,er,ec> = <%d, %d, %d>\n",
			s, dir[i][0], dir[i][1], ef, er, ec);
		if( er<0 || ec<0 || er >= s || ec >= s ){
			printf("continue occurs\n");
			continue;
		}else if(mark[ef][er][ec] > d){
			mark[ef][er][ec] = d;
			if(map[ef][er][ec] == 'T')
				mark[ef][er][ec] += 3;
			q->addQ(element(ef,er,ec,d));
			if(map[ef][er][ec] == 'U' && d > shf){
				printf("up:<f,r,c,d>=%d,%d,%d,%d", up->f, up->r, up->c, up->d);
				up = element(ef-1,er-1,ec-1,d+1);
			}
		}
	}

	s = size;
	for(i=floo+1;-1<--i;s-=2){
		for(j=-1;s>++j;){
			for(k=-1;s>++k;)
				printf("%3d ",mark[i][j][k]);
			printf("\n");
		}
	}
	return FALSE;
}
int main(){
	int fileNo;
	for(fileNo=0;1+1>++fileNo;){ // Load file in order from 1 to 100
		sprintf(inputFile, "test%d.txt", fileNo);
		printf("%s\n", inputFile);
		fp = fopen(inputFile, "r");
		if(fp == NULL){
			printf("[!] \"%s\" file not found...\n", inputFile);
			return 1;
		}
		if(fileScan()){
			q = newQueue();
			q->addQ(start);
			int stop = FALSE;
			while(!stop && !q->isEmpty()){
				Element e = q->delQ();
				printf("----------------- %d -------------------\n", e->d);
				printf("step on <%d, %d, %d>\n", e->f, e->r, e->c);
				stop = bfs(e);
				printf("------------- %s, %s --------------\n",
					(!stop)?"TRUE":"FALSE", (!q->isEmpty())?"TRUE":"FALSE");
			}
			size -= 2;
			printf("up:<f,r,c,d>=%d,%d,%d,%d", up->f, up->r, up->c, up->d);
			q->addQ(up);
			while(!stop && !q->isEmpty()){
				Element e = q->delQ();
				printf("----------------- %d -------------------\n", e->d);
				printf("step on <%d, %d, %d>\n", e->f, e->r, e->c);
				stop = bfs(e);
				printf("------------- %s, %s --------------\n",
					(!stop)?"TRUE":"FALSE", (!q->isEmpty())?"TRUE":"FALSE");
			}
			if(shortest){
				s = size;
				printf("s=%d\n",s);
				for(i=floo+1;-1<--i;s-=2){
					for(j=-1;s>++j;){
						for(k=-1;s>++k;){
							printf("%c ", output[i][j][k]);
						}
						printf("\n");
					}
				}
			} else printf("The path doesn't exist.\n");
		} else continue;
	}
	return 0;
}