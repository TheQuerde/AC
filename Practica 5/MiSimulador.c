#include "CacheSim.h"

/* Posa aqui les teves estructures de dades globals
 * per mantenir la informacio necesaria de la cache
 * */
 unsigned int tag_mem [128]; //memoria de etiquetas -1 equivale a no inicialicado

 unsigned int fallos = 0;
 unsigned int aciertos = 0;

/* La rutina init_cache es cridada pel programa principal per
 * inicialitzar la cache.6,0341937016,034193701
 * La cache es inicialitzada al comen�ar cada un dels tests.
 * */
void init_cache ()
{
    totaltime=0.0;
	/* Escriu aqui el teu codi */
  for (int i = 0; i<128; ++i) tag_mem[i] = 0xffffffff; //vaciar memoria de etiquetas
}

/* La rutina reference es cridada per cada referencia a simular */
void reference (unsigned int address)
{
	unsigned int byte;
	unsigned int bloque_m;
	unsigned int linea_mc;
	unsigned int tag;
	unsigned int miss;	   // boolea que ens indica si es miss
	unsigned int replacement;  // boolea que indica si es reempla�a una linia valida
	unsigned int tag_out;	   // TAG de la linia reempla�ada
	float t1,t2;		// Variables per mesurar el temps (NO modificar)

	t1=GetTime();
	/* Escriu aqui el teu codi */

  replacement = false;
  byte = address & 0x0000001f;
  bloque_m = address & 0xffffffe0;
  linea_mc = bloque_m >> 5;
  linea_mc = linea_mc & 0x0000007f;
  tag = bloque_m >> 12;
  bloque_m = bloque_m >>5;
  miss = (tag_mem[linea_mc] != tag);
  replacement = (miss & tag_mem[linea_mc] != 0xffffffff);
  if (miss)
  {
    if (replacement) tag_out = tag_mem[linea_mc];
    tag_mem[linea_mc] = tag;
    fallos++;
  }
  else aciertos++;
  /* La funcio test_and_print escriu el resultat de la teva simulacio
	 * per pantalla (si s'escau) i comproba si hi ha algun error
	 * per la referencia actual. Tamb� mesurem el temps d'execuci�
	 *
   */
	t2=GetTime();
	totaltime+=t2-t1;
	test_and_print (address, byte, bloque_m, linea_mc, tag,
			miss, replacement, tag_out);
}

/* La rutina final es cridada al final de la simulacio */
void final ()
{
 	/* Escriu aqui el teu codi */
  printf("aciertos: %u \n fallos: %u \n", aciertos, fallos );

}
