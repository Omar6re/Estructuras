#include <stdio.h>

signed long long int tribo(int n) {
   switch (n) {
     case 0 : return 0;
     case 1 : return 0;
     case 2 : return 1;
     case 3 : return 1;
     default: return tribo(n - 1) + tribo(n - 2) + tribo(n - 3);
   }
}

int main() {
   int n;
   printf("Ingrese el valor de n: ");
   scanf("%d", &n);
   printf("El termino %d de Tribonacci es: %.0lli\n", n, tribo(n - 1));
} 