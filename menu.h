#ifndef MENU
#define MENU
#include <stdbool.h>
#include "asztalok.h"
#include "etlap.h"

void menu_valaszto(bool *kilep, Etlap **etlap_eleje, Asztalok **asztal_eleje);
void menu_kirajzol();
void sorminta_fomenu();
void sorminta_almenu();
void etterem_menu();
void etterem_asztalok();
void foglaltsagi_menu();
void szamla_minta();
char *szoveg_beolvas();
int integer_input();
void koordinata_input(int *x, int *y);


#endif
