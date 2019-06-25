// Mihael Scofield de Azevedo || GRR - 20182621
/* Implementações para tratamento de linha de comando */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>

#include "comandos.h"

/* Le os argumentos passados pelo usuario */
int ler_arg (int argc, char **argv, FILE **pti, FILE **pto, float *vol) {
	int opc; // ikey, okey; // Opcoes e chaves.
	char *arg; // Recebera argumento.
	// FILE *arqi, *arqo; // Vem do filtro que a chama

	/* Leitura dos argumentos passados */
	while ((opc = getopt (argc, argv, "i:o:l:")) != -1) {
		switch (opc) {

			case 'i': // Usuario passou -i.
				// ikey = 1;
				arg = optarg; // Argumento da opcao (argv[n+1]).
				*pti = fopen (arg, "r"); // Apenas leitura.
				if (pti == NULL) {
					fprintf(stderr, "\n\tErro ao abrir o arquivo\n\n");
					return 1;
				}
				break;

			case 'o': // Usuario passou -o.
				// okey = 1;
				arg = optarg;
				*pto = fopen (arg, "w"); // Apenas escrita.
				if (pto == NULL) {
					fprintf(stderr, "\n\tErro ao abrir o arquivo\n\n");
					return 1;
				}
				break;

			case 'l': // Usuario passou -l.
				*vol = convert_string(optarg);
				break;

			case '?': // Diagnostico de erros.
				if ( (optopt == 'i') || (optopt == 'o') ) // Esqueceu argumento.
						fprintf (stderr, "Opcao '-%c' requer argumento.\n", optopt);
				else
					if (isprint (optopt)) // Nao reconhecido.
						fprintf (stderr, "Opcao '-%c' desconhecida.\n", optopt);
					else // Reconhecido, mas sem opcoes de uso.
						fprintf (stderr, "Caractere '\\x%x' de opcao desconhecido.\n", optopt);
				return 1;
		}
	}

	/* Stdin ou Stdout */

	return 0;
}

/* Converte uma String em um Float type */
float convert_string (char *pc) {
	int i, cont;
	float aux, resultado = 0;

	/* Preparando terreno. */
	cont = 0;
	for(i = 0; ( (pc[i] != '.') && (pc[i] != '\0') ); i++) { // Descobre quantas casas inteiras existem. 
		cont++;
	}
	aux = (float)pow(10, cont-1);

	/* Conversao propriamente dita. */ 
	for(i = 0; ( (pc[i] != '.') && (pc[i] != '\0') ); i++) { // Primeira passado, ate o ponto.
		resultado += ((pc[i] - '0') * aux);
		aux = (aux/10);
	}

	if (!(pc[i] == '\0')){
		for(i += 1; pc[i] != '\0'; i++){
			resultado += ((pc[i] - '0') * aux);
			aux = (aux/10);
		}
	}
	return resultado;
}