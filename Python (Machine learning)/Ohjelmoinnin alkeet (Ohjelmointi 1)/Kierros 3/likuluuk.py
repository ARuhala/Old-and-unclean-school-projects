# TIE-02100 Johdatus ohjelmointiin
# Liukulukujen vertaileminen

# TÃ¤mÃ¤ on vakion mÃ¤Ã¤rittely. Kun tÃ¤mÃ¤ on tehty, omassa
# ohjelmakoodissa voi kÃ¤tevÃ¤sti kÃ¤yttÃ¤Ã¤ EPSILONia esim.
# vertailun yhteydessÃ¤ if luku < EPSILON: ..., jolloin ei
# tarvitse kirjoittaa koodiin 0.0000000.... moneen paikkaan.
# Vakiot kirjoitetaan isoilla kirjaimilla.
EPSILON = 0.000000001


# mÃ¤Ã¤rittele tÃ¤nne funktio vertailu tehtÃ¤vÃ¤nannon mukaisesti
def vertaile(a,b):
    if abs(a - b) < EPSILON:
        return True
    elif abs(a - b) >= EPSILON:
        return False
def main():
    A=input("Anna liukuluku A: ")
    a=float(A)
    B=input("Anna liukuluku B: ")
    b=float(B)
    vastaus=vertaile(a,b)
    if vastaus==True:
        print("Luvut ovat samat!")
    if vastaus==False:
        print("Luvut eivät ole samat!")


main()