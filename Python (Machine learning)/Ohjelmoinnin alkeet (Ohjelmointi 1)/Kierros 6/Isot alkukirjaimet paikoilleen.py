def isot_alkukirjaimet(merkkijono):
    splitmerkkijono=merkkijono.split()
    korjattulause=""
    for sana in splitmerkkijono:
        korjattusana=sana.capitalize()
        if sana == splitmerkkijono[0]:
            korjattulause=korjattulause + korjattusana
        else:
            korjattulause=korjattulause + " " + korjattusana
    print(korjattulause)
    return korjattulause
isot_alkukirjaimet("lEntäVÄ kaLaKUKko")