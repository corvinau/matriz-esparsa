#include <stdio.h>
#include <stdlib.h>

typedef struct nodo //estrutura que define o nodo
{
    float dado;
    int lin, col;
    struct nodo *prox;
}Matriz_Esparsa;

int i, j, x, k; //variaveis globais

void inicializa_lista(Matriz_Esparsa **lista) //inicializa a lista com NULL
{
    *lista = NULL;
}

Matriz_Esparsa *cria_nodo() //aloca espaco para o nodo criado
{
    Matriz_Esparsa *p;

    p = (Matriz_Esparsa *) malloc(sizeof(Matriz_Esparsa));
    if(!p)
    {
        printf("\nProblema de alocacao\n\n");
        exit(0);
    }
    return p;
}

void insere_elemento_matriz(Matriz_Esparsa **lista, int linha, int coluna, float dado) //insere o elemento na lista com as informacoes de linha, coluna e dado; insere no final da lista
{
    Matriz_Esparsa *novo, *aux;

    novo = cria_nodo();
    novo->lin = linha;
    novo->col = coluna;
    novo->dado = dado;
    printf("O elemento %.2f foi inserido!\n\n", novo->dado);
    novo->prox = NULL;
    if(*lista == NULL)
    {
        *lista = novo;
    }
    else
    {
        aux = *lista;
        while(aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = novo;
    }
}

void recebe_matriz(Matriz_Esparsa **lista) //define se a matriz tem algum valor diferente de 0, se sim pergunta a linha, a coluna e o valor a ser inserido
{
    int linha, coluna;
    float dado;

    do
    {
        printf("\nEssa matriz possui algum valor diferente de 0 ?\n");
        printf("1. Sim\n");
        printf("2. Nao\n");
        scanf("%d", &x);
        switch(x)
        {
        case 1:
            printf("Digite a linha desse elemento:\n");
            scanf("%d", &linha);
            printf("Digite a coluna desse elemento:\n");
            scanf("%d", &coluna);
            printf("Digite o valor a ser inserido:\n");
            scanf("%f", &dado);
            if(dado == 0)
            {
                printf("\nPor favor insira um dado diferente de zero\n\n");
            }
            else
            {
                insere_elemento_matriz(lista, linha, coluna, dado);
            }
            break;
        case 2:
            break;
        default:
            printf("\nOpcao Invalida!\n\n");
        }
    }
    while(x != 2);
}

void libera_lista(Matriz_Esparsa *lista) //libera a lista com a funcao free
{
    Matriz_Esparsa *aux;

    while(lista != NULL)
    {
        aux = lista;
        lista = lista->prox;
        free(aux);
    }
}

float percorre_caminho(Matriz_Esparsa *matriz1, int i, int j) //funcao de busca; retorna o valor a ser utilizado
{
    Matriz_Esparsa *aux;
    float v1 = 0.0;

    for(aux = matriz1; aux != NULL; aux = aux->prox)
    {
        if(aux->col == j && aux->lin == i)
        {
            v1 = aux->dado;
            break;
        }
        if(aux->col > j && aux->lin > i)
        {
            break;
        }
    }
    return v1;
}

void somar_matriz(Matriz_Esparsa *matriz1, Matriz_Esparsa *matriz2, int linha1, int coluna1, int linha2, int coluna2) //utiliza a funcao de busca para somar as matrizes
{
    float v1, v2;

    if(linha1 == linha2 && coluna1 == coluna2)
    {
        for(i = 1; i <= linha1; i++)
        {
            for(j = 1; j <= coluna1; j++)
            {
                v1 = percorre_caminho(matriz1, i, j);
                v2 = percorre_caminho(matriz2, i, j);
                printf("%.2f ", v1 + v2);
            }
            printf("\n");
        }
    }
    else
    {
        printf("\nNao e possivel somar essas matrizes\n\n");
    }
}

void subtrair_matriz(Matriz_Esparsa *matriz1, Matriz_Esparsa *matriz2, int linha1, int coluna1, int linha2, int coluna2) //utiliza a funcao de busca para subtrair as matrizes
{
    float v1, v2;

    if(linha1 == linha2 && coluna1 == coluna2)
    {
        for(i = 1; i <= linha1; i++)
        {
            for(j = 1; j <= coluna1; j++)
            {
                v1 = percorre_caminho(matriz1, i, j);
                v2 = percorre_caminho(matriz2, i, j);
                printf("%.2f ", v1 - v2);
            }
            printf("\n");
        }
    }
    else
    {
        printf("\nNao e possivel subtrair essas matrizes\n\n");
    }
}

void multiplicar_matriz(Matriz_Esparsa *matriz1, Matriz_Esparsa *matriz2, int linha1, int coluna1, int linha2, int coluna2) //utiliza a funcao de busca para multiplicar as matrizes
{
    float sum = 0, v1 = 0.0, v2 = 0.0;

    if(coluna1 == linha2)
    {
        for(i = 1; i <= linha1; i++)
        {
            for(j = 1; j <= coluna2; j++)
            {
                sum = 0;
                for(k = 0; k <= coluna1; k++)
                {
                    sum += percorre_caminho(matriz1, i, k) * percorre_caminho(matriz2, k, j);
                }
                printf(" %.2f ", sum);
            }
            printf("\n");
        }
    }
    else
    {
        printf("\nNao e possivel multiplicar essas matrizes\n\n");
    }
}

void matriz_transposta(Matriz_Esparsa *matriz1, int linha, int coluna) //utiliza a funcao de busca para mostrar as matrizes transpostas
{
    float v1;

    for(i = 1; i <= coluna; i++)
    {
        for(j = 1; j <= linha; j++)
        {
            v1 = percorre_caminho(matriz1,j,i);
            printf("%.2f ",v1);
        }
        printf("\n");
    }
}

void mostra_matriz(Matriz_Esparsa *matriz1, int linha, int coluna) //utiliza a funcao de busca para mostrar as matrizes
{
    float v1;

    for(i = 1; i <= linha; i++)
    {
        for(j = 1; j <= coluna; j++)
        {
            v1 = percorre_caminho(matriz1,i,j);
            printf("%.2f ",v1);
        }
        printf("\n");
    }
}

void diagonal_principal(Matriz_Esparsa *matriz1, int linha, int coluna) //utiliza a funcao de busca para mostar as diagonais das matrizes
{
    float v1;
    int qtd = coluna; //define o valor para qtd como o valor da coluna, se o numero de colunas for maior que o numero de linhas qtd recebe o valor de linha

    if(coluna > linha)
    {
        qtd = linha;
    }
    for(i = 1; i <= qtd; i++)
    {
        v1 = percorre_caminho(matriz1,i,i);
        printf("%.2f\n",v1);
    }
}

void main() //menu do programa
{
    int l1, c1, l2, c2, op, resp;
    Matriz_Esparsa *matriz1, *matriz2;

    inicializa_lista(&matriz1);
    inicializa_lista(&matriz2);
    do
    {
        printf("\n1. Inicializar matrizes");
        printf("\n2. Mostrar matrizes");
        printf("\n3. Imprimir diagonal principal das matrizes");
        printf("\n4. Somar as duas matrizes");
        printf("\n5. Subtrair as duas matrizes");
        printf("\n6. Multiplicar as duas matrizes");
        printf("\n7. Mostrar matrizes transpostas");
        printf("\n0. Sair\n");
        scanf("%d", &op);
        switch(op)
        {
        case 0:
            printf("\nSaindo do programa!\n\n");
            libera_lista(matriz1);
            libera_lista(matriz2);
            break;
        case 1:
            if(matriz1 == NULL && matriz2 == NULL)
            {
                printf("\tMATRIZ 1\n\n");
                printf("\nPor favor, informe o tamanho da matriz 1:\n\n");
                printf("Infome o numero de linhas:\n");
                scanf("%d", &l1);
                printf("Informe o numero de colunas:\n");
                scanf("%d", &c1);
                recebe_matriz(&matriz1);
                printf("\tMATRIZ 2\n\n");
                printf("\nPor favor, informe o tamanho da matriz 2:\n\n");
                printf("Infome o numero de linhas:\n");
                scanf("%d", &l2);
                printf("Informe o numero de colunas:\n");
                scanf("%d", &c2);
                recebe_matriz(&matriz2);
            }
            else
            {
                printf("\n\nDeseja realmente substituir a matriz existente?");
                printf("\n1. Sim");
                printf("\n2. Nao\n");
                scanf("%d", &resp);
                if(resp == 1)
                {
                    libera_lista(matriz1);
                    libera_lista(matriz2);
                    inicializa_lista(&matriz1);
                    inicializa_lista(&matriz2);
                }
                else
                {
                    break;
                }
            }
            break;
        case 2:
            if(matriz1 == NULL && matriz2 == NULL)
            {
                printf("\nInicialize as matrizes antes\n\n");
            }
            else
            {
                printf("\t\nMatriz 1\n\n");
                mostra_matriz(matriz1, l1, c1);
                printf("\t\nMatriz 2\n\n");
                mostra_matriz(matriz2, l2, c2);
            }
            break;
        case 3:
            if(matriz1 == NULL && matriz2 == NULL)
            {
                printf("\nInicialize as matrizes antes\n\n");
            }
            else
            {
                printf("\t\nDiagonal principal da matriz 1\n\n");
                diagonal_principal(matriz1, l1, c1);
                printf("\t\nDiagonal principal da matriz 2\n\n");
                diagonal_principal(matriz2, l2,c2);
            }
            break;
        case 4:
            if(matriz1 == NULL && matriz2 == NULL)
            {
                printf("\nInicialize as matrizes antes\n\n");
            }
            else
            {
                printf("\t\nSoma das matrizes\n\n");
                somar_matriz(matriz1, matriz2, l1, c1, l2, c2);
            }
            break;
        case 5:
            if(matriz1 == NULL && matriz2 == NULL)
            {
                printf("\nInicialize as matrizes antes\n\n");
            }
            else
            {
                printf("\t\nSubtracao das matrizes\n\n");
                subtrair_matriz(matriz1, matriz2, l1, c1, l2, c2);
            }
            break;
        case 6:
            if(matriz1 == NULL && matriz2 == NULL)
            {
                printf("\nInicialize as matrizes antes\n\n");
            }
            else
            {
                printf("\t\nMultiplicacao das matrizes\n\n");
                multiplicar_matriz(matriz1, matriz2, l1, c1, l2, c2);
            }
            break;
        case 7:
            if(matriz1 == NULL && matriz2 == NULL)
            {
                printf("\nInicialize as matrizes antes\n\n");
            }
            else
            {
                printf("\t\nTransposta da matriz 1\n\n");
                matriz_transposta(matriz1, l1, c1);
                printf("\t\nTransposta da matriz 2\n\n");
                matriz_transposta(matriz2, l2, c2);
            }
            break;
        default:
            printf("\nOpcao Invalida!\n\n");
        }
    }
    while(op != 0);
}
