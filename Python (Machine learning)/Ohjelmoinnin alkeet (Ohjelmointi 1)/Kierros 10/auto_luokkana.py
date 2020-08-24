# TIE-02100 Johdatus ohjelmointiin
# Tehtävä auto_luokkana, ohjelmakoodipohja

from math import sqrt

VALIKKOTEKSTI = "1) Tankkaa 2) Aja 3) Lopeta \n-> "


# Luokka Auto: Kuvaa kaksiulotteisessa koordinaatistossa liikkuvaa autoa.
# ============
# Luokka siis määrittelee, millainen auto on: mitä tietoja se sisältää ja
# mitä toimenpiteitä se voi suorittaa. 
class Auto:
    
    # Metodi: rakentaja, alustaa olion alkutilaan (tankki tyhjä ja sijainti
    # origossa)
    # Parametri tankin_koko: auton tankin koko
    # Parametri kulutus_satasella: auton kulutus sadan kilometrin matkalla
    #
    # (Pythonissa rakentajan nimi on aina __init__. Rakenta on metodi, jota 
    # kutsutaan, kun luokasta halutaan luoda uusi olio, ks. rivi 41. Rakentaja
    # alustaa uuden olion sisältämät kentät (tässä muuttujat 
    # self.__tankin_koko ja self.__kulutus_satasella) oikeisiin alkuarvoihin.)
    def __init__(self, tankin_koko, kulutus_satasella):
        self.__tankin_koko = tankin_koko
        self.__kulutus_satasella = kulutus_satasella
        self.__bensaa = 0
        self.__matkaa_mittarissa = 0

    def tulostaTilanne(self):
        print("Auton tankissa on {:1.1f} litraa polttoainetta ja matkamittarissa {:1.1f} kilometriä.".format(self.__bensaa,self.__matkaa_mittarissa))

    def tankkaa(self,bensanmäärä):
        if bensanmäärä < 0:
            print("Bensaa ei voi ottaa pois tankista.")
            return
        self.__bensaa = self.__bensaa + bensanmäärä
        if self.__bensaa >= self.__tankin_koko:
            self.__bensaa = self.__tankin_koko
    def aja(self,kilometrejä):
        if kilometrejä < (self.__bensaa * 100 / self.__kulutus_satasella):
            self.__matkaa_mittarissa = self.__matkaa_mittarissa + kilometrejä
            self.__bensaa = self.__bensaa - kilometrejä * (self.__kulutus_satasella / 100)

        elif kilometrejä >= (self.__bensaa * 100 / self.__kulutus_satasella):
            self.__matkaa_mittarissa = self.__matkaa_mittarissa +  self.__bensaa * 100 / self.__kulutus_satasella
            self.__bensaa = 0
    # TODO: Lisää tähän uusien metodien määrittelyt. Koska metodit ovat osa
    # luokkaa, ne sisennetään samoin kuin yllä oleva rakentaja.


def main():

    tankin_koko  = lue_luku("Kuinka iso bensatankki ajoneuvossa on? ")
    kulutus_satasella = lue_luku("Montako litraa bensaa ajoneuvo kuluttaa "
        + "sadalla kilometrillä? ")

    # Tässä määritellään muuttuja auto, joka on luokan Auto olio. Tämä on 
    # siis se kohta, jossa luokan Auto rakentajaa (__init__) kutsutaan!
    auto = Auto(tankin_koko, kulutus_satasella)
    # (Tässä ohjelmassa tarvitsemme vain yhden auton, mutta luokasta on 
    # mahdollista luoda useampia olioita. Esim. pikkumatin_auto = Auto(10, 10)
    # ja pikkupekan_auto = Auto(20, 30). Tällöin jokaisella oliolla on omat
    # kenttänsä (self.__tankin_koko ja self.__kulutus_satasella), joilla voi
    # olla eri arvot, mutta oliot toimivat samalla tavalla, koska olion 
    # toiminnan määrittelee luokka.)

    while True:
        auto.tulostaTilanne()
        valinta = input(VALIKKOTEKSTI)
        if valinta == "1":
           tankataan = lue_luku("Montako litraa tankataan: ")
           # TODO: Lisää tähän auton tankkaa-metodin kutsu (b-kohta)
           auto.tankkaa(tankataan)
        elif valinta == "2":
           matka = lue_luku("Montako kilometriä ajetaan: ")
           # TODO: Lisää tähän auton aja-metodin kutsu (c-kohta)
           auto.aja(matka)
        elif valinta == "3":
           break
    print("Kiitos ja hei!")



def lue_luku(kehote, virheilmoitus="Vaarantyyppinen syote!"):
    try:   
        return float(input(kehote))
    except ValueError as e:
        print(virheilmoitus)
        return lue_luku(kehote, virheilmoitus)


main()
