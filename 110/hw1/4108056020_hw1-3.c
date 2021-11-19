#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define short unsigned short
FILE *inputFile, *outputFile;
char inputFileName[] = "test data/input_3.txt"; // [PPT] Read the input_3.txt
int m; // [PPT] The first line contains a integer : How much test data is in the input file.
short d; // [PPT] how many destinations to be visited ( 1 ≤ d ≤ 5 )
short n; // [PPT] indicates the size of the map. ( 5 ≤ n ≤ 100 )
short start[2]; // [PPT] indicate the starting point.
int minCost; // [PPT] Find the path with the least consumption.
char outputFileName[] = "output_3.txt"; // [PPT] Please output the result in output_3.txt
bool state[5] = {false};
typedef struct{ bool passed, dest; } BFS;
typedef struct{ int color, point[2]; } Queue;
typedef struct{ int cost[5][5]; } Map;
typedef struct{ int cost[8];} Around; /* 八方位 */
Map *map; Queue *q; BFS **bfs; Around** around;
swap(Queue *a, Queue *b){
	Queue temp = *a; *a = *b; *b = temp;
}
findMinCost(short stand, int cost, Map *map){
	state[stand] = true; // 到訪
	bool allpass = true; // 看其他點有沒有都走過
	for(short i = 0; ++i < d+1;)
		if(state[i] == false) allpass = false;
	if(allpass){ // 其他點都走過
		minCost = (cost > minCost)? minCost : cost;
		state[stand] = false; // 離開
		return;
	}
	for(short i = 0; ++i < d+1;) // 從 stand 開始找
		if(i == stand) continue;
		else if(state[i] == false)
			findMinCost(i, map->cost[stand][i] + cost, map);
	state[stand] = false; // 離開
}
main(){
	if(!(inputFile = fopen(inputFileName, "r"))){
		printf("File open failed \"%s\", exit program.\n", inputFileName);
		perror("Error"); exit(EXIT_FAILURE);
	}
	printf("File opened \"%s\"\n", inputFileName);
	if(!(outputFile = fopen(outputFileName, "w"))){
		printf("File open failed \"%s\", exit program.\n", outputFileName);
		perror("Error"); exit(EXIT_FAILURE);
	}
	printf("File opened \"%s\"\n", outputFileName);
	char direct[8][2] = { // 八方位 XY 差值
		{ 1, 1}, { 1, 0}, { 1,-1},
		{ 0, 1}, /*0, 0*/ { 0,-1},
		{-1, 0}, {-1, 1}, {-1,-1},
	};
	fscanf(inputFile, "%d\n", &m);
	printf("File read \"%s\": %d test data is in the input file.\n", inputFileName, m);
	short **data;
	for(int dest[5][2], i = -1; ++i < m;){
		// [PPT] On the first line of each result, print the sequence number of each test data.
		fprintf(outputFile, "#%d\n", i+1);
		printf("File writed \"%s\": #%d\n", outputFileName, i+1);
		fscanf(inputFile, "%d %d\n%d %d\n", &d, &n, &start[0], &start[1]);
		printf("File read \"%s\": d=%d n=%d x=%d y=%d\n",
			inputFileName, d, n, start[0], start[1]);
		for(short j = -1; ++j < d;)
			fscanf(inputFile, "%d %d\n", &dest[j][0], &dest[j][1]);
		data = malloc(sizeof(short*)*n);
		for(short i = -1; ++i < n; data[i] = malloc(sizeof(short)*n));
		for(short j = -1; ++j < n;)
			for(short k = -1; ++k < n;
				fscanf(inputFile, "%d%[^ \n]", &data[j][k]));
		around = malloc(sizeof(Around*)*n);
		for(short i = -1; ++i < n; around[i] = malloc(sizeof(Around)*n));
		for(short i = -1; ++i < n;){
			for(short j = -1; ++j < n;){
				for(short k = -1; ++k < 8;){
					short dirY = direct[k][0] + i, dirX = direct[k][1] + j;
					if(dirY >= 0 && dirX >= 0 && dirY < n && dirX < n)
						around[i][j].cost[k] = abs(
							data[i][j] - data[dirY][dirX]);
					else around[i][j].cost[k] = -1; // 超出範圍
				}
			}
		}
		for(short i = -1; ++i < n; free(data[i])); free(data);
		q = malloc(sizeof(Queue)*n*n << 2); bfs = malloc(sizeof(BFS*)*n);
		for(short i = -1; ++i < n; bfs[i] = malloc(sizeof(BFS)*n));
		short point[6][2]; point[0][0] = start[0]; point[0][1] = start[1];
		for(short i = 0; ++i <= d;
			point[i][0] = dest[i-1][0],
			point[i][1] = dest[i-1][1]
		);
		for(short i = -1; ++i < n;) // 重設
			for(short j = -1; ++j < n; bfs[i][j].dest = false);
		for(short i = 0; ++i < d+1; bfs[point[i][0]][point[i][1]].dest = true);
		Queue *left, *right, pivot;
		map = malloc(sizeof(Map)); minCost = INT_MAX;
		for(short i = -1; ++i < d;){
			for(short j = -1; ++j < n;) // 重設
				for(short k = -1; ++k < n; bfs[j][k].passed = false);
			bfs[point[i][0]][point[i][1]].dest = false;
			short head = 1;
			q[head].point[0] = point[i][0]; q[head].color = 0;
			q[head++].point[1] = point[i][1];
			for(short cnt = d-i; --head != 0;) { // Dijkstra 直到全部走訪完
				pivot = q[1]; q[1] = q[head]; // dequeue
				const short y = pivot.point[0], x = pivot.point[1];
				bool passed = false;
				if(bfs[y][x].passed == false){
					bfs[y][x].passed = true;
					if(bfs[y][x].dest == true){
						cnt--; int j;
						for(j = i; ++j <= d;)
							if(point[j][0] == y
							&& point[j][1] == x)
								break;
						map->cost[i][j] = pivot.color;
						map->cost[j][i] = pivot.color;
					}else if(cnt == 0) break;
				}else passed = true;
				for(short down = 1;;){
					if((down<<1)+1 < head){
						left = &q[(down<<1)]; right = &q[(down<<1)+1];
						if(q[down].color > left->color
						|| q[down].color > right->color){
							if(left->color <= right->color){
								swap(&q[down], left);
								down <<= 1;
							}else{
								swap(&q[down], right);
								down = (down<<1) + 1;
							}
						}else break;
					}else if(down<<1 < head){
						left = &q[down<<1];
						swap(&q[down], left);
						down = down<<1;
					}else break;
				}
				if(passed) continue;
				for(short k = -1; ++k < 8;){
					if(around[y][x].cost[k] != -1){
						const short dirY = direct[k][0] + y, dirX = direct[k][1] + x;
						if(!bfs[dirY][dirX].passed){
							short up = head;
							for(q[head].color = pivot.color + around[y][x].cost[k],
								q[head].point[0] = dirY, q[head++].point[1] = dirX;
								up != 1 && q[up].color < q[up>>1].color;
								swap(&q[up], &q[up>>1]),
								up >>= 1
							);
						}
					}
				}
			}
		}
		for(short i = -1; ++i < n; free(around[i]),free(bfs[i]));
		free(around); free(bfs);
		findMinCost(0, 0, map); free(map);
		fprintf(outputFile, "cost:%d%c", minCost, (i != m-1)?'\n':'\0');
		printf("File writed \"%s\": cost:%d\n", outputFileName, minCost);
	}
	// fflush(inputFile); fflush(outputFile);
	if(fclose(inputFile)){
		printf("File close failed \"%s\", exit program.\n", inputFileName);
		perror("Error"); exit(EXIT_FAILURE);
	}
	printf("File closed \"%s\"\n", inputFileName);
	if(fclose(outputFile)){
		printf("File close failed \"%s\", exit program.\n", outputFileName);
		perror("Error"); exit(EXIT_FAILURE);
	}
	printf("File closed \"%s\"\n", outputFileName);
}