def main():
    try:
        nimi1 = input("Syötä luettavan tiedoston nimi: ")
        nimi2 = input("Syötä kirjoitettavan tiedoston nimi: ")
        luettutiedosto = open(nimi1, "r", encoding="utf-8")

        # tarkistetaan luettavan tiedoston oikeellisuus
        for rivi in luettutiedosto:
            osat = rivi.split(";")
            # tarkistetaan osan 1 oikeellisuus
            aikaalku = osat[0].split(":")
            int(aikaalku[0]) or str(aikaalku[0])
            int(aikaalku[1])
            int(aikaalku[2])
            # tarkistetaan osan 2,3,4 oikeellisuus
            float(osat[1])
            float(osat[2])
            float(osat[3])
        luettutiedosto.close()
    except:
        print("Virhe tiedoston lukemisessa!")
    # tallennetaan luettava tiedosto listaan
    lista = []
    luettutiedosto = open(nimi1, "r", encoding="utf-8")
    # tallennetaan listaan uudet aikamuodot
    for rivi in luettutiedosto:
        osat = rivi.split(";")
        aikaalku = osat[0].split(":")
        if not(aikaalku == osat[0]):
            print(aikaalku)
            aikasek = aikaalku[0] * 60 * 60 + aikaalku[1] * 60 + aikaalku[2]
            osat[0] = aikasek
            lista.append(osat[0],";",osat[1],";",osat[2],";",osat[3],sep="")
        else:
            lista.append(osat[0])

    luettutiedosto.close()

    # kirjoitetaan listan sisältö uuteen tiedostoon
    kirjoittettavatiedosto = open(nimi2, "w", encoding="utf-8")

    for alkio in lista:
        kirjoittettavatiedosto.write(alkio)


main()