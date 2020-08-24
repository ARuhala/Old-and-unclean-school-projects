def tulosta_ruutu(s,h,m):
    for i in range(h):
        for i in range(s):
            print(m,end="")
        print("")
def main():
    lev=input("Syötä ruudun leveys: ")
    s=int(lev)
    kork=input("Syötä ruudun korkeus: ")
    h=int(kork)
    merk=input("Syötä tulostusmerkki: ")
    m=str(merk)
    print()
    tulosta_ruutu(s,h,m)
main()