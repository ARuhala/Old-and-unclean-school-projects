# Johdatus ohjelmointiin
# Koodipohja pinta-alalaskuihin
def pinta_ala(x,y=None):
    if y==None:
        ala=x*x
    else:
        ala=x*y
    return ala
def main():
    print("Neliön pinta-ala on {:.1f}".format(pinta_ala(3)))
    print("Suorakaiteen pinta-ala on {:.1f}".format(pinta_ala(4,3)))


main()
