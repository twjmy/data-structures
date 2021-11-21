#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
FILE *inputFile, *outputFile;
char recipesFileName[] = "test_case_2-2/recipes.txt"; // [PPT] Read the file (recipes.txt) to let your program know how to cook.
char ordersFileName[] = "test_case_2-2/orders.txt"; // [PPT] Read the file (orders.txt)
char outputFileName[] = "Scoring program/players.txt"; // [PPT] Output the work schedule of two players to players.txt in the order of time.
typedef struct node{
	char object[15];
	struct node *next;
} Node;
typedef struct recipe{
	char recipe_name[35]; // [PPT] The "recipe_name" field indicates which meals your guests ordered.
	int s; // [PPT] The ingredients that need to be cooked first on the stove.
	int c; // [PPT] The ingredients that need to be processed first on the cutting board.
	int others; // [PPT] The ingredients that do not require pre-processing.
	Node *stove; // [PPT] 5 minutes for cooking something on the stove (fixed)
	Node *cut; // [PPT] 3 minutes for cutting something (fixed)
} Recipe;
int recipes; // In the first line, an integer indicates how many recipes there are.
Recipe *recipe; // The following rows are the recipe data.
typedef struct order{ // save orders corresponding s, c, and objects while reading orders.txt without saving "recipe_name"
	int s; Node *stove;
	int c; Node *cut;
	int others;
	int order_ID; // [PPT] The "order_ID" is used to distinguish the meals of different guests. (The range of order_ID is 0000~9999)
	int arrival; // [PPT] The "arrival" field indicates the time when the order arrived.
	int deadline; // [PPT] The "deadline" field indicates how long the meal can be waited for. (𝑎𝑟𝑟𝑖𝑣𝑎𝑙≤𝑑𝑒𝑎𝑑𝑙𝑖𝑛𝑒)
	int money; // [PPT] The "money" field indicates how much money you will earn from this order.
} Order;
int n; // [PPT] In the first line, an integer n indicates how many orders there are.
Order *order; // [PPT] The next n rows are the order data.
// [PPT] The "punishment" field  indicates how much you should pay for the guest if you didn't serve the meal before the deadline.
int punishment;
typedef struct task{
	int t; // [PPT] indicates the time when the player start to do this command.
	int order_ID; // [PPT] order_ID indicates the order you are preparing for.
	/**
	 * [PPT] Three kind of commands :
	 * (1) s+object: cooking "object" on the stove.
	 * (2) c+object: cutting "object" on cutting board.
	 * (3) f : food presentation.
	 */
	char command, object[15];
	struct task *next;
} Task;
int commands; // [PPT] The first line uses an integer to indicate how many commands there are.
/**
 * [PPT] Write a program to schedule the cooking process of TWO players.
 * One line contains only one schedule.
 */
Task *player1, *player2;
main(){ // run in c18
	/* read the Recipes and order */
	if(!(inputFile = fopen(recipesFileName, "r"))){
		printf("File open failed \"%s\", exit program.\n", recipesFileName);
		perror("Error"); exit(EXIT_FAILURE);
	}printf("File opened \"%s\", read:\n", recipesFileName);
	fscanf(inputFile, "%d\n", &recipes);
	recipe = malloc(sizeof(Recipe)*recipes);
	int i, j, k;
	for(i = -1; ++i < recipes;){
		char ch;
		recipe[i].stove = NULL;
		recipe[i].cut = NULL;
		fscanf(inputFile, "%[^ ] ", recipe[i].recipe_name);
		printf("%s:",recipe[i].recipe_name);
		for(recipe[i].s = 0, ch = 0; ch != ' '; ++recipe[i].s){
			Node *new = malloc(sizeof(Node));
			// [PPT] If there are more than one kind of food ingredient , separate them with ",".
			fscanf(inputFile, "%[^ ,]", new->object); // get object till ',' or ' '(before "c")
			ch = fgetc(inputFile); // get ',' or ' '
			new->next = recipe[i].stove;
			recipe[i].stove = new;
			// [PPT] Use "x" to indicate that there is no such kind of ingredient.
			if(!strcmp(new->object, "x")) break;
		}printf("\n stove: "); for(Node *pivot=recipe[i].stove; pivot; printf("%s ",pivot->object), pivot = pivot->next);
		for(recipe[i].c = 0, ch = 0; ch != ' '; ++recipe[i].c){
			Node *new = malloc(sizeof(Node));
			fscanf(inputFile, "%[^ ,]", new->object); // get object till ',' or ' '(before "others")
			ch = fgetc(inputFile); // get ',' or ' '
			new->next = recipe[i].cut;
			recipe[i].cut = new;
			if(!strcmp(new->object, "x")) break;
		}printf("\n cut: "); for(Node *pivot=recipe[i].cut; pivot; printf("%s ",pivot->object), pivot = pivot->next); printf("\n");
		char others[15];
		for(recipe[i].others = 1, ch = 0; !(ch == '\n' || ch == -1); ++recipe[i].others){
			fscanf(inputFile, "%[^\n,]", others); // get object till ',' or '\n'(before next recipe)
			ch = fgetc(inputFile); // get ',' or '\n'
			if(!strcmp(others, "x")) break;
		}
	}
	if(fclose(inputFile)){
		printf("File close failed \"%s\", exit program.\n", recipesFileName);
		perror("Error"); exit(EXIT_FAILURE);
	}printf("File closed \"%s\"\n", recipesFileName);
	// input file (orders) opened with mode "r"
	if(!(inputFile = fopen(ordersFileName, "r"))){
		printf("File open failed \"%s\", exit program.\n", ordersFileName);
		perror("Error"); exit(EXIT_FAILURE);
	}printf("File opened \"%s\"\n", ordersFileName);
	fscanf(inputFile, "%d\n", &n);
	order = malloc(sizeof(Order)*n);
	for(i = -1; ++i < n; order[i].money -= punishment){
		fscanf(inputFile, "%d ", &order[i].order_ID);
		order[i].stove = NULL;
		order[i].cut = NULL;
		char recipe_name[35];
		fscanf(inputFile, "%[^ ] ", recipe_name);
		for(j = -1; ++j < recipes;){
			if(!strcmp(recipe[j].recipe_name, recipe_name)){
				// save orders corresponding s, c, and objects without saving "recipe_name"
				order[i].s = recipe[j].s; order[i].stove = recipe[j].stove;
				order[i].c = recipe[j].c; order[i].cut = recipe[j].cut;
				order[i].others = recipe[j].others;
				break;
			}
		}
		fscanf(inputFile, "%d %d %d %d\n", &order[i].arrival, &order[i].deadline, &order[i].money, &punishment);
	}free(recipe);
	if(fclose(inputFile)){
		printf("File close failed \"%s\", exit program.\n", ordersFileName);
		perror("Error"); exit(EXIT_FAILURE);
	}printf("File closed \"%s\"\n", ordersFileName);
	for(i = -1; ++i < n-1;){ // selection sort order by money
		k = i;
		for(j = i; ++j < n; k = (order[k].money < order[j].money)?j:k);
		if(i != k){
			Order temp = order[i];
			order[i] = order[k];
			order[k] = temp;
		}
	}
	for(i = -1, k = 0; ++i < n; k = (k < order[i].deadline) ? order[i].deadline : k);
	/**
	 * for players go s/c/f
	 * 0: stove, 1,2: player, 3: cut
	 */
	bool field[4][k];
	for(i = -1; ++i < 4;) for(j = -1; ++j < k; field[i][j] = false);
	for(player1 = NULL, player2 = NULL, i = -1; ++i < n;){
		const int s5 = order[i].s*5, c3 = order[i].c*3, f = order[i].deadline - order[i].others;
		int stove[3] = {0}, cut[3] = {0}, put[3] = {0}, start = 0;
		bool done;
		if(order[i].s){
			const int s = f - s5;
			for(done = true, stove[1] = order[i].arrival; stove[1] < s; ++stove[1]){ // player 1
				for(done = true, k = -1; done && ++k < s5;)
					if(field[1][stove[1]+k] || field[0][stove[1]+k])
						done = false;
				if(done) break;
			}
			for(done = true, stove[2] = order[i].arrival; stove[2] < s; ++stove[2]){ // player 2
				for(done = true, k = -1; done && ++k < s5;)
					if(field[2][stove[2]+k] || field[0][stove[2]+k])
						done = false;
				if(done) break;
			}
			if(stove[1] >= s && stove[2] >= s) continue;
			else if(stove[1] < s && stove[2] >= s){
				for(stove[0] = 1, k = -1; ++k < s5; // player 1
					field[1][stove[1]+k] = true,
					field[0][stove[1]+k] = true
				);
				if(stove[1]+s5 > start) start = stove[1]+s5;
			}else if(stove[1] >= s && stove[2] < s){
				for(stove[0] = 2, k = -1; ++k < s5; // player 2
					field[2][stove[2]+k] = true,
					field[0][stove[2]+k] = true
				);
				if(stove[2]+s5 > start) start = stove[2]+s5;
			}else if(stove[1] <= stove[2]){
				for(stove[0] = 1, k = -1; ++k < s5; // player 1
					field[1][stove[1]+k] = true,
					field[0][stove[1]+k] = true
				);
				if(stove[1]+s5 > start) start = stove[1]+s5;
			}else{
				for(stove[0] = 2, k = -1; ++k < s5; // player 2
					field[2][stove[2]+k] = true,
					field[0][stove[2]+k] = true
				);
				if(stove[2]+s5 > start) start = stove[2]+s5;
			}
		}
		if(order[i].c){
			const int c = f - c3;
			for(done = true, cut[1] = order[i].arrival; cut[1] < c; ++cut[1]){ // player 1
				for(done = true, k = -1; done && ++k < c3;)
					if(field[1][cut[1]+k] || field[3][cut[1]+k])
						done = false;
				if(done) break;
			}
			for(done = true, cut[2] = order[i].arrival; cut[2] < c; ++cut[2]){ // player 2
				for(done = true, k = -1; done && ++k < c3;)
					if(field[2][cut[2]+k] || field[3][cut[2]+k])
						done = false;
				if(done) break;
			}
			if(cut[1] >= c && cut[2] >= c){
				if(stove[0] == 1){ // player 1
					for(k = -1; ++k < s5;
						field[1][stove[1]+k] = false,
						field[0][stove[1]+k] = false
					);
				}else if(stove[0] == 2){ // player 2
					for(k = -1; ++k < s5;
						field[2][stove[2]+k] = false,
						field[0][stove[2]+k] = false
					);
				}
				continue;
			}else if(cut[1] < c && cut[2] >= c){
				for(cut[0] = 1, k = -1; ++k < c3; // player 1
					field[1][cut[1]+k] = true,
					field[3][cut[1]+k] = true
				);
				if(cut[1]+c3 > start) start = cut[1]+c3;
			}else if(cut[1] >= c && cut[2] < c){
				for(cut[0] = 2, k = -1; ++k < c3; // player 2
					field[2][cut[2]+k] = true,
					field[3][cut[2]+k] = true
				);
				if(cut[2]+c3 > start) start = cut[2]+c3;
			}else{
				if(cut[1] <= cut[2]){
					for(cut[0] = 1, k = -1; ++k < c3; // player 1
						field[1][cut[1]+k] = true,
						field[3][cut[1]+k] = true
					);
					if(cut[1]+c3 > start) start = cut[1]+c3;
				}else{
					for(cut[0] = 2, k = -1; ++k < c3; // player 2
						field[2][cut[2]+k] = true,
						field[3][cut[2]+k] = true
					);
					if(cut[2]+c3 > start) start = cut[2]+c3;
				}
			}
		}
		for(done = true, put[1] = start; put[1] < f; ++put[1]){ // player 1
			for(done = true, k = -1; done && ++k < order[i].others;)
				if(field[1][put[1]+k])
					done = false;
			if(done) break;
		}
		for(done = true, put[2] = start; put[2] < f; ++put[2]){ // player 2
			for(done = true, k = -1; done && ++k < order[i].others;)
				if(field[2][put[2]+k])
					done = false;
			if(done) break;
		}
		if(put[1] >= f && put[2] >= f){
			if(stove[0] == 1){ // player 1
				for(k = -1; ++k < s5;
					field[1][stove[1]+k] = false,
					field[0][stove[1]+k] = false
				);
			}else if(stove[0] == 2){ // player 2
				for(k = -1; ++k < s5;
					field[2][stove[2]+k] = false,
					field[0][stove[2]+k] = false
				);
			}
			if(cut[0] == 1){ // player 1
				for(k = -1; ++k < c3;
					field[1][cut[1]+k] = false,
					field[3][cut[1]+k] = false
				);
			}else if(cut[0] == 2){ // player 2
				for(k = -1; ++k < c3;
					field[2][cut[2]+k] = false,
					field[3][cut[2]+k] = false
				);
			}
			continue;
		}else if(put[1] < f && put[2] >= f)
			for(put[0] = 1, k = -1; ++k < order[i].others; field[1][put[1]+k] = true); // player 1
		else if(put[1] >= f && put[2] < f)
			for(put[0] = 2, k = -1; ++k < order[i].others; field[2][put[2]+k] = true); // player 2
		else{
			if(put[1] <= put[2])
				for(put[0] = 1, k = -1; ++k < order[i].others; field[1][put[1]+k] = true); // player 1
			else for(put[0] = 2, k = -1; ++k < order[i].others; field[2][put[2]+k] = true); // player 2
		}
		if(stove[0] == 1){ // player 1
			for(Node *pivot = order[i].stove; pivot;){
				Task *temp1 = malloc(sizeof(Task));
				temp1->t = stove[1];
				temp1->order_ID = order[i].order_ID;
				temp1->command = 's';
				strcpy(temp1->object, pivot->object);
				stove[1] += 5;
				if(!player1 || temp1->t > player1->t){
					temp1->next = player1;
					player1 = temp1;
				}else{
					Task *temp2;
					for(temp2 = player1; temp2->next && !(temp2->t > temp1->t
						 && temp1->t > temp2->next->t); temp2 = temp2->next);
					temp1->next = temp2->next;
					temp2->next = temp1;
				}
				pivot = pivot->next;
			}
		}else if(stove[0] == 2){ // player 2
			for(Node *pivot = order[i].stove; pivot;){
				Task *temp1 = malloc(sizeof(Task));
				temp1->t = stove[2];
				temp1->order_ID = order[i].order_ID;
				temp1->command = 's';
				strcpy(temp1->object, pivot->object);
				stove[2] += 5;
				if(!player2 || temp1->t > player2->t){
					temp1->next = player2;
					player2 = temp1;
				}else{
					Task *temp2;
					for(temp2 = player2; temp2->next && !(temp2->t > temp1->t
						 && temp1->t > temp2->next->t); temp2 = temp2->next);
					temp1->next = temp2->next;
					temp2->next = temp1;
				}
				pivot = pivot->next;
			}
		}
		if(cut[0] == 1){ // player 1
			for(Node *pivot = order[i].cut; pivot;){
				Task *temp1 = malloc(sizeof(Task));
				temp1->t = cut[1];
				temp1->order_ID = order[i].order_ID;
				temp1->command = 'c';
				strcpy(temp1->object, pivot->object);
				cut[1] += 3;
				if(!player1 || temp1->t > player1->t){
					temp1->next = player1;
					player1 = temp1;
				}else{
					Task *temp2;
					for(temp2 = player1; temp2->next && !(temp2->t > temp1->t
						 && temp1->t > temp2->next->t); temp2 = temp2->next);
					temp1->next = temp2->next;
					temp2->next = temp1;
				}
				pivot = pivot->next;
			}
		}else if(cut[0] == 2){ // player 2
			for(Node *pivot = order[i].cut; pivot;){
				Task *temp1 = malloc(sizeof(Task));
				temp1->t = cut[2];
				temp1->order_ID = order[i].order_ID;
				temp1->command = 'c';
				strcpy(temp1->object, pivot->object);
				cut[2] += 3;
				if(!player2 || temp1->t > player2->t){
					temp1->next = player2;
					player2 = temp1;
				}else{
					Task *temp2 = player2;
					for(temp2 = player2; temp2->next && !(temp2->t > temp1->t
						 && temp1->t > temp2->next->t); temp2 = temp2->next);
					temp1->next = temp2->next;
					temp2->next = temp1;
				}
				pivot = pivot->next;
			}
		}
		if(put[0] == 1){ // player 1
			Task *temp1 = malloc(sizeof(Task));
			temp1->t = put[1];
			temp1->order_ID = order[i].order_ID;
			temp1->command = 'f';
			if(!player1 || temp1->t > player1->t){
				temp1->next = player1;
				player1 = temp1;
			}else{
				Task *temp2 = player1;
				for(temp2 = player1; temp2->next && !(temp2->t > temp1->t
					 && temp1->t > temp2->next->t); temp2 = temp2->next);
				temp1->next = temp2->next;
				temp2->next = temp1;
			}
		}else if(put[0] == 2){ // player 2
			Task *temp1 = malloc(sizeof(Task));
			temp1->t = put[2];
			temp1->order_ID = order[i].order_ID;
			temp1->command = 'f';
			if(!player2 || temp1->t > player2->t){
				temp1->next = player2;
				player2 = temp1;
			}else{
				Task *temp2 = player2;
				for(temp2 = player2; temp2->next && !(temp2->t > temp1->t
					 && temp1->t > temp2->next->t); temp2 = temp2->next);
				temp1->next = temp2->next;
				temp2->next = temp1;
			}
		}
	}
	Task *middle, *trail;
	for(commands = 0, middle = NULL; player1; commands++,
		trail = middle, // invert player1 task
		middle = player1,
		player1 = player1->next,
		middle->next = trail
	);
	player1 = middle;
	for(middle = NULL; player2; commands++,
		trail = middle, // invert player2 task
		middle = player2,
		player2 = player2->next,
		middle->next = trail
	);
	player2 = middle;
	if(!(outputFile = fopen(outputFileName, "w"))){
		printf("File open failed \"%s\", exit program.\n", outputFileName);
		perror("Error"); exit(EXIT_FAILURE);
	}printf("File opened \"%s\", write:\n", outputFileName);
	fprintf(outputFile, "%d\n", commands);
	printf("%d\n", commands);
	for(; player1 || player2;){
		if(player1 && player2){
			if(player1->t <= player2->t){
				if(player1->command == 'f'){
					fprintf(outputFile, "1 %d %d f\n", player1->t, player1->order_ID);
					printf("1 %d %d %c\n", player1->t, player1->order_ID, player1->command);
				}else{
					fprintf(outputFile, "1 %d %d %c %s\n", player1->t,
						player1->order_ID, player1->command, player1->object);
					printf("1 %d %d %c %s\n", player1->t,
						player1->order_ID, player1->command, player1->object);
				}
				Task *temp = player1;
				player1 = player1->next;
				free(temp);
			}else{
				if(player2->command == 'f'){
					fprintf(outputFile, "2 %d %d f\n", player2->t, player2->order_ID);
					printf("2 %d %d %c\n", player2->t, player2->order_ID, player2->command);
				}else{
					fprintf(outputFile, "2 %d %d %c %s\n", player2->t,
						player2->order_ID, player2->command, player2->object);
					printf("2 %d %d %c %s\n", player2->t,
						player2->order_ID, player2->command, player2->object);
				}
				Task *temp = player2;
				player2 = player2->next;
				free(temp);
			}
		}else if(player1){
			if(player1->command == 'f'){
				fprintf(outputFile, "1 %d %d f\n", player1->t, player1->order_ID);
				printf("1 %d %d %c\n", player1->t, player1->order_ID, player1->command);
			}else{
				fprintf(outputFile, "1 %d %d %c %s\n", player1->t,
					player1->order_ID, player1->command, player1->object);
				printf("1 %d %d %c %s\n", player1->t,
					player1->order_ID, player1->command, player1->object);
			}
			Task *temp = player1;
			player1 = player1->next;
			free(temp);
		}else{
			if(player2->command == 'f'){
				fprintf(outputFile, "2 %d %d f\n", player2->t, player2->order_ID);
				printf("2 %d %d %c\n", player2->t, player2->order_ID, player2->command);
			}else{
				fprintf(outputFile, "2 %d %d %c %s\n", player2->t,
					player2->order_ID, player2->command, player2->object);
				printf("2 %d %d %c %s\n", player2->t,
					player2->order_ID, player2->command, player2->object);
			}
			Task *temp = player2;
			player2 = player2->next;
			free(temp);
		}
	}
	// fflush(outputFile);
	if(fclose(outputFile)){
		printf("File close failed \"%s\", exit program.\n", outputFileName);
		perror("Error"); exit(EXIT_FAILURE);
	}printf("File closed \"%s\"\n", outputFileName);
}