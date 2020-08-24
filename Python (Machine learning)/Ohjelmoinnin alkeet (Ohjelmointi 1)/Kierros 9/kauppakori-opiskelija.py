
# Johdatus ohjelmointiin
# Kauppakori
# Antti Ruhala, 253037


# TODO:
# määrittele tänne tarvitsemasi funktiot

# lukee tiedoston ja luo/palauttaa dictin kauppojen nimistä, joiden takana dicti, jossa kauppojen tuotteiden nimet, joiden takana kauppojen tuotteiden yksilälliset hinnat
# lopullinen tiedosto muotoa kauppalista[kaupan_nimi][tuotteen_nimi][tuotteen_hinta]
def lue_tiedosto(tiedoston_nimi):
    nimilista={}
    try:
        tiedosto = open(tiedoston_nimi, "r", encoding="utf-8")
        for rivi in tiedosto:
            kaupannimi,tuote,hinta = rivi.split(":")
            if not (kaupannimi in nimilista):
                nimilista[kaupannimi]={}
                nimilista[kaupannimi][tuote]= hinta
            else:
                nimilista[kaupannimi][tuote] = hinta

        tiedosto.close()
    except():
        print("Tiedostoa luettaessa tapahtui virhe!")

    return nimilista




# tulostaa kaupat ja niiden tuotteet aakkosjärjestyksessä
def tulosta(nimilista):
    for nimi in sorted(nimilista):
        print(nimi)
        for tuote in sorted(nimilista[nimi]):
            print("    {:<15} {:>10.2f} e".format(tuote,float(nimilista[nimi][tuote])))


# tulostaa saatavilla olevat tuotteet ja niiden halvimman hinnan
def saatavilla(nimilista):
    # käydään jokaisen kaupan tuotteet läpi, tallennetaan tuotteet dictiin
    # ja niiden hinta nimen taakse, jos sama tuote tulee uudestaan vastaan, katsotaan onko hinta halvempi, jos on, korvataan hinta
    halvimmathinnat={}
    for nimi in nimilista:
        for tuote in nimilista[nimi]:
            if not (tuote in halvimmathinnat):
                halvimmathinnat[tuote] = float(nimilista[nimi][tuote])
            else:
                if float(nimilista[nimi][tuote]) < float(halvimmathinnat[tuote]):
                    halvimmathinnat[tuote] = nimilista[nimi][tuote]

    print("Saatavilla olevat eri tuotteet:")
    for tuote in sorted(halvimmathinnat):
        print("    {:<15} {:>10.2f} e".format(tuote,float(halvimmathinnat[tuote])))


def kauppakori(nimilista):
    # tallennetaan käyttäjän syöttämä kauppakori listaan
    # käydään kauppojen tuotteet läpi
    # otetaan vastaavuuksien hinnat ylös, jos löydetään vastaavuudet jokaiselle tuotteelle, lasketaan niiden summa
    # tallennetaan kauppojen nimet dictiin ja summa nimen taakse

    # tulostetaan halvimmat kaupat jos niitä on useampia
    # tulostetaan halvin kauppakorin täyttävä kauppa ja hinta
    # tulostetaan, että halvinta kauppaa ei ole jos yksikään kauppa ei vastaa koko listaa


    kauppakori = input("Anna tuotteet eroteltuna välilyönneillä:\n").split(" ")

    halvimmatkaupat={}
    edellinensumma = 0
    for nimi in nimilista:
        vastaavuudet = {}
        for tuote in nimilista[nimi]:
            if str(tuote) in kauppakori:
                vastaavuudet[tuote] = nimilista[nimi][tuote]
        if len(vastaavuudet) == len(kauppakori):



            summa = 0
            for tuote in vastaavuudet:
                summa = summa + float(vastaavuudet[tuote])
            if summa <= edellinensumma or len(halvimmatkaupat)==0:
                halvimmatkaupat[nimi] = summa
                edellinensumma = summa

    if len(halvimmatkaupat) == 1:
        for alkio in halvimmatkaupat:
            print("Halvin kauppa tälle korille on {:1s} {:1.2f} e hinnallaan!".format(alkio,float(halvimmatkaupat[alkio])))

    if len(halvimmatkaupat) > 1:
        listakaupoista = []
        for alkio in sorted(halvimmatkaupat):
            if not(alkio in listakaupoista):
                listakaupoista.append(alkio)

        pilkkuväli = ", "
        kauppalistastringinä = pilkkuväli.join(listakaupoista)
        print("Seuraavat kaupat myyvät yhtä halvalla {:1.2f} e hinnalla: {:1s}".format(edellinensumma, kauppalistastringinä))

    if len(halvimmatkaupat) == 0:
        print("Yksikään kauppa ei myy kaikkia kauppakorin tuotteita!")



def main():

    # TODO
    # Kutsu tässä tiedostonlukufunktiota. Huomaa,
    # että exitiä ei saa käyttää ohjelman suorituksen
    # lopettamiseen.
    nimilista=lue_tiedosto("tuotetiedot.txt")


    print("Tervetuloa kauppakorisovellukseen!\n"
          "Käytettävissä olevat komennot:\n"
          " T ulosta kaupat tuotteineen\n"
          " S aatavilla olevien tuotteiden listaus\n"
          " K auppakorin halvin myyjä\n"
          " Q uit\n")

    syöte = ""
    while syöte != "Q":
        syöte = input("\nAnna komento (T, S, K, Q): ").upper()

        # HUOMIO!
        # pass on kätevä komento, joka tarkoittaa "älä tee mitään".
        # Nyt kun käyttöliittymässä on pass jokaisen ehtolauseen
        # jälkeen, tämän Python-tiedoston voi suorittaa ilman, että
        # Python-tulkki valittaa virheellisestä koodista. Näin on
        # kätevää ensin paneutua tiedoston lukemiseen ja sitten
        # ensimmäiseen komentoon (T). Muiden komentojen kohdalla
        # voi lukea pass niin kauan kunnes niitä aletaan tehdä,
        # jolloin pass kuuluu poistaa koodista.

        if syöte == "T":
            # TODO: kauppakohtainen tulostus
            tulosta(nimilista)

        elif syöte == "S":
            # TODO: saatavilla olevien tuotteiden tulostus
            saatavilla(nimilista)

        elif syöte == "K":
            # TODO: kauppakori
            kauppakori(nimilista)

        elif syöte == "Q":
            print("Hei hei!")
            return

        else:
            print("Virheellinen komento!")

main()
