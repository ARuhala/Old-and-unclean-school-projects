# TIE-02100 Johdatus ohjelmointiin
# Tehtävä: ROT-13, ohjelmakoodipohja

def salaa(merkki):
    SELKOMERKIT = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l",
                        "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w",
                        "x", "y", "z"]

    SALAMERKIT = ["n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y",
                            "z", "a", "b", "c", "d", "e", "f", "g", "h", "i",
                            "j", "k", "l", "m"]


    # Täydennä merkin salaaminen tähän
    pikkumerkki=merkki.lower()

    if pikkumerkki in SELKOMERKIT:
        indeksi = SELKOMERKIT.index(pikkumerkki)
        # pienille kirjaimille
        if merkki.lower() == merkki:
            merkki = SALAMERKIT[indeksi]
            #isoille kirjaimille
        if merkki.upper() == merkki:
            merkki = SALAMERKIT[indeksi].upper()
    return merkki

def rivin_salaus(merkkijono):
    salattumerkkijono = ""
    for a in merkkijono:
        salattumerkki = salaa(a)
        salattumerkkijono = salattumerkkijono + salattumerkki
    return salattumerkkijono

def lue_viesti():
    lista=[]
    while True:
        syöte = input()
        if syöte == "":
            break
        else:
            lista.append(syöte)
    return lista

def main():
    print("Syötä viestin tekstirivejä. Lopeta syöttämällä tyhjä rivi.")
    viesti = lue_viesti()

    print("ROT13:")
    for merkkijono in viesti:
        salattumerkkijono = rivin_salaus(merkkijono)
        print("{:1s}".format(salattumerkkijono))

main()
