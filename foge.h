#ifndef _FOGE_H_
#define _FOGE_H_

#define HEROI '@'
#define FANTASMA 'F'
#define CIMA 'w'
#define BAIXO 's'
#define DIREITA 'd'
#define ESQUERDA 'a'
#define PILULA 'P'
#define BOMBA 'b'

int acabou();
void move(char direcao);
int ehdirecao(char direcao);
void fantasmas();
int praondefantasmavai(int xatual, int yatual, int* xdestino, int* ydestino);
void explodepilula(int x, int y, int qtd);
void explodepilula2(int x, int y,int somax, int somay, int qtd);

#endif