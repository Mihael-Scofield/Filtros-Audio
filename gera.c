#include <stdio.h>
#include <stdint.h>
#include <math.h>

typedef struct wav {
  char      ChunkID[4]; // “RIFF” constante, identifica o tipo de arquivo
  uint32_t  ChunkSize;  // filesize - 8 tam arquivo em bytes, 
  char      Format[4];  // “WAVE” constante, define o formato interno
  char      SubChunk1ID[4]; // “fmt ” constante, cabeçalho do chunk
  uint32_t  SubChunk1Size;  // 16 (PCM) tamanho deste chunk
  uint16_t  format;     // 1 (PCM) codificação utilizada
  uint16_t  chan;       // 1, 2  número de canais de áudio
  uint32_t  srate;      // 44100, Taxa de amostragem (amostras/seg)
  uint32_t  brate;      // taxa de bytes por segundo
  uint16_t  balign;     // número de bytes por amostra (soma todos os canais)
  uint16_t  bps;        // 16, 32 bits por amostra, por canal
  char      SubChunk2ID[4]; // “data” constante, cabeçalho do chunk
  uint32_t  SubChunk2Size;  // espaço ocupado pelas amostras, em bytes 
} wav_t;

#define DURA 20                  // MAX duracao em segundos

#define S_RATE 44100

#define ONE_SEC S_RATE/2         // 1 segundo, 2 canais

#define N_SAMP (S_RATE * DURA)   // numero de amostras

#define AUDIO_SZ (N_SAMP * 2)    // 2 canais de 16 bits 

#define FREQ 400.0

#define STEP (2.0 * M_PI * FREQ / (float)S_RATE)

#define LEFT  0
#define RGHT  1

wav_t header;

short samp[AUDIO_SZ];


int main(int argc, char *argv[]) {

  FILE *f;
  wav_t *h;
  int status, i, j, val, so_far, end;
  float angle, step;
  
  // 400Hz, 4 sec of 1/2 ampl
  step   = STEP;
  angle  = 0.0;
  so_far = 0;
  end    = 4*ONE_SEC;
  for (i = so_far; i < end; i += 2) {
    samp[i+LEFT] = samp[i+RGHT] = (short)(sin(angle) * (float)INT16_MAX / 2.0);
    angle = angle + step;
  } 
  so_far = i;
  // printf("%d ", so_far);
  
  // 400Hz, 4 sec of 1/4 ampl
  end += 4*ONE_SEC;
  for (j = so_far; j < end; j += 2) {
    samp[j+LEFT] = samp[j+RGHT] = (short)(sin(angle) * (float)INT16_MAX / 4.0);
    angle = angle + step;
  } 
  so_far = j;
  //printf("%d ", so_far);
  
#if 1
  // 400Hz, 4 sec of 1/2 ampl, LEFT
  end += 4*ONE_SEC;
  for (i = so_far; i < end; i += 2) {
    val = (short)(sin(angle) * (float)INT16_MAX / 2.0);
    samp[i+LEFT] = val;
    samp[i+RGHT] = 0; // -1 * (val >> 4); // fase oposta (180g) e atenuado 16x
    angle = angle + step;
  } 
  so_far = i;
  // printf("%d ", so_far);
#endif

#if 1
  // 400Hz, 4 sec of 1/2 ampl, RIGHT
  end += 4*ONE_SEC;
  for (j = so_far; j < end; j += 2) {
    val = (short)(sin(angle) * (float)INT16_MAX / 2.0);
    samp[j+RGHT] = val;
    samp[j+LEFT] = 0; //-1 * (val >> 4); // fase oposta (180g) e atenuado 16x
    angle = angle + step;
  } 
  so_far = j;
  // printf("%d ", so_far);
#endif

  // printf("\n");

  h = &header;

  h->ChunkID[0] = 'R'; // “RIFF” constante, identifica o tipo de arquivo
  h->ChunkID[1] = 'I';
  h->ChunkID[2] = 'F';
  h->ChunkID[3] = 'F';

  h->ChunkSize = (so_far*sizeof(short)) + 36; // filesize - 8 tam em bytes

  h->Format[0] = 'W';  // “WAVE” constante, define o formato interno
  h->Format[1] = 'A';
  h->Format[2] = 'V';
  h->Format[3] = 'E';

  h->SubChunk1ID[0] = 'f'; // “fmt ” constante, cabeçalho do chunk
  h->SubChunk1ID[1] = 'm';
  h->SubChunk1ID[2] = 't';
  h->SubChunk1ID[3] = ' ';

  h->SubChunk1Size = 16; // 16 (PCM) tamanho deste chunk
  h->format = 1;         // 1 (PCM) codificação utilizada
  h->chan = 2;           // número de canais de áudio
  h->srate = S_RATE;     // 44100 Taxa de amostragem (amostras/seg)
  h->brate = S_RATE; //45328; // S_RATE * 2 * 2; // taxa de bytes por segundo
  h->balign = 4;         // num bytes por amostra (soma todos os canais)
  h->bps = 16;           // bits por amostra, por canal

  h->SubChunk2ID[0] = 'd'; // “data” constante, cabeçalho do chunk
  h->SubChunk2ID[1] = 'a';
  h->SubChunk2ID[2] = 't';
  h->SubChunk2ID[3] = 'a';

  h->SubChunk2Size = (so_far*sizeof(short)); // espaço ocupado pelas amostras

  f = fopen( "seno.wav", "w");

  if (f == NULL) {
    fprintf(stderr, "\n\tErro ao abrir o arquivo\n\n");
    return 1;
  }

  status = fwrite( h, sizeof(wav_t), 1, f);
	
  if (status != 1) {
    fprintf(stderr, "\n\tErro ao gravar cabecalho %d\n\n", status);
    return 1;
  }

  status = fwrite( samp, (so_far*sizeof(short)), 1, f);
	
  if (status != 1) {
    fprintf(stderr, "\n\tErro ao gravar audio %d\n\n", status);
    return 1;
  }
}