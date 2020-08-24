def main():
    print("Syötä kilpailijan nimi ja pistemäärä. Lopeta syöttämällä tyhjä rivi.")

    kilpailijalista = {}

    while True:
        syöte=input()

        if syöte != "":
            syötesplit=syöte.split()
            kilpailija=syötesplit[0]
            pisteet=int(syötesplit[1])
            #jos on uusi kilpailijan nimi
            if not(kilpailija in kilpailijalista):
                kilpailijalista[kilpailija] = []
                kilpailijalista[kilpailija].append(pisteet)

            #jos on vanha tuttu
            elif kilpailija in kilpailijalista:
                kilpailijalista[kilpailija].append(pisteet)
        else:
            break
    print("Kilpailijoiden pistetilanne:")
    for kilpailija in sorted(kilpailijalista):
        #pistetilasto ennen yhtäsuuruutta
        pistetilasto=""
        for i in kilpailijalista[kilpailija][:-1]:
            pistetilasto=pistetilasto + "{:1d}".format(i) +" "
        else:
            i = kilpailijalista[kilpailija][-1]
            pistetilasto=pistetilasto + "{:1d}".format(i)
        print("{:1s} {:1s} = {:1d}".format(kilpailija,pistetilasto,sum(kilpailijalista[kilpailija])))
main()