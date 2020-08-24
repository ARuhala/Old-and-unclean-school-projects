def main():
    print("Anna sademaaria, lopeta luvulla 999999.")
    rivi=input("Anna sademaara: ")
    eka=float(rivi)
    if eka<=0:
        eka=0
        summa=0
        i=0
    else:
        summa=eka
        i=1
        sademaara=summa


    while eka!=999999:
        rivi = input("Anna sademaara: ")
        eka = float(rivi)
        i = i + 1
        if eka<0:
            eka=0
            i=i-1


        elif eka!=999999:
            summa = summa + eka
            sademaara = summa / i

        elif eka==999999:
            i=i-1




    if eka==999999 and summa!= 999999 and summa!= 0:
            print("Sademaarien keskiarvo on ",sademaara)
    elif eka==999999 and summa==999999 or summa==0:
        print("Yhtaan sademaaraa ei syotetty.")
main()
