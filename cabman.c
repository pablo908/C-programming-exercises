/*
	Nombre: Pablo Ignacio Pezoa Frau
	Asignatura: Sistemas Operativos
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

// definicion hebra que se encarga de monitorear el deadlock
pthread_t monitor_deadlocks;

// definicion de mutex y variables de condicion para gestionar el orden del cruce
pthread_mutex_t lock;
pthread_cond_t ColaNorte, ColaEste, ColaSur, ColaOeste, NortePrimero, EstePrimero, SurPrimero, OestePrimero;
pthread_mutex_t ColaNorte_lock, ColaEste_lock, ColaSur_lock, ColaOeste_lock, NortePrimero_lock, EstePrimero_lock, SurPrimero_lock, OestePrimero_lock;

// definicion de contadores para la gestión de las hebras
int norte = 0, sur = 0, este = 0, oeste = 0, norteprimero = 0, surprimero = 0, esteprimero = 0, oesteprimero = 0;
int waitn = 0, waits = 0, waite = 0, waito = 0;
int waitnp = 0, waitsp = 0, waitep = 0, waitop = 0;
int ncnt = 0, scnt = 0, ecnt = 0, ocnt = 0;
int cruce_ocupado = 0;

// Se define una estructura para los carros que contiene la hebra y sus demás componentes
typedef struct CAB {
	int num;
	char dir[20];
	char letra;
	pthread_t carro;
} CAB;

//metodo que gestiona la llegada del cab al cruce
void llegada(CAB c) {
	printf("CAB %d desde %s llega al cruce\n", c.num, c.dir);
	pthread_mutex_lock(&lock);

	// se revisa para cada direccion si el hilo actual es el primero de la cola
        switch (c.letra) {
		case 'n':
			waitn++;
			if (ncnt) {
				pthread_cond_wait(&ColaNorte,&lock);
			}
			waitn--;
			ncnt++;
			break;
		case 's':
			waits++;
			if (scnt) {
				pthread_cond_wait(&ColaSur,&lock);
			}
			waits--;
			scnt++;
			break;
		case 'e':
			waite++;
			if (ecnt) {
				pthread_cond_wait(&ColaEste,&lock);
			}
			waite--;
			ecnt++;
			break;
		case 'o':
			waito++;
			if (ocnt) {
				pthread_cond_wait(&ColaOeste,&lock);
			}
			waito--;
			ocnt++;
			break;
        }
	pthread_mutex_unlock(&lock);
}

// metodo que revisa las prioridades para ver si hay un cab a la derecha para esperar a recibir la señal de paso
void cruce(CAB c) {
	sleep(1);
	pthread_mutex_lock(&lock);

	// se revisa que no haya un cab a la derecha por un tema de prioridades
        switch (c.letra) {
		case 'n':
			waitop++;
			if (ocnt) {
				pthread_cond_wait(&OestePrimero,&lock);
			}
			waitop--;
			break;
		case 's':
			waitep++;
			if (ecnt) {
				pthread_cond_wait(&EstePrimero,&lock);
			}
			waitep--;
			break;
		case 'e':
			waitnp++;
			if (ncnt) {
				pthread_cond_wait(&NortePrimero,&lock);
			}
			waitnp--;
			break;
		case 'o':
			waitsp++;
			if (scnt) {
				pthread_cond_wait(&SurPrimero,&lock);
			}
			waitsp--;
			break;
        }
	sleep(1);
	pthread_mutex_unlock(&lock);
}

// este metodo gestiona el partida en si del cab
void partida(CAB c) {
	printf("CAB %d desde %s dejando el cruce\n", c.num, c.dir);
	pthread_mutex_lock(&lock);

	// se avisa a las demas direcciones que partio 
        switch(c.letra) {
		case 'n':
			ncnt--;
			if (waitnp) {
				pthread_cond_signal(&NortePrimero);
			}

			if (waitn) {
				pthread_cond_signal(&ColaNorte);
			}

			break;
		case 's':
			scnt--;
			if (waitsp) {
				pthread_cond_signal(&SurPrimero);
			}

			if (waits) {
				pthread_cond_signal(&ColaSur);
			}

			break;
		case 'e':
			ecnt--;
			if (waitep) {
				pthread_cond_signal(&EstePrimero);
			}

			if (waite) {
				pthread_cond_signal(&ColaEste);
			}

			break;
		case 'o':
			ocnt--;
			if (waitop) {
				pthread_cond_signal(&OestePrimero);
			}

			if (waito) {
				pthread_cond_signal(&ColaOeste);
			}

			break;
	}
	pthread_mutex_unlock(&lock);
}

// este es el metodo que se encarga de solucionar los deadlock
void *check(void *nada){
	for (;;) {
		usleep(5000000);

		// en caso de deadlock se libera al norte de forma arbitraria para asi descongestionar el cruce
		if (waitnp && waitsp && waitep && waitop) {
			printf("DEADLOCK: se detecto un atasco de CAB, señalando al Norte que parta\n");
			pthread_cond_signal(&NortePrimero);
		} else if (!ncnt && !scnt && !ecnt && !ocnt) {
			if (waitn) {
				pthread_cond_signal(&ColaNorte);
			} else if (waits) {
				pthread_cond_signal(&ColaSur);
			} else if (waite) {
				pthread_cond_signal(&ColaEste);
			} else if (waito) {
				pthread_cond_signal(&ColaOeste);
			}
		}
		
		// condicion de termino
		if (!waitn && !waits && !waite && !waito && !waitnp && !waitsp && !waitep && !waitop && !ncnt && !scnt && !ecnt && !ocnt) {                            
                        break;
		}

	}
}

// este es un metodo de monitoreo
void *carro_automatico_bidireccional(void *_carros) {
	CAB *carros = _carros;

	llegada(*carros);
	cruce(*carros);
	partida(*carros);
}

// este metodo inicializa los mutex y las variables condicionales
void inicializar() {
	pthread_mutex_init(&ColaNorte_lock,NULL);
	pthread_mutex_init(&ColaSur_lock,NULL);
	pthread_mutex_init(&ColaEste_lock,NULL);
	pthread_mutex_init(&ColaOeste_lock,NULL);
	pthread_mutex_init(&NortePrimero_lock,NULL);
	pthread_mutex_init(&SurPrimero_lock,NULL);
	pthread_mutex_init(&EstePrimero_lock,NULL);
	pthread_mutex_init(&OestePrimero_lock,NULL);

	pthread_cond_init(&ColaNorte,NULL);
	pthread_cond_init(&ColaSur,NULL);
	pthread_cond_init(&ColaEste,NULL);
	pthread_cond_init(&ColaOeste,NULL);
	pthread_cond_init(&NortePrimero,NULL);
	pthread_cond_init(&SurPrimero,NULL);
	pthread_cond_init(&EstePrimero,NULL);
	pthread_cond_init(&OestePrimero,NULL);
}

// este metodo libera las variables mutex y condicionales
void destruir() {
	pthread_mutex_destroy(&ColaNorte_lock);
	pthread_mutex_destroy(&ColaSur_lock);
	pthread_mutex_destroy(&ColaEste_lock);
	pthread_mutex_destroy(&ColaOeste_lock);
	pthread_mutex_destroy(&NortePrimero_lock);
	pthread_mutex_destroy(&SurPrimero_lock);
	pthread_mutex_destroy(&EstePrimero_lock);
	pthread_mutex_destroy(&OestePrimero_lock);

	pthread_cond_destroy(&ColaNorte);
	pthread_cond_destroy(&ColaSur);
	pthread_cond_destroy(&ColaEste);
	pthread_cond_destroy(&ColaOeste);
	pthread_cond_destroy(&NortePrimero);
	pthread_cond_destroy(&SurPrimero);
	pthread_cond_destroy(&EstePrimero);
	pthread_cond_destroy(&OestePrimero);

	pthread_mutex_destroy(&lock);
}

int main(int argc, char** argv) {
	// inicializacion de variables locales del main
	pthread_mutex_init(&lock,NULL);
	CAB *carros;
	int sw_letra_erronea = 0;

	// se revisa que al ejecutar el programa se le agrege el argumento que indica los cabs a analizar para el problema
	if (argc < 2) {
		printf("Error por favor ingresar parametros\n");
	} else {
		// se incializan variables globales y se crea un proceso de monitoreo
		inicializar();		
		pthread_create(&monitor_deadlocks,NULL,check,NULL);

		// se crea un arreglo de estructuras para la gestion de las hebras de los cab
        	CAB *carros;
		carros = (CAB*)malloc(sizeof(CAB)*(strlen(argv[1])));
		for(int i = 0; i < strlen(argv[1]); i++){
			// se le asignan los valores a cada cab
			carros[i].letra = argv[1][i];
			carros[i].num = i+1;
			switch (argv[1][i]) {
			case 'n':
				strcpy(carros[i].dir, "Norte");
				break;
			case 's':
				strcpy(carros[i].dir, "Sur");
				break;
			case 'e':
				strcpy(carros[i].dir, "Este");
				break;
			case 'o':
				strcpy(carros[i].dir, "Oeste");
				break;
			default:
				sw_letra_erronea = 1;
			}
			
			if (!sw_letra_erronea) {
				pthread_create(&(carros[i].carro),NULL,carro_automatico_bidireccional,&(carros[i]));
			} else {
				printf("Letra no valida se omite: %c\n", argv[1][i]);
				sw_letra_erronea = 0;
			}
		}
        
		// se llama a pthread_join para que se espere a los hilos y luego se libera la memoria y se destruyen los elementos pthread
		for (int i = 0; i < strlen(argv[1]); i++) {
			pthread_join(carros[i].carro,NULL);
		}

		pthread_join(monitor_deadlocks,NULL);

		free(carros);

		destruir();
	}
}
