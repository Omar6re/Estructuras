#include <stdio.h>
#include <bits/types.h>
#include <stdlib.h>
#include <string.h>

#define SWP(x,y) (x^=y, y^=x, x^=y)
char *fibonaccis[20000];


void strrev(char *p)
{
  char *q = p;
  while(q && *q) ++q; /* find eos */
  for(--q; p < q; ++p, --q) SWP(*p, *q);
}

char * Suma (char *n1, char *n2){
  char n3[50];
  int acarreo = 0, i = 0;
  strrev(n1);
  strrev(n2);
  for (i = 0; n1[i] != '\0' && n2[i] != '\0'; i++){
    n3[i] = (n1[i] - '0' + n2[i] - '0' + acarreo + '0') % 10;
    acarreo = (n1[i] - '0' + n2[i] - '0') / 10;
    n3[i + 1] = '\0';
  }
  if(n1[i] != '\0'){
    for (i; n1[i] != '\0'; i++){
      n3[i] = (n1[i] - '0' + acarreo + '0')  % 10;
      acarreo = (n1[i] - '0') / 10;
      n3[i + 1] = '\0';
    }
  }else if(n2[i] != '\0'){
    for (i; n2[i] != '\0'; i++){
      n3[i] = (n2[i] - '0' + acarreo + '0')  % 10;
      acarreo = (n2[i] - '0') / 10;
      n3[i + 1] = '\0';
    }
  } else if(acarreo != 0){
    n3[i] = acarreo + '0';
    n3[i + 1] = '\0';
  }
  strrev(n3);
  return n3;
}

char* fibo(char* n) {
   int i = 0, numero = 0;
   char f_1[30], f_2[30];

   for (i = 0; n[i] != '\0'; i++);

   sscanf(&numero, "%i", n);

   if(fibonaccis[numero] != '\0')
    return fibonaccis[numero];

  sprintf(&f_1, "%i", numero - 1);
  sprintf(&f_2, "%i", numero - 2);

  fibonaccis[numero] = Suma(fibo(f_1), fibo(f_2));
  return fibonaccis[numero];
}

int main() {
   int n, i;
   char numero[51];

   for(i = 0; i < 2000; i++)
    fibonaccis[i] = '\0';

  strcpy(fibonaccis[0], "0");
strcpy(fibonaccis[1], "1");
strcpy(fibonaccis[2], "1");
   printf("Ingrese el valor de n: ");
   scanf("%d", &n);
   sprintf(numero, "i", n - 1);
   printf("El termino %d de Fibonacci es: %s\n", n, fibo(numero));
}
