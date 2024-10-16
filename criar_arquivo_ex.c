#include <stdio.h>
#include <stdlib.h>

void criar_arquivo_exemplo(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        perror("Erro ao criar o arquivo");
        return;
    }
    fprintf(arquivo, "Este é um arquivo de exemplo.\n");
    fclose(arquivo);
    printf("Arquivo '%s' criado com sucesso.\n", nome_arquivo);
}

int main() {
    criar_arquivo_exemplo("exemplo.txt");
    return 0;
}
