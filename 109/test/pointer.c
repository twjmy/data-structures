#include<stdio.h>
int main(){
	int n[] = {327};
	int *p = &n;
	
	printf("n 的位址：%p\n", n);
	printf("&n 的位址：%p\n", &n);
	printf("n 所在位址儲存的值：%d\n", *n);
	printf("p 儲存的位址：%p\n", p);
	printf("p 的位址：%p\n", &p);
	printf("p 儲存的位址所儲存的值：%d\n", *p);

	return 0;
}
