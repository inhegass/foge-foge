#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "foge.h"
#include "mapa.h"
#include "ui.h"

#include "mapa.c"
//arquivo em c com as funções de mapa e os structs

#include "ui.c"

MAPA m;
//criou uma variável m tipo mapa
//pode ser feito n variáveis e cada uma será referida a um conjunto diferente de variáveis dentro do struct

POSICAO heroi;

int tempilula = 0;

int praondefantasmavai(int xatual, int yatual, int* xdestino, int* ydestino){
	
	int opcoes[4][2] = {{xatual, yatual + 1}, {xatual + 1, yatual},
		{xatual, yatual - 1}, {xatual - 1, yatual}};
	
	srand(time(0));
	for(int i = 0; i < 10; i++){
		int posicao = rand() % 4;
		
		if(podeandar(&m, FANTASMA, opcoes[posicao][0], opcoes[posicao][1])){
			*xdestino = opcoes[posicao][0];
			*ydestino = opcoes[posicao][1];
			
			return 1;
		}
	}
	
	return 0;
	
}

void fantasmas(){
	MAPA copia;
	
	copiamapa(&copia, &m);
	//função para copiar o mapa e poder analisar a posição do fantasma sem atrapalhar a movimentação dele no mapa original
	
	for (int i = 0; i < m.linhas; i++){
		for (int j = 0; j < m.colunas; j++){
			
			if(copia.matriz[i][j] == FANTASMA){
				
				int xdestino;
				int ydestino;
				
				int encontrou = praondefantasmavai(i, j, &xdestino, &ydestino);
				
				if(encontrou){
					andanomapa(&m, i, j, xdestino, ydestino);
				}
			}
			
		}
	}
	liberamapa(&copia);
}

int acabou() {
	POSICAO pos;
	int fogefogenomapa = encontramapa(&m, &pos, HEROI);
	int fantasmanomapa = encontramapa(&m, &pos, FANTASMA);
	
	return !fogefogenomapa || !fantasmanomapa;
}

int ehdirecao(char direcao) {
	return
		direcao == ESQUERDA || 
		direcao == CIMA ||
		direcao == BAIXO ||
		direcao == DIREITA;
	// "||" significa ou
}

void move(char direcao){
	
	if(!ehdirecao(direcao))
		return;
		//acontece nada no programa, se o usuário digitar algo diferente de a,s,w ou d
	
	int proximoy = heroi.y;
	int proximox = heroi.x;
	
	
	switch(direcao) {
	//semelhante ao if/else, mas roda todos os casos a partir do pedido, se n colocar break	switch(direcao) {
		//qual é o caso	
		case ESQUERDA:
			proximoy--;
			break;
		case CIMA:
			proximox--;
			break;
		case BAIXO:
			proximox++;
			break;
		case DIREITA:
			proximoy++;
			break;
	}
	
	if(!podeandar(&m, HEROI, proximox, proximoy)) return;
	// por ser so um comando, não precisa de chaves e pode colocar o comando do if/else na mesma linha depois do espaço
	
	if (ehpersonagem(&m, PILULA, proximox, proximoy)){
		tempilula = 2;
	}

	andanomapa(&m, heroi.x, heroi.y, proximox, proximoy);
	heroi.x = proximox;
	heroi.y = proximoy;		
}
 
void explodepilula(int x, int y, int qtd){
	
	if(!tempilula) return;
	
	explodepilula2(heroi.x, heroi.y, 0, 1, qtd);
	explodepilula2(heroi.x, heroi.y, 1, 0, qtd);
	explodepilula2(heroi.x, heroi.y, 0, -1, qtd);
	explodepilula2(heroi.x, heroi.y, -1, 0, qtd);

	tempilula--;			
}

void explodepilula2(int x, int y,int somax, int somay, int qtd){
//funçao recursiva

	if(qtd == 0) return;
	//ponto de fuga da função recursiva	
	
	int novox = x+ somax;
	int novoy = y + somay;
	
	if(!ehvalida(&m, novox, novoy)) return;
	if(ehparede(&m, novox, novoy)) return;

	
	m.matriz[novox][novoy] = '.';
	explodepilula2(novox, novoy, somax, somay, qtd-1);
	
}

int main(){
	
	lemapa(&m);
	encontramapa(&m, &heroi, HEROI);
	
	do{
		printf("Tem pilula: %s\n", (tempilula != 0 ? "SIM" : "NAO"));
		imprimemapa(&m);

        char comando;
        scanf(" %c", &comando);
        move(comando);
		if(comando == BOMBA) {
		
			explodepilula(heroi.x,heroi.y, 2);
		
		}
		fantasmas();
		
	} while (!acabou());
	
	liberamapa(&m);
	
	resultado(&m);
}