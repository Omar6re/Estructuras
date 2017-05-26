#include <stdio.h>

signed long long int fibo(int n) {
   switch (n) {
     case 0 : return 0;
     case 1 : return 1;
     case 2 : return 1;
     default: return fibo(n - 1) + fibo(n - 2);
   }
}

int main() {
   int n;
   printf("Ingrese el valor de n: ");
   scanf("%d", &n);
   printf("El termino %d de Fibonacci es: %.0lli\n", n, fibo(n - 1));
}