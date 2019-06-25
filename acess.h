// Mihael Scofield de Azevedo || GRR - 20182621 
// Cabecalho funcoes para acessar os arquivos WAV.

#include "structs.h"

/* Preenche cabecalho do header */
void preenc_cab (struct wav *h, FILE *arq) ;

/* Escreve cabecalho do Header no arquivo de saida */
void escreve_cab (struct wav *h, FILE *arq) ;

// EOF -----------------------------------------------------