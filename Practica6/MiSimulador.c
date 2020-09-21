#include "CacheSim.h"

/* Posa aqui les teves estructures de dades globals
 * per mantenir la informacio necesaria de la cache
 * */

 typedef struct
 {
             unsigned int TAG;
             unsigned char v;
 } linea;
 linea cache [128];

 unsigned int fallos = 0;
 unsigned int aciertos = 0;

/* La rutina init_cache es cridada pel programa principal per
 * inicialitzar la cache.
 * La cache es inicialitzada al comen�ar cada un dels tests.
 * */
void init_cache ()
{
	/* Escriu aqui el teu codi */

	for (int i = 0; i<128; ++i) cache[i].v = false; // reset a la memoria cache

}

/* La rutina reference es cridada per cada referencia a simular */
void reference (unsigned int address, unsigned int LE)
{
	unsigned int byte;
	unsigned int bloque_m;
	unsigned int linea_mc;
	unsigned int tag;
	unsigned int miss;
	unsigned int lec_mp;
	unsigned int mida_lec_mp;
	unsigned int esc_mp;
	unsigned int mida_esc_mp;
	unsigned int replacement;
	unsigned int tag_out;

	/* Escriu aqui el teu codi */
	byte = address & 0x0000001f;
	bloque_m = address & 0xffffffe0;
	linea_mc = bloque_m >> 5;
	linea_mc = linea_mc & 0x0000007f;
	tag = bloque_m >> 12;
	bloque_m = bloque_m >>5;
	miss = !(cache[linea_mc].v & cache[linea_mc].TAG == tag);
	replacement = (miss & LE == 0 & cache[linea_mc].v);

	if (LE == 0) // lectura
	{
		if (miss)
		{
			if (replacement)
			{
				tag_out = cache[linea_mc].TAG;
			}
			lec_mp = true;
			mida_lec_mp = 32;
			cache[linea_mc].TAG = tag;
			cache[linea_mc].v = true;
      fallos++;
		}
		else // hit
		{
			lec_mp = false;
			mida_lec_mp = 0;
		}
		esc_mp = false;
		mida_esc_mp = 0;
    aciertos++;
	}
	else // escriptura
	{
		lec_mp = false;
		mida_lec_mp = 0;
		esc_mp = true;
		mida_esc_mp = 1;
	}
	/* La funcio test_and_print escriu el resultat de la teva simulacio
	 * per pantalla (si s'escau) i comproba si hi ha algun error
	 * per la referencia actual
	 * */
	test_and_print (address, LE, byte, bloque_m, linea_mc, tag,
			miss, lec_mp, mida_lec_mp, esc_mp, mida_esc_mp,
			replacement, tag_out);
}

/* La rutina final es cridada al final de la simulacio */
void final ()
{
 	/* Escriu aqui el teu codi */
    printf("aciertos: %u \n fallos: %u \n", aciertos, fallos );
}
