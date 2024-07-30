#include "raylib.h"
#include <stdlib.h>
#include <time.h>

typedef struct{
    int pos_x, pos_y, desloc_x, desloc_y;
}Jogador;

typedef struct{
    int
}Inimigo;

typedef struct{
    int tipo, vida, ataque, defesa, xp, nivel;
}Infmon;

//representar os tipos como inteiros de 1 ate 3 (tipo 1, 2, 3)
//todos os outros atributos representados tambem como inteiros
