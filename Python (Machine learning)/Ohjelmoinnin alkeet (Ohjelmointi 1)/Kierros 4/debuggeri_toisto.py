# TIE-02100 Johdatus ohjelmointiin
# Ohjelmakoodipohja debuggerin testaamista varten

def main():

    merkkijono = input("Kuinka monta Fibonaccin lukua haluat: ")
    montako = int(merkkijono)

    vanha = 0
    nyt = 1
    rivinumero = 1

    while rivinumero <= montako:
        print(rivinumero, ". ", nyt, sep="")
        uusi = vanha + nyt
        nyt = uusi
        vanha = nyt

        rivinumero += 1


main()
