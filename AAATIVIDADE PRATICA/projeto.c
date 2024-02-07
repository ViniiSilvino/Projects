/*
    Rafael Ribas de Lima    2461650     rafael.2022@alunos.utfpr.edu.br
    Vinicius Lopes Silvino   2461684     vsilvino@alunos.utfpr.edu.br
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int qtdeDiasAtuais = (365 * 2023) + (30 * 11) + 20; // quantidade de dias a partir de 01/01/0001

// Definindo a estrutura do funcionário
typedef struct
{
    char nome[50];
    struct
    {
        int dia;
        int mes;
        int ano;
    } nascimento;
    struct
    {
        char rua[50];
        int numero;
    } end;
    float salario;
    int diasDeVida;
} Funcionario;

// Definindo a estrutura do nó da lista duplamente encadeada
typedef struct No
{
    Funcionario info;
    struct No *direita;
    struct No *esquerda;
    int altura;
} No;

// Definindo a estrutura da lista duplamente encadeada
typedef struct
{
    No *inicio;
    int qtdeElementos;
} ListaDupla;

void inserirListaDupla(ListaDupla *lista, Funcionario valor); // chamada de uma função de baixo para tirar o warning

// Função para ler um arquivo e inserir os funcionários na lista
void leArquivo(const char *nomeArquivo, ListaDupla *lista)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    char linha[400];
    Funcionario aux;
    char *ptr;

    fgets(linha, 400, arquivo); // Ignora a primeira linha

    while (fgets(linha, 400, arquivo))
    {
        ptr = strtok(linha, ",.;");
        strcpy(aux.nome, ptr); // Salva o nome em aux(nome)

        ptr = strtok(NULL, "/");
        aux.nascimento.dia = atoi(ptr); // Salva o dia em aux(nasc.dia)

        ptr = strtok(NULL, "/");
        aux.nascimento.mes = atoi(ptr); // Salva o mes em aux(nasc.mes)

        ptr = strtok(NULL, ",.;");
        aux.nascimento.ano = atoi(ptr); // Salva o ano em aux(nasc.ano)

        aux.diasDeVida = qtdeDiasAtuais - (365 * aux.nascimento.ano + 30 * aux.nascimento.mes + aux.nascimento.dia); // dias vividos = dias totais - dias até nascer

        ptr = strtok(NULL, ",.;");
        strcpy(aux.end.rua, ptr); // Salva o nome da rua em aux(end.rua)

        ptr = strtok(NULL, ",.;");
        aux.end.numero = atoi(ptr); // Salva o numero da rua em aux(end.numero)

        ptr = strtok(NULL, ",;   /"); // Pula R$

        ptr = strtok(NULL, ",");
        aux.salario = atof(ptr);
        aux.salario = aux.salario * 1000; // Pegar o valor na string e colocar em float;

        inserirListaDupla(lista, aux);
    }

    fclose(arquivo);
}

//====================================================================================================================//
//                                          LISTA DUPLAMENTE ENCADEADA                                                //
//====================================================================================================================//

// Inicializa a lista duplamente encadeada
void iniciaListaDupla(ListaDupla *lista)
{
    lista->inicio = NULL;
    lista->qtdeElementos = 0;
}

// Insere um elemento na lista duplamente encadeada
void inserirListaDupla(ListaDupla *lista, Funcionario valor)
{
    No *novo = (No *)malloc(sizeof(No));
    novo->info = valor;
    novo->direita = NULL;
    novo->esquerda = NULL;

    // Caso a lista esteja vazia
    if (lista->inicio == NULL)
    {
        lista->inicio = novo;
    }
    else
    {
        No *atual = lista->inicio;

        // Encontrar o ponto de inserção
        while (atual->direita != NULL && strcmp(valor.nome, atual->info.nome) > 0)
        {
            atual = atual->direita;
        }

        // Inserir antes de atual
        if (strcmp(valor.nome, atual->info.nome) <= 0)
        {
            novo->direita = atual;
            novo->esquerda = atual->esquerda;
            if (atual->esquerda != NULL)
            {
                atual->esquerda->direita = novo;
            }
            atual->esquerda = novo;

            // Se o novo elemento foi inserido no início, atualizar o início
            if (atual == lista->inicio)
            {
                lista->inicio = novo;
            }
        }
        // Inserir depois de atual
        else
        {
            novo->direita = NULL;
            novo->esquerda = atual;
            atual->direita = novo;
        }
    }

    lista->qtdeElementos++;
}

// Função para imprimir a lista na ordem crescente
void imprimeListaDuplaCres(ListaDupla *lista)
{
    No *atual = lista->inicio;

    printf("\nLista de funcionarios ordenados por nome de A-Z\n\n");
    while (atual != NULL)
    {
        printf("Nome: %s\nSalario: RS%.2f\nEndereco: %s %d\nNascimento:%d/%d/%d\n\n", atual->info.nome, atual->info.salario, atual->info.end.rua, atual->info.end.numero, atual->info.nascimento.dia, atual->info.nascimento.mes, atual->info.nascimento.ano);

        atual = atual->direita;
    }
}

// Função para imprimir a lista na ordem decrescente
void imprimeListaDuplaDecres(ListaDupla *lista)
{
    No *atual = lista->inicio;

    // Avançar até o final da lista
    while (atual != NULL && atual->direita != NULL)
    {
        atual = atual->direita;
    }

    printf("\nLista de funcionarios ordenados por nome de Z-A\n\n");
    while (atual != NULL)
    {
        printf("Nome: %s\nSalario: RS%.2f\nEndereco: %s %d\nNascimento:%d/%d/%d\n\n", atual->info.nome, atual->info.salario, atual->info.end.rua, atual->info.end.numero, atual->info.nascimento.dia, atual->info.nascimento.mes, atual->info.nascimento.ano);
        atual = atual->esquerda;
    }
}

/* Função para remover um elemento específico da lista
void removerElementoListaDupla(ListaDupla *lista, char nome[50])
{
    No *atual = lista->inicio;

    // Encontrar o elemento a ser removido
    while (atual != NULL && strcmp(atual->info.nome, nome) != 0)
    {
        atual = atual->direita;
    }

    // Se o elemento foi encontrado
    if (atual != NULL)
    {
        // Atualizar os ponteiros do elemento esquerda e posterior
        if (atual->esquerda != NULL)
        {
            atual->esquerda->direita = atual->direita;
        }
        else
        {
            lista->inicio = atual->direita; // Se for o primeiro elemento
        }

        if (atual->direita != NULL)
        {
            atual->direita->esquerda = atual->esquerda;
        }

        // Liberar a memória do elemento removido
        free(atual);

        lista->qtdeElementos--;
    }
}*/

// Função para liberar a memória alocada para a lista
void liberarListaDupla(ListaDupla *lista)
{
    No *atual = lista->inicio;
    No *direita;

    while (atual != NULL)
    {
        direita = atual->direita;
        free(atual);
        atual = direita;
    }

    lista->inicio = NULL; // Atualizar o ponteiro de início para refletir a lista vazia
    lista->qtdeElementos = 0;
}

// funcao para pesquisar o intervalo salarial dos funcionarios na LISTA
void pesquisaPorSalarioLISTA(ListaDupla *lista)
{
    No *agora = lista->inicio;
    float min, max;

    printf("Digite o valor minimo do salario: RS ");
    scanf("%f", &min);
    printf("Digite o valor maximo do salario: RS ");
    scanf("%f", &max);
    printf("Informacoes dos funcionarios que tem o salario entre %.2f e %.2f:\n\n", min, max);

    while (agora != NULL)
    {
        if (agora->info.salario >= min && agora->info.salario <= max)
        {
            printf("Nome: %s\nSalario: RS%.2f\nEndereco: %s %d\nNascimento:%d/%d/%d\n\n", agora->info.nome, agora->info.salario, agora->info.end.rua, agora->info.end.numero, agora->info.nascimento.dia, agora->info.nascimento.mes, agora->info.nascimento.ano);
        }
        agora = agora->direita;
    }
}

No *transformarListaEmAVL(ListaDupla *lista); // chamadas de uma função de baixo para tirar o warning
void menuAVL(No *raizAVL);

// menu principal de entrada, parte da LISTA
void menuLISTA(ListaDupla *lista)
{
    No *raizAVL = NULL;
    int opcao;
    printf("===== SISTEMA DE GERENCIAMENTO DE INFORMACOES DE FUNCIONARIOS DE UMA EMPRESA =====");

    do
    {
        printf("\n\nOpcoes:\n(1)Pesquisar os funcionarios na lista por intervalo salarial\n(2)Exibir a lista de funcionarios ordenados por nome de A-Z\n(3)Exibir a lista de funcionarios ordenados por nome de Z-A\n(4)Transformar a lista duplamente encadeada em uma arvore AVL\n(5)Sair\n\nDigite sua opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1: // pesquisa pelo salario
            pesquisaPorSalarioLISTA(lista);
            printf("\n-------------------------------------------------");
            break;

        case 2: // ordem alfabetica
            imprimeListaDuplaCres(lista);
            printf("\n-------------------------------------------------");
            break;

        case 3: // ordem alfabetica reversa
            imprimeListaDuplaDecres(lista);
            printf("\n-------------------------------------------------");
            break;

        case 4: // vira AVL
            raizAVL = transformarListaEmAVL(lista);
            printf("\n-------------------------------------------------");
            menuAVL(raizAVL);
            break;

        default:
            break;
        }
    } while (opcao != 5);
}

//====================================================================================================================//
//                                              ARVORE AVL                                                            //
//====================================================================================================================//

// Função para obter a altura de um nó AVL
int altura(No *n)
{
    return (n == NULL) ? 0 : n->altura;
}

// Função para calcular o fator de balanceamento de um nó AVL
int fatorBalanceamento(No *n)
{
    return (n == NULL) ? 0 : altura(n->esquerda) - altura(n->direita);
}

// funcao auxiliar da atualizar altura
int maximo(int a, int b)
{
    return (a > b) ? a : b;
}

// Função para atualizar a altura de um nó AVL
void atualizarAltura(No *n)
{
    if (n != NULL)
    {
        n->altura = 1 + maximo(altura(n->esquerda), altura(n->direita));
    }
}

// Função para realizar a rotação simples à direita em uma árvore AVL
No *rotacaoDireita(No *y)
{
    No *x = y->esquerda;
    No *T2 = x->direita;

    // Realiza a rotação
    x->direita = y;
    y->esquerda = T2;

    // Atualiza as alturas
    atualizarAltura(y);
    atualizarAltura(x);

    return x;
}

// Função para realizar a rotação simples à esquerda em uma árvore AVL
No *rotacaoEsquerda(No *x)
{
    No *y = x->direita;
    No *T2 = y->esquerda;

    // Realiza a rotação
    y->esquerda = x;
    x->direita = T2;

    // Atualiza as alturas
    atualizarAltura(x);
    atualizarAltura(y);

    return y;
}

// Função para inserir um nó na árvore AVL baseada na quantidade de dias vividos
No *inserirAVL(No *raiz, Funcionario info)
{
    // Inserção padrão em uma árvore binária de busca
    if (raiz == NULL)
    {
        No *novoNo = (No *)malloc(sizeof(No));
        novoNo->info = info;
        novoNo->esquerda = NULL;
        novoNo->direita = NULL;
        novoNo->altura = 1;
        return novoNo;
    }

    // Organiza com base na quantidade de dias vividos
    if (info.diasDeVida < raiz->info.diasDeVida)
    {
        raiz->esquerda = inserirAVL(raiz->esquerda, info);
    }
    else if (info.diasDeVida > raiz->info.diasDeVida)
    {
        raiz->direita = inserirAVL(raiz->direita, info);
    }
    else
    {
        // Duplicatas não são permitidas, você pode ajustar essa lógica conforme necessário
        return raiz;
    }

    // Atualiza a altura do nó atual
    atualizarAltura(raiz);

    // Calcula o fator de balanceamento
    int balanceamento = fatorBalanceamento(raiz);

    // Realiza as rotações, se necessário
    if (balanceamento > 1)
    {
        if (info.diasDeVida < raiz->esquerda->info.diasDeVida)
        {
            return rotacaoDireita(raiz);
        }
        else
        {
            raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
            return rotacaoDireita(raiz);
        }
    }
    if (balanceamento < -1)
    {
        if (info.diasDeVida > raiz->direita->info.diasDeVida)
        {
            return rotacaoEsquerda(raiz);
        }
        else
        {
            raiz->direita = rotacaoDireita(raiz->direita);
            return rotacaoEsquerda(raiz);
        }
    }

    return raiz;
}

// Função para transformar a lista duplamente encadeada em uma árvore AVL
No *transformarListaEmAVL(ListaDupla *lista)
{
    No *raizAVL = NULL; // Inicializa a raiz da árvore AVL como NULL

    // Percorre a lista e insere cada elemento na árvore AVL
    No *atual = lista->inicio;
    while (atual != NULL)
    {
        raizAVL = inserirAVL(raizAVL, atual->info);
        atual = atual->direita;
    }

    // Retorna a raiz da árvore AVL criada
    return raizAVL;
}

// Função para imprimir a árvore AVL em ordem
void imprimirAVLEmOrdem(No *raiz)
{
    if (raiz != NULL)
    {
        imprimirAVLEmOrdem(raiz->esquerda);
        printf("Nome: %s, Salario: %.2f\n", raiz->info.nome, raiz->info.salario);
        imprimirAVLEmOrdem(raiz->direita);
    }
}

// Função para imprimir a árvore AVL em ordem crescente
void imprimeAVLCrescente(No *raiz)
{
    if (raiz != NULL)
    {
        imprimeAVLCrescente(raiz->esquerda);
        printf("Nome: %s\nSalario: RS%.2f\nEndereco: %s %d\nNascimento:%d/%d/%d\nDiasVividos: %d\n\n", raiz->info.nome, raiz->info.salario, raiz->info.end.rua,
               raiz->info.end.numero, raiz->info.nascimento.dia, raiz->info.nascimento.mes,
               raiz->info.nascimento.ano, raiz->info.diasDeVida);
        imprimeAVLCrescente(raiz->direita);
    }
}

// Função para imprimir a árvore AVL em ordem decrescente
void imprimeAVLDecrescente(No *raiz)
{

    if (raiz != NULL)
    {
        imprimeAVLDecrescente(raiz->direita);
        printf("Nome: %s\nSalario: RS%.2f\nEndereco: %s %d\nNascimento:%d/%d/%d\nDiasVividos: %d\n\n", raiz->info.nome, raiz->info.salario, raiz->info.end.rua,
               raiz->info.end.numero, raiz->info.nascimento.dia, raiz->info.nascimento.mes,
               raiz->info.nascimento.ano, raiz->info.diasDeVida);
        imprimeAVLDecrescente(raiz->esquerda);
    }
}

// Função para liberar a memória alocada para a árvore AVL
void liberarAVL(No *raiz)
{
    if (raiz != NULL)
    {
        liberarAVL(raiz->esquerda);
        liberarAVL(raiz->direita);
        free(raiz);
    }
}

void pesquisaPorSalarioAVL(No *raiz, float valormin, float valormax)
{

    if (raiz != NULL)
    {
        pesquisaPorSalarioAVL(raiz->esquerda, valormin, valormax);

        if (raiz->info.salario >= valormin && raiz->info.salario <= valormax)
        {
            printf("Nome: %s, Salário: RS%.2f\n", raiz->info.nome, raiz->info.salario);
        }

        pesquisaPorSalarioAVL(raiz->direita, valormin, valormax);
    }
}

// menu secundario, apos a lista se tornar AVL
void menuAVL(No *raizAVL)
{
    int opcao;
    float valormin, valormax;

    printf("\n\n====== A LISTA FOI TRANSFORMADA EM UMA AVL ======");

    do
    {
        printf("\n\nOpcoes:\n(1)Pesquisar os funcionarios na AVL por intervalo salarial\n(2)Exibir a lista de funcionarios ordenados por idade crescente\n(3)Exibir a lista de funcionarios ordenados por idade decrescente\n(4)Sair\n\nDigite sua opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1: // Pesquisa por intervalo salarial
            printf("\nDigite o valor mínimo: ");
            scanf("%f", &valormin);
            printf("Digite o valor máximo: ");
            scanf("%f", &valormax);
            pesquisaPorSalarioAVL(raizAVL, valormin, valormax);
            printf("\n-------------------------------------------------");
            break;

        case 2: // ordem de idade crescente
            imprimeAVLCrescente(raizAVL);
            printf("\n-------------------------------------------------");
            break;

        case 3: // ordem de idade decrescente
            imprimeAVLDecrescente(raizAVL);
            printf("\n-------------------------------------------------");
            break;

        case 4: // sair
            return;
            break;

        default:
            break;
        }
    } while (opcao != 4);
}

int main(int argc, char const *argv[])
{
    ListaDupla lista;
    iniciaListaDupla(&lista);

    // Leitura do arquivo e inserção na lista
    leArquivo(argv[1], &lista);

    menuLISTA(&lista);

    // Liberação de memória
    liberarListaDupla(&lista);

    return 0;
} // main+++++