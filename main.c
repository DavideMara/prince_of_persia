#include "gamelib.h"
#include <stdio.h>
#include <stdlib.h>




// Questo file continene solo la definizione della funzione main
// con il menu principale 1-2-3

int main( ) {
    int unsigned scelta;
    do {
        printf("\e[1;33m");
        printf("Menu' Generale: \n1 - Imposta gioco\n2 - Gioca\n3 - Mostra crediti \n4 - Termina gioco. \n");
        scanf("%u", &scelta);
        switch(scelta){
            case 1:
                imposta_gioco();
                printf(" \nsium");
                break;
            case 2:     
                printf("gioca\n");
                break;
            case 3:
                printf("crediti\n");
                break;
            case 4:
                printf("termina_gioco\n");
                break;
        }
        
        printf("\n");
    }while(scelta !=4);
} 