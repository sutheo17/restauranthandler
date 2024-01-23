#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "etlap.h"
#include "asztalok.h"
#include "debugmalloc.h"


//Sorminta kirajzolasa a fomenu szamara.
void sorminta_fomenu()
{
    for(int i = 0; i<50; i++)
    {
        printf("/");
        if(i == 49)
        {
            printf("\n");
        }
    }
}

//Sorminta kirajzolasa az almenuk szamara.
void sorminta_almenu()
{
    for(int i = 0; i<50; i++)
    {
        printf("%%");
        if(i == 49)
        {
            printf("\n");
        }
    }
}

/*
 A fomenu. Innen hivodnak meg a kulonbozo almenuk.
 A program a felhasznalotol egy szamot ker be, ami meghivja a megfelelo almenut.
 Paramterkent megkap egy kilep boolean valtozot, ez felelos azert, hogy visszaterjunk
 a fomenube, ha kiakarunk. Valamint megkapja a ket lancolt lista head-jere mutato pointert.
 A kilepes a "9" bevitelevel tortenik.
*/
void menu_valaszto()
{
    bool kilep = false;
    while(kilep == false)
    {
        menu_kirajzol();
        int valasztas = integer_input();

        switch (valasztas)
        {
        case 1:
            system("@cls||clear");
            *etlap_eleje = etlapkezeles(*etlap_eleje);
            break;
        case 2:
            system("@cls||clear");
            foglaltsagi_kezelo(*asztal_eleje);
            break;
        case 3:
            system("@cls||clear");
            asztalkezeles(*asztal_eleje, *etlap_eleje);
            break;
        case 4:
            system("@cls||clear");
            asztalok_szamla(*asztal_eleje, *etlap_eleje);
            break;
        case 9:
            printf("Kilepes, adatok mentese\n");
            kilep = true;
            break;
        default:
            printf("Nincs ilyen valasztasi opcio!\n\n");
            break;
        }
    }

}

//A menu valasztasi opcioit kiirja. Ezt a fomenu hijva meg.
void menu_kirajzol()
{
    sorminta_fomenu();
    printf("/");
    printf("%50s","/\n");
    printf("/");
    printf("%27s%23s","ETTEREM","/\n");
    printf("/");
    printf("%50s","/\n");
    sorminta_fomenu();
    printf("/");
    printf("%30s%20s","1. Menurogzites","/\n");
    printf("/");
    printf("%33s%17s","2. Foglaltsagi terkep","/\n");
    printf("/");
    printf("%32s%18s","3. Asztalok kezelese","/\n");
    printf("/");
    printf("%38s%12s","4. Szamla nyomtatas kepernyore","/\n");
    printf("/");
    printf("%36s%14s","9. Kilepes, adatok mentese","/\n");
    sorminta_fomenu();
    printf("/");
    printf("%43s%7s","Add meg a kivalasztott opcio sorszamat!","/\n");
    sorminta_fomenu();
}

//Az etelek listajat kezelo almenu opcioit iratja ki.
void etterem_menu()
{
    sorminta_almenu();
    printf("%%");
    printf("%35s%15s","1. Etlap megtekintese","%\n");
    printf("%%");
    printf("%33s%17s","2. Etel felvetele","%\n");
    printf("%%");
    printf("%32s%18s","3. Etel levetele","%\n");
    printf("%%");
    printf("%35s%15s","9. Vissza a fomenube","%\n");
    sorminta_almenu();
}

//Az asztalok kezelesere szolgalo almenu opcioit iratja ki.
void etterem_asztalok()
{
    sorminta_almenu();
    printf("%%");
    printf("%32s%18s","1. Asztal lefoglal","%\n");
    printf("%%");
    printf("%37s%13s","2. Asztal fogyasztas hozzaad","%\n");
    printf("%%");
    printf("%37s%13s","3. Asztal eddigi fogyasztas","%\n");
    printf("%%");
    printf("%30s%20s","4. Asztal torol","%\n");
    printf("%%");
    printf("%33s%17s","9. Vissza a fomenube","%\n");
    sorminta_almenu();
}

//A foglaltsagi menu opcioinak kiiratasa.
void foglaltsagi_menu()
{
    sorminta_almenu();
    printf("%%");
    printf("%40s%10s","1. Foglaltsagi terkep kirajzol","%\n");
    printf("%%");
    printf("%40s%10s","2. Asztal adatainak lekerdezese","%\n");
    printf("%%");
    printf("%41s%9s","3. Asztal ferohelyenek modositasa","%\n");
    printf("%%");
    printf("%33s%17s","9. Vissza a fomenube","%\n");
    sorminta_almenu();
}

//Szamla kiiratasanal minta kirajzolas.
void szamla_minta()
{
    for(int i = 0; i<50; i++)
    {
        printf("#");
        if(i == 49)
        {
            printf("\n");
        }
    }
}

//Egy dinamikusan foglalt karaktertombot ad vissza, ha meghivjuk a fuggvenyt.
//Ezt kulonbozo etel nevek beolvasasara szolgal, ezt tobb .c fajl is hasznalja.
char *szoveg_beolvas()
{
    char *szoveg;
    szoveg = (char *) malloc(1* sizeof(char));
    int i = 0;
    szoveg[0] = '\0';
    char temp;
    while(scanf("%c", &temp) == 1 && temp != '\n')
    {
        char *uj = (char*) malloc (sizeof(char) * (i+2));     //zaro nullanak is legyen hely
        for(int j = 0; j < i; ++j)
        {
            uj[j] = szoveg[j];
        }
        free(szoveg);
        szoveg = uj;
        uj[i] = temp;
        uj[i+1] = '\0';
        ++i;
    }
    return szoveg;
}

/*
    A felhasznalo altal megadott integerrel ter vissza.
    Ellenorzi, hogy a felhasznalo megfelelo erteket ad meg.
*/
int integer_input()
{
    int valasztas, tesztelo;
    while (scanf("%d", &valasztas) != 1 || valasztas < 0)
    {
        while (isspace(tesztelo = getchar()) == 0 || tesztelo == ' ');
        {
        }
        printf("Rossz inputot adtal meg!\n");
    }

    return valasztas;
}

/*
    A felhasznalo altal megadott asztal koordinataival ter vissza.
    A parameterkent kapott ket integer erteket modositja.
*/
void koordinata_input(int *x, int *y)
{
    int sor, oszlop;
    while(1)
    {
        char *beolvas = szoveg_beolvas();
        if(sscanf(beolvas, "%d,%d", &sor, &oszlop) == 2)
        {
            if(sor > 0 && oszlop > 0)
            {
                *x = sor;
                *y = oszlop;
                free(beolvas);
                break;
            }
            printf("A koordinata csak poztiv szamokbol allhat!\n");
            free(beolvas);

        }
        else
        {
            printf("Rossz inputot adtal meg!\n");
            free(beolvas);
        }
    }
}
