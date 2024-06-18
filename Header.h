#ifndef HEADER_H
#define HEADER_H

typedef struct bicikli {
	char vrsta[10];
	char naziv[100];
	char kategorija[20];
	char brand[20];
	float cijena;
	char stanje[10];
}BICIKL;

typedef struct admin {
	char korisnicko_ime[20];
	char lozinka[10];
}ADMIN;

typedef enum {
	KORISNICKI_PRISTUP = 1,
	ADMINISTRATORSKI_PRISTUP,
	IZLAZAK,
	NEISPRAVAN_ODABIR
} Izbornik;


typedef enum {
	DODAVANJE_BICIKLA = 1,
	ISPIS_SVIH_BICIKALA_ADMIN,
	UREDJIVANJE_BICIKALA,
	BRISANJE_BICIKLA,
	BRISANJE_DATOTEKE,
	ADMIN_IZLAZ
} Admin;

typedef enum {
	ISPIS_SVIH_BICIKALA_KORISNIK = 1,
	SORTIRANJE,
	PRETRAZIVANJE,
	KUPNJA_BICIKLA,
	KORISNIK_IZLAZ
} Korisnik;

typedef enum {
	OD_NAJMANJE_CIJENE = 1,
	OD_NAJVECE_CIJENE,
	POVRATAK_NA_POCETAK
} Sortiranje;

typedef enum {
	VRSTA = 1,
	NAZIV,
	KATEGORIJA,
	BRAND,
	CIJENA,
	STANJE,
	POVRATAK
} Pretrazivanje;

typedef enum {
	PROMJENA_VRSTE = 1,
	PROMJENA_NAZIVA,
	PROMJENA_KATEGORIJE,
	PROMJENA_BRANDA,
	PROMJENA_CIJENE,
	PROMJENA_STANJA,
	IZBORNIK_POVRATAK
} Uredjivanje;


	extern int br_bicikala;

	void izbornik();
	Izbornik odabir_korisnika();
	int prijava_admin();
	int admin();
	void izlazak();
	void sortiranje(ime_datoteke);
	int broj_bicikala(ime_datoteke);
	void brisanje_bicikla(ime_datoteke);
	void kreiranje_datoteke(ime_datoteke);
	void dodaj_bicikl(ime_datoteke);
	int ispis_svih_bicikala(ime_datoteke);
	BICIKL* ucitavanje_bicikala(ime_datoteke);
	void pretrazivanje(ime_datoteke);
	void ispis_bicikala(bicikli);
	void uredjivanje(ime_datoteke);
	int prijava_korisnik();
	char* odabir_kategorije();
	char* odabir_vrste();
	char* odabir_branda();
	char* odabir_stanja();
	void kupnja_bicikla(ime_datoteke);
	void brisanje_datoteke(ime_datoteke);
	char lozinka(ADMIN* admin);

#endif