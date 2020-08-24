def main():
    rivi = input("Onko tylsää? (k/e) ")
    vastaus = str(rivi)
    while vastaus == "e":
        rivi = input("Onko tylsää? (k/e) ")
        vastaus = str(rivi)
    print("Noh, lopetetaan sitten.")
main()
