#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_QUESTOES 30
#define MAX_OPCOES 5

typedef struct {
    char pergunta[256];
    char respostas[MAX_OPCOES][128];
    int respostaCorreta;
} Questao;

void mostrarMenu();
void carregarQuestoes(Questao questoes[], int *totalQuestoes, int tipo);
void embaralharQuestoes(Questao questoes[], int totalQuestoes);
int jogar(Questao questoes[], int totalQuestoes);

int main() {
    srand(time(NULL));
    int opcao, totalQuestoes = 0, pontuacao;
    Questao questoes[MAX_QUESTOES];

    do {
        mostrarMenu();
        printf("Escolha uma categoria (1-5) ou 9 para sair: ");
        scanf("%d", &opcao);

        if (opcao >= 1 && opcao <= 5) {
            carregarQuestoes(questoes, &totalQuestoes, opcao);
            embaralharQuestoes(questoes, totalQuestoes);
            pontuacao = jogar(questoes, totalQuestoes);

            if (pontuacao >= 100) {
                printf("\nParabéns! Você atingiu 100 pontos e ganhou o jogo!\n");
            } else if (pontuacao > 100) {
                printf("\nVocê ultrapassou os 100 pontos e perdeu o jogo.\n");
            } else {
                printf("\nSua pontuação final foi: %d pontos.\n", pontuacao);
            }
        } else if (opcao != 9) {
            printf("Opção inválida!\n");
        }
    } while (opcao != 9);

    printf("Obrigado por jogar!\n");
    return 0;
}

void mostrarMenu() {
    printf("\n=== JOGO DE PERGUNTAS ===\n");
    printf("1. Ciências\n");
    printf("2. História\n");
    printf("3. Mundo da Fama\n");
    printf("4. Tecnologia\n");
    printf("5. Aleatórios\n");
    printf("9. Sair\n");
    printf("=========================\n");
}

void carregarQuestoes(Questao questoes[], int *totalQuestoes, int tipo) {
    *totalQuestoes = 0;

    // Vetores de perguntas para cada categoria
    Questao ciencias[] = {
        {"Qual é o planeta mais próximo do Sol?",
         {"Vênus", "Terra", "Mercúrio", "Marte", "Saturno"},
         2},
        {"Qual é o elemento químico mais abundante no universo?",
         {"Hélio", "Oxigênio", "Hidrogênio", "Carbono", "Nitrogênio"},
         2},
    };

    Questao historia[] = {
        {"Quem foi o primeiro presidente dos Estados Unidos?",
         {"Abraham Lincoln", "George Washington", "Thomas Jefferson", "John Adams", "James Madison"},
         1},
        {"Em que ano ocorreu a Revolução Francesa?",
         {"1789", "1776", "1804", "1750", "1812"},
         0},
    };

    Questao fama[] = {
        {"Quem ganhou o Oscar de Melhor Atriz em 2023?",
         {"Michelle Yeoh", "Cate Blanchett", "Viola Davis", "Jennifer Lawrence", "Margot Robbie"},
         0},
        {"Qual é a marca de moda fundada por Coco Chanel?",
         {"Dior", "Prada", "Chanel", "Gucci", "Versace"},
         2},
    };

    Questao tecnologia[] = {
        {"Qual foi o primeiro console de videogame lançado no mercado?",
         {"Atari 2600", "Nintendo NES", "Magnavox Odyssey", "PlayStation", "Sega Genesis"},
         2},
        {"O que significa a sigla 'HTTP'?",
         {"Hyper Text Transfer Protocol", "Hyperlink Transfer Text Protocol", "High Transfer Text Page", "Hyper Transfer Type Protocol", "Host Text Transfer Protocol"},
         0},
    };

    // Escolha do vetor de perguntas
    Questao *escolhidas;
    int tamanhoEscolhidas;

    switch (tipo) {
        case 1: // Ciências
            escolhidas = ciencias;
            tamanhoEscolhidas = sizeof(ciencias) / sizeof(ciencias[0]);
            break;
        case 2: // História
            escolhidas = historia;
            tamanhoEscolhidas = sizeof(historia) / sizeof(historia[0]);
            break;
        case 3: // Mundo da Fama
            escolhidas = fama;
            tamanhoEscolhidas = sizeof(fama) / sizeof(fama[0]);
            break;
        case 4: // Tecnologia
            escolhidas = tecnologia;
            tamanhoEscolhidas = sizeof(tecnologia) / sizeof(tecnologia[0]);
            break;
        case 5: // Aleatórios (combinação de todas)
            escolhidas = NULL;
            tamanhoEscolhidas = 0;

            Questao todas[] = {
                ciencias[0], ciencias[1], historia[0], historia[1],
                fama[0], fama[1], tecnologia[0], tecnologia[1]
            };

            memcpy(questoes, todas, sizeof(todas));
            *totalQuestoes = sizeof(todas) / sizeof(todas[0]);
            return;
    }

    // Copiar perguntas para o vetor principal
    if (escolhidas != NULL) {
        memcpy(questoes, escolhidas, sizeof(Questao) * tamanhoEscolhidas);
        *totalQuestoes = tamanhoEscolhidas;
    }
}

void embaralharQuestoes(Questao questoes[], int totalQuestoes) {
    for (int i = 0; i < totalQuestoes; i++) {
        int j = rand() % totalQuestoes;
        Questao temp = questoes[i];
        questoes[i] = questoes[j];
        questoes[j] = temp;
    }
}

int jogar(Questao questoes[], int totalQuestoes) {
    int pontuacao = 0, respostasDadas = 0, index, usadaAjuda;

    for (int i = 0; i < totalQuestoes; i++) {
        printf("\nPergunta %d: %s\n", i + 1, questoes[i].pergunta);
        usadaAjuda = 0;

        for (int j = 0; j < MAX_OPCOES; j++) {
            printf("%d. %s\n", j + 1, questoes[i].respostas[j]);
        }
        printf("0. Ajuda (Remove uma opção incorreta)\n");
        printf("9. Encerrar o jogo\n");

        do {
            printf("Sua resposta: ");
            scanf("%d", &index);

            if (index == 0 && !usadaAjuda) {
                usadaAjuda = 1;
                pontuacao -= 5;

                printf("Dica: Uma das opções incorretas foi removida.\n");
                for (int j = 0; j < MAX_OPCOES; j++) {
                    if (j != questoes[i].respostaCorreta && rand() % 2 == 0) {
                        strcpy(questoes[i].respostas[j], "REMOVIDA");
                        break;
                    }
                }
                for (int j = 0; j < MAX_OPCOES; j++) {
                    if (strcmp(questoes[i].respostas[j], "REMOVIDA") != 0) {
                        printf("%d. %s\n", j + 1, questoes[i].respostas[j]);
                    }
                }
            }
        } while (index == 0);

        if (index == 9) {
            printf("Jogo encerrado!\n");
            break;
        } else if (index - 1 == questoes[i].respostaCorreta) {
            printf("Correto!\n");
            pontuacao += 5;
        } else {
            printf("Errado! Resposta correta era: %s\n", questoes[i].respostas[questoes[i].respostaCorreta]);
        }

        respostasDadas++;
        if (pontuacao >= 100 || respostasDadas >= MAX_QUESTOES) {
            break;
        }
    }
    return pontuacao;
}

