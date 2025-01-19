// Dichiarazione delle funzioni da chiamare in main.c
// Definizione dei tipi necessari alla libreria
void imposta_gioco();
void gioca();
void crediti();
void termina_gioco();

typedef enum Tipo_giocatore{principe, doppelganger} Tipo_giocatore;
typedef enum Tipo_stanza{corridoio, scala, sala_banchetto, magazzino, posto_guardia, prigione, armeria, moschea, torre, bagni};
typedef enum Tipo_trabocchetto{nessuno, tegola, lame, caduta, burrone};
typedef enum Tipo_tesoro{nessun_tesoro, veleno_verde, blu_guarigione, rosso_aumenta, spada_tagliente, scudo};
typedef enum bool {true = 1, false = 0} bool;



typedef struct Giocatore {
    char nome_giocatore [10];
    enum Tipo_giocatore tipo_giocatore;
    struct Stanza* posizione;
    unsigned char p_vita_max;
    unsigned char p_vita;
    unsigned char dadi_attacco;
    unsigned char dadi_difesa;
} Giocatore;

typedef struct Stanza {
    struct Stanza* destra;
    struct Stanza* sinistra;
    struct Stanza* sotto;
    struct Stanza* sopra;
    enum Tipo_stanza Tipo_stanza;
    enum Tipo_trabocchetto Tipo_trabocchetto;
    enum Tipo_tesoro Tipo_tesoro;
} Stanza;