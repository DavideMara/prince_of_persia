#include "gamelib.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

//funzioni gestione players
static void creazione_giocatori();
static void selezione_classe();
static void set_principe();
static void set_doppelganger();
static void set_point();

// variabili gestione player
bool impostato = false;
Giocatore* players[3];
unsigned short num_giocatori;

//funzioni gestione mappa
static void menu_impostazione_mappa();
static void ins_stanza(bool nuova_mappa);
static void del_stanza(void);

// variabili per imposta_map()
bool nuova_mappa;
Stanza * pFirst = NULL;
Stanza * pLast = NULL;
int num_Stanze = 0;
bool mappa_chiusa = false;


// controllo input
int c; 
void svuotaBuffer();
static void stats_players();


void imposta_gioco(){
    unsigned int scelta = 10;
    if (impostato == false){

        printf("Essendo la prima partita impostiamo i giocatori\n");
        creazione_giocatori();
        set_point(); 
        printf("\e[1;33mI giocatori sono stati configurati\n");    
        stats_players(); 
        impostato == true;
    }
    
    
    do {
        printf("\nIl menu dell'impostazione:\n");
        printf("\t0. Esci al menu' generale\n");
        printf("\t1. Vai alle impostazioni mappa\n");
        printf("\t2. \n");
        printf("\t3. Vai alle impostazioni del tempo di pausa del gioco\n");

        printf(">> ");
        scanf("%hu", &scelta);
        svuotaBuffer();

        if(scelta == 1) {
            system ("clear");
        } else if(scelta == 2) {
            system ("clear");
            
        } else if(scelta == 3) {
            system ("clear");
            printf("menu_impostazione_tempo_pausa()");
        } else if(scelta > 3) {
            system ("clear");
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

static void menu_impostazione_mappa(){
    unsigned int scelta = 10;
    do {
        printf("\nIl menu della mappa:\n");
        printf("\t0. Esci dal menù della mappa\n");
        printf("\t1. Inserisci stanza nella mappa! (max 15 stz)\n");
        printf("\t2. Cancellare ultima stanza nella mappa!\n");
        printf("\t3. \n");

        printf(">> ");
        scanf("%hu", &scelta);
        svuotaBuffer();

        if(scelta == 1) {
            system ("clear");
            ins_stanza(nuova_mappa);
        } else if(scelta == 2) {
            system ("clear");
            del_stanza();
        } else if(scelta == 3) {
            system ("clear");
        } else if(scelta > 3) {
            system ("clear");
        }
    }
    while(scelta);{
    }    
}

static void ins_stanza(bool nuova_mappa) {
    if (mappa_chiusa) {
        printf("Impossibile inserire una nuova stanza: la mappa è già chiusa!\n");
        return;
    }

    // Allochiamo la nuova stanza
    Stanza* new_Stanza = malloc(sizeof(Stanza));
    if (!new_Stanza) {
        fprintf(stderr, "Errore di allocazione memoria!\n");
        return;
    }

    // Azzeriamo i puntatori
    new_Stanza->destra   = NULL;
    new_Stanza->sinistra = NULL;
    new_Stanza->sopra    = NULL;
    new_Stanza->sotto    = NULL;

    // Lettura da tastiera dei valori per la nuova stanza
    int tipo_stanza, tipo_trab, tipo_tes;
    printf("Inserisci il tipo di stanza (0..9): ");
    scanf("%d", &tipo_stanza);
    printf("Inserisci il tipo di trabocchetto (0=NESSUNO, 1=TEGOLA, 2=LAME, 3=CADUTA, 4=BURRONE): ");
    scanf("%d", &tipo_trab);
    printf("Inserisci il tipo di tesoro (0=NESSUNO, 1=VERDE, 2=BLU, 3=ROSSO, 4=SPADA, 5=SCUDO): ");
    scanf("%d", &tipo_tes);

    // Assegniamo ai campi della struct
    new_Stanza->Tipo_stanza       = (enum Tipo_stanza)tipo_stanza;
    new_Stanza->Tipo_trabocchetto = (enum Tipo_trabocchetto)tipo_trab;
    new_Stanza->Tipo_tesoro       = (enum Tipo_tesoro)tipo_tes;

    // Se la mappa è nuova oppure non esistono stanze
    if (nuova_mappa || pFirst == NULL) {
        pFirst     = new_Stanza;
        pLast      = new_Stanza;
        num_Stanze = 1;
        printf("Creata la prima stanza della mappa (nuova_mappa=%d).\n", nuova_mappa);
        return;
    }

    // Altrimenti chiedo in quale direzione inserire la nuova stanza rispetto a pLast
    printf("\nDove vuoi inserire la stanza rispetto a quella attuale?\n");
    printf("(s = sopra, g = sotto, d = destra, i = sinistra): ");
    char direzione;
    scanf(" %c", &direzione); // spazio prima di %c per assorbire eventuali newline

    switch (direzione) {
        case 's':
            pLast->sopra       = new_Stanza;
            new_Stanza->sotto = pLast;
            break;
        case 'g':
            pLast->sotto      = new_Stanza;
            new_Stanza->sopra = pLast;
            break;
        case 'd':
            pLast->destra      = new_Stanza;
            new_Stanza->sinistra = pLast;
            break;
        case 'i':
            pLast->sinistra   = new_Stanza;
            new_Stanza->destra = pLast;
            break;
        default:
            printf("Direzione non valida! Rilascio la nuova stanza...\n");
            free(new_Stanza);
            return;
    }

    // Aggiorno pLast
    pLast = new_Stanza;
    num_Stanze--;

    printf("Nuova stanza creata con successo.\n");
    printf("Numero stanze attuali: %d\n", num_Stanze);
}

// Funzione d'appoggio per trovare la "stanza precedente" a pLast
// Restituisce NULL se pLast non ha un "genitore", cioè se pLast == pFirst.
static Stanza* trova_precedente(Stanza* stanza) {
    if (!stanza) return NULL;
    if (stanza == pFirst) return NULL; // Non c'è precedente

    // Se la stanza ha un sinistra != NULL, controlliamo se stanza->sinistra->destra == stanza
    if (stanza->sinistra && stanza->sinistra->destra == stanza) {
        return stanza->sinistra;
    }
    // Se la stanza ha un destra != NULL, controlliamo se stanza->destra->sinistra == stanza
    if (stanza->destra && stanza->destra->sinistra == stanza) {
        return stanza->destra;
    }
    // Se la stanza ha un sopra != NULL, controlliamo se stanza->sopra->sotto == stanza
    if (stanza->sopra && stanza->sopra->sotto == stanza) {
        return stanza->sopra;
    }
    // Se la stanza ha un sotto != NULL, controlliamo se stanza->sotto->sopra == stanza
    if (stanza->sotto && stanza->sotto->sopra == stanza) {
        return stanza->sotto;
    }

    return NULL; // Caso inatteso se la logica è sempre "lineare".
}

static void del_stanza(void) {
    if (mappa_chiusa) {
        printf("Impossibile cancellare stanze: la mappa è già chiusa!\n");
        return;
    }

    if (!pLast) {
        printf("Non ci sono stanze da cancellare!\n");
        return;
    }

    // Se c'è solo una stanza in mappa, la rimuoviamo completamente
    if (pLast == pFirst) {
        free(pLast);
        pLast = NULL;
        pFirst = NULL;
        num_Stanze = 0;
        printf("Cancellata l'unica stanza presente: mappa ora vuota.\n");
        return;
    }

    // Altrimenti troviamo la stanza precedente
    Stanza* precedente = trova_precedente(pLast);
    if (!precedente) {
        // Se succede, c'è qualche errore di collegamento
        printf("Errore: impossibile trovare la stanza precedente!\n");
        return;
    }

    // Scolleghiamo pLast dal "precedente" in base a quale puntatore punta a pLast
    if (precedente->destra == pLast) {
        precedente->destra = NULL;
    }
    if (precedente->sinistra == pLast) {
        precedente->sinistra = NULL;
    }
    if (precedente->sopra == pLast) {
        precedente->sopra = NULL;
    }
    if (precedente->sotto == pLast) {
        precedente->sotto = NULL;
    }

    // Cancelliamo la stanza
    free(pLast);
    pLast = precedente;
    int num_Stanze = num_Stanze--;

    printf("Stanza cancellata correttamente. Stanze rimanenti: %d\n", num_Stanze);
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
