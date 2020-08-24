# TIE-02100 Johdatus ohjelmointiin 
# Tehtävän 9.4. koodipohja

def lue_tiedosto(tiedoston_nimi):
    """Lukee tiedostosta pelaajien pelaamat biisit ja saadut tulokset.""" 
    try:
        tiedosto = open(tiedoston_nimi, "r")

        # TODO: Määrittele käyttämäsi tietorakenne tänne
        nimilista = {}
        # Käydään tiedosto riveittäin läpi, rivi sisältää pelaajan tiedot
        for rivi in tiedosto:
            osat = rivi.strip().split(";")
            pelaaja = osat[0] # sisältää pelaajan nimen
            biisit = osat[1:] # jokainen listan alkio sisältää yhden biisin

            # TODO luo pelaajalle tietorakenne joka sisältää
            # pelaajan pelaamat kappaleet ja niiden tulokset
            nimilista[pelaaja] = {}

            # Käydään läpi pelaajan pelaamat kappaleet yksi kerrallaan
            for biisi in biisit:
                osat = biisi.split(":")
                tulokset = osat[1].split(",")
                # Sisältää kappaleen nimen
                nimi = osat[0]
                # Sisältää listan kappaleen painalluksista (int)
                tulokset = [int(luku) for luku in tulokset]

                nimilista[pelaaja][nimi] = tulokset

            # TODO: Lisää kappaleet ja tulokset sisältävä tietorakenne 
            # pelaajat sisältävään tietorakenteeseen.

        return  nimilista

    except IOError:
        print("Virhe: tiedostoa ei saatu luettua.")
        return None


def main():

    kertoimet = [5, 4, 2, 0, -6, -12]

    tiedoston_nimi = input("Anna tiedoston nimi: ")
    nimilista = lue_tiedosto(tiedoston_nimi)

    # TODO lisää tulostus
    for nimi in sorted(nimilista):
        print("{:1s}:".format(nimi))
        for biisi in sorted(nimilista[nimi]):
            tulos = nimilista[nimi][biisi][0] * 5 + nimilista[nimi][biisi][1] * 4 + nimilista[nimi][biisi][2] * 2 + nimilista[nimi][biisi][3] * 0 + nimilista[nimi][biisi][4] * (-6) + nimilista[nimi][biisi][5] * (-12)
            maksimitulos = (nimilista[nimi][biisi][0] + nimilista[nimi][biisi][1] + nimilista[nimi][biisi][2] + nimilista[nimi][biisi][3] + nimilista[nimi][biisi][4] + nimilista[nimi][biisi][5])*5
            prosenttitulos = float((tulos / maksimitulos) * 100)
            print("- {:1s}: {:1.2f}%".format(biisi,float(prosenttitulos)))


main()
