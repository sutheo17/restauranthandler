#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "menu.h"
#include "etlap.h"
#include "asztalok.h"
#include "debugmalloc.h"
#include "fajlkezeles.h"

//ellenorizzuk, hogy a sorok/oszlopok szama nem nagyobb 25-nel
void asztalok_x_y(int *x, int *y)
{
    int sor, oszlop;
    int hibadb = 0;
    do
    {
        if(hibadb > 0)
        {
            printf("Tul nagy sor- vagy oszlopszamot adtal meg !\n");
        }
        hibadb++;
        koordinata_input(&sor, &oszlop);
    }   while (sor > 25 || oszlop > 25);
    *x = sor;
    *y = oszlop;
}

int main()
{
    Etlap *etlap_eleje = NULL;
    Asztalok *asztal_eleje = NULL;
    printf("Add meg az asztalok szamat! Ebben az alakban: [sorok szama,oszlopok szama]!\n");
    printf("Legfeljebb 25x25-os lehet !\n");
    int sor, oszlop;
    asztalok_x_y(&sor, &oszlop);
    asztal_eleje = asztalok_inicializalas(asztal_eleje, sor, oszlop);       //asztalok lancolt lista letrehozasa
    sorminta_fomenu();
    printf("/");
    printf("%44s%6s","UDVOZOLLEK AZ ETTEREMKEZELO PROGRAMBAN!","/\n");
    etlap_beolvas(&etlap_eleje);
    asztalok_beolvas(asztal_eleje, sor, oszlop);                            //lancolt listakba fajlbol adatok beolvasas
    bool kilep = false;
    do
    {
        menu_valaszto(&kilep, &etlap_eleje, &asztal_eleje);                 //meghivjuk a menut
    }
    while (kilep == false);
    etlap_fajlbakiir(etlap_eleje);
    asztal_adatok_fajlbakiir(etlap_eleje, asztal_eleje);                    //lancolt listak fajlbairatasa, majd felszabaditasa
    etlap_felszabadit(etlap_eleje);
    asztalok_felszabadit(asztal_eleje);
    return 0;
}
