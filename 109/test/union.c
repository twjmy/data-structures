#include<stdio.h>

struct {
	enum {female, male} sex;
	union {
		int children;
		int beard;
	} u;
} st;

int main(){
	puts("############# Program start #############");
	st.sex = male;
	st.u.children = 12;
	printf("%d\n",st.sex);
	printf("%d\n",st.u.beard);
	puts("################## End ##################");
	system("PAUSE");
	return 0;
}
