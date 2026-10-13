#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char sector[100];
	char nombre_tanque[100];
	int nivel;
} Tanque;

void cargar_tanque(Tanque *lista_tanques, int cantidad_actual, Tanque *tanque_min1, Tanque *tanque_min2);
void mostrar_minimos(Tanque *tanque_min1, Tanque *tanque_min2, int cantidad_actual);
void buscar_tanque(Tanque *lista_tanques, int cantidad_actual);
void mostrar_tanques(Tanque *lista_tanques, int cantidad_actual);

int main(int argc, char *argv[]) {
	int opcion = 0;
	int cantidad_tanques = 0;
	int capacidad_inicial = 0;
	int nueva_capacidad = 0;
	
	Tanque *tanque_min1 = (Tanque *)malloc(sizeof(Tanque));
	Tanque *tanque_min2 = (Tanque *)malloc(sizeof(Tanque));
	
	printf("Elija el numero de tanques que va a cargar: ");
	scanf("%d", &capacidad_inicial);
	fflush(stdin);
	
	Tanque *lista_tanques = (Tanque *)malloc(sizeof(Tanque) * capacidad_inicial);
	
	while (opcion != 6) {
		printf("\n=================================================");
		printf("\nMenu:");
		printf("\n1. Cargar tanque");
		printf("\n2. Buscar tanque");
		printf("\n3. Mostrar tanques cargados");
		printf("\n4. Mostrar tanques con minimo nivel de agua");
		printf("\n5. Aumentar cantidad de datos");
		printf("\n6. Salir");
		printf("\n=================================================");
		printf("\nElija opcion: ");        
		scanf("%d", &opcion);
		fflush(stdin);
		
		switch (opcion) {
		case 1:
			if (capacidad_inicial == cantidad_tanques) {
				printf("\nMemoria llena, aumentar cantidad de datos");
			} else {
				cargar_tanque(lista_tanques, cantidad_tanques, tanque_min1, tanque_min2);
				cantidad_tanques++;
			}
			break;
		case 2:
			buscar_tanque(lista_tanques, cantidad_tanques); 
			break;
		case 3:
			mostrar_tanques(lista_tanques, cantidad_tanques);
			break;
		case 4:
			mostrar_minimos(tanque_min1, tanque_min2, cantidad_tanques);
			break;
		case 5:
			printf("\nIngrese cantidad de datos que quiere cargar: ");
			scanf("%d", &nueva_capacidad);
			fflush(stdin);
			if (nueva_capacidad < capacidad_inicial) {
				printf("\nPor favor elija una cantidad de datos mayor a la actual");
			} else {
				lista_tanques = (Tanque *)realloc(lista_tanques, sizeof(Tanque) * nueva_capacidad);
				capacidad_inicial = nueva_capacidad;
			}
			break;
		case 6:
			printf("Programa finalizado");
			break;
		default:
			printf("\nPor favor ingrese un dato valido");
		}
	}
	
	free(lista_tanques);
	free(tanque_min1);
	free(tanque_min2);
	return 0;
}

void cargar_tanque(Tanque *lista_tanques, int cantidad_actual, Tanque *tanque_min1, Tanque *tanque_min2) {    
	printf("\nIngrese el sector del tanque: ");
	fgets(lista_tanques[cantidad_actual].sector, sizeof(lista_tanques[cantidad_actual].sector), stdin);
	fflush(stdin);
	
	printf("\nIngrese el nombre del tanque: ");
	fgets(lista_tanques[cantidad_actual].nombre_tanque, sizeof(lista_tanques[cantidad_actual].nombre_tanque), stdin);
	fflush(stdin);
	
	do {
		printf("\nIngrese el nivel del tanque: ");
		scanf("%d", &lista_tanques[cantidad_actual].nivel);
		fflush(stdin);
		if (lista_tanques[cantidad_actual].nivel > 100 || lista_tanques[cantidad_actual].nivel < 0) {
			printf("\nElija un nivel entre 0 y 100:");
		}
	} while (lista_tanques[cantidad_actual].nivel > 100 || lista_tanques[cantidad_actual].nivel < 0);
	
	if (cantidad_actual == 0) {
		*tanque_min1 = lista_tanques[cantidad_actual];
	}
	if (cantidad_actual == 1) {
		*tanque_min2 = lista_tanques[cantidad_actual];
	}
	if (cantidad_actual >= 2) {
		if (lista_tanques[cantidad_actual].nivel < tanque_min1->nivel) {
			*tanque_min1 = lista_tanques[cantidad_actual];
		} else if (lista_tanques[cantidad_actual].nivel < tanque_min2->nivel) {
			*tanque_min2 = lista_tanques[cantidad_actual];
		}
	}
}

void buscar_tanque(Tanque *lista_tanques, int cantidad_actual) {
	int opcion_busqueda, indice, tanque_encontrado = -1;
	char nombre_buscado[100], sector_buscado[100];
	
	do {
		printf("\nIngrese caracteristica que desea buscar:");
		printf("\n1. Nombre");
		printf("\n2. Sector");
		scanf("%d", &opcion_busqueda);
		fflush(stdin);
		if (opcion_busqueda < 1 || opcion_busqueda > 2) {
			printf("\nIngrese una opcion valida");
		}
	} while (opcion_busqueda < 1 || opcion_busqueda > 2);
	
	if (opcion_busqueda == 1) {
		printf("\nIngrese el nombre del tanque que busca: ");
		fgets(nombre_buscado, sizeof(nombre_buscado), stdin);
		fflush(stdin);
		for (indice = 0; indice < cantidad_actual; indice++) {
			if (strcmp(lista_tanques[indice].nombre_tanque, nombre_buscado) == 0) {
				tanque_encontrado = indice;
				indice += cantidad_actual;
			}
		}
	} else if (opcion_busqueda == 2) {
		printf("\nIngrese el sector del tanque que busca: ");
		fgets(sector_buscado, sizeof(sector_buscado), stdin);
		fflush(stdin);
		for (indice = 0; indice < cantidad_actual; indice++) {
			if (strcmp(lista_tanques[indice].sector, sector_buscado) == 0) {
				tanque_encontrado = indice;
				indice += cantidad_actual;
			}
		}    
	}
	
	if (tanque_encontrado == -1) {
		printf("\nTanque no encontrado");
	} else {
		for (indice = 0; indice < cantidad_actual; indice++) {
			printf("\nTanque encontrado:");
			printf("\nNombre de tanque: %s", lista_tanques[tanque_encontrado].nombre_tanque);
			printf("\nSector del tanque: %s", lista_tanques[tanque_encontrado].sector);
			printf("\nNivel del tanque: %d", lista_tanques[tanque_encontrado].nivel);
		}
	}
}

void mostrar_minimos(Tanque *tanque_min1, Tanque *tanque_min2, int cantidad_actual) {
	if (cantidad_actual < 2) {
		printf("\nPor favor ingrese mas de dos tanques para iniciar esta funcion");
	} else {
		printf("\nLos tanques con el minimo nivel de agua son:");
		printf("\nTanque 1:");
		printf("\nNombre: %s", tanque_min1->nombre_tanque);
		printf("\nSector: %s", tanque_min1->sector);
		printf("\nNivel: %d", tanque_min1->nivel);
		printf("\nTanque 2:");
		printf("\nNombre: %s", tanque_min2->nombre_tanque);
		printf("\nSector: %s", tanque_min2->sector);
		printf("\nNivel: %d", tanque_min2->nivel);
	}
}

void mostrar_tanques(Tanque *lista_tanques, int cantidad_actual) {
	int indice;
	printf("\n== Lista de tanques ==");
	for (indice = 0; indice < cantidad_actual; indice++) {
		printf("\nTanque %d:", indice);
		printf("\nNombre de tanque: %s", lista_tanques[indice].nombre_tanque);
		printf("Sector del tanque: %s", lista_tanques[indice].sector);
		printf("Nivel del tanque: %d", lista_tanques[indice].nivel);
	}
}
