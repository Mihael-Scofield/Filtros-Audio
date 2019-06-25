// Mihael Scofield de Azevedo || GRR - 20182621 
/* Cabecalho de estruturas de dados comuns */

#include <stdint.h>

struct wav {
	char ChunkID[4]; // "RIFF" Constante, identifica o tipo de arquivo.
	uint32_t ChunkSize; // Tamanho do arquivo em bytes, sem considerar este chunk.
	char Format[4]; // "WAVE" Constante, define o formato interno.
	char SubChunk1ID[4]; // "fmt" Constante, cabeçalho do Chunk.
	uint32_t SubChunk1Size; // 16 (PCM) Tamanho deste chunk.
	uint16_t AFormat; // 1 (PCM), codificacao utilizada.
	uint16_t Channels; // 1, 2, numero de canais de audio.
	uint32_t SRate; // 44100, etc, taxa de amostragem (amostras/seg)
	uint32_t BRate; // Taxa de Bytes por segundo.
	uint16_t BAlign; // Numero de bytes por amostra (soma todos os canais)
	uint16_t bps; // 8,16,32... Bits por amostra, por canal.
	char SubChunk2ID[4]; // "data", Constante, cabeçalho do chunk.
	uint32_t SubChunk2Size; // Espaço ocupado pelas amostras, em bytes.
} ;

// EOF -----------------------------------------------------