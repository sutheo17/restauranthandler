#ifndef ASZTAL
#define ASZTAL
#include <stdbool.h>
#include "etlap.h"

typedef struct Asztalok
{
    int x, y;
    int *etel;
    int *db;
    int tetelekdb;
    int ferohely;
    bool foglalt;
    struct Asztalok *kov;
} Asztalok;

void asztalkezeles(Asztalok *asztal_eleje, Etlap *etlap_eleje);
Asztalok *asztalok_inicializalas(Asztalok *asztal_eleje, int sor, int oszlop);
Asztalok *kezdoallapot(Asztalok *uj);
Asztalok *asztalok_koordinata(Asztalok *asztal, int sor, int oszlop);
Asztalok *asztalok_foglaltsag(Asztalok *asztal);
Asztalok *asztalok_keres(Asztalok *eleje, int sor, int oszlop);
void asztalok_foglal(Asztalok *asztal_eleje);
bool telthaz(Asztalok *asztal_eleje);
void asztalok_torol(Asztalok *asztal);
void asztalok_felszabadit(Asztalok *eleje);
void asztal_kezelo(Asztalok *asztal_eleje, int *sorszam, int *oszlopszam);
void asztal_fogyasztas_add(Etlap *etlap_eleje, Asztalok *asztal);
bool asztal_fogyasztas_bennvan(Asztalok *asztal, int sorszam);
void asztal_fogyasztas_kiir(Etlap *etlap_eleje, Asztalok *asztal);
void asztal_fajlbol_alapadatok(Asztalok *asztal, int ferohely, int foglaltsag);
void asztal_fajlbol_etelek(Asztalok *asztal, int sorszam, int eteldb);
void etlap_sorszam(Etlap *etlap_eleje);
void asztalok_szamla(Asztalok *asztal_eleje, Etlap *etlap_eleje);
void foglaltsagi_kezelo(Asztalok *asztal_eleje);
void foglaltsagi_terkep(Asztalok *eleje);
void foglaltsagi_asztal_adatok(Asztalok *asztal_eleje, int x, int y);
void foglaltsagi_asztal_ferohely(Asztalok *asztal_eleje, int x, int y);

#endif
