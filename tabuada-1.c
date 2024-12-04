#include<stdio.h>

int main(){
	int x, y;
	
	printf("Digite o Numero q sera calculado\nR:");
	scanf("%d",& x);
	
	printf("Digite o Numero de vezes q sera calculado\nR:");
	scanf("%d",& y);
	
	printf("Multi\t\t\tSoma\t\t\tDiv\t\t\tSub\n");
	int i;
	for(i= 1; i <= y; i++){
		printf("%d x %d = %d\t\t", x, i, x*i);
		printf("%d + %d = %d\t\t", x, i, x+i);
		printf("%d / %d = %d\t\t", x, i, x/i);
		printf("%d - %d = %d\n", x, i, x-i);
	}
}
