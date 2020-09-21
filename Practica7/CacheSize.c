#include <stdio.h>

#define N 200000
#define tam 16*1024*1024

#define LINE_SIZE 128

int i, j, limite;
unsigned char v[tam];

void InitCache(int cod);
void Referencia(unsigned char *dir);
int Referencias();
int Fallos();

int refs, misses;

int main()
{  int i, j;


  for (limite=256; limite <= 1024*1000; limite+=256) {

    InitCache(0xf51b74cf);

    i = 0;
    for (j=0; j<N; j++) {
      Referencia((unsigned char *)&v[i]);     // acceso a v[i]
      i=i+LINE_SIZE;
      if (i >= limite) i=0;
    }

    refs = Referencias();
    misses = Fallos();

    printf("%6d\n", misses);

  }

  return 0;
}
