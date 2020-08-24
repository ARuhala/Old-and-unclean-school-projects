#include "tiedostonluku.hh"
#include "ksl_lista.hh"
#include <iostream>
#include <regex>
#include <fstream>

using namespace std;
//------------------------------------------------------------------
//Tämän moduulin kehittäjänä on tyoskennellyt:
// Antti Ruhala
//------------------------------------------------------------------

// tässä moduulissa on toteutettu tiedostonlukeminen kokonaisuudessaan.


bool tiedostonluku(KSL_lista &reseptilista)
{
    // tiedoston lukeminen ja teidon pilkkominne riviltä toteutetaan regularexpressioneilla.
    regex TYHJA_REGEX("[[:space:]]*");
    regex KOMMENTTI_REGEX("[[:space:]]*#.*");
    regex CSV_REGEX(
                "[[:space:]]*"
                "([[:alpha:]_]+)"
                "[[:space:]]*"
                ":"
                "[[:space:]]*"
                "([[:alpha:]_]+)"
                "[[:space:]]*"

                );

    // tiedoston nimen syöttäminen
    string syotenimi = "";
    cout << "Syotetiedosto: ";
    getline(cin, syotenimi);
    ifstream file(syotenimi);

    if (not file) {
        cout << "Virhe: Syotetiedostoa ei saatu luettua." << endl;
        return false;
    }


    // tiedoston rivien käsittely yksi kerrallaan.
    // virheellinen rivi aiheuttaa ohjelman sammuttamisen virheilmoituksen kera.
    // kommentti # sekä tyhjiä merkkejä sisältävät rivit ovat sallittuja ja aiheuttavat vai kyseisen rivin skippaamisen.

    string rivi;
    smatch tulos;

    while ( getline(file,rivi) ) {
        if ( regex_match(rivi, TYHJA_REGEX) ) {
            continue;

        }

        else if ( regex_match(rivi, KOMMENTTI_REGEX) ) {
            continue;
        }


        else if ( regex_match(rivi, tulos, CSV_REGEX) ) {
            // oikeanlaiset syöterivit aiheuttavat tiedon erittelyn, sekä tallentamisen halutun laiseen dynaamiseen tietorakenteeseen.
            // tietorakenne on hyvin samankaltainen kuin perinteinen map tietotyyppi.


            // samankaltaisia rivejä ei saa löytyä useaa kappaleta
            // samanlaisen rivin löytyminen aiheuttaa virhetilanteen ja ohjelman sulkeutumisen.
            // samankaltaisuus tunnistetaan, jos sama tieto on jo lisätty tietorakenteeseen akaisemmin.


            reseptilista.lisaa_numerojarjestykseen(tulos.str(1));

            // tarkistetaan, ettei samaa materiaalia ole jo listalla

            if (not reseptilista.lisaa_materiaali(tulos.str(2), tulos.str(1)) ) {
                return false;
            }




        }

        else {
            cout << "Virhe: Virheellinen syoterivi:'" << rivi << "'" << endl;
            return false;
        }


}
    file.close();
    // tiedosto on luettu läpikotaisin onnistuneesti, ja voidaan siirtyä käyttöliittymään
    cout << "Tuotantoketjut luettu onnistuneesti." << endl;
    return true;
}
