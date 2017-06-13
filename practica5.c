#include <stdio.h> 
#include <stdlib.h>

void print_tab(int ** board, int n){
	int i, j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			if(board[i][j] == 1) printf("%c", 81);
			else printf("+");
		}
		printf("\n");
	}
}

void initialize(int *** board, int n, int ** inicial){
	int i, j;
	*board = malloc(sizeof(int*) * n);
	for(i = 0; i < n; i++){
		(*board)[i] = malloc(sizeof(int) * n);
		for(j = 0; j < n; j++){
			if(inicial == NULL){
				(*board)[i][j] = 0;
			}else{
				(*board)[i][j] = inicial[i][j];
			}
		}
	}
}

void add(int ** board, int n, int **** soluciones, int n_soluciones){
	*soluciones = realloc(*soluciones, sizeof(int**) * (n_soluciones + 1));
	initialize(&(*soluciones)[n_soluciones], n, board);
}

void solve(int ** board, int n, int col, int **** soluciones, int * n_soluciones, char print){
	int i;
	if(col == n){
		add(board, n, soluciones, *n_soluciones);
		(*n_soluciones)++;
		for(i = 0; i < col - 1; i++) printf("-------------");
		printf("SOLUCION-----------------------------\n\n");
		}else{
		for(i = 0; i < n; i++){
			board[i][col] = 1;
			print_tab(board, n);
			printf("\n");
			if(PlaceQueen(board, n, i, col)){
				solve(board, n, col + 1, soluciones, n_soluciones, print);
			}
			board[i][col] = 0;
		}
	}
}

int PlaceQueen(int ** board, int n, int x, int y){
	int i, j;
	for(j = 0; j < y; j++){
		if(board[x][j] == 1){
			return 0;
		}
	}
	for(i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--){
		if(board[i][j] == 1){
			return 0;
		}
	}
	for(i = x + 1, j = y - 1; i < n && j >= 0 ; i++, j--){
		if(board[i][j] == 1){
			return 0;
		}
	}
	return 1;
}

int main(){
	int *** soluciones = NULL;
	int n_soluciones = 0;
	int ** board = NULL;
	int n;
	char print;
	int i, j, k;
	printf("Introduce el tamaño del tablero (n x n): ");
	scanf("%d", &n);
	initialize(&board, n, NULL);
	solve(board, n, 0, &soluciones, &n_soluciones, print);
	printf("Se hallaron %d soluciones\n\n", n_soluciones);
	for(i = 0; i < n_soluciones; i++){
		printf("SOLUCION %d:\n", i + 1);
		print_tab(soluciones[i], n);
		printf("\n");
	}
	for(i = 0; i < n; i++){
		free(board[i]);
	}
	free(board);
	for(i = 0; i < n_soluciones; i++){
		for(j = 0; j < n; j++){
			free(soluciones[i][j]);
		}
		free(soluciones[i]);
	}
	free(soluciones);
	return 0;
}