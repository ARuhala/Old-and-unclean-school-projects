# Johdatus ohjelmointiin
# Antti Ruhala, 253037

# Kyseinen projekti on luoto "yksinkertaiseksi versioksi"

# Tämä käyttöliittymäohjelma suorittaa yksinkertaisia fysiikan putoamisliikkelle ominaisia laskuja
# käyttäjän syöttämiä massoja ja korkeuksia hyväksikäyttäen
# Käyttäjä syöttää positiiviset kokonaisluvut: massa, korkeus
# Ohjelma laskee annettujen parametrien perusteella: kappaleen nopeuden sen iskeytyessä maahan, kappaleen maahan kohdistaman voiman suuruuden
# Voiman suuruudessa käytetään hyväksi oletusta, että nopeudesta riippumatta kappaleen nopeus pysähtyy maahan osuessa 1 sekunnin aikana

# Huomioituja virhetilanteita ovat:
# Käyttäjä syöttää negatiivisen massan
# Käyttäjä syöttää negatiivisen korkeuden
# Käyttäjän syöttämät luvut eivät olleet kokonaislukuja
# Käyttäjän syöttämät merkit eivät olleet ollenkaan numeroita

# Sallitaan tilanne, jossa käyttäjä haluaa tietää 0 massaisen
# tai 0 korkeudelta putoavan kappaleen tietoja

# Ohjelmoijan vapaudella sallitaan tilanne, jossa käyttäjä haluaa tietää negatiivisen massan
# Putoamisnopeuden reaalilukuiselta korkeudelta, koska nopeuden lauseke on massasta riippumaton
# Negatiivinen massa on periaatteessa fysiikanlakien vastainen, mutta tämä kattaa myös tilanteen, jossa käyttäjä haluaa tietää
# tuntemattoman massan putoamisnopeuden tietyllä korkeuden arvolla



from tkinter import *
import math

#Luodaan virheikkunoita varten classi
class Virheikkuna:
    def __init__(self):
        self.__Virheikkuna = Tk()

        # Virheilmoituksen teksti
        self.__tekstikenttä = Label(self.__Virheikkuna, text="Syöte voi olla vain positiivinen reaaliluku")
        self.__tekstikenttä.pack()


        # luodaan sammutusnappi
        self.__lopetusnappi = Button(self.__Virheikkuna, text="lopeta",command=self.lopeta)
        self.__lopetusnappi.pack()

        self.__Virheikkuna.mainloop()



    def lopeta(self):
        self.__Virheikkuna.destroy()




class Käyttöliittymä:
    def __init__(self):
        self.__pääikkuna = Tk()

        # Alustetaan massan syöttöikkuna
        self.__tekstikenttämassa = Label(self.__pääikkuna,text="Syötä massan arvo")
        self.__tekstikenttämassa.pack()
        self.__massalähtöarvo = Entry()
        self.__massalähtöarvo.pack()



        # Alustetaan korkeuden syöttöikkuna
        self.__tekstikenttäkorkeus = Label(self.__pääikkuna,text="Syötä korkeuden arvo")
        self.__tekstikenttäkorkeus.pack()
        self.__korkeuslähtöarvo = Entry()
        self.__korkeuslähtöarvo.pack()

        # muunnosnappi nopeudelle
        self.__nopeusmuunnosnappi = Button(self.__pääikkuna, text="Nopeus",command=self.nopeus)
        self.__nopeusmuunnosnappi.pack()
        # Tekstimuotoiset tulosteet nopeudelle
        self.__tekstikenttäTulosnopeus = Label(self.__pääikkuna,text="Nopeus jolla kappale osuu maahan on [m/s]")
        self.__tekstikenttäTulosnopeus.pack()
        self.__tulosarvoNopeus = Entry()
        self.__tulosarvoNopeus.pack()

        # muunnosnappi voimalle
        self.__voimamuunnosnappi = Button(self.__pääikkuna, text="Voima",command=self.voima)
        self.__voimamuunnosnappi.pack()
        # Tekstimuotoiset tulosteet voimalle
        self.__tekstikenttäTulosVoima = Label(self.__pääikkuna,text="Voima jolla kappale osuu maahan on [N]")
        self.__tekstikenttäTulosVoima.pack()
        self.__tulosarvoVoima = Entry()
        self.__tulosarvoVoima.pack()




        # luodaan sammutusnappi
        self.__lopetusnappi = Button(self.__pääikkuna, text="lopeta",command=self.lopeta)
        self.__lopetusnappi.pack()

        self.__pääikkuna.mainloop()


    # Tämä metodi laskee ja kirjoittaa näytölle syötettyä massaa ja korkeutta vastaavan nopeuden
    def nopeus(self):

        # Virhetarkastelu

        try:
            syötekorkeus = self.__korkeuslähtöarvo.get()
            korkeus = int(syötekorkeus)
            if korkeus < 0:
                korkeusvirhe = Virheikkuna()
        except:
            korkeusvirhe = Virheikkuna()



        try:
            nopeus = str(math.sqrt( 2*10*korkeus))
            self.__tulosarvoNopeus.delete(0, END)
            self.__tulosarvoNopeus.insert(0, nopeus)
        except:
            tyhjävirhe = Virheikkuna()



    # Tämä metodi laskee ja kirjoittaa näytölle massaa ja nopeutta vastaavan voiman
    def voima(self):

        # Virhetarkastelu
        try:
            syötemassa = self.__massalähtöarvo.get()
            massa = int(syötemassa)
            if massa < 0:
                massavirhe = Virheikkuna()
        except:
            massavirhe = Virheikkuna()

        try:
            syötekorkeus = self.__korkeuslähtöarvo.get()
            korkeus = int(syötekorkeus)
            if korkeus < 0:
                korkeusvirhe = Virheikkuna()
        except:
            korkeusvirhe = Virheikkuna()

        try:
            voima = massa * math.sqrt(2 * 10 * korkeus)
            self.__tulosarvoVoima.delete(0, END)
            self.__tulosarvoVoima.insert(0, voima)
        except:
            tyhjävirhe = Virheikkuna()



    def lopeta(self):
        # lopetusnapin painaminen, kun syötekentissä on viallisia syötteitä aiheuttaa virheilmoitusten tulemisen
        # ikkunan sulkeutumisen jälkeen, tämä ei ole tarpeellista tietoa enää ikkunan sulkeutumisen jälkeen
        # Tuntuu kuin viimeinen mainloop kierros käydään vielä UIn sulkemisen jälkeen
        # En kuitenkaan keksinyt mitään tapaa estää tämän tapahtumista edes return tai quit käskyllä



        # sulkee pääikkunan
        self.__pääikkuna.destroy()






def main():
    ohjelma = Käyttöliittymä()
main()