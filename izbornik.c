#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#include <conio.h>

char lozinka(ADMIN* admin) {
    ADMIN unos;
    printf("Unesi korisnicko ime:\n");
    scanf("%s", &unos.korisnicko_ime);
    printf("Unesi Lozinku:\n");
    scanf("%s", &unos.lozinka);
    if (strcmp(admin->korisnicko_ime, unos.korisnicko_ime) == 0 && strcmp(admin->lozinka, unos.lozinka) == 0)
        return 1;
    else
        return 0;
};

int prijava_admin() {
    ADMIN admin_unos = { "admin", "admin" };
    ADMIN* admin_pok = &admin_unos;
    int f = 0;
    Admin odabir;

    while (lozinka(admin_pok) == 0 && f < 4) {
        f++;
        if (f == 3) {
            printf("Neuspjesno logiranje\nIskoristeni svi pokusaji!\n\n");
            printf("Pritisnite bilo koju tipku za povratak u izbornik...\n");
            _getch();
            izbornik();
            return 0;
        }
        system("cls");
        printf("Pogresno uneseno korisnicko ime ili lozinka, pokusaj ponovo: \n");
    }
    system("cls");
    printf("Uspjesna prijava.\n\n");

    printf("Odaberi opciju:\n\n");
    printf("1. Dodavanje novog bicikla\n");
    printf("2. Ispis svih bicikala\n");
    printf("3. Uredjivanje bicikala\n");
    printf("4. Brisanje bicikala\n");
    printf("5. Brisanje datoteke sa svim postojecim biciklima\n");
    printf("6. Izlaz iz programa\n");

    odabir = _getch() - '0';  // Korisnik unosi jednu od ponuðenih opcija i pretvaramo je u broj

    switch (odabir) {
    case DODAVANJE_BICIKLA:
        system("cls");
        dodaj_bicikl("bicikli.bin");
        printf("\n\nPritisnite bilo koju tipku za povratak...\n\n");
        _getch();
        break;
    case ISPIS_SVIH_BICIKALA_ADMIN:
        system("cls");
        ispis_svih_bicikala("bicikli.bin");
        printf("\n\nPritisnite bilo koju tipku za povratak...\n");
        _getch();
        system("cls");
        admin();
        break;
    case UREDJIVANJE_BICIKALA:
        system("cls");
        uredjivanje("bicikli.bin");
        printf("\n\nPritisnite bilo koju tipku za povratak...\n\n");
        _getch();
        break;
    case BRISANJE_BICIKLA:
        system("cls");
        brisanje_bicikla("bicikli.bin");
        printf("\n\nPritisnite bilo koju tipku za povratak...\n\n");
        _getch();
        break;
    case BRISANJE_DATOTEKE:
        system("cls");
        brisanje_datoteke("bicikli.bin");
        printf("\n\nPritisnite bilo koju tipku za povratak...\n\n");
        _getch();
        break;
    case ADMIN_IZLAZ:
        izlazak();  // Izlazak iz programa
        break;
    default:
        printf("\nKrivi unos, pritisnite bilo koju tipku za povratak...\n");
        _getch();
        system("cls");
        admin();
        break;
    }
    return 0;
}


int admin() {

    Admin odabir;


    printf("Odaberi opciju:\n\n");
    printf("1. Dodavanje novog bicikla\n");
    printf("2. Ispis svih bicikala\n");
    printf("3. Uredjivanje bicikala\n");
    printf("4. Brisanje bicikala\n");
    printf("5. Brisanje datoteke sa svim postojecim biciklima\n");
    printf("6. Izlaz iz programa\n");

    odabir = _getch() - '0';  // Korisnik unosi jednu od ponuðenih opcija i pretvaramo je u broj

    switch (odabir) {
    case DODAVANJE_BICIKLA:
        system("cls");
        dodaj_bicikl("bicikli.bin");
        printf("\n\nPritisnite bilo koju tipku za povratak...\n\n");
        _getch();
        break;
    case ISPIS_SVIH_BICIKALA_ADMIN:
        system("cls");
        ispis_svih_bicikala("bicikli.bin");
        printf("\n\nPritisnite bilo koju tipku za povratak...\n");
        _getch();
        system("cls");
        admin();
        break;
    case UREDJIVANJE_BICIKALA:
        system("cls");
        uredjivanje("bicikli.bin");
        printf("\n\nPritisnite bilo koju tipku za povratak...\n\n");
        _getch();
        break;
    case BRISANJE_BICIKLA:
        system("cls");
        brisanje_bicikla("bicikli.bin");
        printf("\n\nPritisnite bilo koju tipku za povratak...\n\n");
        _getch();
        break;
    case BRISANJE_DATOTEKE:
        system("cls");
        brisanje_datoteke("bicikli.bin");
        printf("\n\nPritisnite bilo koju tipku za povratak...\n\n");
        _getch();
        break;
    case ADMIN_IZLAZ:
        izlazak();  // Izlazak iz programa
        break;
    default:
        printf("\nKrivi unos, pritisnite bilo koju tipku za povratak...\n");
        _getch();
        system("cls");
        admin();
        break;
    }
    return 0;
}

void izbornik() {
    while (1) {
        system("cls");
        Izbornik odabir = odabir_korisnika();

        switch (odabir) {
        case KORISNICKI_PRISTUP:
            prijava_korisnik();
            _getch();
            break;
        case ADMINISTRATORSKI_PRISTUP:
            prijava_admin();
            _getch();
            break;
        case IZLAZAK:
            izlazak();
            _getch();
            return;  // Prekida petlju i izlazi iz funkcije
        default:
            printf("Neispravan odabir\n\nPritisnite bilo koju tipku za povratak u izbornik...\n");
            _getch();
            break;
        }
    }
}


int prijava_korisnik() {
    Korisnik odabir;

    printf("Odaberi opciju:\n\n");
    printf("1. Ispis svih bicikala\n");
    printf("2. Sortiranje\n");
    printf("3. Pretrazivanje bicikala po (nazivu, kategoriji, brandu ili cijeni)\n");
    printf("4. Kupnja bicikla\n");
    printf("5. Izlaz iz programa\n");

    odabir = _getch() - '0'; // Korisnik unosi jednu od ponuðenih opcija i pretvaramo je u broj

    switch (odabir) {
    case ISPIS_SVIH_BICIKALA_KORISNIK:
        system("cls");
        ispis_svih_bicikala("bicikli.bin");
        printf("\n\nPritisnite bilo koju tipku za povratak...\n");
        _getch();
        system("cls");
        prijava_korisnik();
        break;
    case SORTIRANJE:
        system("cls");
        sortiranje("bicikli.bin");
        break;
    case PRETRAZIVANJE:
        system("cls");
        pretrazivanje("bicikli.bin");
        break;
    case KUPNJA_BICIKLA:
        system("cls");
        kupnja_bicikla("bicikli.bin");
        printf("\n\nPritisnite bilo koju tipku za povratak....\n\n");
        _getch();
        break;
    case KORISNIK_IZLAZ:
        izlazak(); // Izlazak iz programa
        break;
    default:
        printf("\nKrivi unos, pritisnite bilo koju tipku za povratak....\n");
        _getch();
        system("cls");
        prijava_korisnik();
        break;
    }
    return 0;
}


