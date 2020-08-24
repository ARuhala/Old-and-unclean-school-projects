//------------------------------------------------
//  TIE-02200 Ohjelmoinnin peruskurssi -mallikoodi
//  Copyright © 2017  opersk@tut.fi
//------------------------------------------------

#include "todo_rakenne.hh"
#include "apufunktiot.hh"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;


// ----------------------------------------------------------------------------
// lue_tehtavatiedosto
// -------------------
// Funktio lukee parametrina saamansa tietovirran avulla tehtävälistatiedoston
// ja lisää sieltä saamansa tiedot tehtavarakenteeseen.  Jos tiedostossa
// on virheellisiä rivejä, funktion on palautettava false.  Jos tiedosto on
// virheetön, paluuarvon oltava true.  Tiedoston lukemin tämän funktion
// avulla EI SAA TULOSTAA NÄYTÖLLE MITÄÄN, sillä virheilmoitusten tulostuksesta
// on huolehdittu pääohjelmassa.
//
// KOKO TIEDOSTON LUKEMINEN ON TOTEUTETTAVA REKURSION AVULLA.  Tämä funktio,
// eikä sen avuksi itse toteutetut apufunktiot saa sisältää yhtään silmukka-
// rakennetta.  Silmukkarakenteet ovat tässä yhteydessä työn hylkäämisperuste.
//
// Funktion paluuarvo ja parametrien tyypit ja määrä on säilytettävä.
// ET SIIS SAA MUUTTAA LUE_TEHTAVATIEDOSTO-FUNKTION RAJAPINTAA.
// ----------------------------------------------------------------------------
bool prioriteettivirhetarkastus (string prioriteetti) {
    int prioriteettinum = 1;
    if (not muuta_string_intiksi(prioriteetti, prioriteettinum)) {
        return false;
    }
    else if (prioriteetti.find_first_not_of("12345") != string::npos)
    {

        return false;
    }

    else {
        return true;
    }
}

bool paloittele(vector<string>& paloittelulista, string& paloiteltava) {
    string::size_type alkukohta = 0;
    string::size_type loppukohta;
    loppukohta = paloiteltava.find(";");
    string osaeka;
    string osatoka;

    if ( loppukohta == string::npos ) {
        //virheilmoitus("Tiedosto sisaltaa rivin jolla ei ole ; merkkia");
        return false;
    }
    else {
        // katkaistaan rivi kahteen osaan paloiteltavan kohdalta
        osaeka = paloiteltava.substr(alkukohta, loppukohta - alkukohta);
        if ( osaeka.empty() or not(prioriteettivirhetarkastus(osaeka)) ) {
            //virheilmoitus("Tiedosto sisaltaa virheellisen prioriteettinumeron.");
            return false;
        }

        // otetaan katkaisukohdan jälkeen loput
        osatoka = paloiteltava.substr(loppukohta + 1);
        if (osatoka.empty() or (osatoka.find_first_not_of(' ') == string::npos)){
            //virheilmoitus("Tiedosto sisaltaa virheellisen tehtavan.");
            return false;
        }

        //jos virhetarkastukset läpäistään, lisätään osaeka ja osatoka paloittelulistaan
        paloittelulista.push_back(osaeka);
        paloittelulista.push_back(osatoka);
        return true;

    }

}


bool lue_tehtavatiedosto(ifstream& virta, Todo& tehtavarakenne) {
    // funktion vastaanottama tehtavarakenne on muotoa
    // map<int, list<string>>; joka on olion tietoihin talletettuna
    // jossa int tyyppinen avain on tehtävän prioriteetti
    // ja list<string> on lista kyseisen prioriteetin tehtävistä
    // Tulostusfunktiot on rakennettu niin, että lista luetaan alusta lähtien
    // ja alusta löytyy aikaisemmin lisätyt tehtävät, joten tehtävät tallennetaan listaan
    // siten, että listan alusta löytyy vanhimmat tehtävät, ja uudet lisätään aina listan loppuun
    // tämä järjestely tulee ottaa huomioon Suorita funktion toteutuksessa, jossa vanhin tehtävä
    // eli listan ensimmäinen, suoritetaan eli poistetaan aina vuorollaan.

    // kuitenkin nyt tietorakenteeseen lisääminen on toteutettu Todo-olion yleiseen rajapintaan

    // luettava tiedosto on muotoa
    // kiirellisyystaso;tehtävä
    // jos näin ei ole palautetaan false
    // jos riviltä löytyy enemmän kuin yksi ; rivi katkaistaan ensimmäisen ; kohdalta ja loput oletetaan
    // osaksi tehtävää
    // tehtävä ei saa olla tyhjä "" eikä sisältää pelkkiä välilyöntejä
    // kiireellisyystaso on kokonaisluku 1-5, muussa tapauksessa palautetaan false

    string rivi;
    if (not getline(virta, rivi)) {
        // tiedosto on loppuunkäsitelty

        return true;
    }

    else {
        // tiedostosta saadun rivin käsittely

        // paloitellaan rivi ensimmäisen ; kohdalta apufunktion avulla
        // jos apufunktio palauttaa false, rivi oli virheellinen ja tiedoston lukeminenkin voidaan lopettaa
        vector<string> paloittelulista = {}; // nollataan paloittelulista jokakierroksella

        if (not (paloittele(paloittelulista, rivi))) {

            return false;   // paloittelussa löytyi virheellinen rivi
                            // palautetaan false edelliselle kutsunnalle
                            // eli rekursiivisen kutsun pitää myös olla sellainen, että se palauttaa aina falsen edelliselle kutsujalle
                            // jos on saatu itselle false
        }

        int prioriteettinumero;

        muuta_string_intiksi(paloittelulista.at(0), prioriteettinumero);



        // tallennetaan saadut prioriteetti ja tehtävä tehtavarakenteeseen
        tehtavarakenne.lisaa_tehtava(prioriteettinumero, paloittelulista.at(1));


        // lähdetään rekursiivisesti toiselle kierrokselle
        if (not lue_tehtavatiedosto(virta, tehtavarakenne)) {

            return false;
        }


    }




    // jostain syystä, jos tätä ei ole täällä lopussa, valmis ohjelma antaa virheiloitusta, että tiedosto oli virheellinen (vaikkei olisikaan)
    return true;
}
