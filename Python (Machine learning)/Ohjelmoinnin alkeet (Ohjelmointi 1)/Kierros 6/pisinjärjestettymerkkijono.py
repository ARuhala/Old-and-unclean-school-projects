def pisin_jarjestetty_alimerkkijono(merkkijono):
    merkkipituus = len(merkkijono)
    edellinenparas = 0
    parasmerkkijono= ""
    kaikistaparas= ""
    parhaanvika="ö"
    for merkki in merkkijono:
        i=merkkijono.index(merkki)

        if merkkijono[i] <= parhaanvika:
            parasmerkkijono = parasmerkkijono + merkki
            parhaanvika = parasmerkkijono[-1]


        elif parhaanvika < merkkijono[i]:
            parhaimmanpituus=len(parasmerkkijono)

            if parhaimmanpituus > edellinenparas:
                kaikistaparas=parasmerkkijono
                print(kaikistaparas)
                edellinenparas = len(kaikistaparas)
                parasmerkkijono = ""
                parhaanvika = "ö"

    print(kaikistaparas)
    return kaikistaparas

pisin_jarjestetty_alimerkkijono("abcabcdefgabab")
