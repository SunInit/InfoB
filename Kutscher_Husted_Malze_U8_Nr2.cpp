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
        else if (ps > 0.7) {
            ps = 0.7;
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
    Voraussetzung: Eine Strecke in km eingeben
    Effekt: Falls mit der Restakkulaufzeit möglich wird die Strecke gefahren und die Daten aktualisiert.
    Ergebnis: kein
    */
    void fahreKm(double km) {
        if (gibRestKm() >= km) {
            this->daten[2] += km; // neue gesamt km
            this->daten[3] -= (100 * km) / this->daten[1]; // neue Restakku in %
            cout << "Restakku %: " << gibAkku() << " Reststrecke km: " << gibRestKm() << endl;
        }
        else {cout << "Nicht genügend Akku, bitte erst aufladen! Reststrecke möglich: " << gibRestKm() << endl;}
    }

    /*
    Voraussetzung: Keine
    Effekt: Der Akku wird auf 100 % geladen und die gefahrenen Km auf 0 zurück gesetzt.
    Ergebnis: kein
    */
    void ladeAkku() {
        this->daten[3] = 100;
        this->daten[2] = 0;
    }
};

void scooterFahren() {

    double ps = 0;
    double strecke = 0;
    unsigned funktion = 100;

    Escooter leihScooter = Escooter(0.3);

    cout << "Wieviel PS hat dein Scooter? \n";
    cin >> ps;
    Escooter sc1 = Escooter(ps);
    cout << "Dein Scooter hat " << sc1.gibPS() << " PS und damit eine Reichweite von " << sc1.gibRestKm() << " km \n";
    // cout << "Unser Leihscooter hat " << leihScooter.gibPS() << " PS und wäre somit " << (sc1 < leihScooter) ? "stärker \n" : "schwächer \n";

    while (funktion != 0) {
        cout << "Was möchtest du tun? \n 1 - Deinen Scooter fahren \n 2 - Deine Scooter Daten ausgben \n 3 - Deinen Akku aufladen \n 4 - Leihscooter fahren \n 0 - Scooter fahren beenden? \n";
        cin >> funktion;
        if (funktion == 1) {
            cout << "Wie weit soll gefahren werden? \n ";
            cin >> strecke;
            sc1.fahreKm(strecke);
            strecke = 0;
        }
        else if (funktion == 2) {
            cout << "Deine Scooter Daten derzeit: \n    PS: " << sc1.gibPS() << "\n    Akkuladung in %: " << sc1.gibAkku() << "\n    gefahrene Strecke in Km: " << sc1.gibKm() << endl;
        }
        else if (funktion == 3) {
            cout << "Der Akku ist wieder voll geladen! \n";
            sc1.ladeAkku();
        }
        else if (funktion == 4) {
            cout << "Unser Leihscooter hat " << leihScooter.gibPS() << " PS und eine Reichweite von: " << leihScooter.gibRestKm() << "kM \n";
            cout << "Wie weit soll gefahren werden? \n ";
            cin >> strecke;
            if (strecke <= leihScooter.gibRestKm()) {
                leihScooter.fahreKm(strecke);
            }
            else {cout << "Leider schaffen unsere Scooter diese Strecke nicht! \n";}
            leihScooter.ladeAkku(); //Darum muss sich der Kunde beim Leihscooter nicht selber kümmern...
            strecke = 0;
        }
    }
    return;
}


int main () {

    unsigned auswahl = 100;

    while (auswahl != 0) {
        cout << "Welche Simulation soll gestartet werden? 1 - Escooter, 2 - Kochfeld, 0 - Programm beenden \n";
        cin >> auswahl;

        if (auswahl == 1) {scooterFahren();}
        
        else if (auswahl == 2) {return 0;}
    }

    return 0;
}
