#include "splitteri.hh"
#include "tiedostonlukujatalletus.hh"
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <map>
#include <algorithm>
#include <iomanip>
#include <set>

// Harjoitustyön tekijä Antti Ruhala

// Tämä pienimuotoinen ohjelma lukee teksitiedoston ja tallettaa sen tietorakenteeseen
// tietorakenteeseen voidaan suorittaa erilaisia hakuja käyttöliittymän avulla
// Työssä on myös harjoiteltu lähdekoodin jakamista useaan osaan
// Käyttöliittymässä toimivat käskyt ovat:
// Lopeta
// kauppaketjut
// myymalat
// halvin
// tuotevalikoima
// tuotenimet

using namespace std;

void kauppaketjufunktio(const map<string, map<string, vector<Tuote>>>& tietokanta) {
    // tulostetaan kaikki kauppaketjut
    for (auto kauppaketju : tietokanta) {
        cout << kauppaketju.first << endl;
    }
}

void myymalafunktio(string kauppaketju, const map<string, map<string, vector<Tuote>>>& tietokanta ) {
    // katsotaan löytyykö haluttu kauppaketju tietokannastamme
    if (not (tietokanta.find(kauppaketju) == tietokanta.end())) { // verrataan syote kauppaketjua ensimmäisen mapin avaimeen (map.find(avain) == loppuiteraattorin) avulla

        // tulostetaan kyseisen kauppaketjun kaikki kauppa_alueet
        for ( auto kauppa_alue : tietokanta.at(kauppaketju)) {
            cout << kauppa_alue.first << endl;
        }
    }
    else {
        cout << "Virhe: Kyseista kauppaketjua ei loydy." << endl;
    }

}

bool vertailetuotteita (const Tuote& tuote1, const Tuote& tuote2) {
    if ((tuote1.hinta < tuote2.hinta) and (tuote1.hinta != -1)) {
        return true;
    }
    else {
        return false;
    }
}

void halvintuotefunktio(string tuotteennimi, const map<string, map<string, vector<Tuote>>>& tietokanta) {
    vector<string> kauppalista = {};
    string kauppanimi;
    Tuote vertailutuote;

    // käydään kauppoja läpi
    for (auto kauppaketju : tietokanta) {
        for (auto kauppa : tietokanta.at(kauppaketju.first)) {
            for (auto tavara : tietokanta.at(kauppaketju.first).at(kauppa.first)) {
                // tallennetaan halvimmat kaupat (sekä kauppaketju) vektoriin ja halvin hinta muuttujaan vertailutuote
                // kauppa sekä kauppaketju tallennetaan yhtenä stringinä


                if (tavara.tuotenimi == tuotteennimi) {
                    if (kauppalista.size() == 0) {
                        kauppanimi = kauppaketju.first + " " + kauppa.first;
                        kauppalista.push_back(kauppanimi);


                        vertailutuote = {tavara.tuotenimi, tavara.hinta};




                    }
                    // jos löydetään samalla hinnalla kauppa, lisätään kauppa vektoriin
                    else if (tavara.hinta == vertailutuote.hinta) {
                        kauppanimi = kauppaketju.first + " " + kauppa.first;
                        kauppalista.push_back(kauppanimi);



                    }
                    // jos löydetään uusi kauppa halvemmalla hinnalla, nollataan vektori ja tallennetaan uusi kauppa ainoaksi vektorin alkioksi
                    else if (vertailetuotteita(tavara, vertailutuote)) {
                        kauppanimi = kauppaketju.first + " " + kauppa.first;
                        kauppalista = {};
                        kauppalista.push_back(kauppanimi);

                        vertailutuote = {tavara.tuotenimi, tavara.hinta};


                    }
                }

            }
        }
    } // tietorakenne on tutkittu läpikotaisin









    // tuote löytyy yhdestä tai useammasta kaupasta (halvimmat kaupat vektorissa on tavaraa ja hinta on asetettu)
    if ( (kauppalista.size() != 0) ) {

        if (vertailutuote.hinta != -1) {
            cout << setprecision(2) << fixed <<vertailutuote.hinta << " " << "euroa" << endl;
            for (auto kauppa : kauppalista) {
                cout << kauppa << endl;
            }
        }

        // tuote löytyy yhdestä tai useammasta kaupasta, mutta on loppu kaikkialla (halvimmat kaupat vektorissa on tavaraa, mutta hinta on -1)
        else {
              cout << "Tuote on tilapaisesti loppu kaikkialta." << endl;
            }
        }



    // tuotetta ei löydy mistään kaupasta (halvimmat kaupat vektorin pituus on 0)
    else if  (kauppalista.size() == 0) {
        cout << "Tuote ei kuulu valikoimiin." << endl;
    }
}
bool vertailetuotenimia (const Tuote tuote1, const Tuote tuote2) {
    if ( tuote1.tuotenimi < tuote2.tuotenimi ) {
        return true;
    }
    else {
        return false;
    }
}

void tuotevalikoimafunktio(string kauppaketju, string kauppa, map<string, map<string, vector<Tuote>>> tietokanta) {

    if (not (tietokanta.find(kauppaketju) == tietokanta.end())) {
        {
            if(not (tietokanta.at(kauppaketju).find(kauppa) == tietokanta.at(kauppaketju).end() )) {
                // halutaan tulostusket nimien aakkosjärjestyksessä, tuotteet ovat nyt vectorissa hinnan suhteen järjestyksessä
                // joten suoritetaan sorttaus nimen mukaan
                // jotta sort funktiota voidaan käyttää, tietorakennetta ei voida antaa viiteparametrinä
                sort(tietokanta.at(kauppaketju).at(kauppa).begin(), tietokanta.at(kauppaketju).at(kauppa).end(), vertailetuotenimia);
                for (auto tavara : tietokanta.at(kauppaketju).at(kauppa)  ) {

                    if (tavara.hinta == -1) {
                        cout << tavara.tuotenimi << " " << "loppu" << endl;
                    }
                    else {
                        cout << setprecision(2) << fixed << tavara.tuotenimi << " " << tavara.hinta << endl;
                    }
            }
            }

            else {
                cout << "Virhe: Kauppa-aluetta ei loytynyt." << endl;
            }

    }
    }
        else {
            cout << "Virhe: Kauppaketjua ei loytynyt." << endl;
        }


}

void tuotenimifunktio (const map<string, map<string, vector<Tuote>>> tietokanta){
    // lisätään kaikki tuotteet settiin, jos tuote on jos setissä, sitä ei lisätä uudestaan
    set<string> tuotelista = {};
    for (auto kauppaketju : tietokanta){
        for (auto kauppa : tietokanta.at(kauppaketju.first)){
            for (auto tuote : tietokanta.at(kauppaketju.first).at(kauppa.first)){
                if (tuotelista.find(tuote.tuotenimi) == tuotelista.end()) {
                    tuotelista.insert(tuote.tuotenimi);
                }

            }
        }
    }

    // tulostetaan setin sisältö
    for (auto alkio : tuotelista) {
        cout << alkio << endl;
    }

}

int main()
{

    // luodaan suuri tietokanta ja täytetään se tiedoston pohjalta saadulla tiedolla
    map<string, map<string, vector<Tuote>>> tietokanta;
    // haetaan rakennetta: map{ string S-market, map {string Hervanta, vector{banaani, ananas, omena}}}
    // tietokanta.at(S-market) = map{hervanta, vector{banaani, ananas, omena}}
    // tietokanta.at(S-market).at(Hervanta) = vector{banaani, ananas, omena}
    // tietokanta.at(S-market).at(Hervanta).at(0) = Tuote banaani

    if (lisaa_tiedostosta("tuotetiedot.txt", tietokanta)) {
        // siirrytään käyttöliittymään
        while (true) {

            string syote;
            cout << "tuotehaku> ";
            getline(cin, syote);

            Splitter paloittelija(syote);
            paloittelija.paloittele(' ');


            // kauppaketjut
            if (paloittelija.hae_kentta(0) == "kauppaketjut") {
                if ((paloittelija.kenttien_lukumaara() == 1)) {
                    kauppaketjufunktio(tietokanta);

                }
                else {
                    cout << "Virhe: Virheellinen maara syotteita." << endl;
                }
            }

            // myymalat kauppaketjun_nimi
            else if (paloittelija.hae_kentta(0) == "myymalat") {
                if ((paloittelija.kenttien_lukumaara() == 2)) {
                    myymalafunktio(paloittelija.hae_kentta(1), tietokanta);

                }
                else {
                    cout << "Virhe: Virheellinen maara syotteita" << endl;
                }

            }

            // halvin tuotteen_nimi
            else if (paloittelija.hae_kentta(0) == "halvin") {
                if ((paloittelija.kenttien_lukumaara() == 2)) {
                   halvintuotefunktio(paloittelija.hae_kentta(1), tietokanta);


                }
                else {
                    cout << "Virhe: Virheellinen maara syotteita." << endl;
                }

            }

            // tuotevalikoima kauppaketjun_nimi kaupan_sijainti
            else if (paloittelija.hae_kentta(0) == "tuotevalikoima") {
                if (paloittelija.kenttien_lukumaara() == 3) {
                    tuotevalikoimafunktio(paloittelija.hae_kentta(1), paloittelija.hae_kentta(2), tietokanta);
                }
                else {
                    cout << "Virhe: Virheellinen maara syotteita." << endl;
                }

            }

            // tuotenimet
            else if (paloittelija.hae_kentta(0) == "tuotenimet") {
                if (paloittelija.kenttien_lukumaara() == 1) {
                    tuotenimifunktio(tietokanta);
                }
                else {
                    cout << "Virhe: Virheellinen maara syotteita." << endl;
                }


            }

            // lopeta käsky
            else if (paloittelija.hae_kentta(0) == "lopeta") {
                if (paloittelija.kenttien_lukumaara() == 1) {
                    break;
                }
                else {
                    cout << "Virhe: Virheellinen maara syotteita." << endl;
                }
            }

            else {
                cout << "Virhe: Virheellinen syote." << endl;
            }

        }
    }

    else {
        cout << "Virhe: Tiedoston lukemisessa tapahtui virhe." << endl;
    }



}
