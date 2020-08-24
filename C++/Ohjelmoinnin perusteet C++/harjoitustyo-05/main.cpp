#include <iostream>
#include <regex>
#include <fstream>
#include "tiedostonluku.hh"
#include "ksl_lista.hh"


using namespace std;

//------------------------------------------------------------------
//Tämän moduulin kehittäjänä on tyoskennellyt:
// Antti Ruhala
//------------------------------------------------------------------

// tämä ohjelma hahmoittelee usein peleissä löydettävää askartelumekaniikkaa, jossa repusta löytyvillä esineillä
// voidaan luoda erilaisia tavaroita riippuen saatavilla olevista materiaaleista sekä tavaroihin tarvittavista
// tarvikkeista.

// ohjelma alkaa kysymällä syötetiedoston nimen
// ja siirtyy sen jälkeen teksisyötteiseen käyttöliittymään
// käyttöliittymässä käyttäjä voi syöttää seuraavia käskyjä
//
// reppu materiaali1 materiaali2
// tulostareppu
// askarteltavissa esine_tai_materiaali
// materiaalit esine_tai_materiaali
//
// reppu - käsky tyhjentää repun ja luo uuden repun listatuista tapahtumista
// loput käskyt tulostavat tietoa käskystä pääteltävästä aiheesta

// ohjelma on toteutettu niin, ettei valmiita tiedonkäsittelyyn tarkoitettuja STL:moduuleita käytetä, vaan kaikkea käsitellään
// itse toteutetuilla dynaamisilla tietorakenteilla, pääasiassa listoilla.



int main()
{

    // syotetiedoston nimen kysyminen sekä tiedon tallettaminen <map> tyyliseen dynaamiseen tietorakenteeseen
    // jotta tietorakennetta voidaan käyttää myöhemminkin, tietorakenne luodaan ensin, ja annetaan "muokattavaksi" tiedostonlukufunktiolle
    KSL_lista reseptilista;
if ( not tiedostonluku(reseptilista) ) {

    return 1;
}

    // tiedosto on onnistuneesti luettu ja tietorakenne täytetty
    // voidaan siirtyä käyttöliittymään


    string syoterivi;
    // otetaan vastaan käyttäjän syöterivi ja pilkotaan se reguralexpressioneiden avulla
    regex REPPU_REGEX("[[:space:]]*"
                      "reppu"
                      "[[:space:]]*"
                      "(?:([[:alpha:]_]+)[[:space:]]*)*");
    regex REPPUSANA_REGEX("[[:alpha:]_]+");
    regex PELKKAREPPU_REGEX("[[:space:]]*"
                            "reppu"
                            "[[:space:]]*");

    regex TULOSTAREPPU_REGEX("[[:space:]]*"
                             "tulostareppu"
                             "[[:space:]]*");

    regex ASKARRELTAVISSA_REGEX("[[:space:]]*"
                                "askarreltavissa"
                                "[[:space:]]*"
                                "([[:alpha:]_]+)"
                                "[[:space:]]*");

    regex MATERIAALIT_REGEX("[[:space:]]*"
                            "materiaalit"
                            "[[:space:]]*"
                            "([[:alpha:]_]+)"
                            "[[:space:]]*");

    regex LOPPU_REGEX("[[:space:]]*"
                      "loppu"
                      "[[:space:]]*");

    smatch tulos;


    // luodaan käyttäjän reppu
    materiaalilista repputietorakenne;

    // -------------------------------------------
    // KÄYTTÖLIITTYMÄN TOTEUTUS
    // -------------------------------------------


    while ( cout << "testikayttoliittyma> ", getline(cin, syoterivi) ) {

        if ( regex_match(syoterivi, tulos, REPPU_REGEX) ) {

            // tällä käskyllä;
            // tyhjennetään valmiiksi ollut reppu
            // laitetaan käyttäjän syöttämät tavarat reppuun siinä järjestyksessä kuin ne syötetään

            // jos käyttäjä syöttää pelkän sanan "reppu", tyhjennetään reppu ja tehdään erityinen tuloste
            if ( regex_match(syoterivi, tulos, PELKKAREPPU_REGEX) ) {
                repputietorakenne.tyhjenna_lista();
                cout << "Reppu tyhjennetty." << endl;

            }

            else {
            // tyhjennetään valmiiksi ollut reppu, ellei se ole jo tyhjä
            if (repputietorakenne.pituus_materiaalit() != 0) {
                repputietorakenne.tyhjenna_lista();

            }



            // paloitellaan kaikki REPPUSANA_REGEX vastaavat sanat riviltä
            sregex_iterator iter(syoterivi.begin(), syoterivi.end(), REPPUSANA_REGEX);
            sregex_iterator end;

            // REPPUSANA_REGEX hyväksyisi myös sanan reppu, joten skipataan ensimmäinen kierros (näin materiaali nimeltä reppu
            // pääsee silti läpi, jos sellainen tulee myöhemmin vastaan)
            ++iter;

            while ( iter != end ) {

                // reppuun on sallittua laittaa vain asioita, jotka ovat alkuperäisellä reseptilistalla
                if (not reseptilista.materiaalitarkastelu(iter->str())) {
                    cout << "Virhe: yksi tai useampi materiaali ei korreloi tekstitiedoston kanssa." << endl;
                    repputietorakenne.tyhjenna_lista();
                    break;

                }
                else if ( repputietorakenne.onko_arvo_listassa_materiaalit(iter->str())) {
                    cout << "Virhe: Materiaali ei saa olla repussa useaan kertaan." << endl;
                    repputietorakenne.tyhjenna_lista();
                    break;
                }
                else {
                    repputietorakenne.lisaa_alkio_materiaalit(iter->str());

                }
                ++iter;
            }
            if (iter == end) {
               cout << "Repun sisalto asetettu." << endl;
            }



        }
           continue;
        }



        else if ( regex_match(syoterivi, TULOSTAREPPU_REGEX) ) {
            // tällä komennolla tulostetaan repun sisältä samassa järjestyksessä, kuin ne talletettiin
            repputietorakenne.tulosta_materiaalit();

            continue;

        }
        else if ( regex_match(syoterivi, tulos, ASKARRELTAVISSA_REGEX) ) {
            // tämä komento tutkii, löytyykö tutkittavan tavaran kaikki suorat reseptimateriaalit repusta

            // tutkittavan "sanan" on esiinnyttävä alkuperäisessä tekstitiedostossa
            // katsotaan yksi kerrallaan, löytyykö aina tietty tarvittava materiaali repusta
            // katsotaan, löytyykö tavara itsessään repusta, joka myös lasketaan "Onnistumiseksi"

            // tutkitaan löytyykö sana tekstitiedostosta
            if (not reseptilista.materiaalitarkastelu(tulos.str(1))) {
                cout << "Virhe: Askarteltava esine ei korreloi tekstitiedoston kanssa." << endl;
               continue;
            }


            // katsotaan yksi kerrallaan, löytyykö aina tietty tarvittava materiaali repusta
            if (reseptilista.materiaalitarkastelurepulle(repputietorakenne, tulos.str(1))) {
                cout << "On askarreltavissa." << endl;
            }

            else {
                cout << "Ei ole askarreltavissa." << endl;
            }



            continue;

        }
        else if ( regex_match(syoterivi, tulos, MATERIAALIT_REGEX) ) {
            // materiaalit on talletettu etukäteen aakkosjärjestyksessä, joten riittä vain tulostaa
            // ne alusta lähtien

            // tutkitaan löytyykö sana tekstitiedostosta
            if (not reseptilista.materiaalitarkastelu(tulos.str(1))) {
                cout << "Virhe: esine ei korreloi tekstitiedoston kanssa." << endl;
               continue;
            }

            else {

                    reseptilista.materiaalitulostus(tulos.str(1));

                }
            continue;

        }
        else if ( regex_match(syoterivi, LOPPU_REGEX) ) {

            break;

        }
        else {
            cout << "Virhe: virheellinen komento." << endl;
            continue;

        }

    }



    return 0;
}
