// Namen: M. Husted, A. Maltze, S. Kutscher
// Tutorium: Grevens Carpi, Rebecca Maria
// Übung 5, Aufgabe 1
// g++ -std=c++14 -Wall -Wextra -Werror -pedantic -o ultrasort hilfsfunktionen.cpp Kutscher_Husted_Malze_U5_Nr1.cpp

#include "hilfsfunktionen.hpp"
#include <iostream>
#include <vector>

/*
Voraussetzung: Ein Int-Vector eingeben.
Ergebnis:      kein
Effekt:        Der sortierte Vector ist geliefert.
*/
void ultraSort(std::vector<int>& elems);
void ultraSortHelp(std::vector<int>& elems, unsigned start, unsigned end); // Rekursiver Aufruf

/*
Voraussetzung: Ein Int-Vector und einen Anteil angeben.
Ergebnis:      kein
Effekt:        Der sortierte Vector ist geliefert.
*/
void ultraSortParam(std::vector<int>& elems, unsigned fraction);
void ultraSortParamHelp(std::vector<int>& elems, unsigned start, unsigned end, unsigned fraction); // Rekursiver Aufruf

/*
Voraussetzung: Ein Int-Vector und einen Bereich aus Start- und End-Index eingeben.
Ergebnis:      kein
Effekt:        Der Vector im Bereich sortiert ist geliefert.
*/
void insertionSort(std::vector<int>& elems, unsigned begin, unsigned end);

/*
Voraussetzung: Ein Int-Vector und einen Bereich mit einer Unterteilung in zwei sortierte Teile eingeben.
Ergebnis:      kein
Effekt:        Die beiden Teile des Bereiches zusammengefasst sortiert sind geliefert.
*/
void merge(std::vector<int>& elems, unsigned begin, unsigned mid, unsigned end);

/*
Voraussetzung: Einen Vector mit Elementanzahlen eingben.
Ergebnis:      kein
Effekt:        Die Arrays werden mit insertSort sortiert, die jeweils benötigte Zeit ist geliefert.
*/
void testInsertSort (const std::vector<int>& range);

/*
Voraussetzung: Eine Arraygröße eingeben
Ergebnis:      kein
Effekt:        Ein Array angegebener Größe wird mit ultraSort sortiert und eine
			   Aussage, ob dies gelungen ist, ist geliefert.
*/
void funktionUltraSort (unsigned intSize);

/*
Voraussetzung: Einen Vector mit Elementanzahlen eingeben
Ergebnis:      kein
Effekt:        Die Arrays werden mit UltraSort sortiert, die jeweils benötigte Zeit ist geliefert.
*/
void testUltraSort (const std::vector<int>& range);

/*
Voraussetzung: Eine Arraygröße und eine Fraktion eingeben
Ergebnis:      kein
Effekt:        Ein Array angegebener Größe wird mit UltraSortParam sortiert und eine
			   Aussage, ob dies gelungen ist, ist geliefert.
*/
void funktionUltraSortParam(unsigned intSize, unsigned frac);

/*
Voraussetzung: Einen Vector mit Elementanzahlen und einen Vector mit Fraktionen eingeben.
Ergebnis:      kein
Effekt:        Die Arrays werden mit UltraSortParam sortiert, die jeweils benötigte Zeit ist geliefert.
*/
void testUltraSortParam(const std::vector<int>& range, std::vector<int> rangeFrac);

/*
Voraussetzung: Einen Vector mit Float-Elementen eingeben
Ergebnis:      kein
Effekt:        Der Vector wird ausgegeben.
*/
void gebe_ausf(std::vector<float>& vec, unsigned start, unsigned end){
        if(end>vec.size()){
            std::cout << vec.size() << " " << end << std::endl;
            return;
        }
    std::cout << vec[start];
    for(unsigned k=start+1; k<end; k++){
        std::cout << ", " << vec[k];
    }
    std::cout << std::endl;
}


/****************************************   MAIN   ****************************************************
 ******************************************************************************************************/

int main() {

	srand(time(NULL)); // Zufallsgenerator starten

	std::vector<int> range_long = {10000, 100000, 1000000};
	std::vector<int> rangeFrac = {4,6,8,10,12,14,16,18,20,22,24,26,28,30};
	

	unsigned auswahl = 9;

	do {
		std::cout << "_____________________________________________________\n"
				  << "| Welcher Sortiertest?                               |\n"
		          << "| 1 - LZ Insert Sort                                 |\n" 
				  << "| 2 - LZ Ultra Sort 1/3                              |\n" 
				  << "| 3 - LZ Ultra Sort mit unterschiedlichen Fraktionen |\n" 
				  << "| 4 - Funktionstest Ultra Sort 1/3                   |\n" 
				  << "| 5 - Funktionstest Ultra Sort 1/20                  |\n"
				  << "| 0 - Programm beenden                               |\n"
				  << "|____________________________________________________|\n";
	
		std::cin >> auswahl;
		
		if      (auswahl == 1) {testInsertSort(range_long);}
		else if (auswahl == 2) {testUltraSort(range_long);}
		else if (auswahl == 3) {testUltraSortParam(range_long, rangeFrac);}
		else if (auswahl == 4) {funktionUltraSort(100);}
		else if (auswahl == 5) {funktionUltraSortParam(100, 20);}
	} while (auswahl != 0);
	
	return 0;
}

/**************************************  MAIN ENDE  ***************************************************
 * 
 * 
 **************************************  SortierFunktionen  *******************************************/

void insertionSort(std::vector<int>& elems, unsigned begin, unsigned end){

	if(begin==end||begin==end-1){
        return;
    }
	else if (end-begin==2){
		if (elems[begin] > elems[begin+1]) {
			hf::swap(elems, begin, begin+1);
			return;
		}
		return;
	}
    int key=elems[begin];
    unsigned shiftindex;

    for(unsigned i = begin +1; i<end; i++){
        key=elems[i];

        for(shiftindex=i; shiftindex>begin && elems[shiftindex-1]>=key; shiftindex--){
            elems[shiftindex] = elems[shiftindex-1];
        }

        elems[shiftindex] = key;
    }
}

void merge(std::vector<int>& elems, unsigned begin, unsigned mid, unsigned end){

    std::vector<int> firstHalf = hf::copy(elems, begin, mid);
    std::vector<int> secondHalf = hf::copy(elems, mid, end);
    unsigned i = 0;
    unsigned j = 0;
    while(begin + i + j < end){
        if ( j >= secondHalf.size() || ((i<firstHalf.size()) && (firstHalf[i]<secondHalf[j]))){
            elems[begin+i+j] = firstHalf[i];
            i++;
        }else{
            elems[begin+i+j] = secondHalf[j];
            j++;
        }
    }
}

void ultraSortHelp(std::vector<int>& elems, unsigned start, unsigned end) {

	if(start==end||start==end-1){
        return;
    }
	if (start==end-2){
		if (elems[start] > elems[start+1]) {
			hf::swap(elems, start, start+1);
			return;
		}
		return;
	}

    unsigned tri = (end-start)/3;
    insertionSort(elems, start, start+tri);
    ultraSortHelp(elems, start+tri, end);
    merge(elems, start, start+tri, end);

}

void ultraSort(std::vector<int>& elems) {

	ultraSortHelp(elems, 0, elems.size());
}

void ultraSortParamHelp(std::vector<int>& elems, unsigned start, unsigned end, unsigned fraction) {

	if(start==end||start==end-1){
        return;
    }
	else if (end-start==2){
		if (elems[start] > elems[start+1]) {
			hf::swap(elems, start, start+1);
			return;
		}
		return;
	}
	else if (end-start <= fraction) {
    	insertionSort(elems,start,end);
		return;
	}

    unsigned tri = (end-start)/fraction;
    insertionSort(elems, start, start+tri);
    ultraSortParamHelp(elems, start+tri, end, fraction);
    merge(elems, start, start+tri, end);
}

void ultraSortParam(std::vector<int>& elems, unsigned fraction) {

	ultraSortParamHelp(elems, 0, elems.size(), fraction);
}

/***************************************  Testfunktionen   ****************************************************/

void testInsertSort (const std::vector<int>& range) {

	std::vector<int> array;
	double time;

	std::vector<float> erg_rand;
	std::vector<float> erg_rise;
	std::vector<float> erg_fall;

	std::cout << "Testdurchlauf nur mit Insertionsort ohne Fraktionierung: \n";

	for (int size : range) {

		std::cout << "   " << size << " Elemente: \n";
		
		// Zufälliges Array testen:
		array = hf::zufalls_array(size);

		time = clock(); // Startzeit
		insertionSort(array,0, array.size() -1);
		time = clock() - time; // Endzeit

		std::cout << "      Zufällig: " << (time/CLOCKS_PER_SEC) << " Sekunden \n";
		erg_rand.push_back(time/CLOCKS_PER_SEC);

		// Aufsteigend sortiertes Array testen:
		array = hf::sortiertes_array(size, true);

		time = clock(); // Startzeit
		insertionSort(array,0, array.size() -1);
		time = clock() - time; // Endzeit

		std::cout << "      Aufsteigend: " << (time/CLOCKS_PER_SEC) << " Sekunden \n";
		erg_rise.push_back(time/CLOCKS_PER_SEC);
		
		// Absteigend sortiertes Array testen:
		array = hf::sortiertes_array(size, false);

		time = clock(); // Startzeit
		insertionSort(array,0, array.size() -1);
		time = clock() - time; // Endzeit

		std::cout << "      Absteigend: " << (time/CLOCKS_PER_SEC) << " Sekunden \n \n"
		          << "******************************************************** \n";
		erg_fall.push_back(time/CLOCKS_PER_SEC);
	}

	std::cout << "Zusammenfassung:\n zufällig: \n";
	gebe_ausf(erg_rand,0,erg_rand.size()-1);
	std::cout << "steigend: \n";
	gebe_ausf(erg_rise,0,erg_rise.size()-1);
	std::cout << "fallend: \n";
	gebe_ausf(erg_fall,0,erg_fall.size()-1);
	std::cout << "******************************************************** \n" << std::endl;
}

void testUltraSort (const std::vector<int>& range) {

	std::vector<int> array;
	double time;

	std::vector<float> erg_rand;
	std::vector<float> erg_rise;
	std::vector<float> erg_fall;

	std::cout << "Testdurchlauf mit UltraSort Fraktionierung 1 zu 3: \n";


	for (int size : range) {
		std::cout << "   " << size << " Elemente: \n";

		// Zufälliges Array testen:
		array = hf::zufalls_array(size);

		time = clock(); // Startzeit
		ultraSort(array);
		time = clock() - time; // Endzeit

		std::cout << "      Zufällig: " << (time/CLOCKS_PER_SEC) << " Sekunden \n";
		erg_rand.push_back(time/CLOCKS_PER_SEC);

		// Aufsteigend sortiertes Array testen:
		array = hf::sortiertes_array(size, true);

		time = clock(); // Startzeit
		ultraSort(array);
		time = clock() - time; // Endzeit

		std::cout << "      Aufsteigend: " << (time/CLOCKS_PER_SEC) << " Sekunden \n";
		erg_rise.push_back(time/CLOCKS_PER_SEC);

		// Absteigend sortiertes Array testen:
		array = hf::sortiertes_array(size, false);

		time = clock(); // Startzeit
		ultraSort(array);
		time = clock() - time; // Endzeit

		std::cout << "      Absteigend: " << (time/CLOCKS_PER_SEC) << " Sekunden \n \n";
		erg_fall.push_back(time/CLOCKS_PER_SEC);
	}
	std::cout << "Zusammenfassung:\n zufällig: \n";
	gebe_ausf(erg_rand,0,erg_rand.size()-1);
	std::cout << "steigend: \n";
	gebe_ausf(erg_rise,0,erg_rise.size()-1);
	std::cout << "fallend: \n";
	gebe_ausf(erg_fall,0,erg_fall.size()-1);
	std::cout << "******************************************************** \n" << std::endl;

	std::cout << "******************************************************** " << std::endl;
}

void testUltraSortParam(const std::vector<int>& rangeSize, std::vector<int> rangeFrac) {

	std::vector<int> array;
	double time;

	std::cout << "Testdurchlauf mit UltraSortParam: \n";

	
	for (int i : rangeFrac) {

		std::cout << "Laufzeit mit Anteil 1 zu " << i << " mit ultraSortParam \n \n";
		
		for (int size : rangeSize) {

			std::cout << "   " << size << " Elemente: \n";
			// Zufälliges Array testen:
			array = hf::zufalls_array(size);

			time = clock(); // Startzeit
			ultraSortParam(array, i);
			time = clock() - time; // Endzeit

			std::cout << "      Zufällig: " << (time/CLOCKS_PER_SEC) << " Sekunden \n";
			
			// Aufsteigend sortiertes Array testen:
			array = hf::sortiertes_array(size, true);

			time = clock(); // Startzeit
			ultraSortParam(array, i);
			time = clock() - time; // Endzeit

			std::cout << "      Aufsteigend: " << (time/CLOCKS_PER_SEC) << " Sekunden \n";

			// Absteigend sortiertes Array testen:
			array = hf::sortiertes_array(size, false);

			time = clock(); // Startzeit
			ultraSortParam(array, i);
			time = clock() - time; // Endzeit

			std::cout << "      Absteigend: " << (time/CLOCKS_PER_SEC) << " Sekunden \n";
			
		}
		std::cout << "******************************************************** \n" << std::endl;
	}
	std::cout << "******************************************************** \n" << std::endl;
}

void funktionUltraSort (unsigned intSize) {

	std::cout << "Funktionstest zufälliges Array mit UltraSort: \n";
	std::vector<int> array = hf::zufalls_array(intSize);

	ultraSort(array);

	hf::gebe_aus(array,0,array.size()-1);

	unsigned i = 0;
	while (i < array.size() -1) {
		if (array[i] > array[i+1]) {
			std::cout << "\n Array nicht sortiert\n"
			          << " ********************" << std::endl; 
			return;
		}
		i++;
	}

	std::cout << "\n Array korrekt aufsteigend sortiert. \n" 
	          << " ***********************************" << std::endl;
}

void funktionUltraSortParam(unsigned intSize, unsigned frac) {

	std::cout << "Funktionstest zufälliges Array mit UltraSortParam: \n";
	std::vector<int> array = hf::zufalls_array(intSize);

	ultraSortParam(array, frac);

	hf::gebe_aus(array,0,array.size());

	unsigned i = 0;
	while (i < array.size() -1) {
		if (array[i] > array[i+1]) {
			std::cout << "Array nicht sortiert\n"
			          << "********************" << std::endl; 
			return;
		}
		i++;
	}

	std::cout << "\n Array korrekt aufsteigend sortiert. \n"
			  << " *********************************** " << std::endl;
}

