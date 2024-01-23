#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "etlap.h"
#include "menu.h"
#include "debugmalloc.h"

/*A lancolt lista elejere mutato pointer a header fajlban van deklaralva, ezaltal
  a foprogram(main) is latja, tud vele muveleteket vegezni.
  Erre a pointerre innentol kezdve "etlap" -kent fogok hivatkozni (Etlap *etlap_eleje)
*/

/*Ez a fuggveny a felhasznalotol egy szamot ker be. A felhasznalo altal
megadott szam felel a megfelelo opcio kivalasztasaert.
*/
Etlap *etlapkezeles(Etlap *etlap_eleje)
{
    int valasztas;

    bool kilepes = false;
    while(kilepes == false)
    {
        etterem_menu();
        valasztas = integer_input();
        switch (valasztas)
        {
        case 1:
            system("@cls||clear");
            etlap_kiirat(etlap_eleje);
            break;
        case 2:
            system("@cls||clear");
            etlap_eleje = etel_felvetel(etlap_eleje);
            break;
        case 3:
            system("@cls||clear");
            etlap_eleje = etel_levetel(etlap_eleje);
            break;
        case 9:
            system("@cls||clear");
            kilepes = true;
            return etlap_eleje;
            break;
        default:
            printf("Nincs ilyen valasztasi opcio!\n");
            break;
        }
    }
    return etlap_eleje;
}

/*A fuggveny az etlappal ter vissza.
  A felhasznalonak megkell adnia az etlapot paramterkent.
  A szoveg, valamint egy adag etel beolvasasahoz masik ket fuggveny hivodik meg.
  Majd meghivodik az *etel_felvetel fuggveny, amely a tenyleges etelfelfuzest teszi.

*/

Etlap *etlap_fajlbol(Etlap *etlap_eleje, char *etel, int ar)
{
    Etlap *uj = (Etlap*) malloc (sizeof(Etlap));
    int i;
    for(i= 0; etel[i] != '\0' ; i++)
    {
        uj->nev[i] = etel[i];
    }
    uj->nev[i] = '\0';
    uj->ar = ar;
    uj->kov = NULL;

    if (etlap_eleje == NULL)
    {
        etlap_eleje = uj;
        return etlap_eleje;
    }
    else
    {
        Etlap *mozgo = etlap_eleje;
        while (mozgo->kov != NULL)
        {
            mozgo = mozgo->kov;
        }
        mozgo->kov = uj;
        return etlap_eleje;
    }
}

/*
    Az etlaphoz egy etel hozzafuzese.
    Parameterkent az eltap head-jet kell megadni.
    Magaval a lancolt listaval ter vissza.
*/
Etlap *etel_felvetel(Etlap *etlap_eleje)
{
    char *etel;
    printf("Add meg az etel nevet, az enter a szoveg veget jelzi! (max 100 karakter !)\n");
    char felesleges;
    scanf("%c", &felesleges);
    etel = szoveg_beolvas();
    int ar;
    printf("Add meg az etel adagarat!\n");
    ar = integer_input();
    etlap_eleje = etlap_bovit(etlap_eleje, etel, ar);
    free(etel);
    return etlap_eleje;
}

/*A fuggveny az etlappal ter vissza, de a paramterbe megadott
  etelt, valamint arat felveszi kovetkezo elemkent.
  Parameterkent az etlap kell, egy dinamikusan foglalt karaktertomb,
  valamint egy integer kell.
*/
Etlap *etlap_bovit(Etlap *etlap_eleje, char *etel, int ar)
{
    Etlap *uj = (Etlap*) malloc (sizeof(Etlap));
    int i;
    for(i= 0; etel[i] != '\0' ; i++)
    {
        uj->nev[i] = etel[i];
    }
    uj->nev[i] = '\0';
    uj->ar = ar;
    uj->kov = NULL;

    if (etlap_eleje == NULL)
    {
        etlap_eleje = uj;
        return etlap_eleje;
    }
    else
    {
        Etlap *mozgo = etlap_eleje;
        while (mozgo->kov != NULL)
        {
            mozgo = mozgo->kov;
        }
        mozgo->kov = uj;
        return etlap_eleje;
    }
}

/*Az etel levetelert felelos fuggveny.
  Parameterkent az etlapot kell megadnunk. A fuggveny beker
  a felhasznalotol egy sorszamot(integer) aminek a tenyleges
  lancolt lisarol valo torles az *etlap_torol fuggvennyel tortenik.

*/
Etlap *etel_levetel(Etlap *etlap_eleje)
{
    if(etel_db(etlap_eleje) == 0)
    {
        printf("Jelenleg nincs etel az etlapon!\n");
        return etlap_eleje;
    }
    etlap_sorszam(etlap_eleje);
    printf("Adja meg a levenni kivant etel sorszamat!\n");
    int sorszam = integer_input();
    if(sorszam > etel_db(etlap_eleje))
    {
        printf("Tul nagy sorszamot adtal meg!\n");
        return etlap_eleje;
    }
    etlap_eleje = etlap_torol(etlap_eleje, sorszam);
    return etlap_eleje;
}

/*Az etlap valahanyadik elemet torli ez a fuggveny meghivas utan.
  Meg kell adnunk az etlapot, valamint a levenni kivant etel sorszmat.
*/
Etlap *etlap_torol(Etlap *etlap_eleje, int sorszam)
{
    if(sorszam == 1)
    {
        Etlap *kovetkezo;
        kovetkezo = etlap_eleje->kov;
        free(etlap_eleje);
        return kovetkezo;
    }
    else
    {
        int i = 1;
        Etlap *elozo = NULL;
        Etlap *mozgo = etlap_eleje;
        while (i != sorszam)
        {
            elozo = mozgo;
            mozgo = mozgo->kov;
            i++;
        }
        elozo->kov = mozgo->kov;
        free(mozgo);
        return etlap_eleje;
    }
}

/*Az etlap darabszamaval ter vissza.
  Parameterkent az etlapot kell megadnunk.
*/
int etel_db(Etlap *etlap_eleje)
{
    Etlap *p;
    int db = 0;
    for(p = etlap_eleje; p != NULL; p = p->kov)
    {
        db++;
    }
    return db;
}

/* Kiiratja az etlapra felvett eteleket meghivasa utan
   Parameterkent meg kell adnunk az etlapot.
*/
void etlap_kiirat(Etlap *etlap_eleje)
{
    if(etel_db(etlap_eleje) == 0)
    {
        printf("\nJelenleg egyetlen egy etel sincs az etlapon.\n");
    }
    else
    {

        Etlap *kiir;
        int sorszam = 1;
        for(kiir = etlap_eleje; kiir != NULL; kiir = kiir->kov)
        {
            printf("%d %s - %d Ft\n", sorszam, kiir->nev, kiir->ar);
            sorszam++;
        }
        printf("Osszesen %d db etel van az etlapon.\n", etel_db(etlap_eleje));
    }
}

/*
    Az etlap (a dinamikusan foglalt lancolt listat) felszabaditasaert felel.
    Paramterkent az etlapot kell megadnunk.
*/
void etlap_felszabadit(Etlap *etlap_eleje)
{
    Etlap *torol = etlap_eleje;
    while (torol != NULL)
    {
        Etlap *kovetkezo = torol->kov;
        free(torol);
        torol = kovetkezo;
    }
}

/*
    Egy etel adagaraval ter vissza.
    Az etlapot, valamint az etel sorszamat kell megadni parameterkent.
    Ezt a fuggvenyt az szamlakiiratasnal hasznaljuk fel.
*/
int darabar(Etlap *etlap_eleje, int sorszam)
{
    Etlap *mozgo;
    int listasorszam = 1;
    for(mozgo = etlap_eleje; mozgo != NULL; mozgo = mozgo->kov)
    {
        if(listasorszam == sorszam)
        {
            return mozgo->ar;
        }
        listasorszam++;
    }
    return 0;
}

/*
    Egy etel nevevel ter vissza. (a megadott *etel karaktertombre mutato pointer erteket modositja)
    Parameterkent az etlapot, az etel sorszamat, valamint egy karaktertombre mutato pointert kell megadni.
*/

void etelnev(Etlap *etlap_eleje, int sorszam, char *etel)
{
    Etlap *mozgo;
    int listasorszam = 1;
    for(mozgo = etlap_eleje; mozgo != NULL; mozgo = mozgo->kov)
    {
        if(listasorszam == sorszam)
        {
            strcat(etel, mozgo->nev);
            break;
        }
        listasorszam++;
    }
}
