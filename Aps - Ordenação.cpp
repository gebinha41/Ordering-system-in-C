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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>

#define COORD_X 180
#define COORD_Y 90

typedef struct {
    double latitude;
    double longitude;
    int quantidade;
    double *coordenadas;
} GeradorCoordenada;

// Funções para o Gerador de Coordenadas (já descritas anteriormente)
GeradorCoordenada* criarGeradorCoordenada(int qtd);
void liberarGeradorCoordenada(GeradorCoordenada *gerador);
double gerarCoordenadaAleatoria(int n);
void gerarCoordenadas(GeradorCoordenada *gerador);
void exibirCoordenadas(GeradorCoordenada *gerador);
void gravarTexto(const char *nomeArquivo, const char *texto);

// Funções para os algoritmos de ordenação
void quickSort(double *arr, int low, int high);
void mergeSort(double *arr, int l, int r);
void heapSort(double *arr, int n);
void heapify(double *arr, int n, int i);
long calcularTempoExecucao(void (*sortFunc)(double*, int, int), double *arr, int param1, int param2);

// Função para criar diretórios
void criarDiretorio(const char *path) {
    #ifdef _WIN32
        _mkdir(path);
    #else
        mkdir(path, 0700);
    #endif
}

// Função para gerar arquivos
void gerarArquivoCoordenadaDesordenada(double *coordenadasGeradas, int numCoordenadas, const char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }
    for (int i = 0; i < numCoordenadas; i += 2) {
        fprintf(file, "(%.6f, %.6f)\n", coordenadasGeradas[i], coordenadasGeradas[i + 1]);
    }
    fclose(file);
}

void gerarArquivoOrdenado(double *arr, int tamanho, const char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }
    for (int i = 0; i < tamanho; i++) {
        fprintf(file, "%.6f\n", arr[i]);
    }
    fclose(file);
}

// Funções de ordenação
void quickSort(double *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(double *arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    double *L = malloc(n1 * sizeof(double));
    double *R = malloc(n2 * sizeof(double));

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(double *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void heapify(double *arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        double temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heapSort(double *arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        double temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

// Função para calcular tempo de execução
long calcularTempoExecucao(void (*sortFunc)(double*, int, int), double *arr, int param1, int param2) {
    clock_t start = clock();
    sortFunc(arr, param1, param2);
    return (long)(clock() - start) * 1000 / CLOCKS_PER_SEC;
}

// Funções do Gerador de Coordenadas (implementações aqui)
GeradorCoordenada* criarGeradorCoordenada(int qtd);
void liberarGeradorCoordenada(GeradorCoordenada *gerador);
double gerarCoordenadaAleatoria(int n);
void gerarCoordenadas(GeradorCoordenada *gerador);
void gravarTexto(const char *nomeArquivo, const char *texto);

// Função para iniciar o processo de ordenação
void iniciarProcessoOrdenacao(const char *inputNomeArquivo, int inputTamanhoArquivo) {
    char pathOrdenado[] = "C:\\Temp\\Coordenadas\\Ordenado\\";
    char pathDesordenado[] = "C:\\Temp\\Coordenadas\\Desordenado\\";

    criarDiretorio(pathOrdenado);
    criarDiretorio(pathDesordenado);

    GeradorCoordenada *geradorCoordenada = criarGeradorCoordenada(inputTamanhoArquivo);
    gerarCoordenadas(geradorCoordenada);
    
    gerarArquivoCoordenadaDesordenada(geradorCoordenada->coordenadas, geradorCoordenada->quantidade * 2, 
                                       strcat(strdup(pathDesordenado), inputNomeArquivo));

    double *arr = malloc(sizeof(double) * geradorCoordenada->quantidade * 2);
    memcpy(arr, geradorCoordenada->coordenadas, sizeof(double) * geradorCoordenada->quantidade * 2);

    double *arrQuick = malloc(sizeof(double) * geradorCoordenada->quantidade * 2);
    double *arrMerge = malloc(sizeof(double) * geradorCoordenada->quantidade * 2);
    double *arrHeap = malloc(sizeof(double) * geradorCoordenada->quantidade * 2);

    memcpy(arrQuick, arr, sizeof(double) * geradorCoordenada->quantidade * 2);
    memcpy(arrMerge, arr, sizeof(double) * geradorCoordenada->quantidade * 2);
    memcpy(arrHeap, arr, sizeof(double) * geradorCoordenada->quantidade * 2);

    long tempoExecQuickSort = calcularTempoExecucao(quickSort, arrQuick, 0, geradorCoordenada->quantidade * 2 - 1);
    long tempoExecMergeSort = calcularTempoExecucao(mergeSort, arrMerge, 0, geradorCoordenada->quantidade * 2 - 1);
    long tempoExecHeapSort = calcularTempoExecucao(heapSort, arrHeap, geradorCoordenada->quantidade * 2);

    gerarArquivoOrdenado(arrQuick, geradorCoordenada->quantidade * 2, 
                         strcat(strdup(pathOrdenado), strcat(inputNomeArquivo, "QuickSort")));
    gerarArquivoOrdenado(arrMerge, geradorCoordenada->quantidade * 2, 
                         strcat(strdup(pathOrdenado), strcat(inputNomeArquivo, "MergeSort")));
    gerarArquivoOrdenado(arrHeap, geradorCoordenada->quantidade * 2, 
                         strcat(strdup(pathOrdenado), strcat(inputNomeArquivo, "HeapSort")));

    printf("QuickSort: %ld ms\n", tempoExecQuickSort);
    printf("MergeSort: %ld ms\n", tempoExecMergeSort);
    printf("HeapSort: %ld ms\n", tempoExecHeapSort);

    liberarGeradorCoordenada(geradorCoordenada);
    free(arr);
    free(arrQuick);
    free(arrMerge);
    free(arrHeap);
}

// Função principal
int main() {
    srand(time(NULL));
    
    #include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define PATHORDENADO "C:\\Temp\\Coordenadas\\Ordenado\\"
#define PATHDESORDENADO "C:\\Temp\\Coordenadas\\Desordenado\\"

// Estrutura para gerar coordenadas
typedef struct {
    double *coordenadas;
    int quantidade;
} GeradorCoordenada;

// Estrutura para HeapSort
typedef struct {
    double *numeros;
    int tamanho;
} HeapSort;

// Função para criar um GeradorCoordenada
GeradorCoordenada* criarGeradorCoordenada(int qtd) {
    GeradorCoordenada *gerador = malloc(sizeof(GeradorCoordenada));
    gerador->quantidade = qtd;
    gerador->coordenadas = malloc(qtd * sizeof(double) * 2); // 2 para lat e long
    return gerador;
}

// Função para gerar coordenadas aleatórias
void gerarCoordenadas(GeradorCoordenada *gerador) {
    for (int i = 0; i < gerador->quantidade * 2; i += 2) {
        gerador->coordenadas[i] = ((double)rand() / RAND_MAX) * 180.0 - 90.0;  // Latitude
        gerador->coordenadas[i + 1] = ((double)rand() / RAND_MAX) * 360.0 - 180.0; // Longitude
    }
}

// Função para liberar memória do GeradorCoordenada
void liberarGeradorCoordenada(GeradorCoordenada *gerador) {
    free(gerador->coordenadas);
    free(gerador);
}

// Função para criar um objeto HeapSort
HeapSort* criarHeapSort(double *arr, int tamanho) {
    HeapSort *heapSort = malloc(sizeof(HeapSort));
    heapSort->numeros = arr;
    heapSort->tamanho = tamanho;
    return heapSort;
}

// Função para liberar memória do HeapSort
void liberarHeapSort(HeapSort *heapSort) {
    free(heapSort);
}

// Função para realizar o HeapSort
void heapSort(double *arr, int tamanho) {
    for (int i = tamanho / 2 - 1; i >= 0; i--) {
        heapify(arr, tamanho, i);
    }
    for (int i = tamanho - 1; i >= 0; i--) {
        double temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

// Função auxiliar para heapificar o array
void heapify(double *arr, int tamanho, int i) {
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < tamanho && arr[esquerda] > arr[maior]) {
        maior = esquerda;
    }
    if (direita < tamanho && arr[direita] > arr[maior]) {
        maior = direita;
    }
    if (maior != i) {
        double temp = arr[i];
        arr[i] = arr[maior];
        arr[maior] = temp;

        heapify(arr, tamanho, maior);
    }
}

// Função para calcular o tempo de execução do HeapSort
long calcularTempoHeapSort(HeapSort *heapSort) {
    clock_t start = clock();
    heapSort(heapSort->numeros, heapSort->tamanho);
    return (long)(clock() - start) * 1000 / CLOCKS_PER_SEC; // Retorna o tempo em milissegundos
}

// Função para gravar coordenadas em um arquivo
void gravarCoordenadas(const char *nomeArquivo, double *coordenadas, int tamanho) {
    FILE *file = fopen(nomeArquivo, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }
    for (int i = 0; i < tamanho; i += 2) {
        fprintf(file, "(%.6f, %.6f)\n", coordenadas[i], coordenadas[i + 1]);
    }
    fclose(file);
}

// Função principal
int main() {
    srand(time(NULL));

    // Definindo quantidade de coordenadas
    int quantidade = 10; // Exemplo de quantidade de coordenadas
    GeradorCoordenada *gerador = criarGeradorCoordenada(quantidade);
    gerarCoordenadas(gerador);
    
    // Gravar coordenadas desordenadas
    gravarCoordenadas(PATHDESORDENADO "coordenadas.txt", gerador->coordenadas, quantidade * 2);

    // Ordenar coordenadas (apenas a parte das latitudes como exemplo)
    double *arrParaOrdenar = malloc(quantidade * sizeof(double));
    for (int i = 0; i < quantidade; i++) {
        arrParaOrdenar[i] = gerador->coordenadas[i * 2]; // Pegando apenas as latitudes para ordenar
    }

    HeapSort *heapSort = criarHeapSort(arrParaOrdenar, quantidade);
    long tempoExec = calcularTempoHeapSort(heapSort);
    printf("Tempo de execução do HeapSort: %ld ms\n", tempoExec);

    // Gravar coordenadas ordenadas
    gravarCoordenadas(PATHORDENADO "coordenadas_ordenadas.txt", gerador->coordenadas, quantidade * 2);

    // Liberar memória
    liberarGeradorCoordenada(gerador);
    liberarHeapSort(heapSort);
    free(arrParaOrdenar);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PATHORDENADO "C:\\Temp\\Coordenadas\\Ordenado\\"
#define PATHDESORDENADO "C:\\Temp\\Coordenadas\\Desordenado\\"

// Estrutura para gerar coordenadas
typedef struct {
    double *coordenadas;
    int quantidade;
} GeradorCoordenada;

// Estrutura para MergeSort
typedef struct {
    double *v;
    double *w;
    int tamanho;
} MergeSort;

// Função para criar um GeradorCoordenada
GeradorCoordenada* criarGeradorCoordenada(int qtd) {
    GeradorCoordenada *gerador = malloc(sizeof(GeradorCoordenada));
    gerador->quantidade = qtd;
    gerador->coordenadas = malloc(qtd * sizeof(double) * 2); // 2 para lat e long
    return gerador;
}

// Função para gerar coordenadas aleatórias
void gerarCoordenadas(GeradorCoordenada *gerador) {
    for (int i = 0; i < gerador->quantidade * 2; i += 2) {
        gerador->coordenadas[i] = ((double)rand() / RAND_MAX) * 180.0 - 90.0;  // Latitude
        gerador->coordenadas[i + 1] = ((double)rand() / RAND_MAX) * 360.0 - 180.0; // Longitude
    }
}

// Função para liberar memória do GeradorCoordenada
void liberarGeradorCoordenada(GeradorCoordenada *gerador) {
    free(gerador->coordenadas);
    free(gerador);
}

// Função para criar um objeto MergeSort
MergeSort* criarMergeSort(double *arr, int tamanho) {
    MergeSort *mergeSort = malloc(sizeof(MergeSort));
    mergeSort->v = arr;
    mergeSort->w = malloc(tamanho * sizeof(double));
    mergeSort->tamanho = tamanho;
    return mergeSort;
}

// Função para liberar memória do MergeSort
void liberarMergeSort(MergeSort *mergeSort) {
    free(mergeSort->w);
    free(mergeSort);
}

// Função para realizar o MergeSort
void mergeSort(MergeSort *mergeSort, int ini, int fim) {
    if (ini < fim) {
        int meio = (ini + fim) / 2;
        mergeSort(mergeSort, ini, meio);
        mergeSort(mergeSort, meio + 1, fim);
        intercalar(mergeSort, ini, meio, fim);
    }
}

// Função auxiliar para intercalar
void intercalar(MergeSort *mergeSort, int ini, int meio, int fim) {
    for (int k = ini; k <= fim; k++) {
        mergeSort->w[k] = mergeSort->v[k];
    }

    int i = ini;
    int j = meio + 1;

    for (int k = ini; k <= fim; k++) {
        if (i > meio) mergeSort->v[k] = mergeSort->w[j++];
        else if (j > fim) mergeSort->v[k] = mergeSort->w[i++];
        else if (mergeSort->w[i] < mergeSort->w[j]) mergeSort->v[k] = mergeSort->w[i++];
        else mergeSort->v[k] = mergeSort->w[j++];
    }
}

// Função para calcular o tempo de execução do MergeSort
long calcularTempoMergeSort(MergeSort *mergeSort) {
    clock_t start = clock();
    mergeSort(mergeSort, 0, mergeSort->tamanho - 1);
    return (long)(clock() - start) * 1000 / CLOCKS_PER_SEC; // Retorna o tempo em milissegundos
}

// Função para gravar coordenadas em um arquivo
void gravarCoordenadas(const char *nomeArquivo, double *coordenadas, int tamanho) {
    FILE *file = fopen(nomeArquivo, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }
    for (int i = 0; i < tamanho; i += 2) {
        fprintf(file, "(%.6f, %.6f)\n", coordenadas[i], coordenadas[i + 1]);
    }
    fclose(file);
}

// Função principal
int main() {
    srand(time(NULL));

    // Definindo quantidade de coordenadas
    int quantidade = 10; // Exemplo de quantidade de coordenadas
    GeradorCoordenada *gerador = criarGeradorCoordenada(quantidade);
    gerarCoordenadas(gerador);
    
    // Gravar coordenadas desordenadas
    gravarCoordenadas(PATHDESORDENADO "coordenadas.txt", gerador->coordenadas, quantidade * 2);

    // Ordenar coordenadas (apenas a parte das latitudes como exemplo)
    double *arrParaOrdenar = malloc(quantidade * sizeof(double));
    for (int i = 0; i < quantidade; i++) {
        arrParaOrdenar[i] = gerador->coordenadas[i * 2]; // Pegando apenas as latitudes para ordenar
    }

    MergeSort *mergeSort = criarMergeSort(arrParaOrdenar, quantidade);
    long tempoExec = calcularTempoMergeSort(mergeSort);
    printf("Tempo de execução do MergeSort: %ld ms\n", tempoExec);

    // Gravar coordenadas ordenadas
    gravarCoordenadas(PATHORDENADO "coordenadas_ordenadas.txt", gerador->coordenadas, quantidade * 2);

    // Liberar memória
    liberarGeradorCoordenada(gerador);
    liberarMergeSort(mergeSort);
    free(arrParaOrdenar);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PATHORDENADO "C:\\Temp\\Coordenadas\\Ordenado\\"
#define PATHDESORDENADO "C:\\Temp\\Coordenadas\\Desordenado\\"

// Estrutura para gerar coordenadas
typedef struct {
    double *coordenadas;
    int quantidade;
} GeradorCoordenada;

// Estrutura para QuickSort
typedef struct {
    double *numeros;
} QuickSort;

// Função para criar um GeradorCoordenada
GeradorCoordenada* criarGeradorCoordenada(int qtd) {
    GeradorCoordenada *gerador = malloc(sizeof(GeradorCoordenada));
    gerador->quantidade = qtd;
    gerador->coordenadas = malloc(qtd * sizeof(double) * 2); // 2 para lat e long
    return gerador;
}

// Função para gerar coordenadas aleatórias
void gerarCoordenadas(GeradorCoordenada *gerador) {
    for (int i = 0; i < gerador->quantidade * 2; i += 2) {
        gerador->coordenadas[i] = ((double)rand() / RAND_MAX) * 180.0 - 90.0;  // Latitude
        gerador->coordenadas[i + 1] = ((double)rand() / RAND_MAX) * 360.0 - 180.0; // Longitude
    }
}

// Função para liberar memória do GeradorCoordenada
void liberarGeradorCoordenada(GeradorCoordenada *gerador) {
    free(gerador->coordenadas);
    free(gerador);
}

// Função para criar um objeto QuickSort
QuickSort* criarQuickSort(double *arr) {
    QuickSort *quickSort = malloc(sizeof(QuickSort));
    quickSort->numeros = arr;
    return quickSort;
}

// Função para liberar memória do QuickSort
void liberarQuickSort(QuickSort *quickSort) {
    free(quickSort);
}

// Função para particionar o array
int particionar(double *arr, int esq, int dir) {
    int i = esq;
    int j = dir;
    double tmp;
    double pivot = arr[(esq + dir) / 2];

    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;

        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }
    return i;
}

// Função para realizar o QuickSort
void quickSort(double *arr, int esq, int dir) {
    int indice = particionar(arr, esq, dir);
    if (esq < indice - 1) quickSort(arr, esq, indice - 1);
    if (indice < dir) quickSort(arr, indice, dir);
}

// Função para calcular o tempo de execução do QuickSort
long calcularTempoQuickSort(QuickSort *quickSort) {
    clock_t start = clock();
    quickSort(quickSort->numeros, 0, quickSort->numeros[0]);
    return (long)(clock() - start) * 1000 / CLOCKS_PER_SEC; // Retorna o tempo em milissegundos
}

// Função para gravar coordenadas em um arquivo
void gravarCoordenadas(const char *nomeArquivo, double *coordenadas, int tamanho) {
    FILE *file = fopen(nomeArquivo, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }
    for (int i = 0; i < tamanho; i += 2) {
        fprintf(file, "(%.6f, %.6f)\n", coordenadas[i], coordenadas[i + 1]);
    }
    fclose(file);
}

// Função principal
int main() {
    srand(time(NULL));

    // Definindo quantidade de coordenadas
    int quantidade = 10; // Exemplo de quantidade de coordenadas
    GeradorCoordenada *gerador = criarGeradorCoordenada(quantidade);
    gerarCoordenadas(gerador);
    
    // Gravar coordenadas desordenadas
    gravarCoordenadas(PATHDESORDENADO "coordenadas.txt", gerador->coordenadas, quantidade * 2);

    // Ordenar coordenadas (apenas a parte das latitudes como exemplo)
    double *arrParaOrdenar = malloc(quantidade * sizeof(double));
    for (int i = 0; i < quantidade; i++) {
        arrParaOrdenar[i] = gerador->coordenadas[i * 2]; // Pegando apenas as latitudes para ordenar
    }

    QuickSort *quickSort = criarQuickSort(arrParaOrdenar);
    long tempoExec = calcularTempoQuickSort(quickSort);
    printf("Tempo de execução do QuickSort: %ld ms\n", tempoExec);

    // Gravar coordenadas ordenadas
    gravarCoordenadas(PATHORDENADO "coordenadas_ordenadas.txt", gerador->coordenadas, quantidade * 2);

    // Liberar memória
    liberarGeradorCoordenada(gerador);
    liberarQuickSort(quickSort);
    free(arrParaOrdenar);

    return 0;
}





