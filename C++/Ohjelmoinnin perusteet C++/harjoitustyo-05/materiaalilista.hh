#ifndef MATERIAALILISTA_HH
#define MATERIAALILISTA_HH

#include <memory>

using namespace std;

//------------------------------------------------------------------
//Tämän moduulin kehittäjänä on tyoskennellyt:
// Antti Ruhala
//------------------------------------------------------------------

// tämä on Ohjelmoinnin peruskurrsi K2017 linkitetyn listan toteutus kopioituna luentomonisteesta
// toteutusta on muutettu niin, että funktioiden nimiä on muutettu eroavaksi KSL_listan toteutuksesta
// materiaalilista on simppelimpi kahteen suuntaan linkitetty lista, ja toimii KSL_listan alkioihin liitettynä listana
// ikään kuin taulukon sarakkeihin liitettyinä riveinä. KSL_listan alkiot luovat sarakkeen alkiot, ja sarakkeen alkioon on aina liitetty yksi materiaalilista.

class materiaalilista { // Kahteen Suuntaan Linkitetty lista
    public:
        materiaalilista();
        int pituus_materiaalit() const;
        bool onko_arvo_listassa_materiaalit(string arvo) const;
        void tulosta_materiaalit() const;
        bool poista_arvo_materiaalit(string poistettava);
        bool lisaa_numerojarjestykseen_materiaalit(string lisattava);
        // Ei-purkajaa(!)
        void tyhjenna_lista();
        bool lisaa_alkio_materiaalit(string lisattava);
        bool onkorepunarvolistalla(materiaalilista &reppu);

    private:
        struct Listan_alkio {
            string data;
            shared_ptr<Listan_alkio> seuraavan_osoite;
            Listan_alkio* edellisen_osoite;


        };
        shared_ptr<Listan_alkio> ensimmaisen_osoite_;
        Listan_alkio* viimeisen_osoite_;
        int alkioiden_maara_;




};



#endif // MATERIAALILISTA_HH
