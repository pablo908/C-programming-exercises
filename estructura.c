#include <stdio.h>

struct humano
{
	char nombre[50];
	char profesion[50];
	int edad;
	char nacionalidad[50];
}men[5];

int main()
{
	printf("\n");
	for ( int i = 0 ; i < 5 ; i++ )
	{
		printf("ingrese su nombre \n");
		scanf("%s" , men[i].nombre);
		printf("ingrese su profesion \n");
                scanf("%s" , men[i].profesion);
		printf("ingrese su edad \n");
                scanf("%d" , &men[i].edad);
		printf("ingrese su nacionalidad \n");
                scanf("%s" , men[i].nacionalidad);
	}

	for ( int i = 0 ; i < 5 ; i++ )
        {
		printf("\n");
		printf("ficha personal %d \n" , i+1);
                printf("nombre:  %s \n" , men[i].nombre);
                printf("profesion: %s \n" , men[i].profesion);
                printf("edad: %d \n" , men[i].edad);
                printf("nacionalidad: %s \n" , men[i].nacionalidad);
        }
	printf("\n");
}
