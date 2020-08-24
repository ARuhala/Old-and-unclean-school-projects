#ifndef TIEDOSTONLUKUJATALLETUS_HH
#define TIEDOSTONLUKUJATALLETUS_HH
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct Tuote {
    string tuotenimi;
    double hinta;
};

bool onkonumero (const string numero);
bool lisaa_tiedostosta(const string& tiedoston_nimi, map<string, map<string, vector<Tuote>>>& tietokanta);




#endif // TIEDOSTONLUKUJATALLETUS_HH
