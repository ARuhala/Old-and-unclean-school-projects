# Johdatus ohjelmointiin
# Koodipohja ruudun tulostukseen syötteillä
def tulosta_ruutu(s,h,m):
    for i in range(h):
        for i in range(s):
            print(m,end="")
        print("")

def lue_syöte(x):
    syöte=int(input(x))
    while syöte<=0:
        syöte = int(input(x))
    return syöte
def main():
    onnistui = False
    while not onnistui:
        try:
            leveys = lue_syöte("Syötä ruudun leveys: ")
            onnistui = True
        except ValueError:
            onnistui = False
    onnistui = False
    while not onnistui:
        try:
            korkeus = lue_syöte("Syötä ruudun korkeus: ")
            onnistui = True
        except ValueError:
            onnistui = False
    merkki = input("Syötä tulostusmerkki: ")
    print()
    tulosta_ruutu(leveys, korkeus, merkki)

main()
