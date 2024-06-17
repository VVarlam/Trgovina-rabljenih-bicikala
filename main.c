#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#include <conio.h>


int br_bicikala = 0;

int main() {

    kreiranje_datoteke("bicikli.bin");
	br_bicikala = broj_bicikala("bicikli.bin");

	izbornik();


	return 0;
}