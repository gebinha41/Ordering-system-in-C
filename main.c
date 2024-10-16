#include <stdio.h>
#include "criar_arquivo.h"

int main() {
    const char* nomeArquivo = "coordenadas.txt";
    double coordenadas[] = {34.0522, -118.2437, 40.7128, -74.0060}; // Exemplo de coordenadas
    int numCoordenadas = sizeof(coordenadas) / sizeof(coordenadas[0]);

    gerarArquivoCoordenadaDesordenada(coordenadas, numCoordenadas, nomeArquivo);

    printf("Arquivo gerado: %s\n", nomeArquivo);
    return 0;
}
