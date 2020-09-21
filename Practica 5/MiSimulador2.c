#include "CacheSim.h"

/* Posa aqui les teves estructures de dades globals
 * per mantenir la informacio necesaria de la cache
 * */
typedef struct
{
            unsigned int TAG;
            unsigned char v;
} via;

typedef struct
{
            via via[2];
            unsigned char lru;
} conjunt;

conjunt cache[64];
unsigned int fallos = 0;
unsigned int aciertos = 0;

/* La rutina init_cache es cridada pel programa principal per
 * inicialitzar la cache.
 * La cache es inicialitzada al comen�ar cada un dels tests.
 * */
void init_cache ()
{
    totaltime=0.0;
	/* Escriu aqui el teu codi*/
  for (int i = 0; i<64; ++i)
  {
    for (int j = 0; j < 2; ++j)
    {
      cache[i].via[j].v = false;
    }
  }
}

/* La rutina reference es cridada per cada referencia a simular */
void reference (unsigned int address)
{
	unsigned int byte;
	unsigned int bloque_m;
	unsigned int conj_mc;
	unsigned int via_mc;
	unsigned int tag;
	unsigned int miss;	   // boolea que ens indica si es miss
	unsigned int replacement;  // boolea que indica si es reempla�a una linia valida
	unsigned int tag_out;	   // TAG de la linia reempla�ada
	float t1,t2;		// Variables per mesurar el temps (NO modificar)

	t1=GetTime();
	/* Escriu aqui el teu codi */

  byte = address & 0x0000001f;
  bloque_m = address >> 5;
  conj_mc = bloque_m & 0x0000003f;
  tag = bloque_m >> 6;
  miss = ((cache[conj_mc].via[0].TAG == tag & !cache[conj_mc].via[0].v  & cache[conj_mc].via[1].TAG == tag & !cache[conj_mc].via[1].v) | (cache[conj_mc].via[0].TAG != tag  & cache[conj_mc].via[1].TAG != tag));
  replacement = (miss & cache[conj_mc].via[0].v & cache[conj_mc].via[1].v);
  if (!miss) //hit
  {
    aciertos++;
    for (int i = 0; i<2; ++i)
    {
      if (cache[conj_mc].via[i].TAG == tag & cache[conj_mc].via[i].v)
      {
        via_mc = i;
        cache[conj_mc].lru = (i+1)%2;
      }
    }
  }
  else
  {
    fallos++;
    if (!replacement) // conj parcialmente vacio + miss
    {
      if (!cache[conj_mc].via[0].v)
      {
        cache[conj_mc].via[0].TAG = tag;
        via_mc = 0;
        cache[conj_mc].via[0].v = true;
      }
      else
      {
        cache[conj_mc].via[1].TAG = tag;
        via_mc = 1;
        cache[conj_mc].lru = 0;
        cache[conj_mc].via[1].v = true;
      }
    }
    else //remplaça
    {
      via_mc = cache[conj_mc].lru;
      tag_out = cache[conj_mc].via[via_mc].TAG;
      cache[conj_mc].via[via_mc].TAG = tag;
      cache[conj_mc].lru = (via_mc+1)%2;
    }
  }

	/* La funcio test_and_print escriu el resultat de la teva simulacio
	 * per pantalla (si s'escau) i comproba si hi ha algun error
	 * per la referencia actual. Tamb� mesurem el temps d'execuci�
	 *
   */
	t2=GetTime();
	totaltime+=t2-t1;
	test_and_print2 (address, byte, bloque_m, conj_mc, via_mc, tag,
			miss, replacement, tag_out);
}

/* La rutina final es cridada al final de la simulacio */
void final ()
{
 	/* Escriu aqui el teu codi */
  printf("aciertos: %u \n fallos: %u \n", aciertos, fallos );

}
