#include <stdlib.h>
#include<string.h>
#include <stdio.h>
using namespace std;

typedef struct{
	char sector[100];
	char nombreTanque[100];
	int nivel;
}Tanques;

void cargarTanque(Tanques *t, int n, Tanques *t1, Tanques *t2);
void minimos(Tanques *t1, Tanques *t2, int n);
void buscar(Tanques *t, int n);
void mostrar(Tanques *t, int n);


int main(int argc, char *argv[]) {
	int opcion, nTanques, nDatos, nnDatos;
	Tanques *t1 = (Tanques *)malloc(sizeof(Tanques));
	Tanques *t2 = (Tanques *)malloc(sizeof(Tanques));
	printf("Ellija numero de tanques que va a cargar");
	scanf("%d", &nDatos);
	fflush(stdin);
	Tanques *tanque = (Tanques *)malloc(sizeof(Tanques)*nDatos);
	nTanques = 0;
	while(opcion !=6){
		printf("\n=================================================");
		printf("\nMenu:");
		printf("\n1.Cargar tanque");
		printf("\n2.Buscar tanque");
		printf("\n3.Mostrar tanques cargados");
		printf("\n4.Mostrar tanques con minimo nivel de agua");
		printf("\n5.Aumentar cantidad de datos");
		printf("\n6.Salir");
		printf("\n=================================================");
		printf("\nElija opcion:");		
		scanf("%d", &opcion);
		fflush(stdin);
		switch(opcion){
			case 1:
				if(nDatos==nTanques){
					printf("\nMemoria llena, aumentar cantidad de datos");
				}else{
					cargarTanque(tanque, nTanques, t1, t2);
					nTanques++;
				}
				break;
			case 2:
				buscar(tanque, nTanques); 
				break;
			case 3:
				mostrar(tanque, nTanques);
				break;
			case 4:
				minimos(t1, t2, nTanques);
				break;
			case 5:
				printf("\nIngrese cantidad de datos que quiere cargar:");
					scanf("%d", &nnDatos);
					fflush(stdin);
					if(nnDatos<nDatos){
						printf("\nPorfavor elija una cantidad de datos mayor a la actual");
					}else{
						tanque =(Tanques*) realloc(tanque, sizeof(Tanques)* nnDatos);
						nDatos=nnDatos;
					}
				break;
			default:
				printf("\nPorfavor ingrese dato valido");
		}
	}
	free(tanque);
	free(t1);
	free(t2);
	printf("Programa finalizado");
	return 0;
}

void cargarTanque(Tanques *t,int n, Tanques *t1, Tanques *t2){	
	printf("\nIngrese el sector del tanque:");
	fgets(t[n].sector, sizeof(t[n].sector), stdin);
	fflush(stdin);
	printf("\nIngrese el nombre del tanque:");
	fgets(t[n].nombreTanque, sizeof(t[n].nombreTanque), stdin);
	fflush(stdin);
	do{
		printf("\nIngrese el nivel del tanque:");
		scanf("%d", &t[n].nivel);
		fflush(stdin);
		if(t[n].nivel>100 || t[n].nivel<0 ){
			printf("\nElija un nivel entre 0 y 100:");
		}
	} while(t[n].nivel>100 || t[n].nivel<0 );
	if(n==0){
		*t1=t[n];
	}
	if(n==1){
		*t2=t[n];
	}
	if(n>=2){
		if((t[n].nivel)<(t1->nivel)){
			*t1=t[n];
		}else if((t[n].nivel)<(t2->nivel)){
			*t2=t[n];
		}
	}
}

void buscar(Tanques *t, int n){
	int opcion, i, ntanque=-1;
	char nombre[100], sector[100];
	do{
		printf("\nIngrese caracteristica que desea buscar:");
		printf("\n1.Nombre");
		printf("\n2.Sector");
		scanf("%d", &opcion);
		fflush(stdin);
		if(opcion<1||opcion>2){
			printf("\nIngrese una opcion valida");
		}
	} while(opcion<1||opcion>2);
	
	
	if(opcion == 1){
		printf("\nIngrese el nombre del tanque que busca:");
		fgets(nombre, sizeof(nombre), stdin);
		fflush(stdin);
		for(i=0; i<n;i++){
			if(strcmp(t[i].nombreTanque, nombre)==0){
				ntanque = i;
				i+=n;
			}
		}
	}else if(opcion == 2){
		printf("\nIngrese el sector del tanque que busca:");
		fgets(sector, sizeof(sector), stdin);
		fflush(stdin);
		for(i=0; i<n;i++){
			if(strcmp(t[i].sector, sector)==0){
				ntanque = i;
				i+=n;
			}
		}	
	}
	if(ntanque == -1){
			printf("\nTanque no encontrado");
		}else{
		for(i=0;i<n;i++){
			printf("\nTanque encontrado:");
			printf("\nNombre de tanque: %s", t[ntanque].nombreTanque);
			printf("\nSector del tanque: %s", t[ntanque].sector);
			printf("\nNivel del tanque: %d", t[ntanque].nivel);
		}
	}
}

void minimos(Tanques *t1, Tanques *t2, int n){
	if(n<2){
		printf("\nPorfavor ingrese mas de dos tanques para iniciar esta funcion");
	}else{
		printf("\nLos tanque con el minimo nivel de agua son:");
		printf("\nTanque 1:");
		printf("\nNombre: %s", t1->nombreTanque);
		printf("\nSector: %s", t1->sector);
		printf("\nNivel: %d", t1->nivel);
		printf("\nTanque 2:");
		printf("\nNombre: %s", t2->nombreTanque);
		printf("\nSector: %s", t2->sector);
		printf("\nNivel: %d", t2->nivel);
	}
	
}
	
void mostrar(Tanques *t, int n){
	int i;
	printf("\n==Lista de tanques==");
	for(i=0; i<n;i++){
		printf("\nTanque %d:", i);
		printf("\nNombre de tanque: %s", t[i].nombreTanque);
		printf("Sector del tanque: %s", t[i].sector);
		printf("Nivel del tanque: %d", t[i].nivel);
	}

}
