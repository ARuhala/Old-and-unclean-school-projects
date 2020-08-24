# Johdatus ohjelmointiin
# Koodipohja geometrisia kuvioita varten



def valikko():
    while True:
        vastaus = input("Syötä kuvion alkukirjain, q lopettaa (n/s/q): ")
        if vastaus == "n":
        # Tässä käsitellaan neliö

        elif vastaus == "s":
        # Tässä käsitellään suorakaide

        elif vastaus == "q":
            return
        else:
            print("Virheellinen syöte, yritä uudelleen!")
        print()  # Tyhjä rivi, että ohjelman tulostetta on helpompi lukea


def main():
    valikko()
    print("Näkemiin!")


main()