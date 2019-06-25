// Mihael Scofield de Azevedo || GRR - 20182621
// Imprime as principais informacoes do audio.

#include <stdio.h>
#include <stdint.h>

#include "acess.h"
#include "comandos.h"
#include "tratamento.h"

int main (int argc, char **argv, char **envp) {
	struct wav header;
	struct wav *h = &header;
	uint32_t spc; // Samples/Channel.
	float vol = 0.0; // Proveniente de Wavvol, sem uso aqui.
	FILE *arqi, *arqo;

	ler_arg(argc, argv, &arqi, &arqo, &vol); // Ler os comandos.
	preenc_cab(h, arqi);
	spc = (h->SubChunk2Size/h->BAlign); // Calculo pra sair o spc.

	/* Impressao das informacoes */
	printf ("riff tag       : 'RIFF' \n");
	printf ("riff size      : %u \n", h->ChunkSize);
	printf ("wave tag       : 'WAVE' \n");
	printf ("form tag       : 'fmt' \n");
	printf ("fmt_size       : %u\n", h->SubChunk1Size);
	printf ("audio_format   : %u\n", h->AFormat);
	printf ("num_channels   : %u\n", h->Channels);
	printf ("sample_rate    : %u\n", h->SRate);
	printf ("byte_rate      : %u\n", h->BRate);
	printf ("block_align    : %u\n", h->BAlign);
	printf ("bits_per_sample: %u\n", h->bps);
	printf ("data tag       : 'data' \n ");
	printf ("data size      : %u\n", h->SubChunk2Size);
	printf ("samples/channel: %u\n", spc);
}
