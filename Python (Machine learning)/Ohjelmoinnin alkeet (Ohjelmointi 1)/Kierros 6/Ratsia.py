# Johdatus ohjelmointiin
# Ratsia koulun nurkalla
# Antti Ruhala, 253037




# ottaa ylös nopeusrajoituksen
def nopeusrajoitus():
    rajoitus=int(input("Syötä mittauspaikan nopeusrajoitus: "))
    if rajoitus <= 0:
        print ("Nopeusrajoituksen tulee olla positiivinen kokonaisluku.")
        return
    return rajoitus

# tekee listan syötetyistä nopeuksista
def teeNopeuslista():
    nopeuslista = []
    syöte=1
    poistojenmäärä = 0
    print("Syötä nopeusmittauksen tulokset, lopeta tyhjällä rivillä:")
    while True:
        syöte=input()
        if syöte == "":
            break
        elif int(syöte) < 20:
            poistojenmäärä = poistojenmäärä + 1
        else:
            lisäys=int(syöte)
            nopeuslista.append(lisäys)
    if poistojenmäärä != 0:
        print("Poistettiin {:1d} kpl mittaustuloksia, joiden suuruus oli alle 20 km/h".format(poistojenmäärä))
    return nopeuslista

# laskee vaihteluvälin nopeuslistasta
def vaihteluvälilaskuri(lista):
    järjestettylista=sorted(lista)
    vaihteluväli=järjestettylista[-1] - järjestettylista[0]
    return vaihteluväli

# laskee mediaanin nopeuslistasta
def mediaanilaskuri(lista):
    listanpituus=len(lista)
    jakojäännös = listanpituus % 2
    järjestettylista=sorted(lista)
    # Jos listalla on oikeasti keskimmäinen
    if jakojäännös == 1:
        puoliväli=int((listanpituus - 1) / 2)
        mediaani=järjestettylista[puoliväli]

    # Jos listan mediaani lasketaan kahden keskimmäisen keskiarvona
    else:
        puoliväli=int(listanpituus / 2)
        mediaani= ( järjestettylista[puoliväli-1] + järjestettylista[puoliväli] ) / 2
    return float(mediaani)

# laskee sakkojen määrän ja tekee sakkolistan
def sakkolaskuri(lista,rajoitus):
    rikesakkoja=0
    sakkoja=0
    sakkolista=[]
    for a in lista:
        if 8 <= a - rajoitus < 20:
            rikesakkoja=rikesakkoja + 1
            sakkolista.append(a)


        elif 20 <= a - rajoitus:
            sakkoja=sakkoja + 1
            sakkolista.append(a)


    return rikesakkoja, sakkoja, sakkolista

# tulostaa sakkolistan sisällön
def sakkolistantulostin(sakkolista):
    print("Ylinopeudet mittausjärjestyksessä:")
    for a in sakkolista:
        print(a)

# rakentaa ja tulostaa pylväsdiagrammin nopeuslistan sisällöstä
def pylväsdiagrammi(nopeuslista):
    #jnl viittaa järjestettyynnopeuslistaan
    jnl=sorted(nopeuslista)

    # haetaan ensin pienin mittaustulos ja siitä 5km/h jaksoilla listan loppuun jaottelu
    ekanvälinalku=jnl[0]

    #lasketaan tarvittavien välien määrä
    kokovälinkoko=jnl[-1] - jnl[0]
    välienmäärä = int(((kokovälinkoko - (kokovälinkoko % 5)) / 5) + 1)
    if len(nopeuslista)==1:
        välienmäärä = 1
    for i in range(välienmäärä):
        print("{:1d} ".format(jnl[0]+i*5),end="")
        for a in jnl:
            if jnl[0]+i*5 <= a < jnl[0]+(i+1)*5:     #jos a on nykyisen ja seuraavan välin alun sisällä
                print("#",end="")
        print(end="\n")

def main():
    # ottaa ylös nopeusrajoituksen
    rajoitus=nopeusrajoitus()
    # tekee listan syötetyistä nopeuksista
    nopeuslista=teeNopeuslista()
    if len(nopeuslista) != 0:
        # laskee vaihteluvälin nopeuslistasta
        vaihteluväli= vaihteluvälilaskuri(nopeuslista)
        # laskee mediaanin nopeuslistasta
        mediaani=mediaanilaskuri(nopeuslista)
        # laskee sakkojen määrän ja tekee sakkolistan
        rikesakkoja,sakkoja,sakkolista=sakkolaskuri(nopeuslista,rajoitus)

        # Yhdestä/nollasta nopeudesta ei tulosteta tilastotietoja
        if len(nopeuslista) != 0:
            print("Vaihteluväli:", vaihteluväli)
            print("Mediaani: {:1.1f}".format(mediaani))


        # Sakkojen tilastotiedot
        if (len(sakkolista) != 0):
            if rikesakkoja !=0:
                print("Rikesakon ylinopeudesta olisi saanut {:1d} kuljettajaa".format(rikesakkoja))
            if sakkoja !=0:
                print("Sakon ylinopeudesta olisi saanut {:1d} kuljettajaa".format(sakkoja))
            sakkolistantulostin(sakkolista)
            print()


        # tulostetaan pylväsdiagrammi jopa yhdelle nopeudelle
        print("Graafinen esitys aineistosta:")
        pylväsdiagrammi(nopeuslista)
main()

