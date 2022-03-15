#include "arbori_intervale.h"


ArboreDeIntervale *construieste_arbore(int capat_stanga, int capat_dreapta,
        int valoare_predefinita_raspuns_copil,
        void (*f_actualizare)(Nod *nod, int v_actualizare),
        int (*f_combinare_raspunsuri_copii)(int raspuns_stanga, int raspuns_dreapta)) {

	ArboreDeIntervale* arbore;
	int middle;

	arbore = (ArboreDeIntervale*) malloc(sizeof(ArboreDeIntervale));
	arbore->f_actualizare = f_actualizare;
	arbore->f_combinare_raspunsuri_copii = f_combinare_raspunsuri_copii;
	arbore->valoare_predifinita_raspuns_copil = valoare_predefinita_raspuns_copil;
	arbore->radacina = (Nod*) malloc(sizeof(Nod));
	arbore->radacina->info = 0;
	arbore->radacina->interval = (Interval*) malloc(sizeof(Interval));
	arbore->radacina->interval->capat_stanga = capat_stanga;
	arbore->radacina->interval->capat_dreapta = capat_dreapta; 
	
	if (capat_stanga < capat_dreapta) {
		middle = (capat_stanga + capat_dreapta) / 2;
		arbore->radacina->copil_stanga = construieste_arbore(capat_stanga, middle, 																		   valoare_predefinita_raspuns_copil, f_actualizare,
																		 f_combinare_raspunsuri_copii)->radacina;
		arbore->radacina->copil_dreapta = construieste_arbore(middle + 1, capat_dreapta, 																		    valoare_predefinita_raspuns_copil, f_actualizare,
																		  f_combinare_raspunsuri_copii)->radacina;
	}

return arbore;
}

void actualizare_interval_pentru_nod(ArboreDeIntervale *arbore, Nod *nod,
                                        Interval *interval, int v_actualizare) {
//update pentru un singur nod

	int middle;

	if ((interval->capat_stanga <= nod->interval->capat_stanga) &&
		 (nod->interval->capat_dreapta <= interval->capat_dreapta)) 
		arbore->f_actualizare(nod, v_actualizare);
	else {
		middle = (nod->interval->capat_dreapta + nod->interval->capat_stanga) / 2; 
		if (interval->capat_stanga <= middle) 
			actualizare_interval_pentru_nod(arbore, nod->copil_stanga, interval,
																			v_actualizare);
		if (middle < interval->capat_dreapta) 
			actualizare_interval_pentru_nod(arbore, nod->copil_dreapta, interval,
																			v_actualizare);
		arbore->f_actualizare(nod, v_actualizare);
	}
    
}

void actualizare_interval_in_arbore(ArboreDeIntervale *arbore, 
                                        Interval *interval, int v_actualizare) {
    actualizare_interval_pentru_nod(arbore, arbore->radacina, interval, v_actualizare);
}


int interogare_interval_pentru_nod(ArboreDeIntervale *arbore, Nod *nod, Interval *interval) {
//query pentru un singur nod 

	int middle;
	int valoare_stanga = 0, valoare_dreapta = 0;

	if ((interval->capat_stanga <= nod->interval->capat_stanga) && 
		 (nod->interval->capat_dreapta <= interval->capat_dreapta))
		return nod->info;
	else {	
		middle = (nod->interval->capat_stanga + nod->interval->capat_dreapta) / 2;
		if (interval->capat_stanga <= middle)
			valoare_stanga = interogare_interval_pentru_nod(arbore, nod->copil_stanga, 												 interval);
		if (middle < interval->capat_dreapta) 
			valoare_dreapta = interogare_interval_pentru_nod(arbore, nod->copil_dreapta, 												 interval);
		return arbore->f_combinare_raspunsuri_copii(valoare_dreapta, valoare_stanga); 
	}

}

int interogare_interval_in_arbore(ArboreDeIntervale *arbore, Interval *interval) {
    return interogare_interval_pentru_nod(arbore, arbore->radacina, interval);
}


// ----- DOAR pentru bonus si DOAR daca considerati ca e necesara ----- //
void seteaza_info_in_nod_la_valoare_capat_dreapta(Nod* nod) {
    nod->info = nod->interval->capat_dreapta;
}


void seteaza_info_in_arbore_la_valoare_capat_dreapta(ArboreDeIntervale* arbore) {
    seteaza_info_in_nod_la_valoare_capat_dreapta(arbore->radacina);
}
