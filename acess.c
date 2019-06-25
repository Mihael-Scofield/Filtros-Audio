// Mihael Scofield de Azevedo || GRR - 20182621 
// Implementacao de funcoes para acessar os arquivos WAV.

#include <stdio.h>

#include "acess.h"

/* Preenche cabecalho do header */
void preenc_cab (struct wav *h, FILE *arq) {
	fread (h, sizeof(struct wav), 1, arq);
}

/* Escreve cabecalho do Header no arquivo de saida */
void escreve_cab (struct wav *h, FILE *arq) {
	fwrite(h, sizeof(struct wav), 1, arq);
}