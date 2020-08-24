#include "tiedostonlukujatalletus.hh"
#include "splitteri.cpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>


bool onkonumero(const string numero) {
    // funktio tutkii onko annettu stringi numero

    // erityistapaus että yritetään syöttää pelkkää ....... sarjaa
    if (numero.find_first_not_of(".") == string::npos) {
        return false;
    }
    else {
        return numero.find_first_not_of( "0123456789.") == string::npos;
    }



}


bool lisaa_tiedostosta(const string& tiedoston_nimi, map<string, map<string, vector<Tuote>>>& tietokanta ) {
    ifstream syotevirta(tiedoston_nimi);



    if ( not syotevirta ) {
        return false;
    }

    string rivi;
    while ( getline(syotevirta, rivi) ) {
        // Paloitellaan merkijono sanoiksi ennakkotahtävän Splitter-luokan avulla.
        Splitter paloittelija(rivi);

        paloittelija.paloittele(';');


        // Tehdään virhetarkastelu rivin oikeudelle
        if ( not (paloittelija.kenttien_lukumaara() == 4) or (rivi.find(" ") != string::npos) or (rivi.find(";;") != string::npos)
             or not ( onkonumero(paloittelija.hae_kentta(3)) or (paloittelija.hae_kentta(3) == "loppu")) ){

            return false;


        }




        // luodaan tavara
        if ( paloittelija.hae_kentta(3) == "loppu"){

            Tuote tavara = {paloittelija.hae_kentta(2), stod("-1")};


            // lähdetään rakentamaan tietorakennetta
            // lisätään kauppaketjua vastaava tyhjä mappipaikka kauppa-alueille
            tietokanta.insert( {paloittelija.hae_kentta(0), {} } );
            // lisätään kauppaketjulle kauppaalue ja sille tyhjä vectori pariksi
            tietokanta.at(paloittelija.hae_kentta(0)).insert( {paloittelija.hae_kentta(1), {} } );
            // lisätään tyhjään vectoriin tavara
            // HUOM! jos tavara on siellä jo ennestään, se korvataan!

            // etsitään vastaava tuote
            vector<Tuote>::size_type positio = 0;
            vector<Tuote>::iterator iter = tietokanta.at(paloittelija.hae_kentta(0)).at(paloittelija.hae_kentta(1)).begin() + positio;
            for (auto tuote : tietokanta.at(paloittelija.hae_kentta(0)).at(paloittelija.hae_kentta(1))) {
                positio++;
                if (tuote.tuotenimi == paloittelija.hae_kentta(2)) {
                    tietokanta.at(paloittelija.hae_kentta(0)).at(paloittelija.hae_kentta(1)).erase(iter); // poistetaan vanha vastaava tuote


                }
            }

            tietokanta.at(paloittelija.hae_kentta(0)).at(paloittelija.hae_kentta(1)).push_back(tavara);


        }
        else {

            Tuote tavara = {paloittelija.hae_kentta(2), stod(paloittelija.hae_kentta(3))};


            // lähdetään rakentamaan tietorakennetta insert-metodilla
            // jos tietorakenteen osa on jo olemassa, insert ei tee mitään
            // lisätään kauppaketjua vastaava tyhjä mappipaikka kauppa-alueille
            tietokanta.insert( {paloittelija.hae_kentta(0), {} } );
            // lisätään kauppaketjulle kauppaalue ja sille tyhjä vectori pariksi
            tietokanta.at(paloittelija.hae_kentta(0)).insert( {paloittelija.hae_kentta(1), {} } );
            // lisätään tyhjään vectoriin tavara
            // HUOM! jos tavara on siellä jo ennestään, se korvataan!

            // etsitään vastaava tuote
            vector<Tuote>::size_type positio = 0;
            vector<Tuote>::iterator iter = tietokanta.at(paloittelija.hae_kentta(0)).at(paloittelija.hae_kentta(1)).begin() + positio;
            for (auto tuote : tietokanta.at(paloittelija.hae_kentta(0)).at(paloittelija.hae_kentta(1))) {
                positio++;
                if (tuote.tuotenimi == paloittelija.hae_kentta(2)) {
                    tietokanta.at(paloittelija.hae_kentta(0)).at(paloittelija.hae_kentta(1)).erase(iter); // poistetaan vanha vastaava tuote


                }
            }

            tietokanta.at(paloittelija.hae_kentta(0)).at(paloittelija.hae_kentta(1)).push_back(tavara);


        }



    } // while loopin loppu, tiedosto saatiin luettua kokonaan



    syotevirta.close();

    return true;
}



