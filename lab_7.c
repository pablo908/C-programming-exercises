#include <stdio.h>
#define N 8

int is_valid(int cols[N]) {
	for (int i = 0; i < N-1; i++) {
		if (cols[i] == 0) {
			continue;
		}
		for(int j = i+1; j < N; j++) {
			if (cols[i] == cols[j]) {
				printf("filas\n i:%d j:%d cols[i]:%d cols[j]:%d ",i,j,cols[i],cols[j]);
				return 0;
			}
		}
	}
	for(int i = 0; i < N; i++) {
		if (cols[i] != 0) {
			for (int j = i+1 ; j < N ; j++) {
				if (cols[j] != 0) {
					if (cols[i]+(i-j) == cols[j] || cols[i]-(i-j) == cols[j]) {
						printf("diagonal positiva\n i:%d j:%d cols[i]:%d cols[j]:%d cols[i]+j:%d cols[i]-j:%d\n",i,j,cols[i],cols[j],cols[i]+j,cols[i]-j);
						return 0;
					}
				}
			}
			for (int j = i-1 ; j >= 0 ; j--) {
				if (cols[j] != 0) {

					printf("diagonal negativa\n i:%d j:%d cols[i]:%d cols[j]:%d cols[i]+j:%d cols[i]-j:%d\n",i,j,cols[i],cols[j],cols[i]+j,cols[i]-j);

					if (cols[i]+(i-j) == cols[j] || cols[i]-(i-j) == cols[j]) {
						return 0;
					}
				}
			}
		}
	}
	return 1;
}

int main(){
	int queens[8], i;
	for(i=0;i<8;i++)
   	scanf("%d", &queens[i]);
	if(is_valid(queens)) printf("solucion valida\n");
	else printf("solucion no valida\n");
}
