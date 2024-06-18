#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#include <conio.h>

//Provjerava je li naziv datoteke NULL ili prazan string
#define PROVJERI_NAZIV(ime_datoteke) ((ime_datoteke) == NULL || (ime_datoteke)[0] == '\0')

//5, 8

void kreiranje_datoteke(const char* ime_datoteke) {


    //provjerava valjanost imena datoteke
    if (PROVJERI_NAZIV(ime_datoteke)) {
        printf("Greska: Neispravan naziv datoteke.\n");
        return;
    }

    //otvara datoteku za citanje
    FILE* fp = fopen(ime_datoteke, "rb");   

    if (fp != NULL) {
        printf("Datoteka '%s' vec postoji.\n", ime_datoteke);
        fclose(fp);
        return;
    }

    //kreiranje datoteke ako ne postoji
    fp = fopen(ime_datoteke, "wb");


    if (fp == NULL) {
        perror("Otvaranje datoteke");   //poruka o gresci koja se dogodila prilikom otvaranja datoteke
        printf("Neuspjesno stvaranje datoteke '%s'.\n", ime_datoteke);
        exit(EXIT_FAILURE); //izlaz iz programa, greska
    }

    // Inicijalizacija nove datoteke sa poèetnim brojem bicikala
    int br = 0;
    fwrite(&br, sizeof(int), 1, fp);

    printf("Uspjesno kreirana datoteka '%s'.\n", ime_datoteke);
    fclose(fp);
}

int broj_bicikala(char* ime_datoteke) {

    if (PROVJERI_NAZIV(ime_datoteke)) {
        printf("Greska: Neispravan naziv datoteke.\n");
        return NULL;
    }

    int br_bicikala = 0;

    //otvaranje dat za citanje
    FILE* fp = fopen(ime_datoteke, "rb");
   
    if (fp == NULL) {
        printf("Neuspjesno otvaranje datoteke za citanje.\n");
        return -1;
    }

    fread(&br_bicikala, sizeof(int), 1, fp);
    //cita 1 int iz datoteke i smjesti ga u br_bicikala
    fclose(fp);

    return br_bicikala;
}

BICIKL* ucitavanje_bicikala(char* ime_datoteke) {   //vraca pokazivac na BICIKL

    if (PROVJERI_NAZIV(ime_datoteke)) {
        printf("Greska: Neispravan naziv datoteke.\n");
        return NULL;
    }
    
    //greska pri ucitavanju
    if (br_bicikala == -1) {
        return NULL;
    }

    FILE* fp = fopen(ime_datoteke, "rb");
    if (fp == NULL) {
        printf("Neuspjesno otvaranje datoteke za citanje.\n");
        return NULL;
    }
    rewind(fp);
    //nakon sto dobijemo br, vracamo pokazivac na pocetak da citamo bicikle ispocetka

    BICIKL* bicikli = (BICIKL*)calloc(br_bicikala, sizeof(BICIKL));
    if (bicikli == NULL) {
        printf("Greska prilikom alokacije memorije.\n");
        fclose(fp);
        return NULL;
    }
    fread(bicikli, sizeof(BICIKL), br_bicikala, fp);
    //cita bicikle iz datoteke i smjesti ih u bicikli

    free(bicikli);
    fclose(fp);
    return bicikli;
    }
    

    void ispis_bicikala(BICIKL* bicikli) { 
    printf("\nVrsta: %s", bicikli->vrsta);
    printf("\nNaziv: %s", bicikli->naziv);
    printf("\nKategorija: %s", bicikli->kategorija);
    printf("\nBrand: %s", bicikli->brand);
    printf("\nCijena: %.2f eura", bicikli->cijena);
    printf("\nStanje: %s", bicikli->stanje);
    printf("\n");
    return;
}

int ispis_svih_bicikala() {

    static BICIKL* bicikli = NULL;
    FILE* fp = NULL;

    fp = fopen("bicikli.bin", "rb");
    if (fp == NULL) {
        printf("Neuspjesno otvaranje datoteke za citanje.\n");
        return 1;
    }
    else {
        //cita br bicikala iz datoteke
        fread(&br_bicikala, sizeof(int), 1, fp);
        bicikli = (BICIKL*)malloc(sizeof(BICIKL));
        if (bicikli == NULL) {
            return 1;
        }
        else {
            printf("Na zalihama postoji %d bicikala.", br_bicikala);
            for (int i = 0; i < br_bicikala; i++) {
                //cita jednu strukturu BICIKL iz datoteke i smjesta ju u "bicikli"
                fread(bicikli, sizeof(BICIKL), 1, fp);
                ispis_bicikala(bicikli);
            }
            free(bicikli);
            fclose(fp);
            return br_bicikala;
        }
    }
}

//inline funkcija se moze direktno umetnuti na mjesto poziva
void izlazak() {
    int odabir;

    printf("Zelite li izici iz programa?\n");
    printf("1. DA\n");
    printf("2. NE\n");

    do {
        odabir = _getch();
        if (odabir == '1') {
            printf("Pritisnite bilo koju tipku za kraj programa...\n");
            exit(EXIT_SUCCESS);
        }
        else if (odabir != '2') {
            printf("Krivi unos. Molimo pokusajte ponovno.\n");
        }
        else {
            izbornik();
        }
    } while (odabir != '1' && odabir != '2');
}


Izbornik odabir_korisnika() {
    char unos[10];

    printf("Dobrodosli u trgovinu rabljenih automobila\n");
    printf("\t1. Korisnicki pristup\n");
    printf("\t2. Administratorski pristup\n");
    printf("\t3. Izlazak iz programa\n");
    printf("\n\nOdaberite opciju: ");

    int ch = _getch();  // Èitamo jedan karakter bez potrebe za Enter tasterom
    snprintf(unos, sizeof(unos), "%c", ch);  // Pretvaramo karakter u string

    system("cls");

    if (strcmp(unos, "1") == 0) {
        return KORISNICKI_PRISTUP;
    }
    else if (strcmp(unos, "2") == 0) {
        return ADMINISTRATORSKI_PRISTUP;
    }
    else if (strcmp(unos, "3") == 0) {
        return IZLAZAK;
    }
    else {
        return NEISPRAVAN_ODABIR;
    }
}