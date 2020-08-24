#ifndef KSL_LISTA_HH
#define KSL_LISTA_HH
#include <memory>
#include "materiaalilista.hh"

using namespace std;
//------------------------------------------------------------------
//Tämän moduulin kehittäjänä on tyoskennellyt:
// Antti Ruhala
//------------------------------------------------------------------

// tämä on Ohjelmoinnin peruskurrsi K2017 linkitetyn listan toteutus kopioituna luentomonisteesta
// toteutusta on muutettu niin, että listan alkion datana on string tyyppinen muuttuja
// structiin on lisätty materiaalilista, tästä lisää alempana.
// joitain funktioita on lisätty

class KSL_lista { // Kahteen Suuntaan Linkitetty lista
    public:
        KSL_lista();
        int pituus() const;
        bool onko_arvo_listassa(string arvo) const;
        bool poista_arvo(string poistettava);
        bool lisaa_numerojarjestykseen(string lisattava);
        // Ei-purkajaa(!)
        bool lisaa_materiaali(string lisattava_materiaali, string tavara);
        bool materiaalitarkastelu(string tavara);
        bool materiaalitarkastelurepulle(materiaalilista &reppu, string tavara);
        void materiaalitulostus(string tavara);
    private:
        struct Listan_alkio {
            string data;
            shared_ptr<Listan_alkio> seuraavan_osoite;
            Listan_alkio* edellisen_osoite;

            // materiaalilista on simppelimpi kahteen suuntaan linkitetty lista, ja toimii KSL_listan alkioihin liitettynä listana
            // ikään kuin taulukon sarakkeihin liitettyinä riveinä. KSL_listan alkiot luovat sarakkeen alkiot, ja sarakkeen alkioon on aina liitetty yksi materiaalilista.
            // materiaalilistan funktiot on toteutettu erillisellä lähdetiedostolla, vaikka ovat identtisiä KSL_listan funktioille
            // oma taitavuus ei kuitenkaan riittänyt luomaan class-oliota, jonka structin jäsenenä olisi saman classin olio, tämä olisi ainakin  minun mielessäni
            // luonut loppumattoman paradoksin. Ongelmalta vältyttiin luomalla erillinen olio, joka voidaan luoda ilman, että se loisi saman olion uudestaan jne.
            materiaalilista materiaalit;


        };
        shared_ptr<Listan_alkio> ensimmaisen_osoite_;
        Listan_alkio* viimeisen_osoite_;
        int alkioiden_maara_;




};

#endif // KSL_LISTA_HH
