def main():
    rivi = input("Vastaa K tai E: ")
    vastaus = str(rivi)
    while not (vastaus == "K" or vastaus == "k" or vastaus == "E" or vastaus == "e"):
        print("Virheellinen syöte.")
        rivi = input ("Yritä uudelleen: ")
        vastaus = str(rivi)
    print("Vastasit ",rivi)
main()