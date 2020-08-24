
# Johdatus ohjelmointiin
# Antti Ruhala, 253037



class Kulkukortti:

    def __init__(self, tunniste, nimi):
        """
        Luokan rakentaja, eli metodi, joka antaa uuden olion
        luomisvaiheessa sille alkuarvon.

        :param tunniste: henkilön tunniste (str)
        :param nimi: henkilön nimi (str)

        TÄMÄN METODIN TOIMINTA TESTATAAN ERIKSEEN AUTOMAATTITESTISSÄ,
        JOTEN PARAMETRIEN MUUTTAMINEN JOHTAA TESTIEN EPÄONNISTUMISEEN.
        """

        self.__tunniste = str(tunniste)
        self.__nimi = str(nimi)

        #koodit listamuodossa
        self.__koodit = []



    def tulosta_tiedot(self):
        """
        Funktiolla ei ole paluuarvoa. Se tulostaa kulkukortin
        tiedot näytölle täsmälleen seuraavassa muodossa:
        tunniste, nimi, kulkualueet: ka1,ka2,...,kaN eli esimerkiksi:

           567890, Siiri Siivooja, kulkualueet: F,K,P,R,S,T

        Huomaa, että pilkkujen ja kaksoispisteen perässä
        tulevien välilyöntien on oltava tulosteessa juuri
        saman logiikan mukaisesti kuin edellä ja kulkualueiden
        on tulostuttava tehtävänannon määräämässä järjestyksessä.

        TÄMÄN METODIN TOIMINTA TESTATAAN ERIKSEEN AUTOMAATTITESTISSÄ,
        JOTEN PARAMETRIEN TAI TULOSTUSASUN MUUTTAMINEN JOHTAA TESTIEN
        EPÄONNISTUMISEEN.
        """
        print("{:1s}, {:1s}, kulkualueet: ".format(str(self.__tunniste),str(self.__nimi)), ",".join(self.__koodit), sep="")


    def anna_nimi(self):
        """
        :return: Palauttaa kulkukortille talletetun henkilön nimen.
        """

        return self.__nimi


    def tarkista_pääsy(self, kulkualuekoodi):
        """
        Tarkastaa pääseeko kulkukortilla halutulle kulkualueelle.

        TÄMÄN METODIN TOIMINTA TESTATAAN ERIKSEEN AUTOMAATTITESTISSÄ,
        JOTEN PALUUARVOJEN TAI PARAMETRIEN MUUTTAMINEN JOHTAA
        TESTIEN EPÄONNISTUMISEEN.

        :param kulkualuekoodi: alue, jolle kortilla halutaan päästä
        :return: True: ovi avautuu kulkukortille tallennetuilla oikeuksilla.
                 False: ovi ei avaudu kulkukortin oikeuksilla
        """

        # tutkitaan, sisältyykö jokin kortin kulkualuekoodeista kysytyn kulkualuekoodin alkuun
        for koodi in self.__koodit:
            if pääsytesti(koodi,kulkualuekoodi) == True:
                return True
        return False



    def lisää_kulkualue(self, uusi_alue):
        """
        Funktio lisää uuden alueen kulkukortin oikeuksiin tehtävänannossa
        määritellyn säännön mukaisesti. Funktio ei saa tulostaa näytölle mitään.

        TÄMÄN METODIN TOIMINTA TESTATAAN ERIKSEEN AUTOMAATTITESTISSÄ.
        MIKÄLI SE EI TOIMI MÄÄRITTELYN MUKAISESTI, TESTIT EPÄONNISTUVAT.
        MYÖS PARAMETRIEN MUUTTAMINEN JOHTAA AUTOMAATTITESTIEN
        EPÄONNISTUMISEEN.

        :param uusi_alue: Lisättävä kulkualue
        """


        # tilanne jossa lisättävää laajempi löytyy jo listalta
            # ei aiheuta toimenpiteitä

        # tilanne, jossa lisättyä suppeampia löytyy listalta, joten lisättävä halutaan lisätä
        lupa = self.tarkista_pääsy(uusi_alue)
        if lupa == False:
            self.__koodit = sorted (sievennä_kulkuoikeuslista(uusi_alue,self.__koodit) )





    def yhdistä_kulkukortti(self, toinen_kortti):
        """
        Yhdistää toinen_kortti-parametrin sisältämät kulkuoikeudet
        käsiteltävänä olevalle kortille. Toimintalogiikka määritelty
        tehtävänannossa.

        :param toinen_kortti: Kulkukortti, jonka kanssa oikeudet yhdistetään
        """


        for uusikoodi in toinen_kortti.__koodit:
            self.lisää_kulkualue(uusikoodi)


def pääsytesti(kulkuoikeus, tutkittava_alue):
    """
    Funktio tutkii oikeuttaako tietty kulkuoikeus pääsyn
    tutkittavana olevaan huoneeseen/alueelle.

    :param kulkuoikeus: Kulkuoikeus, jonka perusteella halutaan testata,
                       onko tutkittavalle_alueelle pääsyä.
    :param tutkittava_alue: Oikeuttaako parametri kulkuoikeus
                       pääsyyn tutkittavalle alueelle.
    :return: True, jos pääsy on sallittu, False muussa tapauksessa.
    """

    if str(tutkittava_alue).startswith(kulkuoikeus):
        return True
    else:
        return False



def sievennä_kulkuoikeuslista(lisättävä_kulkualue, vanha_kulkuoikeuslista):
    """
    Kun vanhaan_kulkuoikeuslistaan halutaan lisätä uusi kulkualue,
    on syntyvä kulkukoikeuslista sievennettävä siten, että kaikki
    lisättyä kulkualuetta suppeammat alueet poistetaan listalta
    (tehtävänannon esimerkki 5.2).  Koska tämä toimenpide on
    edellisellä toteutuskerralla osoittautunut kovin haastavaksi,
    tämä funktio hoitaa sen nyt kuntoon ilman ongelmia.

    Huomaa aivan erityisesti, että tätä funktiota on tarkoitus kutsua vain,
    kun jo tiedetään, että uusi kulkualue halutaan lisätä kulkukortille.

    Jos esimerkiksi lisättävä_kulkualue on "TE" ja
    vanha_kulkuoikeuslista on [ "S", "TE-110", "K2110", "TE-210" ]
    Funktio palauttaa listan [ "S", "K2110", "TE" ]

    :param lisättävä_kulkualue: Lisättäväksi haluttu kulkualue.
    :param vanha_kulkuoikeuslista: Tämänhetkiset kulkuoikeudet.
    :return: Kulkualuelista, joka saadaan kun vanhasta kulkukoikeuslistasta
             on poistettu kaikki lisättävää kulkualuetta suppeammat (ja saman-
             laajuiset kulkualueet), minkä jälkeen lisättävä_kulkualue on
             liitetty saadun supistetun listan loppuun.
    """

    suodatetut = []

    for alue in vanha_kulkuoikeuslista:
        # Huomaa, kuinka seuraavassa if-rakenteen ehdossa oletetaan
        # että edellä esitetty pääsytesti-funktio on toteutettu ja toimii.
        if not pääsytesti(lisättävä_kulkualue, alue):
            suodatetut.append(alue)

    suodatetut.append(lisättävä_kulkualue)

    return suodatetut


def main():
    # TODO: Toteuta syötetiedoston kulkutiedot.txt lukeminen
    #       ja luettujen tietojen tallennus sopivaan Python-rakenteeseen.
    try:
        lukutiedosto = open("kulkutiedot.txt", "r", encoding="utf-8")

        # luodaan kortit olioina ja tallennetaan korttioliot dictiin oman tunnisteen taake
        # listakaikistakorteista = lkk
        lkk = {}
        for rivi in lukutiedosto:
            osat = rivi.split(";")
            tunniste = osat[0]
            nimi= osat[1]
            #luodaan stringgi jossa koodit
            koodit = str(osat[2]).rstrip().split(",")


            # luodaan olio, jonka "nimi" on tunnisteen arvo
            # tämä ei jostain vielä tuntemattomasta syystä muuta muuttujan "tunniste" arvoa
            tunniste = Kulkukortti(tunniste, nimi)




            #luodaan dicti lkk[tunniste], jonka takaa löytyy olio

            lkk[osat[0]]= tunniste

            #lisätään korttioliolle koodilista
            #metodi lisää yhden aluekoodin kerrallaan, lista on oletuksena tyhjä

            for alue in koodit:
                lkk[osat[0]].lisää_kulkualue(alue)


        lukutiedosto.close()

    except:
        print("Virhe: tiedostoa ei saa luettua.")
        return


    while True:
        rivi = input("komento> ")

        if rivi == "":
            break

        osat = rivi.split()
        käsky = osat[0]

        if käsky == "lista" and len(osat) == 1:
            for tunniste in sorted(lkk):
                lkk[tunniste].tulosta_tiedot()

        elif käsky == "tiedot" and len(osat) == 2:
            tunniste = osat[1]

            try:

                lkk[tunniste].tulosta_tiedot()
            except:
                print("Virhe: tuntematon tunniste.")


        elif käsky == "kulku" and len(osat) == 3:
            tunniste = osat[1]
            alue = osat[2]
            try:

                lupa = lkk[tunniste].tarkista_pääsy(alue)
                if lupa == True:
                    print("Kortilla {:1s} ( {:1s} ) on kulkuoikeus huoneeseen {:1s}".format(tunniste, lkk[tunniste].anna_nimi(), alue))
                else:
                    print("Kortilla {:1s} ( {:1s} ) ei kulkuoikeutta huoneeseen {:1s}".format(tunniste, lkk[tunniste].anna_nimi(), alue))
            except:
                print("Virhe: tuntematon tunniste.")

        elif käsky == "lisää" and len(osat) == 3:
            tunniste = osat[1]
            alue = osat[2]
            try:
                lkk[tunniste].lisää_kulkualue(alue)
            except:
                print("Virhe: tuntematon tunniste.")


        elif käsky == "yhdistä" and len(osat) == 3:
            try:
                kohdekortti = osat[1]
                lähdekortti = osat[2]
                lkk[kohdekortti].yhdistä_kulkukortti(lkk[lähdekortti])
            except:
                print("Virhe: tuntematon tunniste.")

        else:
            print("Virhe: Väärä syöte, yritä uudelleen")


main()
