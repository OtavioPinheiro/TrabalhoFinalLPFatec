#include <stdio.h>
#include <stdlib.h>

#define NUM_RSP 50
#define NUM_CNDT 5

int pontuacao(int i, int j, char **respostas_candidatos, char *gabarito);
void imprimir(int i, char **matricula_candidato, int pontos[NUM_CNDT]);
void ordenar(int i, int j, int menor, int pontos[NUM_CNDT], char **ordem, char **matricula_candidato);

//Inicialização. Declaro as variáveis
char *p_tabela[NUM_CNDT][2] = {NULL};
char *matricula_candidato[] = {"12134", "12131", "12233", "13311", "14411"};
char *respostas_candidato[] = {
    "bcdadceeaabdeaeaabcdadceeadeaeaabcdaceeeababceabceda",
    "cbabcadeacbaeabdeaeaabcdaeeaabdaabdeaeaabcedaaabdeae",
    "abdeaeaabcdaeeaabdaabdeaeadeaeaabcdaeeaabdaabdeaeaaa",
    "cbabcadeacbaeabdeaeaabcdaeeaabdaabdeaeaabcedaaabdeae",
    "eabdeaeaabcdaeeaabdaaeaabcdaeeaaeaeaabcdaeeaabdaabde"
    };
char *gabarito = {"bcdadceeadeaeaabcdaceeeababceabdeaeaabcdaeeaabdabced"};
int pontos[NUM_CNDT] = {0};
int i, j, menor =0;
char *ordem[1] = {NULL};


int main()
{
    for(i = 0; i<NUM_CNDT; i++)
    {
        p_tabela[i][0] = matricula_candidato[i];
        p_tabela[i][1] = respostas_candidato[i];

        printf("%s - %s\n", p_tabela[i][0], p_tabela[i][1]);
    }

    //Pontuação
    pontuacao(i, j, respostas_candidato, gabarito);

    //Imprimir antes de ordenar
    imprimir(i, matricula_candidato, pontos);

    //Ordenar
    ordenar(i, j, menor, pontos, ordem, matricula_candidato);

    printf("\n");

    //Imprimir
    imprimir(i, matricula_candidato, pontos);

    return 0;
}

int pontuacao(int i, int j, char **respostas_candidatos, char *gabarito)
{
    for(i = 0; i < NUM_CNDT; i++)
    {
        for(j = 0; j < NUM_RSP; j++)
        {
            if(respostas_candidato[i][j] == gabarito[i])
            {
                pontos[i]++;
            }
        }
    }

    return *pontos;
}

void imprimir(int i, char **matricula_candidato, int pontos[NUM_CNDT])
{
    for(i = 0; i < NUM_CNDT; i++)
    {
        printf("\n%s - %d", matricula_candidato[i], pontos[i]);
    }
}

void ordenar(int i, int j, int menor, int pontos[NUM_CNDT], char **ordem, char **matricula_candidato)
{
    for(i = 0; i < NUM_CNDT; i++)
    {
        for(j = 0; j < NUM_CNDT; j++)
        {
            if(pontos[i] >= pontos[j])
            {
                menor = pontos[i];
                pontos[i] = pontos[j];
                pontos[j] = menor;

                ordem[0] = matricula_candidato[i];
                matricula_candidato[i] = matricula_candidato[j];
                matricula_candidato[j] = ordem[0];
            }
        }
    }
}
