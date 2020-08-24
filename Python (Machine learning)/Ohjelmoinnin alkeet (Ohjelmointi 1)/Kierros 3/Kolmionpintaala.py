from math import sqrt
def pinta_ala(a,b,c):
    s=(a+b+c)/2
    ala=sqrt(s*(s-a)*(s-b)*(s-c))
    return ala

def main():
    eka=input("Syötä ensimmäinen sivun pituus: ")
    a=float(eka)
    toka=input("Syötä toinen sivun pituus: ")
    b=float(toka)
    kolmas=input("Syötä kolmas sivun pituus: ")
    c=float(kolmas)
    print("Kolmion pinta-ala on {:1.1f}".format(pinta_ala(a,b,c)))
main()