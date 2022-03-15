#include "intersectii.h"

void afiseaza_lista_intervale(ListaIntervale2D *lista) {
    int i;
    for (i = 0; i < lista->dimensiune; i++) {
        Interval2D *interv = lista->intervale[i];
        printf("{punct stanga x: %d, punct stanga y: %d, punct dreapta x: %d, punct dreapta y: %d}\n",
                    interv->punct_stanga->x, interv->punct_stanga->y,
                    interv->punct_dreapta->x, interv->punct_dreapta->y);
    }

}

ListaIntervale2D* citeste_intrare(char *nume_fisier_intrare) {

	int i;
	ListaIntervale2D* lista = malloc(sizeof(ListaIntervale2D));
	FILE *input_file = fopen(nume_fisier_intrare, "rt");

	if (input_file == NULL) {
        fprintf(stderr, "ERROR: Can't open file %s", nume_fisier_intrare);
        return NULL;
	}
 
	fscanf(input_file, "%d", &lista->dimensiune);
	lista->intervale = malloc(lista->dimensiune * sizeof(Interval2D));

	for (i = 0; i < lista->dimensiune; i++) {
		lista->intervale[i] = malloc(sizeof(Interval2D));
		lista->intervale[i]->punct_stanga = malloc(sizeof(Punct2D));
		lista->intervale[i]->punct_dreapta = malloc(sizeof(Punct2D));
		fscanf(input_file, "%d", &lista->intervale[i]->punct_stanga->x);
		fscanf(input_file, "%d", &lista->intervale[i]->punct_stanga->y);
		fscanf(input_file, "%d", &lista->intervale[i]->punct_dreapta->x);
		fscanf(input_file, "%d", &lista->intervale[i]->punct_dreapta->y);
	} 

return lista;
}

// ! Functie pentru actualizarea in arbore
// ! O veti da ca parametru cand initializati arborele
void actualizare_cu_delta(Nod *nod, int v2) {
    nod->info += v2;
}

// ! Functie pentru combinarea raspunsurilor in arbore
// ! O veti da ca parametru cand initializati arborele
int suma_raspunsurilor(int r1, int r2) {
    return r1 + r2;
}

void swap(int *xp, int *yp)  
{  
    int temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
}  

int calculeaza_numar_intersectii(ListaIntervale2D *lista) {
 
	int y_max = lista->intervale[0]->punct_stanga->y;
	int v_x[lista->dimensiune * 2], v_int[lista->dimensiune * 2];
	int ind = 0, numar_intersectii = 0;

	for (int i = 0; i < lista->dimensiune; i++) {
	//parcurg vectorul de segmente
		if (lista->intervale[i]->punct_stanga->y > y_max)
			y_max = lista->intervale[i]->punct_stanga->y;
		if (lista->intervale[i]->punct_dreapta->y > y_max)
			y_max = lista->intervale[i]->punct_dreapta->y;
		v_x[ind] = lista->intervale[i]->punct_stanga->x;
		v_int[ind] = i;
		ind = ind + 1;
		v_x[ind] = lista->intervale[i]->punct_dreapta->x;
		v_int[ind] = i;
		ind = ind + 1;
	}
	
	ArboreDeIntervale *arbore = construieste_arbore(0, y_max, 0, 
															actualizare_cu_delta, suma_raspunsurilor);
	//arbore de intervale cu radacina de la 0 la y_max 
    
	for (int i = 0; i < lista->dimensiune * 2; i++)       
    for (int j = 0; j < lista->dimensiune * 2-i-1; j++)   
			if (v_x[j] >= v_x[j+1]) {
				swap(&v_x[j], &v_x[j+1]);
				swap(&v_int[j], &v_int[j+1]);	 
			} 	 

	for (int k = 0; k < lista->dimensiune * 2; k++) {
		//parcurg lista sortata de coordonate x
			int indice = v_int[k];
			if ((v_x[k] == lista->intervale[indice]->punct_stanga->x) && 
					(lista->intervale[indice]->punct_stanga->y == 
				 	lista->intervale[indice]->punct_dreapta->y)) {
			//daca intalnesc inceput de segment orizontal 
				Interval *interval = malloc(sizeof(Interval));
				interval->capat_stanga = lista->intervale[indice]->punct_stanga->y;
				interval->capat_dreapta = lista->intervale[indice]->punct_stanga->y;
				actualizare_interval_in_arbore(arbore, interval , 1);
			}
			else if (lista->intervale[indice]->punct_stanga->x ==
							 lista->intervale[indice]->punct_dreapta->x) {
			//daca x-ul e al unui segment vertical 
				Interval *intervall = malloc(sizeof(Interval));
				intervall->capat_stanga = lista->intervale[indice]->punct_stanga->y;
				intervall->capat_dreapta = lista->intervale[indice]->punct_dreapta->y;
				numar_intersectii = numar_intersectii + 
												interogare_interval_in_arbore(arbore, intervall);
				k = k + 2;
			}
			else if ((v_x[k] == lista->intervale[indice]->punct_dreapta->x) && 
					(lista->intervale[indice]->punct_stanga->y == 
				 	lista->intervale[indice]->punct_dreapta->y) && 
				 (lista->intervale[v_int[k + 1]]->punct_stanga->x !=
					lista->intervale[v_int[k + 1]]->punct_dreapta->x)) {
			//sfarsitul unui segment orizontal
				Interval *interval = malloc(sizeof(Interval));
				interval->capat_stanga = lista->intervale[indice]->punct_stanga->y;
				interval->capat_dreapta = interval->capat_stanga;
				actualizare_interval_in_arbore(arbore, interval , -1);		
			}
	}

return numar_intersectii;
}

int calculeaza_numar_intersectii_trivial(ListaIntervale2D *lista) {
    
	int i, j, nr_intersectii = 0;

	for (i = 0; i < lista->dimensiune; i++) 
		for (j = 0; j < lista->dimensiune; j++) 
			if (((lista->intervale[j]->punct_stanga->y == 
				    lista->intervale[j]->punct_dreapta->y) && 
					 (lista->intervale[i]->punct_stanga->x == 
				    lista->intervale[i]->punct_dreapta->x))) {	
			//daca unul dintre segmente este orizontal iar celalalt este vertical
			//indicele j pentru orizontal, i pentru vertical  
				if (((lista->intervale[i]->punct_stanga->x >= 
						  lista->intervale[j]->punct_stanga->x) && 
					   (lista->intervale[i]->punct_stanga->x <=  
						  lista->intervale[j]->punct_dreapta->x)) && 
						((lista->intervale[j]->punct_stanga->y >= 
							lista->intervale[i]->punct_stanga->y) && 
						 (lista->intervale[j]->punct_stanga->y <= 
							lista->intervale[i]->punct_dreapta->y)))
					nr_intersectii++; 
			}

return nr_intersectii;
}
