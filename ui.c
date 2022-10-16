#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "foge.h"
#include "mapa.h"
#include "mapa.c"

char desenhofantasma[4][7] = {
    {" .-.  " },
    {"| OO| " },
    {"|   | " },
    {"'^^^' " }
};

char desenhoparede[4][7] = {
    {"......" },
    {"......" },
    {"......" },
    {"......" }
};

char desenhoheroi[4][7] = {
    {" .--. "  },
    {"/ _.-'"  },
    {"\\  '-." },
    {" '--' "  }
};

char desenhopilula[4][7] = {
    {"      "},
    {" .-.  "},
    {" '-'  "},
    {"      "}
};

char desenhovazio[4][7] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "}
};


void imprimeparte(char desenho[4][7], int parte){
	printf("%s", desenho[parte]);
}

void imprimemapa(MAPA* m){
	for(int i= 0; i < m->linhas; i++){	
		for(int parte = 0; parte < 4; parte++){
			for(int j =0; j < m->colunas; j++){
				
				switch(m->matriz[i][j]){
					case FANTASMA:
						imprimeparte(desenhofantasma, parte);
						break;
					
					case HEROI:
						imprimeparte(desenhoheroi, parte);
						break;
					
					case PILULA:
						imprimeparte(desenhopilula, parte);
						break;
					
					case '|':
					case '-':
					//pode por vários cases dessa forma para executar uma funcionalidade
						imprimeparte(desenhoparede, parte);
						break;
					
					case '.':
						imprimeparte(desenhovazio,parte);
						break;
				}
			}
		printf("\n");
		}
	}
}

void resultado(MAPA* m){
	POSICAO pos;
	int fogefogenomapa = encontramapa(m, &pos, HEROI);
	int fantasmanomapa = encontramapa(m, &pos, FANTASMA);
	
	if(!fogefogenomapa){
    	printf("\nQue pena! vc foi comido.");
	
	    printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
	}
	else if(!fantasmanomapa){
	    printf("\nParabens, voce ganhou!\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");	
	}	
}