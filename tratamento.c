// Mihael Scofield de Azevedo || GRR - 20182621
// Tratamentos de audio.

#include <stdio.h>
#include <stdint.h>

#include "tratamento.h"

/* Tratamento de Wavrev, inverte a data. */
void wavrev (int16_t *out, int16_t *pdata, int samples) {
    for (int i = 0; i < samples; ++i) {
    	out[i] = pdata[samples-i-1];
    }	
}


/* Tratamento de Wavvol, aumenta o volume */
void wavvol (int16_t *out, int16_t *pdata, int samples, float vol) {
    for (int i = 0; i < samples; i++) {
    	out[i] = (int16_t)(pdata[i] * vol);
    }
}