def kertoma(a):
    uusi = a
    for i in range(a):
        if i == 0:
            continue
        else:
            uusi = uusi * i
    if a == 0:
        return 1
    else:
        return uusi

def laskuri(n,p):
    tulos=kertoma(n) / ((kertoma(n-p)*kertoma(p)))
    return int(tulos)

def main():
        n=int(input("Syötä lottopallojen kokonaismäärä: "))
        p=int(input("Syötä arvottavien pallojen määrä: "))
        if n < 0:
            print("Pallojen määrän oltava positiivinen luku.")
        elif p > n:
            print("Arvottavia palloja saa olla enintään pallojen kokonaismäärän verran.")
        else:
            tulos=laskuri(n,p)
            print("Kun pelataan yksi rivi, todennäköisyys saada",p,"oikein on","1""/{:1d}".format(tulos),end="")
main()
