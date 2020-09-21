#include <stdio.h>

#define N 200000
#define tam 16*1024*1024

int i, j, step;
unsigned char v[tam];

void InitCache(int cod);
void Referencia(unsigned char *dir);
int Referencias();
int Fallos();


int main()
{  int i, j, step;
   int refs, misses;


  for (step=1; step<=128*64; step++) {

    InitCache(0xf51b74cf);

    i = 0;

    for (j=0; j<N; j++) {
      Referencia((unsigned char *)&v[i]);     // acceso a v[i]
      i = i + step;
      if (i >= tam) i = 0;
    }

    refs = Referencias();
    misses = Fallos();
    printf("%6d\n", misses);

  }

  return 0;
}
