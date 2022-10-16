#ifndef _MAPA_H_
#define _MAPA_H_

typedef struct mapa MAPA;
//cria um "apelido" pro tipo (para o struct mapa chamado MAPA)

typedef struct posicao POSICAO;

void liberamapa(MAPA* m);
void lemapa(MAPA* m);
void alocamapa(MAPA* m);
int encontramapa(MAPA* m, POSICAO* p, char c);
int ehvalida(MAPA* m, int x, int y);
int ehvazia(MAPA* m, int x, int y);
void andanomapa(MAPA* m, int xorigem, int yorigem, int xdestino, int ydestino);
void copiamapa(MAPA* destino, MAPA* origem);
int podeandar(MAPA* m, char personagem, int x, int y);
int ehparede(MAPA* m, int x, int y);
int ehpersonagem(MAPA* m, char personagem, int x, int y);

#endif