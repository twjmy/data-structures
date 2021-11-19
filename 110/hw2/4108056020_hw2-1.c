#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for strlen(char*)
FILE *inputFile, *outputFile;
char inputFileName[] = "test_case_1-3/input_1.txt"; // [PPT] Read the file (input_1.txt)
char *firstLine; // [PPT] The first line presents the initial list.
int n; // [PPT] The second line contains an integer n indicates how many commands there are.
char command[30]; // [PPT] The next n rows are the commands.
char outputFileName[] = "output_1.txt"; // [PPT] write the result of "show" to the file (output_1.txt).
// [PPT] Please use the following structure to implement a singly linked list.
typedef struct listNode *listPointer;
typedef struct listNode{
	int data;
	listPointer link;
} listNode; // ppt missed part
listPointer end = NULL; int size = 0; // of the list
/**
 * @brief [PPT] add the new node whose data field is i to the end of the list.
 * @param i data to add
 */
void add(int i){
	++size;
	listPointer add = malloc(sizeof(listNode));
	add->data = i;
	add->link = end;
	end = add;
}
/**
 * @brief [PPT] delete the i-th node.
 *        [公告] 對於del，若index超出範圍，不用執行。
 * @param i index of the element to delete
 */
void del(int i){
	if(i > size) return;
	listPointer del, pivot = end;
	i = --size-i;
	for(int j = -1; ++j < i; pivot = pivot->link);
	if(pivot == end){
		del = end;
		end = end->link;
	}else{
		del = pivot->link;
		pivot->link = pivot->link->link;
	}
	free(del); del = NULL;
}
/**
 * @brief [PPT] insert the new node whose data field is j after the i-th node.
 *        [公告] 對於ins/mul，測資隨機生成的時候，i的範圍不會超出list內資料的數量。
 * @param i index to insert
 * @param j data field
 */
void ins(int i, int j){
	listPointer pivot = end;
	const int ipreNode = size++-i-1;
	for(int k = -1; ++k < ipreNode; pivot = pivot->link);
	listPointer ins = malloc(sizeof(listNode));
	ins->data = j;
	ins->link = pivot->link;
	pivot->link = ins;
}
/**
 * @brief [PPT] the data field of the i-th to last node multiplies by j.
 *        [公告] 對於ins/mul，測資隨機生成的時候，i的範圍不會超出list內資料的數量。
 * @param i multiplier index
 * @param j multiplicand
 */
void mul(int i, int j){
	listPointer mul = end; i--;
	for(int k = -1; ++k < i; mul = mul->link);
	mul->data *= j;
}
/**
 * @brief [PPT] treat K data as a group and reverse them.
 * @param k number of elements for each group
 */
void rev(int k){
	listPointer trace1 = end , trace2 = end;
	int *rev = malloc(sizeof(int)*k);
	int last = size % k;
	if(last){
		for(int i = -1; ++i < last;
			rev[i] = trace1->data,
			trace1 = trace1->link);
		for(;--last > -1;
			trace2->data = rev[last],
			trace2 = trace2->link);
	}
	const int group = size / k;
	for(int i = -1; ++i < group;){
		for(int j = -1; ++j < k;
			rev[j] = trace1->data,
			trace1 = trace1->link);
		for(int j = k; --j > -1;
			trace2->data = rev[j],
			trace2 = trace2->link);
	}
	free(rev);
}
// [PPT] print out the data in the singly linked list.
void show(){
	listPointer temp = end;
	int *data = malloc(sizeof(int)*size);
	for(int i = size; --i > -1;
		data[i] = temp->data,
		temp = temp->link);
	for(int i = -1; ++i < size;
		fprintf(outputFile, "%d ", data[i]),
		printf("%d ", data[i]));
	fprintf(outputFile, "\n"); printf("\n");
	free(data);
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
	printf("File opened \"%s\", write:\n", outputFileName);
	// [公告] Initial list舉例時存在empty，但是實際測資不會為空，可以不用檢查empty
	int elen = 1; // element number
	int count = 1; // the character number of first line for malloc, 1 for eos
	for(char get; (get=fgetc(inputFile)) != '\n'; ++count)
		if(get==' ') ++elen;
	rewind(inputFile); // after count, put file pointer back
	firstLine = malloc(sizeof(char)*count);
	fscanf(inputFile, "%[^\n]\n", firstLine);
	// [公告] 第一題的測資只包含正整數，不會有浮點數/負數。
	char data[13]; // each initial data string
	for(int i = -1, j = 0; ++i < elen;
		sscanf(&firstLine[j], "%s ", data),
		add(atoi(data)), j += strlen(data)+1);// 1 for space
	free(firstLine);
	fscanf(inputFile, "%d\n", &n);
	for(int m = -1, i, j; ++m < n;){
		fscanf(inputFile, "%[^\n]\n", command); // read command
		sscanf(command, "%*[^ ] %d %d", &i, &j); // get i/j/k
		// [PPT] The singly linked list must have the following functions：
		switch(command[0]){
			case 'a': add(i);	continue; // add i
			case 'd': del(i);	continue; // del i
			case 'i': ins(i,j);	continue; // ins i j
			case 'm': mul(i,j);	continue; // mul i j
			case 'r': rev(i);	continue; // rev k(=i)
			case 's': show();	continue; // show
		}
	}
	for(listPointer pivot; end;
		pivot = end, end = end->link,
		free(pivot)); // free list
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