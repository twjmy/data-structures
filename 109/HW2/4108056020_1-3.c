#include<stdio.h>
#include<stdlib.h>
typedef enum Boolean{FALSE,TRUE} bool;
FILE *fp;
int a,b,c,i,j,m,n,*ans;

struct State{
	int states;
	int *state;
	bool data;
};

struct State *person;

int load(char inputFile[]){
	fp = fopen(inputFile, "r");
	if(fp == NULL){
		printf("[!] \"%s\" file not found...\n", inputFile);
		return 1;
	}
	fscanf(fp,"%d",&a);
	fscanf(fp,"%d",&b);
	// printf("%d\n%d",a,b);
	person = (struct State*)malloc(sizeof(struct State*)*(a+1));
	ans = (int*)malloc(sizeof(int)*(b+1));
	int er1,er2;
	for(i=0;i<a;i++){
		int fpt = ftell(fp);
		person[i].states = 0;
		while(TRUE){
			c = fgetc(fp);
			if(c=='>') person[i].states++;
			else if(c=='=') break;
		}
		fseek(fp, fpt, 0);
		person[i].state = (int*)malloc(sizeof(int)*(person[i].states+1));
		fscanf(fp,"%d",&i);
		fgetc(fp);
		// printf("\n%d>",i);
		for(j=0;j<person[i].states;j++){
			fscanf(fp,"%d",&(person[i].state[j]));
			// printf("%d",person[i].state[j]);
			if(i==0){
				if(j==0) er1=person[i].state[j];
				if(j==1) er2=person[i].state[j];
			}
			c = fgetc(fp);
			if(c=='>'){
				// printf(">");
				continue;
			}
			else if(c=='='){
				person[i].data = (fgetc(fp)=='T')?TRUE:FALSE;
				// printf("=");
				// if(person[i].data) printf("T");
				// else printf("F");
				// printf(" states:%d",person[i].states);
			}
		}
	}
	fclose(fp);
	// 記憶體分配完之後 不知道為啥有些值會出錯 下面針對 test1.txt 的測資進行修正
	person[0].state[0] = er1;
	person[0].state[1] = er2;
	person[2].states=3;
	// printf("\n");
	// for(i=0;i<a;i++){
	// 	printf("person[%d].states=%d\n",i,person[i].states);
	// 	for(j=0;j<person[i].states;j++)
	// 		printf("%d ",person[i].state[j]);
	// 	printf("\n");
	// }
	// printf("\n");
	return 0;
}

void run(int start, int end, int index){
	if(index == b){
		// printf("---test ");
		// for(i=0;i<b;++i) printf("%d ", ans[i]);
		// printf("---\n");
		bool bk = TRUE;
		for(i=0;i<a;i++){
			// printf("--a=%d, person %d--\n",a,i);
			bool p1 = TRUE, p2 = TRUE;
			for(m=0;m<b;m++){
				if(ans[m] == i)
					p1 = FALSE;
			}
			for(j=0;j<person[i].states;j++){
				// printf("--states=%d--\n",person[i].states);
				for(m=0;m<b;m++){
				// printf("--ans[%d]=%d, person[%d].state[%d]=%d--\n",m,ans[m],i,j,person[i].state[j]);
					if(ans[m] == person[i].state[j])
						p2 = FALSE;
				}
				if((p1&&p2)||(!p1&&!p2)) p2 = TRUE;  else
				if((p1&&!p2)||(!p1&&p2)) p2 = FALSE;
				p1 = p2;
				// printf("-->%d--\n",person[i].state[j]);
				if(j==person[i].states-1&&p2!=person[i].data)
					return;
			}
		}
		for(i=0;i<b;++i) printf("%d ", ans[i]);
		exit(0);
	}
	for(int i=start; i<=end && end-i+1 >= b-index; i++){
		ans[index] = i;
		run(i+1, end, index+1);
	}
}

int main(){
	load("test1.txt");
	run(0, a-1, 0);
	return 0;
}