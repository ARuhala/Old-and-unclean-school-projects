def main():
    syöte=0
    lkm=1
    nimi = input("Syötä tiedoston nimi: ")
    try:
        tiedosto = open(nimi, "w", encoding="utf-8")
        print("Syötä viestin tekstirivejä. Lopeta syöttämällä tyhjä rivi.")
        syöte=input()
        while syöte != "":
            tiedosto.write("{:1d} {:1s}".format(lkm,syöte)+"\n")
            lkm += 1
            syöte = input()
        tiedosto.close()
        print("Tiedosto",nimi,"kirjoitettu.")
    except OSError:
        print("Tiedoston",nimi,"kirjoittaminen epäonnistui.")

main()