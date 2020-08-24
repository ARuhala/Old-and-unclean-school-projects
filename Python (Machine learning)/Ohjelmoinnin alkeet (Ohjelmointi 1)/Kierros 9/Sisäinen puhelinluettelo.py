# tehdään dicti "Tiedosto", jossa käyttäjän nimen takana dicti,
# jossa nimien "huone" , "nimi" "numero" takana tietoja
# saadaan auki kaavalla Tiedosto["nimi"]["huone"]

# funktio palauttaa dictin "tiedosto"
def lue_tiedosto(tiedostonnimi):
    lukutiedosto = open(tiedostonnimi,"r",encoding="utf-8")
    #luodaan jokaisen nimen taake dicti, jossa "huone", "nimi", "puh"
    tiedosto={}
    for rivi in lukutiedosto:

        splitti=rivi.split(";")
        huone = splitti[0]
        nimi = splitti[1]
        puh = splitti[2]
        nimidicti = {"huone" : huone, "nimi" : nimi, "puh" : puh}
        # listätään tiedostoon saatu nimidicti nimen taakse
        tiedosto[nimi] = nimidicti

    return tiedosto
