#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#define LARGURA 800
#define ALTURA 800
#define LADO 20
#define MAX_INIMIGOS 10
#define TRUE 1
#define FALSE 0

int moveInimigo();
void inicializaPosicao();
void redefineDeslocamento();

typedef struct{
    int x, y, dx, dy;
}Inimigo;
//struct inimigo guarda as posicoes x e y e os deslocamentos dx e dy

int main(void)
{
    Inimigo inimigos[MAX_INIMIGOS];
    //vetor de inimigos do tipo struct Inimigo

    int player_x=0,player_y=0,i;
    int returnMove;
    int flagDentroLimites = 1;
    InitWindow(LARGURA, ALTURA, "Quadrado");
    SetTargetFPS(60);

    srand(time(NULL));
    //uma vez so antes do laco

    for(i=0;i<MAX_INIMIGOS;i++){
        inicializaPosicao(&inimigos[i]);
        redefineDeslocamento(&inimigos[i]);
    }
    //antes de comecar inicializa as posicoes e os deslocamentos dos inimigos

    while (!WindowShouldClose() && flagDentroLimites)
    {
        if (IsKeyPressed(KEY_D))
            player_x+=LADO;
        if (IsKeyPressed(KEY_A))
            player_x-=LADO;
        if (IsKeyPressed(KEY_W))
            player_y-=LADO;
        if (IsKeyPressed(KEY_S))
            player_y+=LADO;
        if(player_x<0||player_x>=LARGURA||player_y<0||player_y>=ALTURA)
            flagDentroLimites = 0;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangle(player_x,player_y,LADO,LADO,GREEN);

        for(i=0;i<MAX_INIMIGOS;i++){
            DrawRectangle(inimigos[i].x, inimigos[i].y, LADO, LADO, ORANGE);
        }
        //desenha os inimigos numa posicao aleatoria
        for(i=0;i<MAX_INIMIGOS;i++){
            returnMove = moveInimigo(&inimigos[i]);
            if (returnMove == 0)
                redefineDeslocamento(&inimigos[i]);
        }
        //mexe os inimigos se moveInimigo == e manda redefinir o deslocamento toda vez que moveInimigo == 0
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

int moveInimigo(Inimigo *ptr1_inimigo){
    int mover_x = ptr1_inimigo->x + (LADO * ptr1_inimigo->dx);
    int mover_y = ptr1_inimigo->y + (LADO * ptr1_inimigo->dy);

    if (mover_x > 780 || mover_x < 0 || mover_y > 780 || mover_y < 0){
        return FALSE;
    }
    else {
        ptr1_inimigo->x = mover_x;
        ptr1_inimigo->y = mover_y;
        return TRUE;
    }
}
//mover = posicao + lado * deslocamento
//se o deslocamento eh maior que as paredes, return 0, se nao, realiza o movimento e return 1

void inicializaPosicao(Inimigo *ptr2_inimigo){
    ptr2_inimigo->x = (rand() % (40)) * LADO;
    ptr2_inimigo->y = (rand() % (40)) * LADO;
}
//inicializa as posicoes aleatoriamente dos inimigos

void redefineDeslocamento(Inimigo *ptr3_inimigo){
    do{
    ptr3_inimigo->dx = (-1 + (rand() % (3)));
    ptr3_inimigo->dy = (-1 + (rand() % (3)));
    }while(ptr3_inimigo->dx == 0 && ptr3_inimigo->dy == 0);
}
//redefine o deslocamento dos inimigos, e tenta denovo se dx e dy sao iguais a 0 ao mesmo tempo
