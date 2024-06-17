#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#include <conio.h>

char* odabir_kategorije() {
    int odabir;
    odabir = _getch();
    switch (odabir) {
    case '1':
        return "MTB";
    case '2':
        return "Cestovni";
    case '3':
        return "Trekking";
    case '4':
        return "Enduro";
    case '5':
        return "Downhill";
    case '6':
        return "Triatlon";
    case '7':
        return "Gradski";
    default:
        printf("\nKrivi unos! Molimo unesite ponovno.\n");
        return odabir_kategorije();
    }
}

char* odabir_vrste() {
    int odabir;
    odabir = _getch();
    switch (odabir) {
    case '1':
        return "E bicikl";
    case '2':
        return "Bicikl";
    default:
        printf("\nKrivi unos! Molimo unesite ponovno.\n");
        return odabir_vrste();
    }
}

char* odabir_branda() {
    int odabir;
    odabir = _getch();
    switch (odabir) {
    case '1':
        return "Cube";
    case '2':
        return "Specialized";
    case '3':
        return "Kross";
    case '4':
        return "Giant";
    case '5':
        return "Liv";
    case '6':
        return "MBM";
    default:
        printf("\nKrivi unos! Molimo unesite ponovno.\n");
        return odabir_branda();
    }
}


char* odabir_stanja() {
    int odabir;
    odabir = _getch();
    switch (odabir) {
    case '1':
        return "Novo";
    case '2':
        return "Rabljeno";
    default:
        printf("\nKrivi unos! Molimo unesite ponovno.\n");
        return odabir_stanja();
    }
}

void dodaj_bicikl(const char* ime_datoteke) {

    if (ime_datoteke == NULL || ime_datoteke[0] == '\0') {
        printf("Greska: Neispravan naziv datoteke.\n");
        return;
    }

    BICIKL novi_bicikl;

    //otvaranje datoteke za citanje i pisanje
    FILE* fp = fopen(ime_datoteke, "rb+");

    if (fp == NULL) {
        //ako ne postoji, otvara se dat za citanje i pisanje
        fp = fopen(ime_datoteke, "wb+");
        if (fp == NULL) {
            printf("Greska pri otvaranju datoteke.\n");
            return;
        }
        int br = 0;
        fwrite(&br, sizeof(int), 1, fp);
        //0 na pocetak datoteke
    }

    br_bicikala++;
    rewind(fp);
    //pokazivac na pocetak datoteke, kako bi se br sacuvao u datoteku 
    fwrite(&br_bicikala, sizeof(int), 1, fp);
    //azurira br bicikala na pocetku dat
    fseek(fp, 0, SEEK_END);
    //pokazivac na kraj, dodavanje bicikla


    printf("Odaberite vrstu: \n");
    printf("1. E bicikl\n");
    printf("2. Bicikl\n");

    char* vrsta = odabir_vrste();
    if (vrsta == NULL) {
        fclose(fp);
        return;
    }
    strcpy(novi_bicikl.vrsta, vrsta);

    do {
        printf("Unesi naziv: \n");
        int c;  //ciscenje ulaznog buffera (priv skladiste u memoriji, koristi se za cuvanje podataka)
        while ((c = getchar()) != '\n' && c != EOF);  //sve dok ne naidje na znak novog reda ili kraj dat
        fgets(novi_bicikl.naziv, sizeof(novi_bicikl.naziv), stdin);
        //trazi prvo pojavljivanje znaka novog reda i na njegovo mjesto stavlja NULL karakter
        novi_bicikl.naziv[strcspn(novi_bicikl.naziv, "\n")] = '\0';
        if (novi_bicikl.naziv[0] == '\0') {
            printf("Naziv ne moze biti prazan.\n");
        }
    } while (novi_bicikl.naziv[0] == '\0');

    printf("\nOdaberite kategoriju: \n");
    printf("1. MTB\n");
    printf("2. Cestovni\n");
    printf("3. Trekking\n");
    printf("4. Enduro\n");
    printf("5. Downhill\n");
    printf("6. Triatlon\n");
    printf("7. Gradski\n");

    char* kategorija = odabir_kategorije();
    if (kategorija == NULL) {
        fclose(fp);
        return;
    }
    strcpy(novi_bicikl.kategorija, kategorija);

    printf("\nOdaberite brand: \n");
    printf("1. Cube\n");
    printf("2. Specialized\n");
    printf("3. Kross\n");
    printf("4. Giant\n");
    printf("5. Liv\n");
    printf("6. Canyon\n");

    char* brand = odabir_branda();
    if (brand == NULL) {
        fclose(fp);
        return;
    }
    strcpy(novi_bicikl.brand, brand);
    do {
        printf("\nUnesite cijenu: \n");
        if (scanf("%f", &novi_bicikl.cijena) != 1) {
            printf("Neispravan unos. Molimo unesite cijenu kao broj.\n");
            // Oèisti ulazni bafer kako bi se izbjeglo beskonaèno petljanje
            while (getchar() != '\n');
        }
        else if (novi_bicikl.cijena <= 0) {
            printf("Cijena mora biti pozitivan broj.\n");
        }
    } while (novi_bicikl.cijena <= 0);

    printf("Unesite stanje bicikla: \n");
    printf("1. Novo\n");
    printf("2. Rabljeno\n");

    char* stanje = odabir_stanja();
    if (stanje == NULL) {
        fclose(fp);
        return;
    }
    strcpy(novi_bicikl.stanje, stanje);

    //upisuje novi bicikl u datoteku
    fwrite(&novi_bicikl, sizeof(BICIKL), 1, fp);

    fclose(fp);
    printf("Novi bicikl uspjesno dodan.\n");

    printf("\nPritisnite bilo koju tipku za povratak u izbornik...\n");
    _getch();
    system("cls");
    admin();
}


void brisanje_bicikla(const char* ime_datoteke) {

    if (ime_datoteke == NULL || ime_datoteke[0] == '\0') {
        printf("Greska: Neispravan naziv datoteke.\n");
        return NULL;
    }

    ispis_svih_bicikala("bicikli.bin");
    printf("\n");
    FILE* fp = fopen(ime_datoteke, "rb");
    if (fp == NULL) {
        printf("Neuspjesno otvaranje datoteke za citanje.\n");
        return;
    }

    //cita br bicikala iz datoteke
    fread(&br_bicikala, sizeof(int), 1, fp);

    BICIKL* bicikli = (BICIKL*)malloc(br_bicikala * sizeof(BICIKL));
    if (bicikli == NULL) {
        printf("Greska pri alokaciji memorije\n");
        fclose(fp);
        return;
    }

    //ucitavaju se bicikli iz dat
    fread(bicikli, sizeof(BICIKL), br_bicikala, fp);
    fclose(fp);

    char trazeni_naziv[30];
    printf("Unesite naziv bicikla kojeg zelite obrisati: \n");
    scanf(" %99[^\n]", trazeni_naziv);

    // Pretvaranje unosa u mala slova
    for (int i = 0; trazeni_naziv[i]; i++) {
        trazeni_naziv[i] = tolower(trazeni_naziv[i]);
    }

    int indeks = -1;
    for (int i = 0; i < br_bicikala; i++) {
        // Pretvaranje naziva bicikla iz datoteke u mala slova
        char mala_slova[sizeof(bicikli[i].naziv)];
        strcpy(mala_slova, bicikli[i].naziv);
        for (int j = 0; mala_slova[j]; j++) {
            mala_slova[j] = tolower(mala_slova[j]);
        }
        //usporedjuje
        if (strcmp(bicikli[i].naziv, trazeni_naziv) == 0) {
            indeks = i;
            break;
        }
    }

    if (indeks == -1) {
        printf("Bicikl nije pronaden.\n");
        free(bicikli);
        return;
    }

    // Ako se bicikl nalazi na zadnjem mjestu, jednostavno smanjimo broj bicikala
    if (indeks == br_bicikala - 1) {
        br_bicikala--;
    }
    else {
        // Ako se bicikl nalazi negdje drugdje, podaci ostalih se premjestaju
        for (int i = indeks; i < br_bicikala - 1; i++) {
            bicikli[i] = bicikli[i + 1];
        }
        br_bicikala--;
    }

    fp = fopen(ime_datoteke, "wb");
    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke.\n");
        free(bicikli);
        return;
    }

    //zapisuje novi br bicikala u dat
    fwrite(&br_bicikala, sizeof(int), 1, fp);
    //prepisuju se preostali bicikli iz "bicikli" u dat
    fwrite(bicikli, sizeof(BICIKL), br_bicikala, fp);

    fclose(fp);
    free(bicikli);
    printf("Bicikl je uspjesno obrisan!\n");

    printf("\nPritisnite bilo koju tipku za povratak na pocetak...\n");
    _getch();
    system("cls");
    admin();
}


void brisanje_datoteke(const char* ime_datoteke) {

    int odabir = 0;

    printf("Jeste li sigurni da zelite izbrisati datoteku?\n");
    printf("1. DA\n");
    printf("2. NE\n");

    do {
        odabir = _getch();
        if (odabir == '1') {
            if (remove(ime_datoteke) == 0) {
                printf("Datoteka '%s' uspjesno obrisana.\n", ime_datoteke);
            }
            else {
                printf("Greska prilikom brisanja datoteke '%s'.\n", ime_datoteke);
            }

            printf("\nPritisnite bilo koju tipku za kreiranje nove datoteke\n");
            _getch();
            kreiranje_datoteke("bicikli.bin");

            printf("\nPritisnite bilo koju tipku za povratak na pocetak\n");
            _getch();
            admin();
        }
        else if (odabir == '2') {
            printf("Brisanje datoteke otkazano.\n");
            printf("\nPritisnite bilo koju tipku za povratak u izbornik\n");
            _getch();
            system("cls");
            admin();
        }
        else {
            printf("Krivi unos. Molimo pokusajte ponovno.\n");
        }
    } while (odabir != '1' && odabir != '2');

}

void uredjivanje(const char* ime_datoteke) {
    if (ime_datoteke == NULL || ime_datoteke[0] == '\0') {
        printf("Greska: Neispravan naziv datoteke.\n");
        return;
    }

    Uredjivanje odabir;
    int f = 0;
    BICIKL* bicikli = NULL;
    BICIKL temp = { 0 };
    int br_bicikala = 0;

    FILE* fp = fopen(ime_datoteke, "rb+");
    if (fp == NULL) {
        printf("Neuspjesno otvaranje datoteke za èitanje.\n");
        return;
    }

    // citaju se podaci bicikala iz "bicikli"
    fread(&br_bicikala, sizeof(int), 1, fp);
    bicikli = (BICIKL*)malloc(br_bicikala * sizeof(BICIKL));
    if (bicikli == NULL) {
        printf("Greska pri alokaciji memorije.\n");
        fclose(fp);
        return;
    }

    fread(bicikli, sizeof(BICIKL), br_bicikala, fp);

    printf("Unesite naziv bicikla kojeg zelite promijeniti:\n");
    scanf(" %29[^\n]", temp.naziv);

    // Pretvorimo temp.naziv u sva mala slova radi usporedbe
    for (int i = 0; temp.naziv[i]; i++) {
        temp.naziv[i] = tolower(temp.naziv[i]);
    }

    for (int i = 0; i < br_bicikala; i++) {
        // Pretvaranje naziva bicikla iz datoteke u mala slova
        char mala_slova[sizeof(bicikli[i].naziv)];
        strcpy(mala_slova, bicikli[i].naziv);
        for (int j = 0; mala_slova[j]; j++) {
            mala_slova[j] = tolower(mala_slova[j]);
        }

        if (strcmp(temp.naziv, mala_slova) == 0) {
            printf("Vrsta: %s\nNaziv: %s\nKategorija: %s\nBrand: %s\nCijena: %.2f\nStanje: %s\n\n",
                bicikli[i].vrsta,
                bicikli[i].naziv,
                bicikli[i].kategorija,
                bicikli[i].brand,
                bicikli[i].cijena,
                bicikli[i].stanje);

            printf("Odaberite opciju:\n");
            printf("1. Promjena vrste\n");
            printf("2. Promjena naziva\n");
            printf("3. Promjena kategorije\n");
            printf("4. Promjena branda\n");
            printf("5. Promjena cijene\n");
            printf("6. Promjena stanja\n");
            printf("7. Povratak u izbornik\n");

            f = 1;
            odabir = _getch() - '0';

            switch (odabir) {
            case PROMJENA_VRSTE: {
                printf("Odaberite novu vrstu bicikla: \n");
                printf("1. E bicikl\n");
                printf("2. Bicikl\n");

                char* vrsta = odabir_vrste();
                if (vrsta == NULL) {
                    free(bicikli);
                    fclose(fp);
                    return;
                }
                strcpy(bicikli[i].vrsta, vrsta);
                break;
            }
            case PROMJENA_NAZIVA: {
                printf("Unesite novi naziv bicikla: \n");
                scanf(" %29[^\n]", temp.naziv);
                strcpy(bicikli[i].naziv, temp.naziv);
                break;
            }
            case PROMJENA_KATEGORIJE: {
                printf("Odaberite novu kategoriju bicikla: \n");
                printf("1. MTB\n");
                printf("2. Cestovni\n");
                printf("3. Trekking\n");
                printf("4. Enduro\n");
                printf("5. Downhill\n");
                printf("6. Triatlon\n");
                printf("7. Gradski\n");

                char* kategorija = odabir_kategorije();
                if (kategorija == NULL) {
                    free(bicikli);
                    fclose(fp);
                    return;
                }
                strcpy(bicikli[i].kategorija, kategorija);
                break;
            }
            case PROMJENA_BRANDA: {
                printf("Unesite novi brand bicikla: \n");
                printf("1. Cube\n");
                printf("2. Specialized\n");
                printf("3. Kross\n");
                printf("4. Giant\n");
                printf("5. Liv\n");
                printf("6. MBM\n");

                char* brand = odabir_branda();
                if (brand == NULL) {
                    free(bicikli);
                    fclose(fp);
                    return;
                }
                strcpy(bicikli[i].brand, brand);
                break;
            }
            case PROMJENA_CIJENE: {
                printf("Unesite novu cijenu bicikla: \n");
                scanf("%f", &temp.cijena);
                bicikli[i].cijena = temp.cijena;
                break;
            }
            case PROMJENA_STANJA: {
                printf("Promijenite stanje bicikla: \n");
                printf("1. Novo\n");
                printf("2. Rabljeno\n");

                char* stanje = odabir_stanja();
                if (stanje == NULL) {
                    free(bicikli);
                    fclose(fp);
                    return;
                }
                strcpy(bicikli[i].stanje, stanje);
                break;
            }
            case IZBORNIK_POVRATAK: {
                free(bicikli);
                fclose(fp);
                izbornik();
                return;
            }
            default:
                printf("Krivi unos.\n");
                continue;
            }

            // cilj je pomaknuti pokazivac na poziciju zapisa koji azuriramo
            fseek(fp, sizeof(int) + i * sizeof(BICIKL), SEEK_SET);
            // pisanje promjenjenih podataka iz niza strukture bicikli u datoteku 
            fwrite(&bicikli[i], sizeof(BICIKL), 1, fp);
            printf("Promjena uspjesno izvrsena.\n");
            printf("\nPritisnite bilo koju tipku za povratak na pocetak.\n");
            _getch();
            break;
        }
    }

    if (f == 0) {
        printf("Bicikl s nazivom '%s' nije pronaden.\n", temp.naziv);
    }

    free(bicikli);
    fclose(fp);

    admin();
}

void preimenuj_datoteku(const char* stari_naziv) {
    char novi_naziv[100];
    char unos[100];

    printf("Unesite stari naziv datoteke: ");
    scanf("%s", unos);

    if (strcmp(unos, stari_naziv) != 0) {
        printf("Uneseni stari naziv datoteke nije ispravan.\n");
        return;
    }

    printf("Unesite novo ime datoteke: ");
    scanf("%s", novi_naziv);

    if (rename(stari_naziv, novi_naziv) == 0) {
        printf("Datoteka '%s' uspješno preimenovana u '%s'.\n", stari_naziv, novi_naziv);
    }
    else {
        printf("Greška prilikom preimenovanja datoteke.\n");
    }
}
