def main():
    rivi = input("Onko tylsää? (k/e) ")
    vastaus = str(rivi)
    while not (vastaus=="k" or vastaus=="K"):
        while not (vastaus == "K" or vastaus == "k" or vastaus == "E" or vastaus == "e"):
            print("Virheellinen syöte.")
            rivi = input ("Yritä uudelleen: ")
            vastaus = str(rivi)
        while vastaus == "e" or vastaus == "E":
            rivi = input("Onko tylsää? (k/e) ")
            vastaus = str(rivi)

    print("Noh, lopetetaan sitten.")
main()