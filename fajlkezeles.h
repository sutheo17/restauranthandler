#ifndef FAJLKEZELES
#define FAJLKEZELES

void etlap_fajlbakiir(Etlap *eleje);
void asztal_adatok_fajlbakiir(Etlap *etlap_eleje, Asztalok *asztal_eleje);
void asztalok_max_koordinata(Asztalok *asztal_eleje, int *x, int *y);
void etlap_beolvas(Etlap **eleje);
void asztalok_beolvas_vegig(Asztalok *asztal_eleje, FILE *fp);
void asztalok_beolvas_reszben(Asztalok *asztal_eleje, FILE *fp, int sormax, int oszlopmax);
void asztalok_beolvas(Asztalok *asztal_eleje, int x_be, int y_be);

#endif
