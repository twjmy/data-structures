#include <stdlib.h>
#include <stdio.h>
#include <string.h>
FILE *inputFile, *outputFile;
char inputFileName[] = "test data/input_2.txt"; // [PPT] Read file (input_2.txt)
int m; // [PPT] The first line contains a integer : How much test data is in the input file.
int n; // [PPT] indicates the size of the array is N*N. ( N ≤ 500 )
int g; // [PPT] indicates how many generations that we will simulate.
char outputFileName[] = "output_2.txt"; // [PPT] Please output the result in output_2.txt
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
	fscanf(inputFile, "%d", &m);
	printf("File read \"%s\": %d test data is in the input file.\n", inputFileName, m);
	for(int cnt = 0, i = -1; ++i < m; cnt = 0){
		fscanf(inputFile, "%d %d", &n, &g);
		printf("File read \"%s\": N=%d G=%d\n", inputFileName, n, g);
		int matrix[n+2][n+2], next[n+2][n+2];
		for(int j = -1; ++j < n+2;){
			for(int k = -1; ++k < n+2; next[j][k] = matrix[j][k]){
				if(j == 0 || j == n+1 || k == 0 || k == n+1)
					matrix[j][k] = 0;
				else fscanf(inputFile,"%d ",&matrix[j][k]);
			}
		}
		for(int sum, i = -1; ++i < g;){
			for(int j = 0; ++j < n+1;){
				for(int k = 0; ++k < n+1;){
					sum = matrix[j-1][k-1] + matrix[j-1][k]
					    + matrix[j-1][k+1] + matrix[j][k-1]
					    + matrix[j+1][k-1] + matrix[j][k+1]
					    + matrix[j+1][k+1] + matrix[j+1][k];
					if(matrix[j][k] == 0){
						if(sum == 3) next[j][k] = 1;
					}else if(sum == 2 || sum == 3) next[j][k] = 1;
					else next[j][k] = 0;
				}
			}
			for(int j = 0; ++j < n+1;)
				for(int k = 0; ++k <= n; matrix[j][k] = next[j][k]);
		}
		for(int j = 0; ++j < n+1;)
			for(int k = 0; ++k < n+1;)
				if(matrix[j][k] == 1) cnt++;
		fprintf(outputFile,"%d %d %d\n", n, n, cnt);
		printf("File writed \"%s\": %d %d %d\n", outputFileName, n, n, cnt);
		for(int j = 0; ++j < n+1;)
			for(int k = 0; ++k < n+1;)
				if(matrix[j][k] == 1){
					const int temp = matrix[j-1][k-1] + matrix[j-1][k]
								   + matrix[j-1][k+1] + matrix[j][k-1]
								   + matrix[j+1][k-1] + matrix[j][k+1]
								   + matrix[j+1][k+1] + matrix[j+1][k];
					// [PPT] Use the sparse matrix to output the answer after g times of evolution.
					fprintf(outputFile, "%d %d %d\n", j-1, k-1, temp);
					printf("File writed \"%s\": %d %d %d\n", outputFileName, j-1, k-1, temp);
				}
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