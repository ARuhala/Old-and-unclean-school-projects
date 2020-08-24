# Johdatis ohjelmointiin
# Kulujen tasaaminen
# Antti Ruhala, 253037




def funktio():
    try:
        nimi = input("Anna tiedoston nimi: ")
        tiedosto = open(nimi, "r" , encoding="utf-8")


        # tarkistetaan rivin formaatin oikeellisuus
        for rivi in tiedosto:
            osat = rivi.split(":")
            try:
                str(osat[0])
                float(osat[1])

            except ValueError:
                print("Virhe! Tiedoston rivien pitää olla muotoa nimi:summa.")
                return
            except IndexError:
                print("Virhe! Tiedoston rivien pitää olla muotoa nimi:summa.")
                return
        tiedosto.close()
        # lasketaan yhteinen summa
        summa=0
        tiedosto = open(nimi, "r", encoding="utf-8")
        for rivi in tiedosto:
            osat = rivi.split(":")
            summa = summa + float(osat[1])
        print("Kokonaiskustannukset ovat: {:1.2f}e".format(summa))
        tiedosto.close()
        # Lasketaan yksittäisten henkilöiden saannit ja osuudet
        # Yksittäisen henkilön osuus koko summasta on summa / henkilöiden määrä
        # Yksittäinen henkilö voi maksaa useammassa erässä
        henkilölista = {}
        tiedosto = open(nimi, "r", encoding="utf-8")
        for rivi in tiedosto:
            osat = rivi.split(":")
            henkilö=osat[0]
            raha=osat[1]
            # jos on uusi henkilön nimi
            if not henkilö in henkilölista:
                henkilölista[henkilö] = []
                henkilölista[henkilö].append(float(raha))
            # jos on vanha tuttu
            elif henkilö in henkilölista:
                henkilölista[henkilö].append(float(raha))
        tiedosto.close()
        # Kun kaikkien henkilöiden pisteet on lokeroitu omien nimiensä taakse listaan, lasketaan listat summiksi

        for nimi in henkilölista:
            nimisumma = 0
            for alkio in henkilölista[nimi]:
                nimisumma = nimisumma + alkio

        # Talletetaan uusi saatu summa nimen taakse
            henkilölista[nimi] = nimisumma


        # Lasketaan yksittäisen henkilön osuus
        henkilömäärä = len(henkilölista)
        #käytetään aikaisemmin laskettua "summaa"
        if not(henkilömäärä == 0):
                osuus = summa / henkilömäärä
        else:
            osuus = summa


        #Esitetään yksittäisen henkilön vaadittavat toimenpiteet
        #Erikoistapaus, jos omaosuus on alle 5 senttiä eli 0.05 mitään ei saada eikä makseta
        for alkio in sorted(henkilölista):

            # jos maksu ja osuus täsmää tai ollaan siellä 5 sentin alueella
            if henkilölista[alkio] == osuus:
                print(alkio,"on maksanut {:1.2f}e, eikä hänellä ole maksettavaa tai saatavaa.".format(henkilölista[alkio]))
            # Jos yksittäinen henkilö on maksanut enemmän kuin hänen osuutensa, hän saa takaisin maksu - osuus
            elif (henkilölista[alkio] > osuus):
                if henkilölista[alkio] - osuus >= 0.05:
                    print(alkio,"on maksanut {:1.2f}e,".format(henkilölista[alkio]),"hänen pitää saada takaisin {:1.2f}e.".format(henkilölista[alkio] - osuus))
                else:
                    print(alkio,"on maksanut {:1.2f}e, eikä hänellä ole maksettavaa tai saatavaa.".format(henkilölista[alkio]))
            # Jos yksittäinen henkilö on maksanut vähemmän kuin hänen osuutensa, hänen tulee maksaa vielä osuus - maksu
            elif henkilölista[alkio] < osuus:
                if osuus - henkilölista[alkio] >= 0.05:
                    print(alkio,"on maksanut {:1.2f}e,".format(henkilölista[alkio]),"hänen pitää maksaa vielä {:1.2f}e.".format(osuus - henkilölista[alkio]))
                else:
                    print(alkio,"on maksanut {:1.2f}e, eikä hänellä ole maksettavaa tai saatavaa.".format(henkilölista[alkio]))


    except OSError:
        print("Virhe! Tiedostoa",nimi,"ei voida lukea.")

def Main():
    funktio()


Main()