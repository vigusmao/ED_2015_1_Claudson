#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _elemento {
    char nome[30];
    int DRE;
    float CRA;
    struct _elemento* prox;
} ELEMENTO;

typedef struct _lista_encadeada {
    ELEMENTO* inicio;
    ELEMENTO* fim;
    int tamanho;
} LISTA_ENCADEADA;

void inserir(LISTA_ENCADEADA* lista,
             ELEMENTO* antecessor,
             ELEMENTO* novo) {
    if (antecessor == NULL) {
        // inserir no comeco da lista
        novo->prox = lista->inicio;
        lista->inicio = novo;
    } else {
        novo->prox = antecessor->prox;
        antecessor->prox = novo;
    }

    if (novo->prox == NULL) {
        // acabamos de inserir no fim da lista
        lista->fim = novo;
    }

    lista->tamanho++;
}

void inserir_fim(LISTA_ENCADEADA* lista,
                 ELEMENTO* novo) {
    inserir(lista, lista->fim, novo);
}

void inserir_inicio(LISTA_ENCADEADA* lista,
                 ELEMENTO* novo) {
    inserir(lista, NULL, novo);
}

LISTA_ENCADEADA* inicializar_lista() {
    LISTA_ENCADEADA* lista = (LISTA_ENCADEADA*) malloc(sizeof(LISTA_ENCADEADA));
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
    return lista;
}

float encontrar_CRA(LISTA_ENCADEADA* lista, int dre) {
    ELEMENTO* no;
    no = lista->inicio;
    while (no) {  // equivalente a while (no != NULL)
        if (no->DRE == dre) {
            return no->CRA;
        }
        no = no->prox;
    }
    return -1;
}

void imprimir_lista(LISTA_ENCADEADA* lista) {
    if (lista->tamanho == 0) {
        printf("\nLista vazia!");
    }

    ELEMENTO* no;
    no = lista->inicio;
    while (no != NULL) {
        printf("\n%d - %s - %.2f", no->DRE, no->nome, no->CRA);
        no = no->prox;
    }
}

void imprimir_CRA(LISTA_ENCADEADA* lista, int dre) {
    printf("\nDRE = %d - ", dre);
    float cra = encontrar_CRA(lista, dre);
    if (cra != -1) {
        printf("CRA = %.2f", cra);
    } else {
        printf("aluno nao encontrado!");
    }
}

int main() {
    LISTA_ENCADEADA* lista = inicializar_lista();

    // Criamos o primeiro aluno
    ELEMENTO aluno1;
    aluno1.DRE = 111111;
    aluno1.CRA = 7.5;
    strcpy(aluno1.nome, "Aluno 1");

    inserir(lista, NULL, &aluno1);

    // Criamos o segundo aluno (de outra maneira)
    ELEMENTO* ptr_aluno2 = (ELEMENTO*) malloc(sizeof(ELEMENTO));
    (*ptr_aluno2).DRE = 22222; // sintaxe valida
    ptr_aluno2->CRA = 10;      // sintaxe igualmente valida
    // aluno2.CRA = 10;  sintaxe invalida!!
    strcpy(ptr_aluno2->nome, "Aluno 2");

    //inserir(lista, &aluno1, ptr_aluno2);
    inserir_fim(lista, ptr_aluno2);

    // Criamos o terceiro aluno
    ELEMENTO aluno3;
    aluno3.DRE = 333;
    aluno3.CRA = 3.3;
    strcpy(aluno3.nome, "Aluno 3");

    inserir_inicio(lista, &aluno3);

    imprimir_lista(lista);

    imprimir_CRA(lista, 111111);
    imprimir_CRA(lista, 1234234);

    printf("\n\n");

    return 1;
}
