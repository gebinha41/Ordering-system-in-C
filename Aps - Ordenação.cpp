#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CalcTempoExecucao.h"

// Estrutura para representar a criação de arquivos
struct ClasseCriacaoArquivoExemplo {
    // Você pode adicionar atributos aqui, se necessário
};

// Função para inicializar a estrutura (se necessário)
void inicializarClasse(struct ClasseCriacaoArquivoExemplo *classe) {
    // Inicialização de atributos, se houver
}

// Função para gravar texto em um arquivo
void gravarTexto(const char *nomeArquivo, const char *texto) {
    FILE *file = fopen(nomeArquivo, "a"); // Abre o arquivo em modo append
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }
    fprintf(file, "%s\n", texto);
    fclose(file);
}

// Função para criar um arquivo de exemplo
void criarArquivo(const char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "w"); // Abre o arquivo para escrita
    if (file == NULL) {
        perror("Erro ao criar o arquivo");
        return;
    }
    fprintf(file, "Este é um exemplo de arquivo criado.\n");
    fclose(file);
}

// Função para gerar um arquivo com coordenadas desordenadas
void gerarArquivoCoordenadaDesordenada(double *coordenadasGeradas, int numCoordenadas, const char *nomeArquivo) {
    for (int i = 0; i < numCoordenadas; i += 2) {
        char coordenadas[100]; // Buffer para coordenadas
        snprintf(coordenadas, sizeof(coordenadas), "(%.6f, %.6f)", coordenadasGeradas[i], coordenadasGeradas[i + 1]);
        gravarTexto(nomeArquivo, coordenadas);
    }
}

// Função para gerar um arquivo com coordenadas ordenadas
void gerarArquivoOrdenado(double *arrQuick, int tamanho, const char *nomeArquivo) {
    char coordenas[200]; // Buffer para coordenadas
    int contador = 0;

    for (int i = 0; i < tamanho; i++) {
        char buffer[20]; // Buffer temporário para uma coordenada
        snprintf(buffer, sizeof(buffer), "%.6f", arrQuick[i]);

        if (contador == 0) {
            coordenas[0] = '\0'; // Limpa o buffer
        }

        strcat(coordenas, buffer); // Adiciona a coordenada ao buffer

        if (contador < 9) {
            strcat(coordenas, ", "); // Adiciona vírgula se não for o último item da linha
            contador++;
        } else {
            gravarTexto(nomeArquivo, coordenas); // Grava as coordenadas no arquivo
            contador = 0; // Reinicia o contador
        }
    }

    // Grava o restante, se houver
    if (contador > 0) {
        gravarTexto(nomeArquivo, coordenas);
    }
}

// Função exemplo que simula o tempo de execução de um algoritmo
long meuAlgoritmo(void) {
    // Implementação do algoritmo
    return 42; // Exemplo de retorno
}

// Função principal
int main() {
    struct ClasseCriacaoArquivoExemplo exemplo;
    inicializarClasse(&exemplo); // Inicializa a estrutura, se necessário

    // Criar um arquivo de exemplo
    criarArquivo("exemplo.txt");

    // Exemplo de coordenadas desordenadas
    double coordenadas[] = {34.123456, -118.123456, 35.654321, -119.654321}; 
    int numCoordenadas = sizeof(coordenadas) / sizeof(coordenadas[0]);

    gerarArquivoCoordenadaDesordenada(coordenadas, numCoordenadas, "coordenadas.txt");

    // Exemplo de coordenadas ordenadas
    double arrQuick[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    int tamanho = sizeof(arrQuick) / sizeof(arrQuick[0]);

    gerarArquivoOrdenado(arrQuick, tamanho, "coordenadas_ordenadas.txt");

    // Cálculo do tempo de execução
    CalcTempoExecucao calc;
    calc.calcularTempoAlgoritmo = meuAlgoritmo;

    long tempo = calc.calcularTempoAlgoritmo();
    printf("Tempo de execução: %ld\n", tempo);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define COORD_X 180
#define COORD_Y 90

typedef struct {
    double latitude;
    double longitude;
    int quantidade;
    double *coordenadas; // Alocaremos um vetor dinâmico para armazenar as coordenadas
} GeradorCoordenada;

// Função para criar um gerador de coordenadas
GeradorCoordenada* criarGeradorCoordenada(int qtd) {
    GeradorCoordenada *gerador = (GeradorCoordenada*)malloc(sizeof(GeradorCoordenada));
    gerador->quantidade = qtd;
    gerador->coordenadas = (double*)malloc(sizeof(double) * qtd * 2); // 2 para latitude e longitude
    return gerador;
}

// Função para liberar a memória alocada para o gerador de coordenadas
void liberarGeradorCoordenada(GeradorCoordenada *gerador) {
    free(gerador->coordenadas);
    free(gerador);
}

// Função para gerar uma coordenada aleatória
double gerarCoordenadaAleatoria(int n) {
    double coordenada = ((double)rand() / RAND_MAX) * (2 * n) - n; // Gera coordenada entre -n e n
    return round(coordenada * 1000000.0) / 1000000.0; // Arredonda para 6 casas decimais
}

// Função para gerar coordenadas
void gerarCoordenadas(GeradorCoordenada *gerador) {
    for (int i = 0; i < gerador->quantidade; i++) {
        gerador->latitude = gerarCoordenadaAleatoria(COORD_Y);
        gerador->longitude = gerarCoordenadaAleatoria(COORD_X);
        gerador->coordenadas[i * 2] = gerador->latitude; // Armazena latitude
        gerador->coordenadas[i * 2 + 1] = gerador->longitude; // Armazena longitude
    }
}

// Função para formatar coordenadas como string
void formataCoordenadas(double latitude, double longitude, char *buffer) {
    sprintf(buffer, "%.6f, %.6f", latitude, longitude);
}

// Função para exibir todas as coordenadas
void exibirCoordenadas(GeradorCoordenada *gerador) {
    char buffer[50];
    for (int i = 0; i < gerador->quantidade; i++) {
        formataCoordenadas(gerador->coordenadas[i * 2], gerador->coordenadas[i * 2 + 1], buffer);
        printf("Coordenada %d: %s\n", i + 1, buffer);
    }
}

// Função para gravar texto em um arquivo
void gravarTexto(const char *nomeArquivo, const char *texto) {
    FILE *file = fopen(nomeArquivo, "a"); // Abre o arquivo em modo append
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }
    fprintf(file, "%s\n", texto);
    fclose(file);
}

// Função principal
int main() {
    srand(time(NULL)); // Semente para números aleatórios

    int quantidade = 5; // Número de coordenadas a serem geradas
    GeradorCoordenada *gerador = criarGeradorCoordenada(quantidade);

    gerarCoordenadas(gerador);
    exibirCoordenadas(gerador);

    // Salvar coordenadas em um arquivo
    for (int i = 0; i < quantidade; i++) {
        char buffer[50];
        formataCoordenadas(gerador->coordenadas[i * 2], gerador->coordenadas[i * 2 + 1], buffer);
        gravarTexto("coordenadas.txt", buffer);
    }

    liberarGeradorCoordenada(gerador); // Libera a memória
    return 0;
}



