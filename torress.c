#include <stdio.h>   
#include <stdlib.h>
typedef struct torre
{
	int discos[100];
	int index;
} torre;

char * cual(int index){
	switch(index){
		case 0: return "ORIGEN";
		case 1: return "AUXILIAR";
		case 2: return "DESTINO";
		default: return "";
	}
}

void agrega(int numero_de_discos, torre * T){
	T->discos[++T->index] = numero_de_discos;
}

int quita(torre * T){
	return T->discos[T->index--];
}

void mover(int numero_de_discos, int origen, int destino, torre * torres, int * movimientos){
	(*movimientos)++;
	agrega(quita(&torres[origen]), &torres[destino]);
	printf("%d: ARRASTRAR DISCO %d DE %s A %s.\n", *movimientos, numero_de_discos, cual(origen), cual(destino));
}

void hanoi(int numero_de_discos, int origen, int aux, int destino, torre * torres, int * movimientos){
	if(numero_de_discos == 1){
		mover(numero_de_discos, origen, destino, torres, movimientos);
	}else{
		hanoi(numero_de_discos - 1, origen, destino, aux, torres, movimientos);
		mover(numero_de_discos, origen, destino, torres, movimientos);
		hanoi(numero_de_discos - 1, aux, origen, destino, torres, movimientos);
	}
}

int main(){
	int numero_de_discos = 0, i = 0, movimientos = 0;
	torre torres[3];
	for(i = 0; i < 3; i++){
		torres[i].index = -1;
	}

	printf("INTRODUCE LA CANTIDAD DE DISCOS: ");
	scanf("%d", &numero_de_discos);

	for(i = numero_de_discos; i >= 1; i--){
		agrega(i, &torres[0]);
	}

	system("clear");

	hanoi(numero_de_discos, 0, 1, 2, torres, &movimientos);
	
	return 0;
}