#include <stdio.h>
#include <stdlib.h>
#define MAX 999
typedef enum Boolean
{
	FALSE,
	TRUE
} bool;
bool first = TRUE;
FILE *fp;
short **mark[6];
char inputFile[13], **map[6], **output[6], tmp;
int
	i, j, k, s, floo,
	ans = 0, size = 0,
	dir[4][2] = {
		/*n*/ {-1, 0},
		/*e*/ {0, 1},
		/*s*/ {1, 0},
		/*w*/ {0, -1},
	};

typedef struct e *Element;
typedef struct q *Queue;

Element start;
Queue q;

struct e
{
	short f, r, c, d;
};

struct q
{
	int _cap;
	int _rear;
	int _len;
	int _front;
	Element *list;
	Element (*delQ)();
	Element (*addQ)(Element);
	int (*isEmpty)();
	void (*printQ)();
};

Element addQ(Element e)
{
	if ((q->_len + 1) == (q->_cap))
	{
		int newCap = q->_cap << 1;
		Element *newList = malloc(sizeof(*newList) * newCap);
		int i;
		for (i = 0; i < q->_len; i++)
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

void printQ()
{
	int i;
	Element e;
	for (i = 0; i < q->_len; i++)
	{
		e = q->list[(q->_rear + i) % q->_cap];
		printf("<%d,%d> -> ", e->r, e->c);
	}
	printf("NULL\n");
}

Element delQ()
{
	if (q->isEmpty(q))
	{
		printf("[!] Queue empty\n");
		printQ(q);
		exit(1);
	}
	Element tmp = q->list[q->_rear];
	q->_rear = (q->_rear + 1) % q->_cap;
	q->_len--;
	return tmp;
}

int isEmpty()
{
	return q->_len == 0;
}

Queue newQueue()
{
	q = malloc(sizeof(*q));
	q->_cap = 8;
	q->_len = 0;
	q->_rear = 0;
	q->_front = 0;
	q->list = malloc(q->_cap * sizeof(*(q->list)));
	q->addQ = addQ;
	q->delQ = delQ;
	q->isEmpty = isEmpty;
	q->printQ = printQ;
	return q;
}

Element element(short f, short r, short c, short d)
{
	Element e = malloc(sizeof(*e));
	e->f = f;
	e->r = r;
	e->c = c;
	e->d = d;
	return e;
}

void mapMark(int f, int r, int c)
{
	switch (tmp)
	{
	case 'S':
		start = element(f, r, c, 0);
	case 'X':
		mark[f][r][c] = 0;
		break;
	default:
		mark[f][r][c] = MAX;
		break;
	}
}

int sizef(int f)
{
	switch (f)
	{
	case 5:
		return 13;
	case 4:
		return 11;
	case 3:
		return 9;
	case 2:
		return 7;
	case 1:
		return 5;
	case 0:
		return 3;
	default:
		exit(1);
	}
}

bool fileScan()
{
	size = 0;
	while (fscanf(fp, "%c ", &tmp) > 0)
		size++;
	switch (size)
	{
	// 1+3*3=10, 10+5*5=35, 35+7*7=84,
	// 84+9*9=165, 165+11*11=286, 286+13*13=455.
	case 455:
		size = 13;
		floo = 5;
		break;
	case 286:
		size = 11;
		floo = 4;
		break;
	case 165:
		size = 9;
		floo = 3;
		break;
	case 84:
		size = 7;
		floo = 2;
		break;
	case 35:
		size = 5;
		floo = 1;
		break;
	case 10:
		size = 3;
		floo = 0;
		break;
	}
	if (first)
	{
		s = 13;
		for (i = 6; - 1 < --i; s -= 2)
		{
			map[i] = malloc((s + 1) * sizeof(char *));
			output[i] = malloc((s + 1) * sizeof(char *));
			mark[i] = malloc((s + 1) * sizeof(short *));
			for (j = -1; s > ++j;)
			{
				map[i][j] = malloc((s + 1) * sizeof(char));
				output[i][j] = malloc((s + 1) * sizeof(char));
				mark[i][j] = malloc((s + 1) * sizeof(short));
			}
		}
		first = FALSE;
	}
	if (size > 1)
	{
		rewind(fp);
		s = size;

		//printf("s=%d\n",s);
		for (i = floo + 1; - 1 < --i; s -= 2)
		{
			for (j = -1; s > ++j;)
			{
				for (k = -1; s > ++k;)
				{
					fscanf(fp, "%c ", &tmp);
					map[i][j][k] = tmp;
					output[i][j][k] = tmp;
					mapMark(i, j, k);
					// printf("%c ", map[i][j][k]);
				}
				// printf("\n");
			}
		}
	}
	else
	{
		printf("Path length: 0\n");
		printf("=====outMaze=====\n");
		printf("*\n");
		fclose(fp);
		return FALSE;
	}
	s = size;
	/*
printf("s=%d\n",s);
for(i=floo+1;-1<--i;s-=2){
for(j=-1;s>++j;){
for(k=-1;s>++k;)
printf("%3d ",mark[i][j][k]);
printf("\n");
}
}
*/
	fclose(fp);
	return TRUE;
}

bool in_array_bound(short f, short r, short c)
{
	if (r < 0)
		return FALSE;
	if (c < 0)
		return FALSE;
	if (f < 0)
		return FALSE;
	if (r >= sizef(f))
		return FALSE;
	if (c >= sizef(f))
		return FALSE;
	if (f > floo)
		return FALSE;
	return TRUE;
}

bool isFinal(short f, short r, short c)
{
	if (f == 0 && map[f][r][c] == 'U')
		return TRUE;
	return FALSE;
}

bool bfs(short ef, short er, short ec, short ed)
{
	int f, r, c, d, array2D_size;

	for (i = 0; i < 4; i++)
	{
		if (map[ef][er][ec] == 'U')
		{
			f = ef - 1;
		}
		else if (map[ef][er][ec] == 'D')
		{
			f = ef + 1;
		}
		else
		{
			f = ef;
		}
		r = er + ((map[ef][er][ec] == 'U') ? -1 : (map[ef][er][ec] == 'D' ? 1 : dir[i][0]));
		c = ec + ((map[ef][er][ec] == 'U') ? -1 : (map[ef][er][ec] == 'D' ? 1 : dir[i][1]));
		d = ed + ((map[ef][er][ec] == 'T') ? 3 : 1);
		array2D_size = sizef(f);

		if (in_array_bound(f, r, c))
		{
			if (isFinal(f, r, c))
			{
				ans = d + 1;
				return TRUE;
			}
			if (mark[f][r][c] > d)
			{
				mark[f][r][c] = d;
				q->addQ(element(f, r, c, d));
			}
		}
	}
	return FALSE;
}

int main()
{
	int fileNo;
	bool stop = FALSE;
	Element e;
	for (fileNo = 1; fileNo <= 100; fileNo++)
	{ // Load file in order from 1 to 100
		sprintf(inputFile, "test%d.txt", fileNo);
		printf("%s\n", inputFile);
		fp = fopen(inputFile, "r");
		if (fp == NULL)
		{
			printf("[!] \"%s\" file not found...\n", inputFile);
			return 1;
		}
		if (fileScan())
		{
			ans = 0;
			q = newQueue();
			q->addQ(start);
			stop = FALSE;

			while (!stop && !q->isEmpty())
			{
				e = q->delQ();
				stop = bfs(e->f, e->r, e->c, e->d);
				free(e);

				/*
if(q->isEmpty()){
printf("q is empty");
}
if(stop){
printf("stop");
}
s = size;
printf("-----------------------------------\n");
printf("s=%d\n",s);
for(i=floo+1;-1<--i;s-=2){
for(j=-1;s>++j;){
for(k=-1;s>++k;)
printf("%3d ",mark[i][j][k]);
printf("\n");
}
}
printf("-----------------------------------\n");
*/
			}
			if (ans)
			{
				printf("Path length: %d\n", ans);
			}
			else
			{
				printf("Path not found\n");
			}
		}
	}
	return 0;
}