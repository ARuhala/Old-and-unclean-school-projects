# Tämä dict on globaali vakio, jota hyödynnetään tulevaisuudessa hyökkäysten
# tehokkuuksien laskemisessa. Kyseessä on dict jonka avaimina on tyyppejä ja
# arvoina dictejä, joissa avaimina hyökkäysten tyyppejä ja arvoina niiden
# tehokkuuskertoimia. Esimerkiksi Normal-tyypin Pokemoniin Ghost-tyyppinen
# isku tekee 0.8x vahinkoa, mutta Fighting-tyyppinen 1.25-kertaisesti.
TYYPIT = {"Normal": {"Fighting": 1.25, "Ghost": 0.8},
          "Fighting": {"Flying": 1.25, "Psychic": 1.25, "Fairy": 1.25,
                       "Rock": 0.8, "Bug": 0.8, "Dark": 0.8},
          "Flying": {"Electric": 1.25, "Rock": 1.25, "Ice": 1.25, "Grass": 0.8,
                     "Bug": 0.8, "Fighting": 0.8, "Ground": 0.8},
          "Poison": {"Ground": 1.25, "Psychic": 1.25, "Fighting": 0.8,
                     "Bug": 0.8, "Poison": 0.8, "Grass": 0.8, "Fairy": 0.8},
          "Ground": {"Water": 1.25, "Grass": 1.25, "Ice": 1.25, "Poison": 0.8,
                     "Rock": 0.8, "Electric": 0.8},
          "Rock": {"Fighting": 1.25, "Ground": 1.25, "Steel": 1.25,
                   "Water": 1.25, "Grass": 1.25, "Normal": 0.8, "Flying": 0.8,
                   "Poison": 0.8, "Fire": 0.8},
          "Bug": {"Flying": 1.25, "Rock": 1.25, "Fire": 1.25, "Fighting": 0.8,
                  "Ground": 0.8, "Grass": 0.8},
          "Ghost": {"Ghost": 1.25, "Dark": 1.25, "Bug": 0.8, "Poison": 0.8,
                    "Normal": 0.8, "Fighting": 0.8},
          "Steel": {"Fighting": 1.25, "Ground": 1.25, "Fire": 1.25,
                    "Normal": 0.8, "Flying": 0.8, "Rock": 0.8, "Bug": 0.8,
                    "Steel": 0.8, "Grass": 0.8, "Psychic": 0.8, "Ice": 0.8,
                    "Dragon": 0.8, "Fairy": 0.8, "Poison": 0.8},
          "Fire": {"Ground": 1.25, "Rock": 1.25, "Water": 1.25, "Bug": 0.8,
                   "Steel": 0.8, "Fire": 0.8, "Ice": 0.8, "Fairy": 0.8},
          "Water": {"Grass": 1.25, "Electric": 1.25, "Steel": 0.8, "Fire": 0.8,
                    "Water": 0.8, "Ice": 0.8},
          "Grass": {"Flying": 1.25, "Poison": 1.25, "Bug": 1.25, "Fire": 1.25,
                    "Ice": 1.25, "Ground": 0.8, "Water": 0.8, "Grass": 0.8,
                    "Electric": 0.8},
          "Electric": {"Ground": 1.25, "Flying": 0.8, "Steel": 0.8,
                       "Electric": 0.8},
          "Psychic": {"Bug": 1.25, "Ghost": 1.25, "Dark": 1.25, "Fighting": 0.8,
                      "Psychic": 0.8},
          "Ice": {"Fighting": 1.25, "Rock": 1.25, "Steel": 1.25, "Fire": 1.25,
                  "Ice": 1.25},
          "Dragon": {"Ice": 1.25, "Dragon": 1.25, "Fairy": 1.25, "Fire": 0.8,
                     "Grass": 0.8, "Water": 0.8, "Electric": 0.8},
          "Dark": {"Fighting": 1.25, "Bug": 1.25, "Fairy": 1.25, "Ghost": 0.8,
                   "Psychic": 0.8},
          "Fairy": {"Poison": 1.25, "Steel": 1.25, "Fighting": 0.8, "Bug": 0.8,
                    "Dark": 0.8, "Dragon": 0.8}}

def hae_kerroin(hyökkäyksen_tyyppi, pokemonin_tyyppi):
    """
    Etsii tietorakenteesta tiedon siitä kuinka paljon vahinkoa
    tietyn tyyppinen hyökkäys tekee Pokemonille.
    :param hyökkäyksen_tyyppi: Merkkijono
    :param pokemonin_tyyppi:   Merkkijono
    :return: Palauttaa kertoimen vahingon määrälle.
    """
    if pokemonin_tyyppi in TYYPIT:

        if hyökkäyksen_tyyppi in TYYPIT[pokemonin_tyyppi]:
            return TYYPIT[pokemonin_tyyppi][hyökkäyksen_tyyppi]

    return 1

class Pokemon:
    """ Kuvaa yhtä Pokemonia, joka koostuu nimestä, tyypeistä, osumapisteistä,
        tasosta ja liikkeistä."""

    def __init__(self, laji, tyypit, hp=50, level=20):
        """
        Luokan rakentaja. Tarkastaa että kesto ja taso ovat järkeviä, ja
        tallentaa tiedot.

        :param laji:   Pokemonin laji
        :param tyypit: Pokemonin tyypit
        :param hp:     Pokemonin kestopisteiden määrä
        :param level:  Millä tasolla Pokemon on
        """

        self.__laji = laji.capitalize()
        self.__tyypit = tyypit

        if not isinstance(hp, int) or not isinstance(level, int) \
                or hp < 0 or level < 1:
            raise ValueError

        self.__hp = hp
        self.__max_hp = hp
        self.__level = level
        self.__liikkeet = {}

    def tulosta(self):
        """
        Tulostaa Pokemonin muodossa laji, tyypit, jäljellä olevat osumapisteet.
        """
        print(self.__laji, ", ", self.__hp, "hp", ", Types: ",
              ", ".join(self.__tyypit), sep="")
        print()

    def paranna(self,parametri):
        try:
            if int(parametri) > 0:
                hipaalussa = self.__hp
                self.__hp =int( self.__hp + parametri)

                if self.__hp >= self.__max_hp:
                    self.__hp = self.__max_hp
                hipalopussa = self.__hp
                print("{:1s} was healed for {} hp.".format(self.__laji,abs(hipalopussa - hipaalussa)))

                return True
            else:
                return False
        except:

                return False

    def vahingoita(self,parametri):
        try:
            if int(parametri) > 0:
                hipaalussa = self.__hp
                self.__hp = int( self.__hp - parametri)
                if self.__hp <= 0:
                    self.__hp = 0
                hipalopussa = self.__hp
                print("{:1s} lost {} hp.".format(self.__laji,hipaalussa-hipalopussa))
                if self.__hp <= 0:
                    self.__hp = 0
                    print("{:1s} fainted!".format(self.__laji))
                return True

            else:
                return False
        except:
            return False

    def aseta_tyypit(self,tyypit):
        uudettyypit = []
        for alkio in tyypit:
            if alkio.capitalize() in TYYPIT:
                uudettyypit.append(alkio.capitalize())
            else:
                return False


        self.__tyypit = uudettyypit
        return True


    def lisää_tyyppi(self,tyyppi):
        if tyyppi.capitalize() in TYYPIT:
            vanhattyypit = []
            for alkio in self.__tyypit:
                vanhattyypit.append(alkio.capitalize())
            vanhattyypit.append(tyyppi.capitalize())
            self.__tyypit = vanhattyypit
            return True
        else:
            return False

    def lisää_liike(self,nimi,power,type):
        if len(self.__liikkeet) < 2:
            self.__liikkeet[nimi.title()]={}
            self.__liikkeet[nimi.title()][power]=str(type)

            return True
        else:
            return False

    def tulosta_liikkeet(self):
        print("{:1s}'s moves:".format(self.__laji))
        for liike in sorted(self.__liikkeet):
            nimi = liike
            for voima in self.__liikkeet[liike]:
                power = voima
                tyyppi = self.__liikkeet[liike][power]
                type = tyyppi
                print("{}, {}, {:1s}".format(nimi, power, type))
        print()

    def hyökkää(self,iskunnimi,kohde):
        if (iskunnimi.title() in self.__liikkeet) and (self.__hp != 0):
            nimi = iskunnimi.title()
            for voima in self.__liikkeet[nimi]:
                power = int(voima)
                tyyppi = self.__liikkeet[nimi][power]
                type = tyyppi

            print("{} used {}.".format(self.__laji,nimi))


            #etsitään kerroin
            #Haetaan pokemonin jokaisen tyypin kerroin ja kerrotaan ne yhteen
            kerroin = 1
            for pokemontyyppi in kohde.__tyypit:
                kerroin = kerroin * hae_kerroin(type,pokemontyyppi)
            if kerroin > 1:
                print("It's super effective!")
            if kerroin < 1:
                print("It's not very effective.")
            kohde.vahingoita(kerroin*int(power))
            print()
            return True
        elif self.__hp == 0:
            print("Pokemon has fainted and can't attack.")
            return False
        else:
            return False

