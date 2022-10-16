#ifndef _MAPA_C_
#define _MAPA_C_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "foge.h"
#include "mapa.h"

struct mapa {
	//conjunto de multiplas variaveis diferentes
	char** matriz;
	//** e ponteiro de ponteiro (matriz)
	//matrizes sao ponteiros que apontam para uma lista de arrays, cada linha e um ponteiro
	int linhas;
	int colunas;
};

struct posicao {
	int x;
	int y;
};

void liberamapa(MAPA* m){
	for(int i= 0; i < m->linhas; i++){
		//m->, ou (*m), pra se referir ao ponteiro da variavel m da struct mapa 
		free(m->matriz[i]);
		//liberar a memoria alocada
		//libera cada linha
	}
	free(m->matriz);
	//para o ponteiro todo
}

void alocamapa(MAPA* m){
	m->matriz = malloc(sizeof(char*) * m->linhas);
	//alocacao de memoria dinamica
	//nao especifica o tamnho da memoria alocada
	//para char malloc(1), para double malloc(8), para int malloc(4) (numero de bytes)
	//a funcao sizeof() deifine quantos bytes um tipo de variavel precisa
	//ao multiplicar dentro de um malloc() aloca mais de uma variavel de um determinado tipo dentro de um ponteiro
	for(int i = 0; i < m->linhas; i++){
		m->matriz[i] = malloc(sizeof(char) * (m->colunas + 1));
		//aloca a memoria como uma matriz
		//+1 no final por causa do enter
	}
}

void lemapa(MAPA* m){
	FILE* f;
	f = fopen("mapa.txt", "r");
	if(f == 0){
		printf("Erro na leitura do mapa\n");
		exit(1);
		}
		
	fscanf(f, "%d %d", &m->linhas, &m->colunas);
	
	alocamapa(m);
	
	for(int i = 0; i < 5; i++){
		fscanf(f, "%s", m->matriz[i]);
		//adiciona uma linha do texto para a linha da matriz
	}	
	fclose(f);	
}



int encontramapa(MAPA* m, POSICAO* p, char c){
	//acha a posicao do foge-foge
	for(int i = 0; i < m->linhas; i++){
		//m. e pq se refere a variavel m da struct mapa
		for(int j = 0; j < m->colunas; j++){
			if(m->matriz[i][j] == c){
				// sempre que usar matriz e char usar uma aspa (''), inves de duas ("") para se referir a um termo
				p->x = i;
				p->y = j;
				return 1;
			}
		}
	}
	
	return 0;
	
}

int ehvalida(MAPA* m, int x, int y) {
	if(x >= m->linhas) 
	//nao precisa colocar chave no if/else se for so um comando
		return 0;
	if(y >= m->colunas) 
		return 0;

	return 1;	
}

int ehvazia(MAPA* m, int x, int y) {
	return m->matriz[x][y] == '.';
}

void andanomapa(MAPA* m, int xorigem, int yorigem, 
	int xdestino, int ydestino) {

	char personagem = m->matriz[xorigem][yorigem];
	m->matriz[xdestino][ydestino] = personagem;
	m->matriz[xorigem][yorigem] = '.';

}

void copiamapa(MAPA* destino, MAPA* origem){
	destino->linhas = origem->linhas;
	destino->colunas = origem->colunas;
	
	alocamapa(destino);
	for(int i = 0; i < origem->linhas; i++){
		strcpy(destino->matriz[i], origem->matriz[i]);
		//copia uma string para um lugar de outro
	}
	
}

int podeandar(MAPA* m, char personagem, int x, int y){
	return
		ehvalida(m, x, y) && !ehparede(m, x, y) && !ehpersonagem(m, personagem, x, y);
		//agrupando as funcoes
}

int ehparede(MAPA* m, int x, int y){
	
	return m->matriz[x][y] == '|' || m->matriz[x][y] == '-';

}

int ehpersonagem(MAPA* m, char personagem, int x, int y){
	
	return m->matriz[x][y] == personagem;
	
}

#endif