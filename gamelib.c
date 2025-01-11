#include "gamelib.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int c; //variabile controllo input
void svuotaBuffer();
static void stats_players();

//funzioni per imposta_gioco()
static void creazione_giocatori();
static void selezione_classe();
static void set_principe();
static void set_doppelganger();
static void set_point();
static void menu_impostazione_mappa();
static void ins_stanza(bool nuova_mappa);


static int num_Stanze = 0; //variabile che contiene il numero di stanze
static struct Stanza* pFirst = NULL;//puntatore in cima alla lista Stanza
static struct Stanza* pLast = NULL;//puntatore in fondo alla lista Stanza


bool impostato = false;
Giocatore* players[3];
unsigned short num_giocatori;



//Giocatore* giocatori[3];

void imposta_gioco(){
    unsigned int scelta = 10;
    if (impostato == false){

        printf("Essendo la prima partita creare i giocatori\n");
        creazione_giocatori();
        set_point(); 
        printf("\e[1;33mI giocatori sono stati configurati\n");    
        stats_players(); 
    }
    
    
    do {
    printf("\nIl menu dell'impostazione:\n");
    printf("\t0. Inizializzazione stanza\n");
    printf("\t1. Vai all'impostazione della mappa\n");
    printf("\t2. Vai all'impostazione della mappa\n");
    printf("\t3. Vai all'impostazione del tempo di pausa del gioco\n");

    printf(">> ");
    scanf("%hu", &scelta);
    svuotaBuffer();

    if(scelta == 1) {
        ins_stanza(true);
    } else if(scelta == 2) {
        printf("menu_impostazione_giocatori()");
    } else if(scelta == 3) {
        printf("menu_impostazione_tempo_pausa()");
    } else if(scelta > 3) {
        printf("Il comando non riconosciuto!\n");
    }
    }
    while(scelta);{
    }
}



static void creazione_giocatori(){
    do{
        printf("\e[0;33m E' possibile inserire al massimo 3 giocatori \e[1;33m \nQuanti giocatori si desidera utilizzare: ");
        scanf("%hu", &num_giocatori);
        svuotaBuffer();
        }
    while (num_giocatori == 0 || num_giocatori > 3);

    for (int i = 0; i < num_giocatori; i++ ){
        players[i] = (Giocatore*) (malloc(sizeof(Giocatore)));
        printf("Ciao Giocatore %d! Qual'è il tuo nome? (Massimo 10 caratteri): ", i+1); //Chiedo di inserire il nome di giocatore
        do {
            fgets(players[i] -> nome_giocatore, 10, stdin);
            players[i] -> nome_giocatore[strcspn(players[i] -> nome_giocatore, "\n")] = 0;
            svuotaBuffer();
        }while (strcmp(players[i] -> nome_giocatore, "")== 0);
        printf("Il giocatore %d impostato con successo!\n", i+1);


    } 
    selezione_classe();
    if (num_giocatori< 2){
        printf("Il \e[0;34m Principe \e[1;33m sarà il giocatore: ");
        printf("%s", players[0]->nome_giocatore);
        printf("\n");    
    }
    else {
        printf("Selezionato il \e[0;34m Principe \e[1;33m ! \n");
    } 
}


static void selezione_classe(){
    int unsigned a=0 , scelta;

    for (int a = 0; num_giocatori > a; a++ ){
        set_doppelganger(a);    
    }
    if(num_giocatori==1){
        set_principe(1);
    }
    else{
        printf("Selezionare chi sara' il principe : ");
        scanf("%u", &scelta);
        svuotaBuffer();
        set_principe(scelta);
    }
}




static void set_principe(int unsigned scelta){
    players[scelta - 1] -> tipo_giocatore = principe;
}

static void set_doppelganger(int unsigned a){
    players[a] -> tipo_giocatore = doppelganger;
}

static void set_point(){
    for (int i=0 ; num_giocatori > i ; i++ ){
        players[i]->p_vita_max = 3;
        players[i]->p_vita = 3;
    }
}

static void ins_stanza(bool nuova_mappa){
    int i;
    time_t t;

    srand((unsigned)time(&t));
    Stanza* new_Stanza = (Stanza*) (malloc(sizeof(Stanza)));
    new_Stanza -> destra = NULL;
    new_Stanza -> sinistra = NULL;
    new_Stanza -> sopra = NULL;
    new_Stanza -> sotto = NULL;

    if(nuova_mappa){
        pFirst = new_Stanza;
    } else {
        pLast -> destra = new_Stanza;
    }
    
    for (int i = 0; i < 15; i++){
       new_Stanza -> Tipo_stanza = rand() % 10;
       new_Stanza -> Tipo_trabocchetto = rand() % 10;
    }

}



static void stats_players(){
    int i;
    for (int i = 0; i < num_giocatori; i++){
        printf("%s\n", players[i]->nome_giocatore);
        printf("type class : %d\n", players[i]->tipo_giocatore);
        printf("max hp: %d\n", players[i]->p_vita_max);
        printf("current hp: %d\n", players[i]->p_vita);
    }
    
}    

void svuotaBuffer(){
    while ((c =getchar()) != '\n'&& c != EOF);
}
// Definizioni delle funzioni in gamelib.c.
// Piu altre funzioni di supporto.
// Le funzioni richiamabili in main.c non devono essere static.
// Le altre devono essere static (non visibili all'esterno).
