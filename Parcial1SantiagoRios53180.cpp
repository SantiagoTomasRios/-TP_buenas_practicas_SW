#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANIO_CADENA 100
#define NIVEL_MINIMO 0
#define NIVEL_MAXIMO 100

#define OPCION_CARGAR 1
#define OPCION_BUSCAR 2
#define OPCION_MOSTRAR 3
#define OPCION_MINIMOS 4
#define OPCION_AUMENTAR 5
#define OPCION_SALIR 6

typedef struct {
	char sector[TAMANIO_CADENA];
	char nombre_tanque[TAMANIO_CADENA];
	int nivel;
} Tanque;

/* --- PROTOTIPOS DE FUNCIONES --- */
void cargar_tanque(Tanque *lista_tanques, int cantidad_actual, Tanque *tanque_min1, Tanque *tanque_min2);
void buscar_tanque(const Tanque *lista_tanques, int cantidad_actual);
void mostrar_tanques(const Tanque *lista_tanques, int cantidad_actual);
void mostrar_minimos(const Tanque *tanque_min1, const Tanque *tanque_min2, int cantidad_actual);

int main(int argc, char *argv[]) {
	int opcion = 0;
	int cantidad_tanques = 0;
	int capacidad_inicial = 0;
	int nueva_capacidad = 0;
	
	printf("Elija el numero de tanques que va a cargar: ");
	if (scanf("%d", &capacidad_inicial) != 1 || capacidad_inicial <= 0) {
		printf("\nError: Cantidad inicial invalida.\n");
		return 1;
	}
	fflush(stdin);
	
	Tanque *tanque_min1 = (Tanque *)malloc(sizeof(Tanque));
	Tanque *tanque_min2 = (Tanque *)malloc(sizeof(Tanque));
	Tanque *lista_tanques = (Tanque *)malloc(sizeof(Tanque) * capacidad_inicial);
	
	if (tanque_min1 == NULL || tanque_min2 == NULL || lista_tanques == NULL) {
		printf("\nError critico: No se pudo asignar memoria dinamica.\n");
		free(tanque_min1);
		free(tanque_min2);
		free(lista_tanques);
		return 1;
	}
	
	while (opcion != OPCION_SALIR) {
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
		if (scanf("%d", &opcion) != 1) {
			printf("\nError: Ingrese un valor numerico valido.");
			fflush(stdin);
			continue;
		}
		fflush(stdin);
		
		switch (opcion) {
		case OPCION_CARGAR: {
			if (capacidad_inicial == cantidad_tanques) {
				printf("\nMemoria llena, aumentar cantidad de datos");
			} else {
				cargar_tanque(lista_tanques, cantidad_tanques, tanque_min1, tanque_min2);
				cantidad_tanques++;
			}
			break;
		}
		case OPCION_BUSCAR: {
			buscar_tanque(lista_tanques, cantidad_tanques); 
			break;
		}
		case OPCION_MOSTRAR: {
			mostrar_tanques(lista_tanques, cantidad_tanques);
			break;
		}
		case OPCION_MINIMOS: {
			mostrar_minimos(tanque_min1, tanque_min2, cantidad_tanques);
			break;
		}
		case OPCION_AUMENTAR: {
			printf("\nIngrese cantidad de datos que quiere cargar: ");
			if (scanf("%d", &nueva_capacidad) != 1) {
				printf("\nError: Entrada invalida.");
				fflush(stdin);
				break;
			}
			fflush(stdin);
			
			if (nueva_capacidad < capacidad_inicial) {
				printf("\nPor favor elija una cantidad de datos mayor a la actual");
			} else {
				Tanque *temp = (Tanque *)realloc(lista_tanques, sizeof(Tanque) * nueva_capacidad);
				if (temp == NULL) {
					printf("\nError: No se pudo reasignar memoria.");
				} else {
					lista_tanques = temp;
					capacidad_inicial = nueva_capacidad;
					printf("\nMemoria redimensionada correctamente.");
				}
			}
			break;
		}
		case OPCION_SALIR: {
			printf("Programa finalizado");
			break;
		}
		default: {
			printf("\nPor favor ingrese un dato valido");
			break;
		}
		}
	}
	
	free(lista_tanques);
	free(tanque_min1);
	free(tanque_min2);
	return 0;
}

/**
* Carga un nuevo tanque en la lista y actualiza los dos registros con menores niveles.
* @param lista_tanques Puntero al arreglo dinámico de tanques.
* @param cantidad_actual Posición actual donde se guardará el nuevo tanque.
* @param tanque_min1 Puntero que almacena el tanque con el nivel más bajo.
* @param tanque_min2 Puntero que almacena el tanque con el segundo nivel más bajo.
*/
void cargar_tanque(Tanque *lista_tanques, int cantidad_actual, Tanque *tanque_min1, Tanque *tanque_min2) {    
	printf("\nIngrese el sector del tanque: ");
	fgets(lista_tanques[cantidad_actual].sector, sizeof(lista_tanques[cantidad_actual].sector), stdin);
	fflush(stdin);
	
	printf("\nIngrese el nombre del tanque: ");
	fgets(lista_tanques[cantidad_actual].nombre_tanque, sizeof(lista_tanques[cantidad_actual].nombre_tanque), stdin);
	fflush(stdin);
	
	do {
		printf("\nIngrese el nivel del tanque (%d a %d): ", NIVEL_MINIMO, NIVEL_MAXIMO);
		if (scanf("%d", &lista_tanques[cantidad_actual].nivel) != 1) {
			printf("\nError: Ingrese un valor numerico.");
			fflush(stdin);
			lista_tanques[cantidad_actual].nivel = -1;
			continue;
		}
		fflush(stdin);
		
		if (lista_tanques[cantidad_actual].nivel > NIVEL_MAXIMO || lista_tanques[cantidad_actual].nivel < NIVEL_MINIMO) {
			printf("\nElija un nivel valido:");
		}
	} while (lista_tanques[cantidad_actual].nivel > NIVEL_MAXIMO || lista_tanques[cantidad_actual].nivel < NIVEL_MINIMO);
	
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

/**
* Busca un tanque en el sistema utilizando su nombre o sector.
* @param lista_tanques Arreglo constante de tanques a recorrer.
* @param cantidad_actual Cantidad de elementos cargados actualmente en el sistema.
*/
void buscar_tanque(const Tanque *lista_tanques, int cantidad_actual) {
	int opcion_busqueda = 0;
	int indice = 0;
	int tanque_encontrado = -1;
	char nombre_buscado[TAMANIO_CADENA];
	char sector_buscado[TAMANIO_CADENA];
	
	do {
		printf("\nIngrese caracteristica que desea buscar:");
		printf("\n1. Nombre");
		printf("\n2. Sector");
		if (scanf("%d", &opcion_busqueda) != 1) {
			printf("\nError: Entrada invalida.");
			fflush(stdin);
			opcion_busqueda = 0;
			continue;
		}
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

/**
* Muestra por pantalla los dos tanques con el nivel de agua más bajo.
* @param tanque_min1 Puntero al primer tanque mínimo.
* @param tanque_min2 Puntero al segundo tanque mínimo.
* @param cantidad_actual Cantidad total de tanques cargados.
*/
void mostrar_minimos(const Tanque *tanque_min1, const Tanque *tanque_min2, int cantidad_actual) {
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

/**
* Muestra el listado completo de todos los tanques registrados.
* @param lista_tanques Arreglo de tanques a mostrar.
* @param cantidad_actual Número de elementos cargados.
*/
void mostrar_tanques(const Tanque *lista_tanques, int cantidad_actual) {
	int indice = 0;
	printf("\n== Lista de tanques ==");
	for (indice = 0; indice < cantidad_actual; indice++) {
		printf("\nTanque %d:", indice);
		printf("\nNombre de tanque: %s", lista_tanques[indice].nombre_tanque);
		printf("Sector del tanque: %s", lista_tanques[indice].sector);
		printf("Nivel del tanque: %d", lista_tanques[indice].nivel);
	}
}
