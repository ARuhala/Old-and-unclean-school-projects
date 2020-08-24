def main():
    aikalista=[]

    for i in range(5):
        uusiarvo=float(input("Syötä {:1d}. suorituksen aika: ".format(i+1)))
        aikalista.append(uusiarvo)
    aikalista.sort()
    del aikalista [0]
    del aikalista [-1]

    summa=0
    for a in aikalista:
        summa=summa+a
    jako=float(summa/len(aikalista))
    print("Virallinen kilpailutulos on {:1.2f} sekuntia.".format(jako))
main()