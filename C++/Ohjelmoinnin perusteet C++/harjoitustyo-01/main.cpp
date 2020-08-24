

// Taman tyon on tehnyt
// Antti Ruhala



#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;


// Taman ohjelma mallintaa simppelin pankkitilisysteemin toimintaa
// ohjelma ottaa kayttajalta syotteina kaskyja, ja toimii niiden perusteella
// kaskyt syotetaan syntaxilla "kasky tilinkaskynumero"
// ohjelma luo automaattisesti kolme tilia, tilikaskynumeroilla 1 2 ja 3
// tileille ominaiset arvot voidaan muuttaa myohemmin "aseta" kaskylla
// seuraavat kaskyt ovat sallittuja:
// tulosta 1
// aseta 1
// pano 1
// otto 1
// tilisiirto 1 2  // tilisiirto tililta 1 tilille 2
// lopeta


class Pankkitili {
public:
    // Rakentaja
    Pankkitili(string tilinumero = "FIplaceholder", double saldo = 0, string asiakasnumero = "ANplaceholder");
    void tulosta() const ;
    void aseta(string tilinumero, double saldo, string asiakasnumero);
    bool pano(double lisays);
    bool otto(double otettava);
    bool tilisiirto(double siirtosumma, Pankkitili& kohde);

private:
    string tilinumero_;
    double saldo_;
    string asiakasnumero_;

};

Pankkitili::Pankkitili(string tilinumero, double saldo, string asiakasnumero) :
    tilinumero_(tilinumero), saldo_(saldo), asiakasnumero_(asiakasnumero) {
    //tama on rakentajametodi

}



void Pankkitili::tulosta() const {
    //Tama metodi tulostaa olion arvot naytolle

    cout << "Tilinumero: " << tilinumero_ << endl;
    cout << "Saldo: " << fixed << setprecision(2) << saldo_ << endl;
    cout << "Asiakasnumero: " << asiakasnumero_ << endl;

}

void Pankkitili::aseta(string tilinumero, double saldo, string asiakasnumero) {
    tilinumero_ = tilinumero;
    saldo_ = saldo;
    asiakasnumero_ = asiakasnumero;
}


// tama metodi kuvastaa tilille rahan lisaamista, joten ihan periaatteen vuoksi kielletaan negatiivisen rahan lisaaminen, tai erilaisten merkkien
bool Pankkitili::pano(double lisays) {
    if (lisays >= 0) {
        saldo_ = saldo_ + lisays;
        return true;
    }
    else {
        return false;
    }
}

// tama metodi kuvastaa tilista rahan poistamista
bool Pankkitili::otto(double otettava) {
    if ((otettava >= 0) && (saldo_ - otettava >= 0)) {
        saldo_ = saldo_ - otettava;
        return true;
    }

    else {
        return false;
    }
}

bool Pankkitili::tilisiirto(double siirtosumma, Pankkitili& kohde) {
    //tehdaan tarkastelu, onko siirrettavaa summaa olemassa
    if (saldo_ >= siirtosumma) {
        otto(siirtosumma);
        kohde.pano(siirtosumma);
        return true;
    }
    else {
        return false;
    }
}
// aseta funktion syotteen lukufunktiot 1-3, ottavat syotteen ja palauttavat sen
string asetatiedot1() {
    string tilinumero;

    cout << "Syota tilinumero: ";
    cin >> tilinumero;
    cin.clear();
    cin.ignore(256, '\n');

    return tilinumero;
}

double asetatiedot2() {
    double saldo;

    cout << "Syota saldo: ";
    cin >> saldo;
    cin.clear();
    cin.ignore(256, '\n');

    //Jos syotetaan saldoksi kirjaimia, saadaan nopeasti negatiivinen saldo aikaiseksi
    if (saldo < 0) {
        saldo = 0;
    }

    return saldo;

}

string asetatiedot3() {
    string asiakasnumero;

    cout << "Syota asiakasnumero: ";
    cin >> asiakasnumero;
    cin.clear();
    cin.ignore(256, '\n');

    return asiakasnumero;

}


// Tama funktio toimii yleisena rahasyotteen lukijana
double rahasyote() {
    double rahat;
    cout << "Syota rahamaara: ";
    cin >> rahat;
    cin.clear();
    cin.ignore(256, '\n');

    return rahat;
}

// Tama funktio toimii tilisiirron tulostajana ja lukijana, koska siina on hieman eroavan tulostus
double tilisiirtosyote() {
    double rahat;
    cout << "Syota siirtomaara: ";
    cin >> rahat;
    cin.clear();
    cin.ignore(256, '\n');

    return rahat;
}



int main()
{
    //luodaan kolme pankkitilia joita ohjelma voi kayttaa myohemmin
    Pankkitili eka("FI1234567891123456",0,"123456");
    Pankkitili toka("DE1234324231421344",0,"654321");
    Pankkitili kolmas("SE321321321323213",0,"987654");
    string splitattava = "";
    string operandi1;
    string operandi2;


    // luodaan looppi, jossa ohjelma pyorii, kunnes kayttaja syottaa "lopeta"
    // jolloin vedetaan breakit ja ohjelma sammuu
    while (true) {


        cout << "pankkitilitesti> ";
        getline(cin, splitattava);



        // kaytetaan netista loydettya split toiminnon vastinetta, joka luo annetusta stringistä listan,
        // joka on splitattu määritellyn merkin split_char kohdalta, nyt välilyönnistä
        // kaytetaan tata halkaisemaan syote kaskyksi, seka operandeiksi

        //
        // inputs
        std::string str(splitattava);
        char split_char = ' ';

        // work
        std::istringstream split(str);
        std::vector<std::string> tokens;
        for (std::string each; std::getline(split, each, split_char); tokens.push_back(each));
        // now use `tokens`
        //




        // ohjelma tekee toiminnon kaskysanan mukaisesti operandeihin


        // tulostus kasky
        // osaamisen puutteen takia ei saada aikaiseksi tokens.at(1).tulosta(); tyylistä ratkaisua vaan iso liuta if lauseita
        if (tokens.at(0) == "tulosta") {
            if (tokens.size() != 2){
                cout << "Virhe: operandi puuttuu tai on virheellinen" << endl;
            }
            else if (tokens.at(1) == "1") {
                eka.tulosta();
            }
            else if (tokens.at(1) == "2") {
                toka.tulosta();
            }
            else if (tokens.at(1) == "3") {
                kolmas.tulosta();
            }

            else {
                cout << "Virhe: operandi puuttuu tai on virheellinen" << endl;
            }


        }

        // asetus kasky
        // tama metodi asettaa tilille uudet tiedot
        else if ((tokens.at(0) == "aseta")) {

            if (tokens.size() != 2){
                cout << "Virhe: operandi puuttuu tai on virheellinen" << endl;
            }

            // vielä tuntemattomasta syystä, jos funktiot laitetaan suoraan .aseta metodin parametreiksi
            // ne kaydaan lapi oikealta vasemmalle
            else if ((tokens.at(1) == "1") || (tokens.at(1) == "2") || (tokens.at(1) == "3")) {


                string aseta1 = asetatiedot1();
                double aseta2 = asetatiedot2();
                string aseta3 = asetatiedot3();



            if (tokens.at(1) == "1") {
                eka.aseta(aseta1,aseta2,aseta3);
                cout << "Tilin 1 tiedot asetettu." << endl;
            }
            else if (tokens.at(1) == "2") {
                toka.aseta(aseta1,aseta2,aseta3);
                cout << "Tilin 2 tiedot asetettu." << endl;
            }
            else if (tokens.at(1) == "3") {
                kolmas.aseta(aseta1,aseta2,aseta3);
                cout << "Tilin 3 tiedot asetettu." << endl;
            }

            }
            else {
                cout << "Virhe: Operandi on virheellinen." << endl;
            }

        }

        // pano kasky
        // tama metodi laittaa tilille lisaa rahaa
        else if (tokens.at(0) == "pano") {

            if (tokens.size() != 2){
                cout << "Virhe: operandi puuttuu tai on virheellinen" << endl;
            }

            else if (tokens.at(1) == "1") {
                if (eka.pano(rahasyote())) {
                    cout << "Pano suoritettu tilille 1." << endl;
                }
                else {
                    cout << "Virhe: Tilillepano epaonnistui" << endl;
                }
            }
            else if (tokens.at(1) == "2") {
                if (toka.pano(rahasyote())) {
                    cout << "Pano suoritettu tilille 2." << endl;
                }
                else {
                    cout << "Virhe: Tilillepano epaonnistui" << endl;
                }

            }
            else if (tokens.at(1) == "3") {
                if (kolmas.pano(rahasyote())) {
                    cout << "Pano suoritettu tilille 3." << endl;
                }
                else {
                    cout << "Virhe: Tilillepano epaonnistui" << endl;
                }

            }
            else {
                cout << "Virhe: operandi puuttuu tai on virheellinen" << endl;
            }


        }

        // otto kasky
        // tama metodi ottaa tililta rahaa kunnes tili on tyhja, jonka jalkeen tulee vain erroria
        else if (tokens.at(0) == "otto") {
            if (tokens.size() != 2){
                cout << "Virhe: operandi puuttuu tai on virheellinen" << endl;
            }

            else if (tokens.at(1) == "1") {
                if (eka.otto(rahasyote())) {
                    cout << "Otto suoritettu tililta 1." << endl;
                }
                else {
                    cout << "Virhe: Tililtaotto epaonnistui" << endl;
                }

            }
            else if (tokens.at(1) == "2") {
                if (toka.otto(rahasyote())) {
                    cout << "Otto suoritettu tililta 2." << endl;
                }
                else {
                    cout << "Virhe: Tililtaotto epaonnistui" << endl;
                }
            }
            else if (tokens.at(1) == "3") {
                if (kolmas.otto(rahasyote())) {
                    cout << "Otto suoritettu tililta 3." << endl;
                }

                else {
                    cout << "Virhe: Tililtaotto epaonnistui" << endl;
                }

            }
            else {
                cout << "Virhe: operandi puuttuu tai on virheellinen" << endl;
            }



        }

        // tilisiirto kasky
        else if (tokens.at(0) == "tilisiirto") {

            if (tokens.size() != 3){
                cout << "Virhe: operandit puuttuvat tai on virheellisia" << endl;
            }

            else if (tokens.at(1) == "1") {
                if (tokens.at(2) == "1") {
                    cout << "Virhe: Oman tilin sisainen tilisiirto ei ole sallittu" << endl;
                }
                else if (tokens.at(2) == "2") {
                    eka.tilisiirto(tilisiirtosyote(), toka);
                }
                else if (tokens.at(2) == "3") {
                    eka.tilisiirto(tilisiirtosyote(), kolmas);
                }
                else {
                    cout << "Virhe: tilisiirto epaonnistui" << endl;
                }
            }
            else if (tokens.at(1) == "2") {
                if (tokens.at(2) == "1") {
                    toka.tilisiirto(tilisiirtosyote(), eka);
                }
                else if (tokens.at(2) == "2") {
                    cout << "Virhe: Oman tilin sisainen tilisiirto ei ole sallittu" << endl;
                }
                else if (tokens.at(2) == "3") {
                    toka.tilisiirto(tilisiirtosyote(), kolmas);
                }
                else {
                    cout << "Virhe: tilisiirto epaonnistui" << endl;
                }
            }
            else if (tokens.at(1) == "3") {
                if (tokens.at(2) == "1") {
                    kolmas.tilisiirto(tilisiirtosyote(), eka);
                }
                else if (tokens.at(2) == "2") {
                    kolmas.tilisiirto(tilisiirtosyote(), toka);
                }
                else if (tokens.at(2) == "3") {
                    cout << "Virhe: Oman tilin sisainen tilisiirto ei ole sallittu" << endl;
                }
                else {
                    cout << "Virhe: tilisiirto epaonnistui" << endl;
                }
            }
            else {
                cout << "Virhe: operandi puuttuu tai on virheellinen" << endl;
            }


        }


        //loppu

        else if (tokens.at(0) == "loppu") {
            break;
        }

        else {
            cout << "Virhe: virheellinen kasky." << endl;
        }
    }

    return 0;
}



