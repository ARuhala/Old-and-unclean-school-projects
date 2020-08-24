def main():
    print("Syötä viestin tekstirivejä. Lopeta syöttämällä tyhjä rivi.")
    esiintymälista = {}
    while True:
        syöte = input()
        if syöte != "":
            lauselistana = syöte.split()
            for alkio in lauselistana:
                sana=alkio.lower()
                if sana in esiintymälista:
                    esiintymälista[sana] = esiintymälista[sana] +1
                else:
                    esiintymälista[sana] = 1
        else:
            break
    for sanapari in sorted(esiintymälista):
        print("{:1s} : {:1d} kpl".format(sanapari,esiintymälista[sanapari]))

main()