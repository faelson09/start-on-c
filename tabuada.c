#include<stdio.h>

int main(){
	int x, y;
	
	printf("Digite o Numero q sera multiplicado\nR:");
	scanf("%d",& x);
	
	printf("Digite o Numero de vezes q sera multiplicado\nR:");
	scanf("%d",& y);
	
	int i;
	for(i= 1; i <= y; i++){
		printf("%d x %d\t= %d\n", x, i, x*i);
	}
	
}
