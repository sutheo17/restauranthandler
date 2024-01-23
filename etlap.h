#ifndef ETLAP
#define ETLAP
#include "stdbool.h"

typedef struct Etlap{
    char nev[101];
    int ar;
    struct Etlap *kov;
} Etlap;

Etlap *etlap_bovit(Etlap *etlap_eleje, char *etel, int ar);
Etlap *etlap_torol(Etlap *etlap_eleje, int sorszam);
Etlap *etel_felvetel(Etlap *etlap_eleje);
Etlap *etel_levetel(Etlap *etlap_eleje);
void etlap_kiirat(Etlap *etlap_eleje);
void etlap_felszabadit(Etlap *etlap_eleje);
Etlap *etlapkezeles(Etlap *etlap_eleje);
int etel_db(Etlap *etlap_eleje);
int darabar(Etlap *etlap_eleje, int sorszam);
void etelnev(Etlap *etlap_eleje, int sorszam, char *etel);
Etlap *etlap_fajlbol(Etlap *etlap_eleje, char *etel, int ar);

#endif
