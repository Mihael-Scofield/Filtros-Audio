// Mihael Scofield de Azevedo || GRR - 20182621
// Reverte o áudio.

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>

#include "comandos.h"
#include "acess.h"
#include "tratamento.h"

int main (int argc, char **argv) {
	struct wav header;
	int16_t *pdata, *out;
	int samples;
	float vol = 0.0; // Proveniente de Wavvol, nao possui uso aqui.
	FILE *arqi, *arqo;

	/* Rotina habitual referente a cabecalho e linha de comando */
	ler_arg(argc, argv, &arqi, &arqo, &vol); // Ler os comandos.
	preenc_cab(&header, arqi); // Preencher cabecalho da struct.

    samples = header.SubChunk2Size/sizeof(uint16_t);

	/* Carregamento de data */
	pdata = malloc(header.SubChunk2Size); // Vetor de tamanho dos dados.
    out = malloc(header.SubChunk2Size);
	if(pdata == 0) {
		printf ("Erro na criacao de 'Audio Data'.\n");
		return 1;
	}
	fseek(arqi, sizeof(struct wav) + 1, SEEK_SET); // Vai ate o inicio dos dados.
	fread(pdata, header.SubChunk2Size, 1, arqi); // Carrega vetor com dados.

	/* Tratamento de Audio */
    wavrev(out, pdata, samples); // Inverte audio.
	fclose (arqi); // Acabei com arquivo de entrada.

	/* Preenchimento do arquivo de saida */
	escreve_cab(&header, arqo); // Copia cabecalho.
	fseek(arqo, sizeof(struct wav)+1, SEEK_SET);
	fwrite(out, header.SubChunk2Size, 1, arqo); // Escreve data.

	fclose(arqo);
	free(pdata);

	return 0;
}