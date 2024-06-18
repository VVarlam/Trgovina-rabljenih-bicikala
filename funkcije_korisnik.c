#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#include <conio.h>

//24

//funkcija spaja dva vec sortirana podniza
void podnizovi(BICIKL* bicikli, int l, int s, int d) {

	//odredjuje br elemenata u lijevom/desnom podnizu
	int n1 = s - l + 1;
	int n2 = d - s;

	BICIKL* lijevo = (BICIKL*)malloc(n1 * sizeof(BICIKL));
	if (lijevo == NULL) {
		printf("Greska pri alokaciji memorije\n");
        exit(EXIT_FAILURE);
	}
	BICIKL* desno = (BICIKL*)malloc(n2 * sizeof(BICIKL));
	if (desno == NULL) {
		printf("Greska pri alokaciji memorije\n");
        exit(EXIT_FAILURE);
	}

	//zapisuje bicikle u lijevi/desni podniz
	for (int i = 0; i < n1; i++)
		lijevo[i] = bicikli[l + i];
	for (int j = 0; j < n2; j++)
		desno[j] = bicikli[s + 1 + j];

	//prolazi kroz sve bicikle i ako bicikl ima manju ili jednaku cijenu kao iduci bicikl, ostavlja ga s lijeve strane, a ako ima vecu cijenu ga stavlja desno
	int i = 0, j = 0, k = l;
	//usporedjuje lijevi i desni podniz
	while (i < n1 && j < n2) {
		if (lijevo[i].cijena <= desno[j].cijena) {
			bicikli[k] = lijevo[i];
			i++;
		}
		else {
			bicikli[k] = desno[j];
			j++;
		}
		//povecava se za svaki kopirani element
		k++;
	}

	while (i < n1) {
		bicikli[k] = lijevo[i];
		i++;
		k++;
	}

	while (j < n2) {
		bicikli[k] = desno[j];
		j++;
		k++;
	}

	free(lijevo);
	free(desno);
}

void sortiranje_podnizova(BICIKL* bicikli, int l, int d) {
	if (l < d) {
		int s = l + (d - l) / 2;

		//sortiranje lijevog pa desnog podniza
		sortiranje_podnizova(bicikli, l, s);
		sortiranje_podnizova(bicikli, s + 1, d);

		podnizovi(bicikli, l, s, d);
	}
}

void sortiranje_od_najmanje(BICIKL* bicikli, int br_bicikala) {
	sortiranje_podnizova(bicikli, 0, br_bicikala - 1);

	printf("Popis je sortiran od najmanje cijene prema najvecoj\n\n");
	for (int i = 0; i < br_bicikala; i++) {
		printf("Vrsta: %s\nNaziv: %s\nKategorija: %s\nBrand: %s\nCijena: %.2f\nStanje: %s\n\n",
			bicikli[i].vrsta,
			bicikli[i].naziv,
			bicikli[i].kategorija,
			bicikli[i].brand,
			bicikli[i].cijena,
			bicikli[i].stanje);
	}

	printf("\nPritisnite bilo koju tipku za povratak u izbornik\n");
	_getch();
	system("cls");
	prijava_korisnik();
}

void sortiranje_od_najvece(BICIKL* bicikli, int br_bicikala) {
	sortiranje_podnizova(bicikli, 0, br_bicikala - 1);

	//for petlja koja preokrece sortirani niz, prolazi kroz prvu polovicu
	for (int i = 0; i < br_bicikala / 2; i++) {
		BICIKL temp = bicikli[i];
		//el s pocetka zamjeni se s onim sa kraja
		bicikli[i] = bicikli[br_bicikala - i - 1];
		bicikli[br_bicikala - i - 1] = temp;
	}

	printf("Popis je sortiran od najvece cijene prema najmanjoj\n\n");
	for (int i = 0; i < br_bicikala; i++) {
		printf("Vrsta: %s\nNaziv: %s\nKategorija: %s\nBrand: %s\nCijena: %.2f\nStanje: %s\n\n",
			bicikli[i].vrsta,
			bicikli[i].naziv,
			bicikli[i].kategorija,
			bicikli[i].brand,
			bicikli[i].cijena,
			bicikli[i].stanje);
	}

	printf("\nPritisnite bilo koju tipku za povratak u izbornik\n");
	_getch();
	system("cls");
	prijava_korisnik();
}

void sortiranje(const char* ime_datoteke) {
    if (ime_datoteke == NULL || ime_datoteke[0] == '\0') {
        printf("Greska: Neispravan naziv datoteke.\n");
        return;
    }

    BICIKL* bicikli = NULL;
    Sortiranje odabir;

    FILE* fp = fopen(ime_datoteke, "rb");
    if (fp == NULL) {
        printf("Neuspjesno otvaranje datoteke za citanje.\n");
    }
    else {
		//cita br bicikala iz dat
        fread(&br_bicikala, sizeof(int), 1, fp);
        bicikli = (BICIKL*)malloc(br_bicikala * sizeof(BICIKL));
        if (bicikli == NULL) {
            printf("Greska prilikom alokacije memorije.\n");
        }
        else {
			//cita podatke bicikala iz bicikli
            fread(bicikli, sizeof(BICIKL), br_bicikala, fp);
            fclose(fp);

            system("cls");
            printf("Sortiraj: \n");
            printf("1. Od najmanje cijene prema najvecoj\n");
            printf("2. Od najvece cijene prema najmanjoj\n");
            printf("3. Povratak na pocetak\n");

            odabir = _getch() - '0'; // Pretvaramo unos u broj

            switch (odabir) {
            case OD_NAJMANJE_CIJENE:
                sortiranje_od_najmanje(bicikli, br_bicikala);
                break;
            case OD_NAJVECE_CIJENE:
                sortiranje_od_najvece(bicikli, br_bicikala);
                break;
            case POVRATAK_NA_POCETAK:
                system("cls");
                printf("\nPritisni bilo koju tipku za povratak...\n");
                _getch();
                system("cls");
                prijava_korisnik();
                break;
            default:
                printf("\nKrivi unos, pritisnite bilo koju tipku za povratak....\n");
                _getch();
                system("cls");
                sortiranje(ime_datoteke);
            }

			//4otvaranje dat za pisanje
			fp = fopen(ime_datoteke, "wb");
			if (fp == NULL) {
				printf("Neuspjesno stvaranje datoteke\n");
			}
			else {
				//upisuje se br bicikala
				fwrite(&br_bicikala, sizeof(int), 1, fp);
				//upisuju se podaci o biciklima
				fwrite(bicikli, sizeof(BICIKL), br_bicikala, fp);
				fclose(fp);
			}
			free(bicikli);
		}
	}
}


//Ova funkcija usporeðuje dva elementa tipa BICIKL po nazivu bicikla
int usporedba(const void* a, const void* b) {
    return strcmp(((BICIKL*)a)->naziv, ((BICIKL*)b)->naziv);
}

void pretrazivanje(const char* ime_datoteke) {

    if (ime_datoteke == NULL || ime_datoteke[0] == '\0') {
        printf("Greska: Neispravan naziv datoteke.\n");
        return NULL;
    }

    Pretrazivanje odabir;    
    int f = 0;
    BICIKL* bicikli = NULL;
    BICIKL temp = { 0 };
    //privremena struktura za unos

    system("cls");
    printf("1. Pretrazivanje po vrsti bicikla\n");
    printf("2. Pretrazivanje po nazivu bicikla\n");
    printf("3. Pretrazivanje po kategoriji bicikla\n");
    printf("4. Pretrazivanje po brandu bicikla\n");
    printf("5. Pretrazivanje po cijeni bicikla\n");
    printf("6. Pretrazivanje po stanju bicikla\n");
    printf("7. Povratak na pocetak\n");

    odabir = _getch() - '0';

    FILE* fp = fopen(ime_datoteke, "rb");
    if (fp == NULL) {
        printf("Neuspjesno otvaranje datoteke za citanje.\n");
    }
    else {
        //cita br bicikala iz dat
        fread(&br_bicikala, sizeof(int), 1, fp);
        bicikli = (BICIKL*)malloc(br_bicikala * sizeof(BICIKL));
        if (bicikli == NULL) {
            printf("Greska pri alokaciji memorije\n");
            fclose(fp);
            return;
        }
        else {
            fread(bicikli, sizeof(BICIKL), br_bicikala, fp);

            //sortira niz bicikala prema nazivu
            qsort(bicikli, br_bicikala, sizeof(BICIKL), usporedba);
            //Sortiranje niza može ubrzati pretraživanje, posebno ako imamo velik broj bicikala, jer olakšava brzu pretragu unutar sortiranog skupa podataka

            switch (odabir) {
            case VRSTA:
                printf("Odaberite vrstu bicikla: \n");
                printf("1. E bicikl\n2. Bicikl\n");
                strcpy(temp.vrsta, odabir_vrste());
                for (int i = 0; i < br_bicikala; i++) {
                    if (strcmp(temp.vrsta, bicikli[i].vrsta) == 0) {
                        printf("Vrsta: %s\nNaziv: %s\nKategorija: %s\nBrand: %s\nCijena: %.2f\nStanje: %s\n\n",
                            bicikli[i].vrsta,
                            bicikli[i].naziv,
                            bicikli[i].kategorija,
                            bicikli[i].brand,
                            bicikli[i].cijena,
                            bicikli[i].stanje);
                        f = 1;
                    }
                }
                if (f == 0) {
                    printf("Bicikl trazene vrste ne postoji\n");
                }
                printf("\nPritisnite bilo koju tipku za povratak...\n");
                _getch();
                system("cls");
                prijava_korisnik();
                break;
            case NAZIV:
                printf("Unesite naziv trazenog bicikla:\n");
                //brisanje svih preostalih znakova u ulaznom bufferu
                //fflush(stdin);
                fgets(temp.naziv, sizeof(temp.naziv), stdin);
                temp.naziv[strcspn(temp.naziv, "\n")] = '\0'; // Ukloni newline karakter ako postoji, fgets ga moze zadrzati

                // Pretvorimo temp.naziv u sva mala slova radi usporedbe
                for (int i = 0; temp.naziv[i] != '\0'; i++) {
                    temp.naziv[i] = tolower(temp.naziv[i]);
                }

                for (int i = 0; i < br_bicikala; i++) {
                    // Pretvorimo bicikli[i].naziv u sva mala slova radi usporedbe
                    char mala_slova[sizeof(bicikli[i].naziv)];
                    strcpy(mala_slova, bicikli[i].naziv);
                    for (int j = 0; mala_slova[j] != '\0'; j++) {
                        mala_slova[j] = tolower(mala_slova[j]);
                    }

                    //mogucnost da korisnik upise samo dio naziva
                    if (strstr(mala_slova, temp.naziv) != NULL) { // Provjeri ako naziv sadrzi trazeni string
                        printf("Vrsta: %s\nNaziv: %s\nKategorija: %s\nBrand: %s\nCijena: %.2f\nStanje: %s\n\n",
                            bicikli[i].vrsta,
                            bicikli[i].naziv,
                            bicikli[i].kategorija,
                            bicikli[i].brand,
                            bicikli[i].cijena,
                            bicikli[i].stanje);
                        f = 1;
                    }
                }
                if (f == 0) {
                    printf("Bicikl s tim nazivom ne postoji\n");
                }
                printf("\nPritisnite bilo koju tipku za povratak...\n");
                _getch();
                system("cls");
                prijava_korisnik();
                break;
            case KATEGORIJA:
                printf("Odaerite kategoriju bicikla: \n");
                printf("1. MTB\n");
                printf("2. Cestovni\n");
                printf("3. Trekking\n");
                printf("4. Enduro\n");
                printf("5. Downhill\n");
                printf("6. Triatlon\n");
                printf("7. Gradski\n");
                strcpy(temp.kategorija, odabir_kategorije());
                for (int i = 0; i < br_bicikala; i++) {
                    if (strcmp(temp.kategorija, bicikli[i].kategorija) == 0) {

                        printf("Vrsta: %s\nNaziv: %s\nKategorija: %s\nBrand: %s\nCijena: %.2f\nStanje: %s\n\n",
                            bicikli[i].vrsta,
                            bicikli[i].naziv,
                            bicikli[i].kategorija,
                            bicikli[i].brand,
                            bicikli[i].cijena,
                            bicikli[i].stanje);
                        f = 1;
                    }
                }
                if (f == 0) {
                    printf("Bicikl trazene kategorije ne postoji\n");
                }
                printf("\nPritisnite bilo koju tipku za povratak...\n");
                _getch();
                system("cls");
                prijava_korisnik();
                break;
            case BRAND:
                printf("Unesite brand bicikla: \n");
                printf("1. Cube\n");
                printf("2. Specialized\n");
                printf("3. Kross\n");
                printf("4. Giant\n");
                printf("5. Liv\n");
                printf("6. MBM\n");
                strcpy(temp.brand, odabir_branda());
                for (int i = 0; i < br_bicikala; i++) {
                    if (strcmp(temp.brand, bicikli[i].brand) == 0) {

                        printf("Vrsta: %s\nNaziv: %s\nKategorija: %s\nBrand: %s\nCijena: %.2f\nStanje: %s\n\n",
                            bicikli[i].vrsta,
                            bicikli[i].naziv,
                            bicikli[i].kategorija,
                            bicikli[i].brand,
                            bicikli[i].cijena,
                            bicikli[i].stanje);
                        f = 1;
                    }
                }
                if (f == 0) {
                    printf("Bicikl trazenog branda ne postoji\n");
                }
                printf("\nPritisnite bilo koju tipku za povratak...\n");
                _getch();
                system("cls");
                prijava_korisnik();
                break;
            case CIJENA:
                printf("Unesite minimalnu cijenu trazenog bicikala:\n");
                float min_cijena;
                scanf("%f", &min_cijena);

                printf("Unesite maksimalnu cijenu trazenog bicikala:\n");
                float max_cijena;
                scanf("%f", &max_cijena);

                int f = 0; // Zastavica koja prati da li je pronaðen bicikl u datom rasponu

                for (int i = 0; i < br_bicikala; i++) {
                    if (bicikli[i].cijena >= min_cijena && bicikli[i].cijena <= max_cijena) {

                        printf("Vrsta: %s\nNaziv: %s\nKategorija: %s\nBrand: %s\nCijena: %.2f\nStanje: %s\n\n",
                            bicikli[i].vrsta,
                            bicikli[i].naziv,
                            bicikli[i].kategorija,
                            bicikli[i].brand,
                            bicikli[i].cijena,
                            bicikli[i].stanje);
                        f = 1;
                    }
                }

                if (f == 0) {
                    printf("Bicikl u navedenom rasponu cijena ne postoji\n");
                }
                printf("\nPritisnite bilo koju tipku za povratak...\n");
                _getch();
                system("cls");
                prijava_korisnik();
                break;
            case STANJE:
                printf("Odaberite stanje bicikla: \n");
                printf("1. Novo\n");
                printf("2. Rabljeno\n");
                strcpy(temp.stanje, odabir_stanja());
                for (int i = 0; i < br_bicikala; i++) {
                    if (strcmp(temp.stanje, bicikli[i].stanje) == 0) {

                        printf("Vrsta: %s\nNaziv: %s\nKategorija: %s\nBrand: %s\nCijena: %.2f\nStanje: %s\n\n",
                            bicikli[i].vrsta,
                            bicikli[i].naziv,
                            bicikli[i].kategorija,
                            bicikli[i].brand,
                            bicikli[i].cijena,
                            bicikli[i].stanje);
                        f = 1;
                    }
                }
                if (f == 0) {
                    printf("Bicikl trazenog stanja ne postoji\n");
                }
                printf("\nPritisnite bilo koju tipku za povratak...\n");
                _getch();
                system("cls");
                prijava_korisnik();
                break;
            case POVRATAK:
                system("cls");
                printf("\nPritisni bilo koju tipku za povratak...\n");
                _getch();
                system("cls");
                prijava_korisnik();
                break;
            default:
                printf("\nKrivi unos, pritisnite bilo koju tipku za povratak....\n");
                _getch();
                system("cls");
                prijava_korisnik();
                break;
            }
        }
        free(bicikli);
        fclose(fp);
    }
}



void kupnja_bicikla(const char* ime_datoteke) {

    if (ime_datoteke == NULL || ime_datoteke[0] == '\0') {
        printf("Greška: Neispravan naziv datoteke.\n");
        return NULL;
    }

    int odabir;
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

    //ucitava bicikle iz dat
    fread(bicikli, sizeof(BICIKL), br_bicikala, fp);
    fclose(fp);

    char trazeni_naziv[30];
    printf("Unesite naziv bicikla kojeg zelite kupiti: \n");
    scanf(" %99[^\n]", trazeni_naziv);

    // Pretvorimo trazeni_naziv u sva mala slova radi usporedbe
    for (int i = 0; trazeni_naziv[i]; i++) {
        trazeni_naziv[i] = tolower(trazeni_naziv[i]);
    }

    int indeks = -1;
    for (int i = 0; i < br_bicikala; i++) {
        // Pretvori naziv iz datoteke u mala slova za usporedbu
        char mala_slova[sizeof(bicikli[i].naziv)];
        strcpy(mala_slova, bicikli[i].naziv);
        for (int j = 0; mala_slova[j]; j++) {
            mala_slova[j] = tolower(mala_slova[j]);
        }

        if (strcmp(trazeni_naziv, mala_slova) == 0) {
            indeks = i;
            break;
        }
    }

    if (indeks == -1) {
        printf("Bicikl nije pronaden.\n");
        free(bicikli);
        printf("\nPritisnite bilo koju tipku za povratak u izbornik...\n");
        _getch();
        system("cls");
        prijava_korisnik();
        return;
    }

    printf("Zelite li nastaviti s kupnjom bicikla ciji ste naziv unjeli?\n");
    printf("1. DA\n");
    printf("2. NE\n");

    do {
        odabir = _getch();
        if (odabir == '1') {

            // Ako se bicikl nalazi na zadnjem mjestu, jednostavno smanjimo broj bicikala
            if (indeks == br_bicikala - 1) {
                br_bicikala--;
            }
            else {
                // Ako se bicikl nalazi negdje drugdje, prepišemo podatke ostalih bicikala u novi niz
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
            printf("Bicikl je uspjesno kupljen!\n");
        }
        else if (odabir != '2') {
            printf("Krivi unos. Molimo pokusajte ponovno.\n");
        }
    } while (odabir != '1' && odabir != '2');

    printf("\nPritisnite bilo koju tipku za povratak na pocetak...\n");
    _getch();
    system("cls");
    prijava_korisnik();
}

