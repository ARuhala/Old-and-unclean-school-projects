import math
pi=float(math.pi)
def neliö(a):
    mitta=a*4
    ala=a*a
    return mitta, ala

def suorakaide(a,b):
    mitta=a+a+b+b
    ala=a*b
    return mitta, ala

def ympyrä(r):
    mitta=2*pi*r
    ala=pi*r*r
    return mitta, ala

def main():
    kuvio=1
    while kuvio!="q":
        kuvio=str(input("Syötä kuvion alkukirjain, q lopettaa (n/s/y/q): "))
        if kuvio!="n" and kuvio!="s" and kuvio!="q" and kuvio!="y":
            print("Virheellinen syöte, yritä uudelleen!")
            print()

        elif kuvio == "n":
            reuna=-1
            while reuna<=0:
                reuna=float(input("Syötä neliön sivun pituus: "))
            mitta, ala=neliö(reuna)
            print("Ympärysmitta on {:1.2f}".format(mitta))
            print("Pinta-ala on {:1.2f}".format(ala))


        elif kuvio == "s":
            sivu1=-1
            while sivu1<=0:
                sivu1=float(input("Syötä suorakaiteen sivun 1 pituus: "))
            sivu2=-1
            while sivu2<=0:
                sivu2=float(input("Syötä suorakaiteen sivun 2 pituus: "))
            mitta, ala=suorakaide(sivu1,sivu2)
            print("Ympärysmitta on {:1.2f}".format(mitta))
            print("Pinta-ala on {:1.2f}".format(ala))

        elif kuvio =="y":
            säde=-1
            while säde<=0:
                rivi=input("Syötä ympyrän säde: ")
                säde=float(rivi)
                mitta, ala = ympyrä(säde)
                print("Ympärysmitta on {:1.2f}".format(mitta))
                print("Pinta-ala on {:1.2f}".format(ala))

        elif kuvio =="q":
            print("Näkemiin!")
            break
        print()
main()
