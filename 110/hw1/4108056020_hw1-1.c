#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_STACK_SIZE 200 // [PPT] Each line contains a string ( length ≤ 100 ) **100 for extra ' '**
FILE *inputFile, *outputFile;
char inputFileName[] = "test data/input_1x.txt"; // [PPT] Reading the test data from input_1.txt
char outputFileName[] = "output_1x.txt"; // [PPT] Please output the result in output_1.txt
getToken(char symbol){
	switch(symbol){ /* 根據範例出現的運算符按圖 3.12 的優先順序 */
		case '*': case '/': case '%': return 6;
		case '+': case '-': return 5;
		case '>': case '<': return 4;
		case '&': return 3;
		case '^': return 2;
		case '|': return 1;
		default: return 0;
	}
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
	char line[MAX_STACK_SIZE] = {'\0'};
	for(int top = 0, pivot = 0; fscanf(inputFile, "%s\n", &line) != EOF; top = 0, pivot = 0){
		printf("File read \"%s\": %s\n", inputFileName, line);
		char result[MAX_STACK_SIZE] = {'\0'}, // [PPT] Each line contains a result of one testing data.
			stack[MAX_STACK_SIZE] = {'\0'};
		// result 是反過來的，因為不知會有多少空格
		for(int i = strlen(line); --i > -1;){// 反過來讀每一行
			if(line[i] == '-'){ // 負數處理
				if(!getToken(line[i-1]) && line[i-1] != '('){
					// [PPT] For the output, use a space to separate each operator and operand.
					for(result[pivot++] = ' ';
						getToken(stack[top]) > getToken(line[i]);
						result[pivot++] = stack[top--],
						result[pivot++] = ' '
					);
					stack[++top] = line[i];
				}else result[pivot++] = line[i]; // 是運算符或開括號
			}else if(getToken(line[i])){ // 運算符處理
				for(result[pivot++] = ' ';
					getToken(stack[top]) > getToken(line[i]);
					result[pivot++] = stack[top--],
					result[pivot++] = ' '
				);
				stack[++top] = line[i];
			}else if(line[i] == '('){ // 開括號處理，因為是反過來讀，所以
				for(;stack[top] != ')'; // 將 stack 的東西吐出來直到關括號
					result[pivot++] = ' ',
					result[pivot++] = stack[top--]
				);
				top--;
			}else if(line[i] == ')') stack[++top] = line[i]; // 關括號處理
			else result[pivot++] = line[i]; // 數字
			// printf("result: %s\n", strrev(result)); strrev(result); perror("Error"); // debug
		}
		for(;top > 0;
			result[pivot++] = ' ',
			result[pivot++] = stack[top--]
		);
		fprintf(outputFile, "%s\n", strrev(result)); // 反轉 result 寫到輸出檔案
		printf("File writed \"%s\": %s\n", outputFileName, result);
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