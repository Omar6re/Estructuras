/* Diccionario Hash
El diccionario Hash tiene un menú que se muestra el ejecutarse, cuenta con las siguientes funciones:
1.- Cargar archivo de definiciones.
2.- Agregar una palabra y su definición.
3.- Buscar una palabra y ver su definición.
4.- Modificar una definición.
5.- Ver diccionario.
6.- Eliminar una palabra.
7.- Guardar diccionario.
8.- Mostrar estadísticas de tabla hash.
9.- Salir.
El diccionario tiene dos funciones hash distintas que generan las colisiones.
*/

//Librerias que contienen funciones que se utilizan en el programa.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADLista/TADLista.h"


int tamanio, opc_hash, hash;
char* palabra_cad[200];

/*
La función recibe una tabla hash e itera sobre la misma desde el inicio hasta el fin, en cada iteración
imprime la palabra que contiene y su definición. Se imprime también el número de pasos que le tomó realizar
el proceso.
*/
void Imprimir_diccionario(lista* tabla_hash)
{
	int i, pasos = 0;

	for(i = 0; i < tamanio; i++)
		if(tabla_hash[i].frente)
		{
			nodo *aux = tabla_hash[i].frente;

			while(aux)
			{
				printf("%s: %s\n", aux->e.palabra, aux->e.definicion);
				aux = aux->atras;
				pasos++;
			}
		}
	printf("El proceso tomó: %i pasos (colisiones)", ++pasos);
}

/*
Recibe una lista, en la que el usuario introduce el nombre del archivo y lo guardamos
con la extensión ".dic", mientras la lista contenga un elemento que no este vacio ni tenga
una referencia a NULL, estará guardando las palabras y su definición, con las funciones
fopen y fclose se guarda el archivo.
*/
void Guardar_Diccionario(lista* tabla_hash)
{
	int i;
	char nombre[500];
	FILE* f;

	printf("Introduzca el nombre del archivo:");
	scanf("%s", nombre);
	strcat(nombre, ".dic");

	f = fopen(nombre, "w");

	for(i = 0; i < tamanio; i++)
		if(tabla_hash[i].frente)
		{
			nodo *aux = tabla_hash[i].frente;

			while(aux)
			{
				fprintf(f, "%s: %s\n", aux->e.palabra, aux->e.definicion);
				aux = aux->atras;
			}
		}
	fclose(f);
}

/*
Primera función hash. Regresa un entero como resultado.
*/
int Hash(char* palabra)
{
	hash = (*palabra - 'A') % tamanio;

	printf("El hash generado es: %i\n", hash);

	return hash;
}

/*
Segunda función hash. Regresa un entero como resultado.
*/
int Hash_2(char* palabra)
{
	int i;

	for(i = 0; palabra[i] != '\0'; i++)
		hash = (palabra[i] * (i + 1)) % tamanio;

	if(hash < 0)
		hash *= -1;

	printf("El hash generado es: %i\n", hash);

	return hash;
}

/*
La función recibe una palabra por el usuario, es una función auxiliar para otras funciones
más importantes.
*/
void Recibir_Nueva_Palabra(elemento* nueva_palabra)
{
	//Iterador.
	int i;

	printf("\nIntroduzca una palabra: ");
	scanf("%s", nueva_palabra->palabra);
}

/*
Recibe una lista y una nueva palabra, una vez que la recibe, la agrega al diccionario.
*/
void Agregar_Palabra(lista* tabla_hash, elemento nueva_palabra)
{
	nodo* aux;
	int pasos = 0;

	Add(&tabla_hash[hash], nueva_palabra);

	aux = tabla_hash[hash].frente;

	while(aux)
	{
		aux = aux->atras;
		pasos++;
	}

	printf("El proceso tomó: %i pasos (colisiones)", ++pasos);
}

/*
Reciba una lista que es el diccionario, e itera sobre el mismo hasta que cuenta una posición
vacía o que tenga un apuntador a NULL. Busca una palabra y se aplica una de las dos funciones hash.
*/
posicion Buscar_Palabra(lista* tabla_hash)
{
	//Iterador
	int i;
	//Elemento auxiliar para realizar la búsqueda.
	elemento busqueda;

	//Posición donde se encuentra la palabra buscada.
	posicion palabra;

	strcpy(busqueda.palabra, palabra_cad);

	if(opc_hash == 1)
		hash = Hash(palabra_cad);
	else
		hash = Hash_2(palabra_cad);

	palabra = Search(&tabla_hash[hash], busqueda);

	return palabra;
}

/*
Recibe una posición en la que se al colocarse, modificará la definición de
la palabra que se recibió.
*/
void Modificar_Definicion(posicion palabra)
{
	int i;

	printf("\nIntroduzca la definición: ");
	scanf("%s", palabra->e.definicion);

	for(i = 0; palabra->e.definicion[i] != '\0'; i++)
		if(palabra->e.definicion[i] == '_')
			palabra->e.definicion[i] = ' ';
}

/*
Recibe una posición que se buscará en el diccionario y al encontrarla
va a imprimir la palabra que se encuentra en aquella posición.
*/
void Imprimir_Palabra(posicion palabra)
{
	printf("%s: %s\n", palabra->e.palabra, palabra->e.definicion);
}

/*
Recibe el diccionario y una posición que se va a buscar en el dicciionario.
Una vez que se encuentra la palabra que está en esta posición, se elimina.
*/
void Eliminar_Palabra(lista *tabla_hash, posicion palabra)
{
	if(opc_hash == 1)
		hash = Hash(palabra->e.palabra);
	else
		hash = Hash_2(palabra->e.palabra);

	Remove(&tabla_hash[hash], palabra);
}

/*
La funcioón recibe una lista, el usuario introduce el nombre del archivo con la extensión
".dic" y una vez que se encuentra, se comiezan a imprimir las palabras junto con sus definiciones.
*/
void Cargar_Archivo(lista *tabla_hash)
{
	//Iterador
	int i = 0;

	//Cadena para guardar la ruta del archivo y cadena para leer palabra y definición.
	char direccion[501], cadena[300];

	//Caracter auxiliar al leer el archivo.
	char aux;

	elemento palabra;

	//Puntero al archivo.
	FILE *f;

	printf("Introduzca la dirección del archivo: ");
	fflush(stdin);
	scanf("%s", direccion);
	strcat(direccion, ".dic");

	f = fopen(direccion, "r");

	aux = fgetc(f);
	while(TRUE)
	{
		switch(aux)
		{
			case ':':
				cadena[i] = '\0';
				strcpy(palabra.palabra, cadena);
				strcpy(palabra_cad, cadena);
				posicion pal = Buscar_Palabra(tabla_hash);
				//puts(cadena);
				i = 0;
				break;
			case '\n':
				break;
			case '.':
				cadena[i++] = '.';
				cadena[i] = '\0';
				strcpy(palabra.definicion, cadena + 1);
				if(pal)
					continue;
				else
					Agregar_Palabra(tabla_hash, palabra);
				i = 0;
				break;
			default:
				cadena[i++] = aux;
		}

		aux = fgetc(f);

		if(aux == EOF)
			break;
	}

	fclose(f);
}

/*
La función recibe el diccionario y muestra el tamaño de la tabla, la mayor complejidad
de la búsqueda y finalmente el número de celdas que se encuentran vacías.
*/
void Mostrar_Estadisticas(lista* tabla_hash)
{
	int i, tam_aux, vacias = 0;

	for(i = 0; i < tamanio; i++)
		if(tabla_hash[i].frente)
		{
			nodo *aux = tabla_hash[i].frente;
			tam_aux = 0;

			while(aux)
			{
				tam_aux++;
				aux = aux->atras;
			}

			if(tam_aux > tamanio)
				tamanio = tam_aux;
		}
		else
			vacias++;

	printf("El tamaño de la tabla es: %i\n", tamanio);
	printf("El orden máximo de búsqueda son: %i\n", tamanio);
	printf("El el número de celdas vacías es: %i\n", vacias);
}

/*
Recibe una palabra y recibe su nueva definición, se agrega al diccionario.
*/
Recibir_Nueva_Definicion(elemento* nueva_palabra)
{
	int i;

	printf("\nIntroduzca la definición: ");
	scanf("%s", nueva_palabra->definicion);

	for(i = 0; nueva_palabra->definicion[i] != '\0'; i++)
		if(nueva_palabra->definicion[i] == '_')
			nueva_palabra->definicion[i] = ' ';
}

/*
Entra a la función que muestra el menú y las posibles selecciones.
Se muestra el menú con las funciones que se pueden utilizar y se selecciona una
que conduce a las demás. El usuario introduce el tamaño de la lista.
*/
void Menu()
{
	//Variable de control de las opciones del menú e iterador.
	int opcion, i;

	//Tabla hash
	lista* tabla_hash;

	//Posicion de alguna palabra.
	posicion palabra;

	elemento pal;

	puts("Introduzca el tamaño de la tabla hash:");
	scanf("%i", &tamanio);

	puts("Introduzca la funció hash a utilizar:");
	scanf("%i", &opc_hash);

	tabla_hash = (lista*)malloc(sizeof(lista) * tamanio);

	//Inicialización de tabla hash.
	for(i = 0; i < tamanio; i++)
		Initialize(&tabla_hash[i]);

	while(TRUE)
	{
		//Limpiamos la terminal.
		system("clear");
		fflush(stdin);
		//Desplegar opciones del menúu.
		puts("1.- Cargar archivo de definiciones.");
		puts("2.- Agregar una palabra y su definición.");
		puts("3.- Buscar una palabra y ver su definición.");
		puts("4.- Modificar una definición.");
		puts("5.- Ver diccionario.");
		puts("6.- Eliminar una palabra.");
		puts("7.- Guardar diccionario.");
		puts("8.- Mostrar estadísticas de tabla hash");
		puts("9.- Salir.");

		scanf("%i", &opcion);

		switch(opcion)
		{
			case 1:
				//Limpiamos la tabla actual.
				for(i = 0; i < 27; i++)
					Destroy	(&tabla_hash[i]);
				Cargar_Archivo(tabla_hash);
				fflush(stdin);
				break;
			case 2:
				Recibir_Nueva_Palabra(&pal);
				Recibir_Nueva_Definicion(&pal);
				strcpy(palabra_cad, pal.palabra);
				palabra = Buscar_Palabra(tabla_hash);
					if(palabra)
						puts("No se encontró la palabra.");
					else
						Agregar_Palabra(tabla_hash, pal);
				fflush(stdin);
				getchar();
				getchar();
				break;
			case 3:
				Recibir_Nueva_Palabra(&pal);
				strcpy(palabra_cad, pal.palabra);
				palabra = Buscar_Palabra(tabla_hash);
				if(!palabra)
					puts("No se encontró la palabra.");
				else
					Imprimir_Palabra(palabra);
				fflush(stdin);
				getchar();
				getchar();
				break;
			case 4:
				Recibir_Nueva_Palabra(&pal);
				strcpy(palabra_cad, pal.palabra);
				palabra = Buscar_Palabra(tabla_hash);
				if(!palabra)
					puts("No se encontró la palabra.");
				else
					Modificar_Definicion(palabra);
				fflush(stdin);
				getchar();
				getchar();
				break;
			case 5:
				Imprimir_diccionario(tabla_hash);
				getchar();
				getchar();
				break;
			case 6:
				Recibir_Nueva_Palabra(&pal);
				strcpy(palabra_cad, pal.palabra);
				palabra = Buscar_Palabra(tabla_hash);
				if(!palabra)
					puts("No se encontró la palabra.");
				else
					Eliminar_Palabra(tabla_hash, palabra);
				fflush(stdin);
				getchar();
				getchar();
				break;
			case 7:
				Guardar_Diccionario(tabla_hash);
				break;

			case 8:
				Mostrar_Estadisticas(tabla_hash);
				getchar();
				getchar();
				break;
			case 9:
				return;
		}
	}
}

int main()
{
	Menu();

	return 0;
}