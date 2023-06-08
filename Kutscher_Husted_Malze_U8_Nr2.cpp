#include<iostream>

using namespace std;

class Escooter {

/* Quelle: https://eroller-mit-zulassung.de/e-scooter-motor/
1 PS = 735,49875 Watt
150 Watt:  10 Km; 250 Watt: 20 Km; 350 Watt: 26 Km; 500 Watt: 40 Km
Faktor ca: 12,5
*/

private:

    double* daten;

public:

    /*
    Voraussetzung: Ps-Wert nicht negativ und nicht größer als 0.7
    Effekt: Ein Escooter Objekt mit Leistung ps, 100 % Akkuladung und 0 km gelaufen ist erzeugt
    Ergebnis: keins
    */
    Escooter (double ps) {

        if (ps < 0) {
            ps = 0.1;
        }
        
        double akku = 100;
        double km = 0;
        const double reichweite = (ps * (735.49875)) / 12.5; // Reichweite des Akkus in km

        this->daten = new double[4];
        this->daten[0] = ps;
        this->daten[1] = reichweite;
        this->daten[2] = km;
        this->daten[3] = akku;

    }

    /*
    Voraussetzung: Keine
    Effekt: Der Speicher des Objekts ist freigegeben
    Ergebnis: Keins
    */
    ~Escooter() {
        delete [] this->daten;
    }

    /*
    Voraussetzung: Keine
    Effekt: Der Vergleichsoperatoren vergleichen die PS der Scooter
    Ergebnis: Keins
    */
    bool operator<(const Escooter& c) const {
        return this->daten[0] < c.daten[0];
    }

    bool operator==(const Escooter& c) const {
        return this->daten[0] == c.daten[0];
    }

    bool operator>(const Escooter& c) const {
        return this->daten[0] > c.daten[0];
    }

    /*
    Voraussetzung: Keine
    Effekt: kein
    Ergebnis: Die PS des Scooters sind geliefert
    */
    double gibPS() {
        return this->daten[0];
    }

    /*
    Voraussetzung: Keine
    Effekt: kein
    Ergebnis: Die Akkurestladung des Scooters ist geliefert
    */
    double gibAkku() {
        return this->daten[3];
    }

    /*
    Voraussetzung: Keine
    Effekt: kein
    Ergebnis: Die gelaufenen KM des Scooters seit der letzen Ladung sind geliefert.
    */
    double gibKm() {
        return this->daten[2];
    }

    /*
    Voraussetzung: Keine
    Effekt: kein
    Ergebnis: Die verbleibenden Km des Scooters bis Akku leer sind geliefert
    */
    double gibRestKm() {
        return this->daten[1] - this->daten[2];
    }

     /*
    Voraussetzung: Keine
    Effekt: Alle aktuellen Daten auf Konsole ausgeben
    Ergebnis: kein
    */
    void zeigeInfo() {
        cout << "    PS: " 
             << gibPS() << "\n    Akkuladung: " 
             << gibAkku() << " % \n    gefahrene Strecke: " 
             << gibKm() << " km \n    Reststrecke: " 
             << gibRestKm() << " km" << endl;
    }

    /*
    Voraussetzung: Eine Strecke in km eingeben
    Effekt: Falls mit der Restakkulaufzeit möglich wird die Strecke gefahren und die Daten aktualisiert.
    Ergebnis: kein
    */
    void fahreKm(double km) {
        if (gibRestKm() >= km) {
            this->daten[2] += km; // neue gesamt km
            this->daten[3] -= (100 * km) / this->daten[1]; // neue Restakku in %
            cout << "\n Restakku: " << gibAkku() << " %, Reststrecke: " << gibRestKm() << " km" << endl;
        }
        else {cout << "\n Nicht genügend Akku. Reststrecke möglich: " << gibRestKm() << " km" << endl;}
    }

    /*
    Voraussetzung: Keine
    Effekt: Der Akku wird auf 100 % geladen und die gefahrenen Km auf 0 zurück gesetzt.
    Ergebnis: kein
    */
    void ladeAkku() {
        this->daten[3] = 100;
        this->daten[2] = 0;
        cout << "\n Der Akku ist wieder voll geladen! \n";
    }
};

void scooterFahren() {

    double ps = 0;
    double strecke = 0;
    unsigned funktion = 100;

    Escooter leihScooter = Escooter(0.3);

    cout << "\n Wieviel PS hat dein Scooter? \n";
    cin >> ps;
    Escooter sc1 = Escooter(ps);
    sc1.zeigeInfo();

    if (sc1 < leihScooter) {
        cout << "\n Unser Leihscooter hat : \n";
        leihScooter.zeigeInfo();
    }

    while (funktion != 0) {
        cout << "\n Was möchtest du tun? \n"
             << " 1 - Deinen Scooter fahren \n"
             << " 2 - Deine Scooter Daten ausgben \n" 
             << " 3 - Deinen Akku aufladen \n"
             << " 4 - Leihscooter fahren \n"
             << " 0 - Scooter fahren beenden \n";
        cin >> funktion;
        if (funktion == 1) {
            cout << "\n Wie viele km soll gefahren werden? \n ";
            cin >> strecke;
            sc1.fahreKm(strecke);
            strecke = 0;
        }
        else if (funktion == 2) {
            cout << "Deine Scooter Daten: \n";
            sc1.zeigeInfo();
        }
        else if (funktion == 3) {
            sc1.ladeAkku();
        }
        else if (funktion == 4) {
            cout << "Unser Leihscooter hat: \n";
            leihScooter.zeigeInfo();

            while (leihScooter.gibRestKm() > 0) {

                cout << "\n Wie viele km soll gefahren werden? \n Gib 0 ein für Rückgabe! \n ";
                cin >> strecke;

                if (strecke == 0) {cout << "\n Vielen Dank \n"; leihScooter.ladeAkku(); break;}

                else {leihScooter.fahreKm(strecke); strecke = 0;}
            }
        }
    }
    return;
}


int main () {

    unsigned auswahl = 100;

    while (auswahl != 0) {
        cout << "\n Welche Simulation soll gestartet werden? \n"
             << " 1 - E-Scooter \n"
             << " 2 - Kochfeld \n"
             << " 0 - Programm beenden \n";
        cin >> auswahl;

        if (auswahl == 1) {scooterFahren();}
        
        else if (auswahl == 2) {return 0;}
    }

    return 0;
}
