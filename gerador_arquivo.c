#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double latitude;
    double longitude;
} Coordenada;

typedef struct {
    const char *path;
} GeradorArquivo;

// Função para formatar coordenadas
void formata_coordenadas(double latitude, double longitude, char *buffer) {
    sprintf(buffer, "%lf, %lf", latitude, longitude);
}

// Função para gravar texto em um arquivo
void gravar_texto(const GeradorArquivo *gerador, const char *nome_arquivo, const char *texto) {
    FILE *file;
    file = fopen(nome_arquivo, "a");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }
    fprintf(file, "%s\n", texto);
    fclose(file);
}

// Função para gerar arquivo de coordenadas desordenadas
void gerar_arquivo_coordenada_desordenada(GeradorArquivo *gerador, Coordenada *coordenadas, size_t tamanho, const char *nome_arquivo) {
    char buffer[50];
    for (size_t i = 0; i < tamanho; i++) {
        formata_coordenadas(coordenadas[i].latitude, coordenadas[i].longitude, buffer);
        gravar_texto(gerador, nome_arquivo, buffer);
    }
}

// Função para gerar arquivo de coordenadas ordenadas
void gerar_arquivo_ordenado(GeradorArquivo *gerador, double *arr, size_t tamanho, const char *nome_arquivo) {
    char buffer[50];
    for (size_t i = 0; i < tamanho; i++) {
        sprintf(buffer, "%lf", arr[i]);
        gravar_texto(gerador, nome_arquivo, buffer);
    }
}

// Função principal
int main() {
    GeradorArquivo gerador;
    gerador.path = "C:/Temp/"; // Defina o caminho desejado

    Coordenada coordenadas[] = {
        {34.0522, -118.2437},
        {40.7128, -74.0060},
        {51.5074, -0.1278}
    };
    size_t tamanho_coordenadas = sizeof(coordenadas) / sizeof(coordenadas[0]);
    
    // Gerar arquivo com coordenadas desordenadas
    gerar_arquivo_coordenada_desordenada(&gerador, coordenadas, tamanho_coordenadas, "coordenadas_desordenadas.txt");

    // Exemplo de coordenadas ordenadas
    double coordenadas_ordenadas[] = {3.0, 1.5, 2.2, 4.8, 2.9};
    size_t tamanho_ordenadas = sizeof(coordenadas_ordenadas) / sizeof(coordenadas_ordenadas[0]);

    // Gerar arquivo com coordenadas ordenadas
    gerar_arquivo_ordenado(&gerador, coordenadas_ordenadas, tamanho_ordenadas, "coordenadas_ordenadas.txt");

    return 0;
}
