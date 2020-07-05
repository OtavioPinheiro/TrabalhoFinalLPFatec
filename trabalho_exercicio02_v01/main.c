#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>

#define MAX 100
#define DSC 30

typedef enum { false, true } bool;

struct produto {
    unsigned long int codigo;
    char descricao[DSC];
    int num_item;
    float preco_unit;
};

struct carrinho {
    int qtd;
    int prod_dif;
    float preco_final;
    float preco_total_item;
    struct produto item;
} compras[MAX];

char menu();
double textopdouble(const char *v);
void inicializa();
void adicionar();
void calc_total();
int espaco_livre();
void remover();
void mostrar();
bool verifica_cod(struct carrinho *cod);

int main()
{
    setlocale(LC_ALL, "Portuguese");

    inicializa();

    //Valores iniciais
    compras[0].item.codigo = 12311;
    //compras[0].item.descricao[DSC] = "COCA-COLA 2LT\0"; não posso fazer isso! strings não podem ser atribuidas diretamente.
    strcpy(compras[0].item.descricao, "COCA-COLA 2LT");
    compras[0].item.num_item = 1;
    compras[0].item.preco_unit = 5.98;

    compras[1].item.codigo = 13111;
    strcpy(compras[1].item.descricao,"FANTA 2LT");
    compras[1].item.num_item = 1;
    compras[1].item.preco_unit = 5.23;

    compras[2].item.codigo = 14422;
    strcpy(compras[2].item.descricao, "SKOL LATINHA");
    compras[2].item.num_item = 1;
    compras[2].item.preco_unit = 2.98;

    compras[3].item.codigo = 14221;
    strcpy(compras[3].item.descricao, "SKOL GARRAFA");
    compras[3].item.num_item = 1;
    compras[3].item.preco_unit = 3.11;

    calc_total();

    char escolha;

    for(;;)
    {
        escolha = '\0';
        escolha = menu();
        switch(escolha)
        {
            case 'a':
                system("cls");
                adicionar();
                break;
            case 'r':
                system("cls");
                remover();
                break;
            case 'm':
                system("cls");
                mostrar();
                break;
            case 's':
                system("cls");
                printf("\nFinalizando a compra. Obrigado pela preferência!\n");
                mostrar();
                exit(0);
                break;
        }
    }

    return 0;
}

char menu()
{
    char opcao;
    opcao = '\0';
    do
    {
        printf("(A)dicionar produto ao carrinho\n");
        printf("(R)emover produto do carrinho\n");
        printf("(M)ostrar carrinho\n");
        printf("(S)air\n");
        scanf(" %c", &opcao);
        opcao = tolower(opcao);
    }while(opcao != 'a' && opcao != 'r' && opcao != 'm' && opcao != 's');

    return opcao;
}

void inicializa()
{
    int i;
    for(i = 0; i<MAX; i++)
    {
        compras[i].qtd = 0;
        compras[i].item.codigo = 0;
        compras[i].preco_final = 0;
    }
}

int espaco_livre()
{
    int e;
    for(e = 0; compras[e].item.codigo && e < MAX; ++e)
    {
        if(e == MAX)
        {
            return -1; //está cheio.
        }
    }
    return e;
}

bool verifica_cod(struct carrinho *cod)
{
    bool repetiu = false;
    int i, j, p;
    p = espaco_livre();
    for(i = 0; i < p; i++)
    {
        for(j = 0; j < p; j++)
        {
            if(i != j)
            {
                if(cod[i].item.codigo == cod[j].item.codigo)
                {
                    repetiu = true;
                }
            }
        }
    }

    return repetiu;
}

void adicionar()
{
    int p;
    bool r;
    char val[5];
    p = espaco_livre();
    compras[p].prod_dif = p;
    if(p == -1)
    {
        printf("\nSeu carrinho está cheio! Não é possível adicionar mais itens.");
        return;
    }

    do
    {
        printf("\nInforme o código do produto: ");
        scanf("%lu", &compras[p].item.codigo);
        fflush(stdin);
        r = verifica_cod(compras);
        if(r == true)
        {
            printf("\nEsse Código já existe!\nDigite um código válido diferente.\n");
        }
    }while(r == true);

    printf("\nInforme a descrição do produto: ");
    //scanf("%s", compras[p].item.descricao); nesse caso o gets é melhor
    gets(compras[p].item.descricao);

    printf("\nInforme quantos desse item deseja: ");
    scanf("%d", &compras[p].item.num_item);
    fflush(stdin);

    printf("\nInforme o preço do produto: R$ ");
    scanf("%s", val);
    compras[p].item.preco_unit = textopdouble(val); //não pude usar apenas o %f pq ele funciona apenas com vírgula, pq eu usei o setlocale, senão iria funcionar só com ponto.
                                                    //Dessa forma funcionará com ambos, SEM imprimir o menu duas vezes!

    calc_total();

    printf("\nProduto adicionado com sucesso!\n\n");

    return;
}

void calc_total()
{
    int i;
    int p;

    p = espaco_livre();
    for(i = 0; i < p; ++i)
    {
        compras[i].preco_total_item = compras[i].item.num_item * compras[i].item.preco_unit;
        if(i==0)
        {
            compras[i].preco_final = compras[i].preco_total_item;
            compras[i].qtd = compras[i].item.num_item;
        }
        else
        {
            compras[i].preco_final = compras[i - 1].preco_final + compras[i].preco_total_item;
            compras[i].qtd = compras[i - 1].qtd + compras[i].item.num_item;
        }
    }
}

void mostrar()
{
    int i;
    int p;
    p = espaco_livre();
    compras[p].prod_dif = p;

    printf("\nCódigo  |      Descrição      |   Num_itens   | Preço R$/unid |        Total       |\n");
    i = 0;
    for(i = 0; i < MAX; ++i)
    {
        if(compras[i].item.codigo)
        {
            printf("\n  %lu   |", compras[i].item.codigo);
            printf("   %s    |", compras[i].item.descricao);
            printf("   %d     |", compras[i].item.num_item);
            printf("   %.2f   |", compras[i].item.preco_unit);
            printf("   %.2f   |\n", compras[i].preco_total_item);
        }
    }
    printf("\nFinal   |qtde prod variados  %d|  qtde total %d |               | Valor final R$%.2f |\n\n", compras[p].prod_dif, compras[p-1].qtd, compras[p-1].preco_final);
}

double textopdouble(const char *v)
{
    char *p = strchr(v, '.');
    if(p) *p = ',';
    return strtod(v, NULL);
}

void remover()
{
    int i, p, codigo;
    char confirma;
    p = espaco_livre();
    printf("\nInforme o código do produto a ser removido: ");
    scanf("%d", &codigo);
    for(i = 0; i < p; i++)
    {
        if(compras[i].item.codigo == codigo)
        {
            printf("\nTem certeza que deseja remover este produto?\nEssa ação não poderá ser desfeita.\n\n");
            printf("Descrição do produto: %s\n", compras[i].item.descricao);
            printf("\n(S)im / (N)ão: ");
            scanf(" %c", &confirma);
            confirma = tolower(confirma);
            if(confirma == 's')
            {
                compras[i].item.codigo = 0;
                printf("\nProduto removido com sucesso!\nCarrinho atualizado com sucesso!\n\n");
                return;
            }
            else
            {
                return;
            }
        }
    }
    printf("\nProduto não encontrado!\nPor favor verifique o código do produto\n\n");
}
