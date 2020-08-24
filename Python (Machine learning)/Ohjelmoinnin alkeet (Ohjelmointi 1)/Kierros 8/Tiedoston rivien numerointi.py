def main():
    nimi = input("Syötä tiedoston nimi: ")
    try:
        tiedosto = open(nimi,"r", encoding="utf-8")
        riviluku = 1
        for rivi in tiedosto:
            rivi = rivi.rstrip()
            print("{:1d} {:1s}".format(riviluku,rivi))
            riviluku +=1
        tiedosto.close()
    except OSError:
        print("Virhe tiedoston lukemisessa.")
main()