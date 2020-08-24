def laske_abbat(merkkijono):
    merkkipituus = len(merkkijono)
    abbacounter = 0
    for i in range(merkkipituus):
        if 0 <= i < merkkipituus - 3:
            if "abba" in merkkijono[i:i+4]:
                abbacounter = abbacounter + 1
        elif merkkipituus - 3 <= i < merkkipituus:
            if "abba" in merkkijono[i:]:
                abbacounter = abbacounter + 1
    return abbacounter