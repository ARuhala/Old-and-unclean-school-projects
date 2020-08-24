# Johdatus ohjelmointiin
# Koodipohja nimettyihin parametreihin


def tulosta_ruutu(leveys,korkeus,reunamerkki="#",sisämerkki=" "):
    for i in range(leveys):
        if i == leveys-1:
            print(reunamerkki)
        else:
            print(reunamerkki,end="")


    for i in range(korkeus-2):
        print(reunamerkki,end="")
        for i in range(leveys-2):
            print(sisämerkki,end="")
            if i ==leveys-3:
                print(reunamerkki)

    for i in range(leveys):
        if i == leveys-1:
            print(reunamerkki)
        else:
            print(reunamerkki,end="")
    print()

def main():
    tulosta_ruutu(5, 4)
    tulosta_ruutu(3, 8, "*")
    tulosta_ruutu(5, 4, "O", "o")
    tulosta_ruutu(sisämerkki=".", reunamerkki="O", korkeus=4, leveys=6)

main()
