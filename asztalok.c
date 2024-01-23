#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "asztalok.h"
#include "menu.h"
#include "etlap.h"
#include "debugmalloc.h"

/*Ez a fuggveny a felhasznalotol egy szamot ker be. A felhasznalo altal
megadott szam felel a megfelelo opcio kivalasztasaert.
*/
void asztalkezeles(Asztalok *asztal_eleje, Etlap *etlap_eleje)
{
    int valasztas;
    bool kilepes = false;
    while(kilepes == false)
    {
        int x, y;
        etterem_asztalok();
        valasztas = integer_input();
        switch (valasztas)
        {
        case 1:
            system("@cls||clear");
            asztalok_foglal(asztal_eleje);
            break;
        case 2:
            system("@cls||clear");
            if(etel_db(etlap_eleje) == 0)
            {
                printf("Jelenleg meg nincs etel az etlapon!\n\n");
            }
            else
            {
                asztal_kezelo(asztal_eleje, &x, &y);
                Asztalok* asztal = asztalok_keres(asztal_eleje, x, y);
                if(asztal == NULL)          //van-e ilyen asztal
                {
                    printf("Sajnalom ez az asztal nem letezik!\n\n");
                }
                else if(asztalok_keres(asztal_eleje, x, y)->foglalt == false)       //foglalt-e mar az asztal
                {
                    printf("Ez az asztal meg nincs lefoglalva!\n");
                }
                else
                {

                    asztal_fogyasztas_add(etlap_eleje, asztalok_keres(asztal_eleje, x, y));
                }
            }

            break;
        case 3:
            system("@cls||clear");
            asztal_kezelo(asztal_eleje, &x, &y);
            Asztalok* asztal = asztalok_keres(asztal_eleje, x, y);
            if(asztal == NULL)      //van-e ilyen asztal
            {
                printf("Sajnalom ez az asztal nem letezik!\n\n");
            }
            else if(asztalok_keres(asztal_eleje, x, y)->foglalt == false)   //foglalt-e mar asztal
            {
                printf("Ez az asztal meg nincs lefoglalva!\n");
            }
            else
            {
                asztal_fogyasztas_kiir(etlap_eleje, asztalok_keres(asztal_eleje, x, y));
            }
            break;
        case 4:
            system("@cls||clear");
            asztal_kezelo(asztal_eleje, &x, &y);
            asztalok_torol(asztalok_keres(asztal_eleje, x, y));
            break;
        case 9:
            system("@cls||clear");
            kilepes = true;
            break;
        default:
            printf("Nincs ilyen valasztasi opcio!\n");
            break;
        }
    }

}

/*A fuggveny meghivasa az asztalok pointerevel ter vissza, benne mar az asztalok
  x,y koordinataval vannak ellatva, valamint ossze vannak fuzve egy lancolt listaban.
  Parameterkent az asztalok head-jet, egy sor, es egy oszlopszamot kell megadni.
*/
Asztalok *asztalok_inicializalas(Asztalok *asztal_eleje, int sor, int oszlop)
{
    Asztalok *legelso = (Asztalok*) malloc (sizeof(Asztalok));
    legelso = asztalok_koordinata(legelso, 0, 0);
    legelso = kezdoallapot(legelso);
    Asztalok *mozgo = legelso;
    legelso->kov = mozgo;

    for(int i = 1; i <= sor; i++)
    {
        for(int j = 1; j <= oszlop; j++)
        {
            Asztalok *uj = (Asztalok*) malloc (sizeof(Asztalok));
            uj = asztalok_koordinata(uj, i, j);
            uj = kezdoallapot(uj);
            uj->kov = NULL;
            mozgo->kov = uj;
            mozgo = mozgo->kov;
        }
    }
    Asztalok *generalt;                //inicializalashoz hasznalt kezdo asztal torlese
    generalt = legelso->kov;
    free(legelso);
    return generalt;
}

/*
    Egy adott asztal kezdoallapot beallitja.
    Paramterkent egy asztalra mutato pointert kell megadni.
*/
Asztalok *kezdoallapot(Asztalok *uj)
{
    uj->foglalt = false;
    uj->db = NULL;
    uj->etel = NULL;
    uj->tetelekdb = 0;
    uj->ferohely = 0;
    return uj;
}

/*Egy olyan pointerrel ter vissza, aminek az x es y koordinataja a paramterkent
  adott sor- és oszlopszam.
  Parameterkent meg kell adnunk egy dinamikusan foglalt Asztalok tipusu
  pointert, valamint ket integer erteket, amely a sor-, es oszlopszamot jelolik.

*/
Asztalok *asztalok_koordinata(Asztalok *asztal, int sor, int oszlop)
{
    asztal->x = sor;
    asztal->y = oszlop;
    return asztal;
}

/*A fuggveny egy adott asztal foglaltsagat valtoztatja meg (foglaltrol szabadra, es forditva)
  A fuggveny paramterekent az adott asztalra mutato pointert kell megadnunk.
*/
Asztalok *asztalok_foglaltsag(Asztalok *asztal)
{
    (asztal->foglalt == false) ? (asztal->foglalt = true) : (asztal->foglalt = false);
    return asztal;
}

/*Egy adott x,y koordinataju asztal pointerevel ter vissza.
  Paramterkent az asztalok head-jet, valamint ket integer erteket kell megadnunk
  sor-, valamint az oszlopszamot. (x,y koordinata)
*/
Asztalok *asztalok_keres(Asztalok *eleje, int sor, int oszlop)
{
    Asztalok *kereso;
    for(kereso = eleje; kereso != NULL; kereso = kereso->kov)
    {
        if(kereso->x == sor && kereso->y == oszlop)
        {
            return kereso;
        }
    }
    return NULL;
}

/*
    Egy adott asztal foglaltsagat modositja, hibakezelest is tartalmaz.
    Foglaltsag modositas eseten meghivja az asztalok_foglaltsag fuggvenyt.
    Parameterkent az asztalok head-jet kell megadni.
*/
void asztalok_foglal(Asztalok *asztal_eleje)
{
    if(telthaz(asztal_eleje))
    {
        printf("Telthaz van!\n");
    }
    else
    {
        int x, y;
        printf("Melyik asztalt szeretned lefoglalni?(x,y)\n");
        char felesleg;
        scanf("%c", &felesleg);         //ne zavarjon be az elotte levo szoveg
        koordinata_input(&x, &y);
        if(asztalok_keres(asztal_eleje, x, y) == NULL)
        {
            printf("Sajnalom, ez az asztal nem letezik!\n");
        }
        else if(asztalok_keres(asztal_eleje, x, y)->foglalt == true)
        {
            printf("Sajnalom, ez az asztal mar foglalt!\n");
        }
        else
        {
            printf("Sikeres asztalfoglalas!\n");
            Asztalok *asztal = asztalok_keres(asztal_eleje, x, y);
            asztal = asztalok_foglaltsag(asztal);
        }
    }
}

/*
    Egy boolean ertekkel ter vissza (igaz/hamis), ami jelzi, hogy minden asztal foglalt-e.
    Parameterkent az asztalok head-jet kell megadni.
*/
bool telthaz(Asztalok *asztal_eleje)
{
    bool foglaltosszes = true;
    Asztalok *mozgo;
    for(mozgo = asztal_eleje; mozgo != NULL; mozgo = mozgo->kov)
    {
        if(mozgo->foglalt == false)
        {
            foglaltosszes = false;
        }
    }
    return foglaltosszes;
}

/*
    Egy adott asztal adatait az eredetire valtoztatja, torli a fogyasztassat.
    Parameterkent egy adott asztal pointeret kell megadni.
*/
void asztalok_torol(Asztalok *asztal)
{
    if(asztal == NULL)
    {
        printf("Sajnalom, ez az asztal nem letezik!\n");
    }
    else if(asztal->foglalt == false)
    {
        printf("Ez az asztal meg szabad!\n");
    }
    else
    {
        printf("Sikeres asztaltorles!\n\n");
        if(asztal->db != NULL || asztal->etel != NULL)
        {
            free(asztal->db);
            free(asztal->etel);
        }
        kezdoallapot(asztal);
    }
}

/*
    Az asztalok pointerenek (a dinamikusan foglalt lancolt lista) felszabaditasaert felel.
    Paramterkent az asztalok pointeret kell megadnunk.
*/
void asztalok_felszabadit(Asztalok *eleje)
{
    Asztalok *torol = eleje;
    while (torol != NULL)
    {
        Asztalok *kovetkezo = torol->kov;
        if(torol->db != NULL || torol->etel != NULL)
        {
            free(torol->db);
            free(torol->etel);
        }
        free(torol);
        torol = kovetkezo;
    }
}

/*
    A felhasznalo altal megadott sor-, oszlopszamot adja vissza.
    Parameterkent az asztalok head-jet, valamint elsokent a sor, valamint oszlopszam memoriacimet kell megadni.
    A parameterkent megadott ket pointer ertekent valtoztatja meg.
    Ezt a fuggvenyt a koordinata bekerese soran sokszor felhasznaljuk.
    Nem ellenorizzuk, hogy tul nagy erteket ad-e meg a felhasznalo, ezt a tobbi fuggveny ellenorzi.
*/
void asztal_kezelo(Asztalok *asztal_eleje, int *sorszam, int *oszlopszam)
{
    int sor, oszlop;
    printf("Melyik asztalt akarod kezelni? (x,y)\n");
    char felesleg;
    scanf("%c", &felesleg);
    koordinata_input(&sor, &oszlop);
    *sorszam = sor;
    *oszlopszam = oszlop;
}

/*
    Egy asztalhoz fogyasztast ad hozza.
    Paramterkent az etlapot (etlap_eleje head-jet), valamint az asztalok head-jet kell megadni.
*/
void asztal_fogyasztas_add(Etlap *etlap_eleje, Asztalok *asztal)
{
    int sorszam, adag;
    int hibadb = 0;
    printf("\n");
    etlap_sorszam(etlap_eleje);
    do
    {
        if(hibadb > 0)
        {
            printf("Nincs ilyen sorszamu etel!\n\n");
        }
        printf("Add meg az etel sorszamat!\n");
        sorszam = integer_input();
        hibadb++;
    }
    while (sorszam == 0 || sorszam > etel_db(etlap_eleje));         //ellenorizzuk letezik-e ilyen sorszamu etel
    printf("Hany adag etel?\n");
    adag = integer_input();

    if(asztal_fogyasztas_bennvan(asztal, sorszam))          //az asztal mar fogyasztott ebbol az etelbol
    {
        int meddig = asztal->tetelekdb;
        for(int i = 0; i < meddig; i++)
        {
            if(asztal->etel[i] == sorszam)
            {
                asztal->db[i] += adag;
            }
        }
    }
    else        //az asztal meg nem fogyasztott ebbol az etelbol
    {
        int darab = asztal->tetelekdb + 1;
        asztal->etel = (int *) realloc (asztal->etel, sizeof(int) * darab);
        asztal->db = (int *) realloc (asztal->db, sizeof(int) * darab);
        asztal->etel[asztal->tetelekdb] = sorszam;
        asztal->db[asztal->tetelekdb] = adag;
        asztal->tetelekdb++;
    }

}

/*
    Ellenorzi, hogy az adott etelbol fogyasztott-e mar az asztal.
    Parameterkent az asztalok head-jet, valamint az etel sorszamat kell megadni.
*/
bool asztal_fogyasztas_bennvan(Asztalok *asztal, int sorszam)
{
    int meddig = asztal->tetelekdb;
    for(int i = 0; i < meddig; i++)
    {
        if(asztal->etel[i] == sorszam)
        {
            return true;
        }
    }
    return false;
}

/*
    Kiiratja egy asztal fogyasztasat.
    Parameterkent az etlapot (etlap head-jet), valamint az asztalok head-jet kell megadni.
*/
void asztal_fogyasztas_kiir(Etlap *etlap_eleje, Asztalok *asztal)
{
    if(asztal->tetelekdb == 0)
    {
        printf("Ennek az asztalnak jelenleg meg nincs fogyasztasa!\n");
    }
    else
    {
        printf("Az asztal eddigi fogyasztasa:\n");
        int meddig = asztal->tetelekdb;
        for(int i = 0; i < meddig; i++)
        {
            char etel[101] = "";
            etelnev(etlap_eleje, asztal->etel[i], etel);
            printf("%s - %d db\n", etel, asztal->db[i]);
        }
    }

}

/*
    A fajlbol az adott asztalhoz tartozo ferohely, foglaltsag beolvasasa.
    Parameterkent az asztalok head-jet, valamint ket integert erteket kell megadni.
    Eloszor a ferohelyet, majd a foglaltsagot.
*/
void asztal_fajlbol_alapadatok(Asztalok *asztal, int ferohely, int foglaltsag)
{
    asztal->ferohely = ferohely;
    (foglaltsag == 1) ? (asztal->foglalt = true) : (asztal->foglalt = false);
}

/*
    A fajlbol az adott asztalhoz tartozo etelek beolvasasa.
    Parameterkent az asztalok head-jet, valamint ket integer erteket kell megadni.
    Eloszor az etel sorszamat, majd a darabszamot kell megadni.
*/
void asztal_fajlbol_etelek(Asztalok *asztal, int sorszam, int eteldb)
{
    int darab = asztal->tetelekdb + 1;
    asztal->etel = (int *) realloc (asztal->etel, sizeof(int) * darab);
    asztal->db = (int *) realloc (asztal->db, sizeof(int) * darab);
    asztal->etel[asztal->tetelekdb] = sorszam;
    asztal->db[asztal->tetelekdb] = eteldb;
    asztal->tetelekdb++;
}

/*
    Az etlap kiiratasa, az etelek sorszamaval egyutt.
    Paramterkent az etlapot kell megadnunk. (etlap head-jet)
*/
void etlap_sorszam(Etlap *etlap_eleje)
{
    if(etel_db(etlap_eleje) == 0)
    {
        printf("Jelenleg egyetlen egy etel sincs az etlapon.\n");
    }
    else
    {
        Etlap *kiir;
        int sorszam = 1;
        for(kiir = etlap_eleje; kiir != NULL; kiir = kiir->kov)
        {
            printf("%d %s\n", sorszam, kiir->nev);
            sorszam++;
        }
    }
}

/*
    Szamla kiiratasa kepernyore, valamint asztal alaphelyzetbe allitasa.
    Pramterekent az asztalok head-jet, valamint az etlap head-jet kell megadni.
    A kezdoallapot fuggvenyt hivja meg az alaphelyzetbe allitashoz, de az asztal ferohelyet megorzi.
*/
void asztalok_szamla(Asztalok *asztal_eleje, Etlap *etlap_eleje)
{
    int x, y;
    asztal_kezelo(asztal_eleje, &x, &y);
    Asztalok *asztal = asztalok_keres(asztal_eleje, x, y);
    if(asztal == NULL)
    {
        printf("Sajnalom ez az asztal nem letezik!\n");
    }
    else if(asztal->foglalt == false)
    {
        printf("Ez az asztal meg szabad!\n");
    }
    else
    {
        printf("\n");
        szamla_minta();
        printf("#");
        printf("%27s%23s","SZAMLA","#\n");
        szamla_minta();
        if(asztal->tetelekdb == 0)
        {
            printf("Jelenleg ures az asztalhoz tartozo szamla!\n\n");
        }
        else
        {
            int szum = 0;
            for(int i = 0; i < asztal->tetelekdb; i++)
            {
                int ar = darabar(etlap_eleje, asztal->etel[i]) * asztal->db[i];
                char etel[101] = "";
                etelnev(etlap_eleje, asztal->etel[i], etel);
                printf("%d x %s\t %d Ft\n", asztal->db[i], etel, ar);
                szum += ar;
            }
            printf("\nVegosszeg: %d Ft\n", szum);
            szamla_minta();
            int temp = asztal->ferohely;            //asztal ferohelyenek megjegyzese temporalis valtozoba
            asztalok_torol(asztal);
            asztal->ferohely = temp;            //asztal ferohelyet visszaadjuk a temporalis valtozobol
        }
    }
}

/*
    Foglaltsagi menu agya.
    Innen hivodnak meg a foglaltsagi terkephez tartozo valasztasi opciok.
    Paramterkent az asztalok head-jet kell megadni.
*/
void foglaltsagi_kezelo(Asztalok *asztal_eleje)
{
    int valasztas;
    bool kilepes = false;
    while(kilepes == false)
    {
        int x, y;
        foglaltsagi_menu();
        valasztas = integer_input();
        switch(valasztas)
        {
        case 1:
            system("@cls||clear");
            foglaltsagi_terkep(asztal_eleje);
            break;
        case 2:
            system("@cls||clear");
            asztal_kezelo(asztal_eleje, &x, &y);
            foglaltsagi_asztal_adatok(asztal_eleje, x, y);
            break;
        case 3:
            system("@cls||clear");
            asztal_kezelo(asztal_eleje, &x, &y);
            foglaltsagi_asztal_ferohely(asztal_eleje, x, y);
            break;
        case 9:
            system("@cls||clear");
            kilepes = true;
            break;
        }
    }

}

/*
    Kirajzolja a foglaltsagi terkepet.
    Parameterkent az asztalok head-jet kell megadni.
    (O = szabad, X = foglalt)
*/
void foglaltsagi_terkep(Asztalok *eleje)
{
    printf("Foglaltsagi terkep:\n\n");
    Asztalok *utolso;
    for(utolso = eleje; utolso->kov != NULL; utolso = utolso->kov)
    {
    }
    for(int i = 1; i <= utolso->x; i++)
    {
        for(int j = 1; j <= utolso->y; j++)
        {
            Asztalok *keresett = asztalok_keres(eleje, i, j);
            if(keresett->foglalt == false)
            {
                printf("O ");
            }
            else
            {
                printf("X ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

/*
    Egy asztal ferohelyet, valamint foglaltsagat irja ki.
    Paramaterkent az asztalok head-jet, valamint egy x es y koordinatat kell megadni.
*/
void foglaltsagi_asztal_adatok(Asztalok *asztal_eleje, int x, int y)
{
    Asztalok *asztal = asztalok_keres(asztal_eleje, x, y);
    if(asztal == NULL)          //letezik-e az asztal
    {
        printf("Nem letezo asztal!\n");
    }
    else
    {
        printf("Asztal koordinatai: x = %d / y = %d\n", asztal->x, asztal->y);
        printf("Ferohely: ");
        (asztal->ferohely == 0) ? (printf("Meg nincs megadott ferohelye ennek az asztalnak!\n")) : (printf("%d\n", asztal->ferohely));
        printf("Foglaltsag: ");
        (asztal->foglalt != true) ? (printf("SZABAD\n\n")) : (printf("FOGLALT\n\n"));
    }
}

/*
    Egy asztal ferohelyet modositja.
    Parameterkent az asztalok head-jet, valamint egy x es y koordinatat kell megadni.
*/
void foglaltsagi_asztal_ferohely(Asztalok *asztal_eleje, int x, int y)
{
    Asztalok *asztal = asztalok_keres(asztal_eleje, x, y);
    if(asztal == NULL)          //letezik-e az asztal
    {
        printf("Nem letezo asztal!\n");
    }
    else
    {
        printf("Hany ferohelyes az asztal?\n");
        int hely;
        hely = integer_input();
        asztal->ferohely = hely;
        printf("Sikeres ferohelymodositas!\n\n");
    }
}
