#include "ksl_lista.hh"
#include <iostream>
#include <memory>

using namespace std;
//------------------------------------------------------------------
//Tämän moduulin kehittäjänä on tyoskennellyt:
// Antti Ruhala
//------------------------------------------------------------------

// tässä lähdetiedostossa on esitetty ksl_listan funktiot toteutuksineen

KSL_lista::KSL_lista():
    ensimmaisen_osoite_(nullptr),
    viimeisen_osoite_(nullptr),
    alkioiden_maara_(0){
}
int KSL_lista::pituus() const {
    return alkioiden_maara_;
}

bool KSL_lista::onko_arvo_listassa(string arvo) const {
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





bool KSL_lista::poista_arvo(string poistettava) {
    // tällähetkellä käyttämätön alkion poistofunktio
    // tulevaisuuden kehityksen kannalta kuitenkin lähes välttämätön
    if ( pituus() == 0 ) {
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




bool KSL_lista::lisaa_numerojarjestykseen(string lisattava) {
    shared_ptr<Listan_alkio> uuden_osoite(new Listan_alkio);
    uuden_osoite->data = lisattava;
    // Lisäys tyhjään listaan.
    if ( pituus() == 0 ) {
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

bool KSL_lista::lisaa_materiaali(string lisattava_materiaali, string tavara) {
    // tämä funktio lisää tietorakennealkion (tavara) materiaalilistaan alkion.
    shared_ptr<Listan_alkio> lisattavan_osoite = ensimmaisen_osoite_;




    while ( true ) {


    if ( lisattavan_osoite->data == tavara ) {
        // tarkistetaan, ettei lisättävä tavara ole jo listalla
        if (lisattavan_osoite->materiaalit.onko_arvo_listassa_materiaalit(lisattava_materiaali) ) {
        return false;

        }

        lisattavan_osoite->materiaalit.lisaa_numerojarjestykseen_materiaalit(lisattava_materiaali);

        break;

    }
    else {
        // ei ollut ensimmäinen tavaran materiaali, siirrytään eteenpäin listalla
        lisattavan_osoite = lisattavan_osoite->seuraavan_osoite;

        if (lisattavan_osoite == nullptr) {
            // kyseistä tavaraa ei löytynyt reseptilistalta
            // tänne ei pitäisi koskaan tarvita tulla

            break;
        }
    }



    }

    // kaikki meni ainakin niin, ettei ole syytä lopettaa ohjelman toimintaa.
    return true;


}

bool KSL_lista::materiaalitarkastelu(string tavara)
{
    // tämä funktio tarkastelee annetun tavaran ja KSL_tietorakenteen vastaavuuksia
    // (löytyykö tavara jostainpäin tietorakennetta)
   // käydään läpi koko tietorakenne ja tarkastetaan, löytyykö edes yksi vastaavuus
    shared_ptr<Listan_alkio> tarkasteltavanosoite = ensimmaisen_osoite_;

    if (pituus() == 0) {
        return false;
    }
    // katsotaan läpi rakennettavat kohteet
    else if (onko_arvo_listassa(tavara)) {
        return true;
    }
    while (true) {
        // katsotaan läpi rakennettavien kohteiden sisältämät materiaalilistat
        if (tarkasteltavanosoite->materiaalit.onko_arvo_listassa_materiaalit(tavara)) {

            return true;
        }
        else {
            tarkasteltavanosoite = tarkasteltavanosoite->seuraavan_osoite;
            if (tarkasteltavanosoite == nullptr) {
                return false;
            }
        }
    }


    return false;
}

bool KSL_lista::materiaalitarkastelurepulle(materiaalilista &reppu, string tavara)
{
    // tämä funktio toteuttaa materiaalitarkastelun repulle, eli tarkastaa löytyykö tietyn tavaran
    // kaikki materiaalit repusta ja palauttaa true/false
    // jos tavara itsessään on repussa, tämä todetaan "onnistumiseksi"
    if (reppu.onko_arvo_listassa_materiaalit(tavara)) {
        return true;
    }
    // käydään yksitellen läpi jokainen tavaraan liittyvä materiaali, ja katsotaan, löytyykö kyseisen materiaali repusta
    shared_ptr<Listan_alkio> tarkasteltavan_osoite = ensimmaisen_osoite_;



    while (true) {
            if ( tarkasteltavan_osoite->data == tavara ) {
                // löydettiin oikea tavaraan liittyvä materiaalilista
                // osoitteesta tarkasteltava_osoite
                // siirrytään vertailemaan listojen sisältöä


            // alla oleva funktio käy while loopilla läpi koko materiaali listan ja palauttaa true/false
           return tarkasteltavan_osoite->materiaalit.onkorepunarvolistalla(reppu);



            }


            else {
                tarkasteltavan_osoite = tarkasteltavan_osoite->seuraavan_osoite;

                if (tarkasteltavan_osoite == nullptr) {
            // tarkasteltava, etsittävä tavara ei edes ollut reseptilistalla
                    return false;
                }
            }

    }
}

void KSL_lista::materiaalitulostus(string tavara)
{
    // tämä funktio tulostaa materiaaliluettelon tietylle tavaralle
    // materiaalit on talletettu etukäteen aakkosjärjestyksessä, joten riittä vain tulostaa
    // ne alusta lähtien




        // etsitään kysytty esine tietorakenteesta
        shared_ptr<Listan_alkio> tarkasteltavan_osoite = ensimmaisen_osoite_;

        while (true) {
                if ( tarkasteltavan_osoite->data == tavara ) {
                    // löydettiin oikea tavaraan liittyvä materiaalilista
                    // osoitteesta tarkasteltava_osoite
                    tarkasteltavan_osoite->materiaalit.tulosta_materiaalit();
                    break;

                }

                else {
                    tarkasteltavan_osoite = tarkasteltavan_osoite->seuraavan_osoite;

                    if (tarkasteltavan_osoite == nullptr) {

                        break;

    }
    }
        }



}


