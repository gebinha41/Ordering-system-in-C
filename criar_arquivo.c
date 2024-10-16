#include <stdio.h>
#include "criar_arquivo.h"

void gerarArquivoCoordenadaDesordenada(double* coordenadas, int numCoordenadas, const char* nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "w");
    if (file == NULL) {
        perror("Erro ao criar o arquivo");
        return;
    }

    for (int i = 0; i < numCoordenadas; i += 2) {
        fprintf(file, "Latitude: %.4f, Longitude: %.4f\n", coordenadas[i], coordenadas[i + 1]);
    }

    fclose(file);
}
