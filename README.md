# README- Barbu Maria-Alexandra, 315CD 

## Partea I:

## Arbori de intervale:
### Pentru construirea arborelui: 
Am alocat dinamic arborele, radacina arborelui, si intervalul corespunzator 
radacinii. Am atribuit arborelui functiile de "actualizare" si de "combinare 
raspunsuri copii", dar si "valoarea predefinita raspuns copil" pe care functia
le-a primit ca parametru. Am atribuit radacinii o informatie nula si 
intervalului acesteia capetele primite de functie. Am calculat mijlocul
intervalului si am apelat recursiv pana la frunze functia de construire a 
arborelui pentru intervalele (capat_stanga, mijloc) si (mijloc + 1, capat 
dreapta). Am intors arborele creat. 

### Pentru update nod:    
Daca intervalul nodului este inclus in intervalul primit ca parametru, se 
apeleaza functia de actualizare specifica arborelui respectiv. Daca nu, se 
calculeaza mijlocul intervalului nodului si se merge de-a lungul arborelui, pe
stanga sau pe dreapta, pana se ajunge la un interval inclus in cel primit de 
functie. Se apeleaza functia recursiv si se realizeaza actualizarea informatiei
din nod. 

### Pentru query nod:
Raspunsurile copiilor sunt initializate cu 0. Daca intervalul nodului este 
inclus in intervalul primit ca parametru, se returneaza informatia din nod. 
Altfel, se calculeaza mijlocul intervalului nodului si se merge de-a lungul 
arborelui, pe stanga sau pe dreapta, pana se ajunge la un interval inclus in
cel primit de functie. Se apeleaza recursiv functia de interogare si se 
apeleaza functia de "combinare_raspunsuri_copii" specifica arborelui. 

## Partea a II-a: 

## Intersectii de intervale:
### Pentru citirea din fisierul dat ca input:
Am alocat lista si vectorul de intervale, am deschis fisierul pentru citire si 
am citit mai intai ("fscanf") numarul de segmente. Am parcurs vectorul de 
intervale, alocand fiecare interval in parte, impreuna cu punctul din stanga si 
punctul din dreapta sa. Pentru fiecare interval am citit din "input_file" cele 
4 coordonate. Am intors lista de intervale formata. 

### Pentru calcularea numarului de intersectii, solutia cu arbori de intervale: 
Am parcurs vectorul de segmente si am retinut ordonata maxima, atat pentru 
punctele din stanga, cat si pentru cele din dreapta. Am pus intr-un vector de 
lungime cat de doua ori dimensiunea listei ("v_x") toate abscisele punctelor 
din stanga sau din dreapta. Intr-un alt vector ("v_int") de aceeasi lungime 
(2 * lista->dimensiune) am pus pentru fiecare coordonata "x" indicele 
segmentului din care face parte. Am creat un arbore de intervale cu radacina de 
la 0 la "y_max". Mi-am creat o functie de "swap" si am folosit algoritmul 
"Bubble Sort" pentru a sorta crescator vectorul de abscise. Cand am dat swap in
"v_x", am dat swap si in "v_int", pentru a avea mereu la aceeasi pozitie 
coordonata "x" si indicele intervalului din care face parte. Am pornit apoi cu
bara imaginara de maturare parcurgand, de fapt, lista sortata de abscise. Daca
am intalnit inceputul unui segment orizontal (abscisa provine dintr-un 
punct_stanga si y-ul punctului_stanga este y-ul punctului_dreapta), am alocat 
un interval format doar din coordonata "y" si am facut update in arbore pe 
acest interval. Daca x-ul intalnit este al unui segment vertical ("x"-ul 
punctului_stanga este "x"-ul punctului_dreapta), mi-am alocat un interval care
sa cuprinda intregul segment vertical (de la "y"-ul punctului_stanga la "y"-ul
punctului_dreapta) si am facut query in arbore pe acel interval. Am avut grija
sa nu realizez doua interogari pentru aceeasi verticala (ar fi iesit un numar
dublu de intersectii), de aceea l-am incrementat pe k in acest caz. In cazul in
care am intalnit sfarsitul unui segment orizontal (abscisa apartine unui punct
dreapta si "y"-ul punctului_stanga este egal cu "y"-ul punctului_dreapta), daca
urmatoarea abscisa din lista nu este egala cu cea curenta si nu apartine unei 
drepte verticale, voi aloca un interval cu ambele capete egale cu ordonata 
punctului si voi face update in arbore pe acest interval, de data aceasta cu 
valoarea "-1". Functia intoarce numarul de intersectii gasite. 

### Pentru calcularea numarului de intersectii, solutia triviala: 
Pentru solutia trviala am luat interval cu interval (2 for-uri) si daca am 
gasit o pereche segment orizontal-segment vertical, daca x-ul celui vertical 
este cuprins intre x-urile extremitatilor segmentului orizontal si daca y-ul 
celui orizontal este cuprins intre y-urile extremitatilor celui vertical, 
atunci incrementez numarul de intersectii. Functia intoarce numarul total de 
intersectii gasite.  

## Partea a III-a:

## Pozitie libera: 
### Pentru citirea datelor din fisierul dat ca input:
Am alocat structura ce cuprinde datele de intrare. Am deschis fisierul de 
intrare si am citit mai intai numarul maxim din intrari si apoi numarul de 
intrari. Ulterior, am parcurs vectorul de intrari si am citit cu "fscanf" 
fiecare intrare in parte. 

### Solutia triviala:
Am alocat vectorul solutie, initializand totodata toate elementele sale cu 
zero. Am parcurs cu "for" lista de intrari si, daca la pozitia data de fiecare 
element din lista, vectorul cu raspunsuri era nul, l-am facut sa aiba valoarea
respectivului numar din vectorul de intrari. Daca, insa, pozitia era ocupata, 
am parcurs inapoi vectorul cu raspunsuri pana am gasit o pozitie libera. 

### Solutia cu arbori de intervale:
Am alocat vectorul-solutie si am construit un arbore de intervale cu radacina 
de la 0 la numarul maxim din intrari. Am parcurs vectorul de intrari si, pentru
fiecare intrare, mi-am construit un interval cu amandoua capetele egale cu 
intrarea respectiva. Am realizat un query in arbore pentru acel interval si, 
pentru un rezultat nul (pozitie cu elementul nul in vectorul-solutie) am facut 
update pe acel interval si am ocupat automat pozitia din vectorul de raspunsuri 
data de intrarea la care am ajuns cu respectiva valoare a intrarii (nodul 
a avut, deci, informatia egala cu 1, odata ce intervalul sau a fost ocupat in 
vectorul-solutie). Daca rezultatul interogarii nu a fost nul, am mers inapoi 
prin frunzele arborelui pana am dat de un nod cu informatia 0, am facut update 
pentru acel nod si am ocupat pozitia corespunzatoare nodului in vectorul de 
raspunsuri. Am intors vectorul solutie.   


