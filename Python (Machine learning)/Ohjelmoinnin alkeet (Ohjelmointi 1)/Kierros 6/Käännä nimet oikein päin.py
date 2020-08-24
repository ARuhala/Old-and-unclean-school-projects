def käännä_nimi(a):
    if "," in a and not(len(a.strip()) == 1):
        splita=a.split(",")
        etunimi=splita[1]
        sukunimi=splita[0]
        stripetunimi = etunimi.strip()
        stripsukunimi = sukunimi.strip()
        nimi = stripetunimi + " " + stripsukunimi
        if len(a.strip()) == 2:
            nimi = stripetunimi + stripsukunimi
    elif "," in a and len(a.strip()) == 1:
        nimi = ""
    else:
        nimi=a.strip()
    print(nimi)
    return nimi
käännä_nimi("X,")

