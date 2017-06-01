#include <stdio.h>

void
hanoi (int numero_de_discos, char *x, char *y, char *z, int *movimientos)
{
  if (numero_de_discos > 0)
    {
      hanoi (numero_de_discos - 1, x, z, y, movimientos);
      (*movimientos)++;
      printf ("%d) De %s a %s\n", *movimientos, x, y);
      hanoi (numero_de_discos - 1, z, y, x, movimientos);
    }
}

void
main ()
{
  int numero_de_discos, movimientos = 0;
  printf ("Introduce el número de discos: ");
  scanf ("%d", &numero_de_discos);
  printf("\nTorre 1 = Origen\nTorre 2 = Auxiliar\nTorre 3 = Destino\n\n");
  hanoi (numero_de_discos, "Torre 1", "Torre 3", "Torre 2", &movimientos);
}
