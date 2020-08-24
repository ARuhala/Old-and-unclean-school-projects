#include "materiaalilista.hh"

#include "ksl_lista.hh"
#include <iostream>
#include <memory>

using namespace std;

//------------------------------------------------------------------
//Tämän moduulin kehittäjänä on tyoskennellyt:
// Antti Ruhala
//------------------------------------------------------------------

// tässä lähdetiedostossa on esitetty ksl_listan erityisversion, materiaalilistan funktiot toteutuksineen

materiaalilista::materiaalilista():
    ensimmaisen_osoite_(nullptr),
    viimeisen_osoite_(nullptr),
    alkioiden_maara_(0){
}

int materiaalilista::pituus_materiaalit() const {
    return alkioiden_maara_;
}

bool materiaalilista::onko_arvo_listassa_materiaalit(string arvo) const {
    shared_ptr<Listan_alkio>
            tutkittavan_osoite = ensimmaisen_osoite_;
    while ( tutkittavan_osoite != nullptr ) {
        if ( tutkittavan_osoite->data == arvo ) {
            return true;
        }

        tutkittavan_osoite = tutkittavan_osoite->seuraavan_osoite;
    }
    return false;
}


void materiaalilista::tulosta_materiaalit() const {
    shared_ptr<Listan_alkio> tulostettavan_osoite = ensimmaisen_osoite_;
    while ( tulostettavan_osoite != nullptr ) {
        cout << tulostettavan_osoite->data << endl;
        tulostettavan_osoite = tulostettavan_osoite->seuraavan_osoite;
    }

}



bool materiaalilista::poista_arvo_materiaalit(string poistettava) {
    if ( pituus_materiaalit() == 0 ) {
        return false;
    }
    shared_ptr<Listan_alkio> poistettavan_osoite = ensimmaisen_osoite_;
    while ( true ) {
        if ( poistettavan_osoite->data == poistettava ) {
            break; // Poistettava arvo löytyi.
        } else if ( poistettavan_osoite->data
                    > poistettava ) {
            return false; // Arvo ei voi olla loppulistassa.
        } else if ( poistettavan_osoite->seuraavan_osoite == nullptr ) {
            return false; // Viimeinen alkio on käsitelty.
        } else {
            poistettavan_osoite = poistettavan_osoite->seuraavan_osoite;
        }
    }

    // Tässä kohdassa tiedetään, että poistettava arvo löytyi
    // listasta ja poistettavan_osoite osoittaa siihen.


    // Poistettava alkio on listan ainoa alkio.
    if ( ensimmaisen_osoite_.get() == viimeisen_osoite_ ) {
        ensimmaisen_osoite_ = nullptr;
        viimeisen_osoite_ = nullptr;
        // Poistettava alkio on listan ensimmäinen alkio.
    } else if ( poistettavan_osoite == ensimmaisen_osoite_ ) {
        ensimmaisen_osoite_ = ensimmaisen_osoite_->seuraavan_osoite;
        ensimmaisen_osoite_->edellisen_osoite = nullptr;
        // Poistettava alkio on listan viimeinen alkio.
    } else if ( poistettavan_osoite.get() == viimeisen_osoite_ ) {
        viimeisen_osoite_ = viimeisen_osoite_->edellisen_osoite;
        viimeisen_osoite_->seuraavan_osoite = nullptr;
        // Poistettava alkio on listan keskellä.
    } else {
        poistettavan_osoite->edellisen_osoite->seuraavan_osoite = poistettavan_osoite->seuraavan_osoite;
        poistettavan_osoite->seuraavan_osoite->edellisen_osoite = poistettavan_osoite->edellisen_osoite;
    }
    --alkioiden_maara_;
    return true;
}






bool materiaalilista::lisaa_numerojarjestykseen_materiaalit(string lisattava) {
    // tämä funktio lisää alkion aakkosjärjestykseen muihin alkioihin nähden
    shared_ptr<Listan_alkio> uuden_osoite(new Listan_alkio);
    uuden_osoite->data = lisattava;
    // Lisäys tyhjään listaan.
    if ( pituus_materiaalit() == 0 ) {
        uuden_osoite->seuraavan_osoite = nullptr;
        uuden_osoite->edellisen_osoite = nullptr;
        ensimmaisen_osoite_ = uuden_osoite;
        viimeisen_osoite_ = uuden_osoite.get();
        // Lisäys lista alkuun.
    } else if ( lisattava < ensimmaisen_osoite_->data ) {
        uuden_osoite->seuraavan_osoite = ensimmaisen_osoite_;
        uuden_osoite->edellisen_osoite = nullptr;
        ensimmaisen_osoite_->edellisen_osoite
                = uuden_osoite.get();
        ensimmaisen_osoite_ = uuden_osoite;
        // Lisäys listan loppuun.
    } else if ( lisattava > viimeisen_osoite_->data ) {
        uuden_osoite->seuraavan_osoite = nullptr;
        uuden_osoite->edellisen_osoite = viimeisen_osoite_;
        viimeisen_osoite_->seuraavan_osoite = uuden_osoite;
        viimeisen_osoite_ = uuden_osoite.get();


        // Lisäys listan keskelle.
    } else {
        shared_ptr<Listan_alkio>
                tutkittavan_osoite = ensimmaisen_osoite_;
        // Etsitään listasta ensimmäinen alkio, jonka sisältämä
        // arvo on suurempi tai yhtäsuuri kuin lisättävä arvo.
        while ( tutkittavan_osoite->data < lisattava ) {
            tutkittavan_osoite = tutkittavan_osoite->seuraavan_osoite;
        }
        // Arvo ei voi saa olla listassa useammin kuin kerran.
        if ( tutkittavan_osoite->data == lisattava ) {
            return false;
        }
        // Nyt tutkittavan_osoite osoittaa ensimmäiseen
        // alkioon listan sisällä, jonka arvo on suurempi
        // kuin lisättävä arvo: uusi alkio lisätään sen eteen.
        uuden_osoite->seuraavan_osoite = tutkittavan_osoite;
        uuden_osoite->edellisen_osoite = tutkittavan_osoite->edellisen_osoite;
        uuden_osoite->edellisen_osoite->seuraavan_osoite = uuden_osoite;
        uuden_osoite->seuraavan_osoite->edellisen_osoite = uuden_osoite.get();
    }
    ++alkioiden_maara_;
    return true;
}

// tämän viivan alapuolelle on toteutettu luentomonisteesta poikkeavat funktiot
// joitain harvoja valmiita funktioita on muutettu yhteensopiviksi string tyypin kanssa (oli int alunperin)
// --------------------------------------------------------------------------------------------------------------------------


void materiaalilista::tyhjenna_lista() {
    // tämä funktio tyhjentää koko materiaalilistan (yhden tavaran materiaalit, tai repun)
    while (alkioiden_maara_ != 0){
        poista_arvo_materiaalit(ensimmaisen_osoite_->data);
    }

}

bool materiaalilista::lisaa_alkio_materiaalit(string lisattava)
{
    // tämä funktio on simppelimpi versio alkion lisäämisestä, ja lisää alkion aina listan loppuun.
    shared_ptr<Listan_alkio> uuden_osoite(new Listan_alkio);
    uuden_osoite->data = lisattava;
    // Lisäys tyhjään listaan.
    if ( pituus_materiaalit() == 0 ) {
        uuden_osoite->seuraavan_osoite = nullptr;
        uuden_osoite->edellisen_osoite = nullptr;
        ensimmaisen_osoite_ = uuden_osoite;
        viimeisen_osoite_ = uuden_osoite.get();

        // Lisäys listan loppuun.
    } else {
        uuden_osoite->seuraavan_osoite = nullptr;
        uuden_osoite->edellisen_osoite = viimeisen_osoite_;
        viimeisen_osoite_->seuraavan_osoite = uuden_osoite;
        viimeisen_osoite_ = uuden_osoite.get();

    }
    ++alkioiden_maara_;
    return true;
}

 bool materiaalilista::onkorepunarvolistalla(materiaalilista &reppu)
 {
     // tämä on KSL_lista funktion apufunktio
     // funktio tutkii, löytyykö repun ja materiaalilistalta eroavaisuuksia niin päin
     // että materiaalilistalla on alkio jota ei löydy repusta ja palauttaa true/false

     shared_ptr<Listan_alkio> listanmateriaalinosoite = ensimmaisen_osoite_;
         while(true) {
             
             if (reppu.onko_arvo_listassa_materiaalit(listanmateriaalinosoite->data )) {
                 
                 // materiaalilistan jäsen vastaa repussa olevaa jäsentä
                 // voidaan tarkastella listan seuraavaa jäsentä

                 listanmateriaalinosoite = listanmateriaalinosoite->seuraavan_osoite;
                 if (listanmateriaalinosoite == nullptr) {
                     // päästiin koko materiaalilista läpi
                     return true;
                 }
                 continue;
             }

             else {

                 // tämä else-haara tarkoittaa, että repusta ei löytynyt arvoa, joka olisi vastannut listanmateriaalinosoitteen dataa
                 // eli siis repussa ei ollut jotain tarvittavaa materiaalia
                 return false;

             }
         }

return false;

 }





