#include <stdio.h>
#include <stdlib.h>
#include "etlap.h"
#include "asztalok.h"
#include "debugmalloc.h"

/*
    Etlap fajlbairatasa.
    Parameterkent az etlap head-jet kell megadni.
*/
void etlap_fajlbakiir(Etlap *etlap_eleje)
{
    FILE *fp;

    fp = fopen("etlap.txt", "wt");
    if (fp == NULL)
    {
        perror("Etlap fajlbairasa sikertelen!");
        return;
    }

    Etlap *kiir;
    for(kiir = etlap_eleje; kiir != NULL; kiir = kiir->kov)
    {
        fprintf(fp, "%d %s\n", kiir->ar, kiir->nev);
    }

    fclose(fp);
}

/*
    Az asztalok lancolt lista legnagyobb x es y koordinataju elemet adja vissza.
    Parameterkent asztal head-jet, valamint ket integer erteket kell megadni.
    Eloszor az x, majd az y koordinatat.
*/
void asztalok_max_koordinata(Asztalok *asztal_eleje, int *x, int *y)
{
    Asztalok *mozgo;
    for(mozgo = asztal_eleje; mozgo != NULL; mozgo = mozgo->kov)
    {
        *x = mozgo->x;
        *y = mozgo->y;
    }
}

/*
    Asztalok adatainak fajlbairatasa.
    Parameterekent az etlap, valamint az asztalok head-jet kell megadni.
*/
void asztal_adatok_fajlbakiir(Etlap *etlap_eleje, Asztalok *asztal_eleje)
{
    FILE *fp;
    int x, y;

    fp = fopen("asztalok.txt", "wt");
    if (fp == NULL)
    {
        perror("Menu fajlbairasa sikertelen!");
        return;
    }

    asztalok_max_koordinata(asztal_eleje, &x, &y);          //elso sorba a koordinata fog kiiratodni
    fprintf(fp, "%d,%d\n\n", x, y);


    Asztalok *kiir;
    for(kiir = asztal_eleje; kiir != NULL; kiir = kiir->kov)
    {
        fprintf(fp, "%d %d %d %d %d\n", kiir->x, kiir->y, kiir->ferohely, kiir->tetelekdb, kiir->foglalt);
        int meddig = kiir->tetelekdb;
        if(meddig > 0)
        {
            for(int i = 0; i < meddig; i++)
            {
                char etel[101] = "";
                etelnev(etlap_eleje, kiir->etel[i], etel);
                fprintf(fp, "%d %d\n", kiir->etel[i], kiir->db[i]);
            }
        }

    }

    fclose(fp);
}

/*
    Etlap beolvasasa fajlbol. (etlap.txt)
    Parameterkent az etlap head-jere mutato pointert kell megadni.
*/
void etlap_beolvas(Etlap **etlap_eleje)
{

    FILE *fp;
    int ar;
    char *etel;

    fp = fopen("etlap.txt", "rt");
    if (fp == NULL)
    {
        perror("Etlap fajlbololvasasa sikertelen!");
        return;
    }

    while(true)
    {
        if(feof(fp))
        {
            break;

        }
        //soronkent beletesszuk az etlapba oket
        if(fscanf(fp, "%d %[^\n]", &ar, etel) == 2)
        {
            *etlap_eleje = etlap_fajlbol(*etlap_eleje, etel, ar);
        }

    }

    fclose(fp);
}

/*
    Asztalok beolvasasa fajlbol. (asztalok.txt)
    Parameterkent az asztalok head-jet, valamint a felhasznalo altal megadott x,y koordinata kell.
*/
void asztalok_beolvas(Asztalok *asztal_eleje, int x_be, int y_be)
{
    FILE *fp;

    int Xmax, Ymax;

    fp = fopen("asztalok.txt", "rt");
    if (fp == NULL)
    {
        perror("Asztalok fajlbololvasasa sikertelen!");
        return;
    }

    fscanf(fp, "%d,%d", &Xmax, &Ymax);              //eloszor beolvassuk az elmentett sorok, oszlopok szamat
    int valasztas = 2;
    int hibauzenet = 0;
    bool kilep = false;
    if(x_be < Xmax || y_be < Ymax)              //ellenorizzuk, hogy a megadott sor-, oszlopszam nagyobb-e az elmentettnel
    {
        system("@cls||clear");
        printf("A megadott asztalszam [%d,%d] tul keves, igy adatok veszhetnek el! Biztos folytatni akarod?\n", x_be, y_be);
        printf("A fajlban elmentett asztalok sorszama: [%d], oszlopszama:[%d]\n", Xmax, Ymax);
        printf("\nIgen - 1\tNem - 0\n\n");
        printf("Add meg a valasztasodhoz megfelelo szamot!\n");
        while(valasztas > 1)
        {
            if(hibauzenet > 0)
            {
                printf("A valasztasod 0 vagy 1 lehet!\n");
            }
            hibauzenet++;
            valasztas = integer_input();
        }
    }

    hibauzenet = 0;
    char felesleg;
    int sor = x_be;
    int oszlop = y_be;
    while (kilep == false)
    {
        switch(valasztas)
        {
        case 2:
            asztalok_beolvas_vegig(asztal_eleje, fp);               //a megadott sor-, oszlopszam nagyobb a mentettnel, vagy a felhasznalo felirast valasztott
            kilep = true;
            break;
        case 1:
            asztalok_beolvas_reszben(asztal_eleje, fp, sor, oszlop);
            kilep = true;
            break;
        case 0:
            if(hibauzenet == 0)
            {
                scanf("%c", &felesleg);     //elotte levo szoveg ne zavarjon be
            }
            printf("Adj meg egy megfelelo sor- es oszlopszamot ebben az alakban: [sorszam,oszlopszam]\n");      //addig kerjuk, mig megfelelot nem ad meg
            printf("Legalabb %d soru, %d oszlopu legyen az adatok megorzese erdekeben.\n", Xmax, Ymax);
            koordinata_input(&sor, &oszlop);
            hibauzenet++;
            break;
        }
        if((sor < Xmax || oszlop < Ymax))
        {
            valasztas = 0;
            if(hibauzenet > 0)
            {
                printf("Nem megfelelo asztalszam!\n\n");
            }
        }
        else if(kilep == false)
        {
            asztalok_felszabadit(asztal_eleje);                                 //az elejen letrehozott asztal lancolt lista felszabaditas
            asztal_eleje = asztalok_inicializalas(asztal_eleje, sor, oszlop);   //egy uj lancolt lista letrehozasa, amelybe belefer a megadott asztalszam
            valasztas = 2;
        }

    }
    fclose(fp);
}

/*
    Vegig beolvasa a fajlbol az asztalok adatait, ha a megadott asztalszam egyenlo, vagy tobb a fajlban mentettnel.
    Parameterkent az asztalok head-je, valamint a fajlkezelo pointer kell.
*/
void asztalok_beolvas_vegig(Asztalok *asztal_eleje, FILE *fp)
{
    int x, y, ferohely, db, eteldb, etelsorszam, foglalt;
    while(true)
    {
        if(feof(fp))
        {
            break;
        }
        if(fscanf(fp, " %d %d %d %d %d", &x, &y, &ferohely, &db, &foglalt) == 5)
        {
            Asztalok *asztal = asztalok_keres(asztal_eleje, x, y);
            asztal_fajlbol_alapadatok(asztal, ferohely, foglalt);
            for(int i=0; i < db; i++)           //ahany etel van(db) annyi sor tartozik egy asztalhoz
            {
                fscanf(fp, "%d %d", &etelsorszam, &eteldb);
                asztal_fajlbol_etelek(asztal, etelsorszam, eteldb);
            }

        }
    }
}

/*
    Csak reszben olvassa be az elmentett adatokat. A megadott x, y koordinata felettieket kihagyja.
    Parameterkent az asztalok head-je, a fajlkezelo pointer, valamint a beolvasando max
    sor- es oszlopszam kell.
*/
void asztalok_beolvas_reszben(Asztalok *asztal_eleje, FILE *fp, int sormax, int oszlopmax)
{
    int x, y, ferohely, db, eteldb, etelsorszam, foglalt;
    while(true)
    {
        if(feof(fp))
        {
            break;
        }
        if(fscanf(fp, " %d %d %d %d %d", &x, &y, &ferohely, &db, &foglalt) == 5)
        {
            if(x <= sormax && y <= oszlopmax)               //ellenorizzuk, hogy a koordinata megfelelo-e
            {
                Asztalok *asztal = asztalok_keres(asztal_eleje, x, y);
                asztal_fajlbol_alapadatok(asztal, ferohely, foglalt);
                for(int i=0; i < db; i++)           //ahany etel van annyi sor tartozik az asztalhoz
                {
                    fscanf(fp, "%d %d", &etelsorszam, &eteldb);
                    asztal_fajlbol_etelek(asztal, etelsorszam, eteldb);
                }
            }
            else
            {
                for(int i=0; i < db; i++)           //a nem kell sorok eteleit figyelmen kivul hagyjuk, atlepunk rajtuk
                {
                    fscanf(fp, "%d %d", &etelsorszam, &eteldb);
                }
            }

        }
    }
}
