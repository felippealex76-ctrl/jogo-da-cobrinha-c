#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define LARGURA 40
#define ALTURA  20

#define SETA_CIMA 72
#define SETA_BAIXO 80
#define SETA_ESQUERDA 75
#define SETA_DIREITA 77
#define VELOCIDADE_INICIAL 150
#define VELOCIDADE_MINIMA 60
#define TAM_MAX (LARGURA * ALTURA)
#define ARQUIVO_RECORDE "recorde.txt"


typedef struct {
    int x;
    int y;
} Ponto;

typedef enum {
    CIMA,
    BAIXO,
    ESQUERDA,
    DIREITA
}Direcao;

int ehParede(int x, int y) {

    return(x == 0 || x == LARGURA - 1 || y == 0 || y == ALTURA - 1);
}

Ponto proximaCabeca(Ponto cabeca, Direcao direcao) {
    switch (direcao) {
        case DIREITA:
            cabeca.x++;
            break;

        case ESQUERDA:
            cabeca.x--;
            break;

        case BAIXO:
            cabeca.y++;
            break;

        case CIMA:
            cabeca.y--;
            break;
    }
    return cabeca;
}

char caractereCabeca(Direcao direcao) {
    switch (direcao) {
        case DIREITA:
            return '>';

        case ESQUERDA:
            return '<';

        case BAIXO:
            return 'v';

        case CIMA:
            return '^';
    }
    return '>';
}

int indiceCobra(Ponto cobra[], int tamanho, int x, int y) {
    for (int i = 0; i < tamanho; i++) {
        if (cobra[i].x == x && cobra[i].y == y) {
            return i;
        }
    }
    return -1;
}

Ponto sortearComida(Ponto cobra[], int tamanho) {
    Ponto nova;

    do {
        nova.x = 1 + rand() % ( LARGURA - 2);
        nova.y = 1 + rand() % ( ALTURA - 2);
    } while (indiceCobra(cobra, tamanho, nova.x, nova.y) != - 1);
    return nova;
}


void mover(Ponto cobra[], int tamanho, Direcao direcao) {
    for (int i = tamanho - 1; i > 0; i--) {
        cobra[i] = cobra[i - 1];
    }
    cobra[0] = proximaCabeca(cobra[0], direcao);

}


void desenharTabuleiro(Ponto comida, Ponto cobra[], int tamanho, Direcao direcao, int pontos, int recorde) {
    for (int y = 0; y < ALTURA; y++) {
        for (int x = 0; x < LARGURA; x++) {

            int i = indiceCobra(cobra, tamanho, x, y);

            if (ehParede(x, y)) {
                printf("#");
            } else if (i == 0) {
                printf("%c", caractereCabeca(direcao));
            } else if (i > 0) {                       
                printf("o");
            } else if (x == comida.x && y == comida.y) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("Pontos: %d     Recorde: %d     (Ctrl+C para sair)\n", pontos, recorde);

}

void irParaTopo(void) {
    COORD origem = { 0, 0 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), origem);
}

void esconderCursor(void) {
    CONSOLE_CURSOR_INFO info = { 1, FALSE };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

Direcao lerDirecao(Direcao atual) {
    if (!_kbhit()) {
        return atual;
    }

    int tecla = _getch();

    if (tecla == 0 || tecla == 224) {
        tecla = _getch();

        switch (tecla) {
            case SETA_CIMA:
                return CIMA;
            case SETA_BAIXO:
                return BAIXO;
            case SETA_ESQUERDA:
                return ESQUERDA;
            case SETA_DIREITA:
                return DIREITA;
        }
    }
        return atual;
}

int calcularVelocidade(int tamanho) {
    int velocidade =  VELOCIDADE_INICIAL - (tamanho - 3) * 5;

    if (velocidade < VELOCIDADE_MINIMA) {
        velocidade = VELOCIDADE_MINIMA;
    }
    return velocidade;
}

int ehOposta(Direcao a, Direcao b) {

    return (a == CIMA && b == BAIXO) || (a == BAIXO && b == CIMA) || ( a == ESQUERDA && b == DIREITA ) ||
        ( a == DIREITA && b == ESQUERDA);
}

int lerRecorde(const char *caminho) {
    FILE *arquivo = fopen(caminho, "r");

    if (arquivo == NULL) {
        return 0;
    }
    int recorde = 0;
    if (fscanf(arquivo, "%d", &recorde) != 1) {
        recorde = 0;
    }
    fclose(arquivo);
    return recorde;
}

void salvarRecorde(const char *caminho, int recorde) {
    FILE *arquivo = fopen(caminho, "w");

    if (arquivo != NULL) {
        fprintf(arquivo, "%d\n", recorde);
        fclose(arquivo);
    }
}

int jogarPartida(int recorde) {

    Ponto cobra[TAM_MAX] = {{5, 5}, {4, 5}, {3, 5}};
    int tamanho = 3;
    Direcao direcao = DIREITA;
    int pontos = 0;
    int rodando = 1;
    Ponto comida = sortearComida(cobra, tamanho);

    while (rodando) {
        Direcao nova = lerDirecao(direcao);
        if (!ehOposta(nova, direcao)) {
            direcao = nova;
        }

        Ponto destino = proximaCabeca(cobra[0], direcao);

        if (ehParede(destino.x, destino.y) ||
            indiceCobra(cobra, tamanho, destino.x, destino.y) != -1) {
            rodando = 0;
            } else if (destino.x == comida.x && destino.y == comida.y) {
                tamanho++;
                mover(cobra, tamanho, direcao);
                comida = sortearComida(cobra, tamanho);
                pontos += 10;
            } else {
                mover(cobra, tamanho, direcao);
            }

        irParaTopo();
        desenharTabuleiro(comida, cobra, tamanho, direcao, pontos, recorde);
        Sleep(calcularVelocidade(tamanho));
    }
    return pontos;
}

int perguntarJogarNovamente(void) {

    while (_kbhit()) {
        _getch();
    }

    printf("Jogar de novo ? (s/n): ");
    fflush(stdout);

    while (1) {
        int tecla = _getch();

        if (tecla == 's' || tecla == 'S') {
            printf("s\n");
            return 1;
        }
        if (tecla == 'n' || tecla == 'N') {
            printf("n\n");
            return 0;
        }
    }
}

int main(void) {
    srand(time(NULL));
    esconderCursor();

    int recorde = lerRecorde(ARQUIVO_RECORDE);
    int jogarDeNovo = 1;

    while (jogarDeNovo) {
        int pontos = jogarPartida(recorde);

        if (pontos > recorde) {
            printf("\nNovo recorde! %d pontos!\n", pontos);
            salvarRecorde(ARQUIVO_RECORDE, pontos);
        } else {
            printf("\nFim de jogo! Pontuacao: %d (recorde: %d)\n", pontos, recorde);
        }
        jogarDeNovo = perguntarJogarNovamente();
    }
    printf("Obrigado por jogar!\n");
    return 0;
}
