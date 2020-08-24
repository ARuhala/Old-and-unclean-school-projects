# TIE-02100 Johdatus ohjelmointiin
# Tehtävä 9.2. koodipohja


def lue_tiedosto(tiedoston_nimi):
    """Lukee ja tallentaa tiedostossa olevat sarjat ja niiden genret."""

    # TODO alusta tietorakenne
    tietorakenne = {}
    try:
        tiedosto = open(tiedoston_nimi, "r")

        for rivi in tiedosto:
            # Erotellaan nimi ja genret erilleen
            # nimi on merkkijono ja genret lista
            nimi, genret = rivi.rstrip().split(";")
            genret = genret.split(",")

            for genre in genret:
                if not( genre in tietorakenne):
                    tietorakenne[genre] = []

            for genre in genret:
                tietorakenne[genre].append(nimi)

        tiedosto.close()
        return  tietorakenne

    except ValueError:
        print("Virhe: rivi ei ole muotoa nimi;genret.")
        return None

    except IOError:
        print("Virhe: tiedostoa ei saada luettua.")
        return None


def main():

    tiedoston_nimi = input("Anna tiedoston nimi: ")
    genrerakenne = lue_tiedosto(tiedoston_nimi)

    genrelista = []
    for genre in sorted(genrerakenne):
        genrelista.append(genre)
    pilkkuväli = ", "
    print("Valittavia genrejä ovat:", pilkkuväli.join(genrelista))

    while True:
        genre = input("> ")

        if genre == "lopeta":
            return
        if genre in genrerakenne:
            for alkio in sorted(genrerakenne[genre]):
                print(alkio)

main()
