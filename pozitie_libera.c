#include "pozitie_libera.h"
#include "arbori_intervale.h"

void actualizare_cu_delta(Nod *nod, int v2) {
    nod->info += v2;
}

int suma_raspunsurilor(int r1, int r2) {
    return r1 + r2;
}

DateIntrare* citeste_fisier_in(char *nume_fisier_intrare) {
    
	int i;
	DateIntrare* date_input = malloc(sizeof(DateIntrare));
	FILE *input_file = fopen(nume_fisier_intrare, "rt");

	if (input_file == NULL) {
        fprintf(stderr, "ERROR: Can't open file %s", nume_fisier_intrare);
        return NULL;
	}

	fscanf(input_file, "%d", &date_input->numarul_maxim_din_intrari);
	fscanf(input_file, "%d", &date_input->numar_intrari);
	date_input->intrari = malloc(date_input->numar_intrari * sizeof(int));

	for (i = 0; i < date_input->numar_intrari; i++) {
		fscanf(input_file, "%d", &date_input->intrari[i]);
	}

return date_input;
}

int* calculeaza_vector_raspuns(DateIntrare *date_intrare) {
    
	int* vector_raspuns;
	vector_raspuns = calloc(date_intrare->numarul_maxim_din_intrari + 1, sizeof(int));
	ArboreDeIntervale *arbore;
	arbore = construieste_arbore(0, date_intrare->numarul_maxim_din_intrari, 0, 
															actualizare_cu_delta, suma_raspunsurilor);

	for (int i = 0; i < date_intrare->numar_intrari; i++) {
		int element = date_intrare->intrari[i];
		Interval *interval = malloc(sizeof(Interval));
		interval->capat_stanga = element;
		interval->capat_dreapta = interval->capat_stanga;
		int interogare = interogare_interval_in_arbore(arbore, interval);
		if (interogare == 0) {
			actualizare_interval_in_arbore(arbore, interval , 1);
			vector_raspuns[element] = element;
		}
		else {
			for (int j = element; j >= 0; j--) {
				Interval *intervall = malloc(sizeof(Interval));
				intervall->capat_stanga = j;
				intervall->capat_dreapta = intervall->capat_stanga;
				int interogaree = interogare_interval_in_arbore(arbore, intervall);
				if (interogaree == 0) {
					vector_raspuns[j] = element;
					actualizare_interval_in_arbore(arbore, intervall , 1);
					break;
				}
			}
		}
	}
	
return vector_raspuns;
}

int* calculeaza_vector_raspuns_trivial(DateIntrare *date_intrare) {
  
	int* vector_raspuns;
	vector_raspuns = calloc(date_intrare->numarul_maxim_din_intrari + 1, sizeof(int));
	int i, j;

	for (i = 0; i < date_intrare->numar_intrari; i++) {
		int element = date_intrare->intrari[i]; 
		if (vector_raspuns[element] == 0) 
			vector_raspuns[element] = element;
		else 
			for (j = element; j >= 0; j--) 
				if (vector_raspuns[j] == 0) {
					vector_raspuns[j] = element;
					break;
				}
	}
 	
return vector_raspuns;
}
