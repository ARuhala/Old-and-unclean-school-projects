# TIE-02100 - Johdatus ohjelmointiin
# Hirsipuu
# Antti Ruhala, 253037



def aloituskysely():
    sana=input("Syötä arvuuteltava sana: ")
    print("Putsataan näyttö...")
    for i in range(10):
        print()
    #määritellään vastauskenttä
    pituus = len(sana)
    vastauskenttä = "_"*pituus
    return sana,vastauskenttä

def luo_vastauskenttälista(vastauskenttä):
    uusivastauskenttälistana = []
    for i in range(len(vastauskenttä)):
        uusivastauskenttälistana.append("tyhjä")
    return uusivastauskenttälistana

def arvauksentalletus(arvattava,arvaus,vastauskenttä,vastauskenttälistana):
    voittoarvo = False
    if arvaus.upper() in arvattava.upper():
        paikat=[]
        paikka=0
        for merkki in arvattava.upper():
            if merkki == arvaus.upper():
                paikat.append(paikka) #luo listan jossa on oikeiden arvausten paikat

            paikka = paikka + 1


        #luodaan uusi vastauskenttä, jossa oikeat kirjaimet sijoitettuna
        for i in range(len(vastauskenttä)):
            if i in paikat:
                vastauskenttälistana[i]=arvaus.upper()

        #sijoitetaan vastauskenttään uudet merkit
        vastauskenttä=""
        for merkki in vastauskenttälistana:
            if merkki == "tyhjä":
                vastauskenttä=vastauskenttä + "_"
            else:
                vastauskenttä=vastauskenttä + merkki.upper()
        #Katsotaan tuliko koko vastauskenttä täyteen
        if not("tyhjä" in vastauskenttälistana):
            voittoarvo = True
    return vastauskenttä,vastauskenttälistana,voittoarvo






def main():
    #määrittelee arvattavan sanan ja luo tyhjän vastauskentän, printtaa 10 tyhjää
    arvattava,vastauskenttä=aloituskysely()
    #luo tyhjän vastauskenttälistan joka on vastauskentän pituinen
    vastauskenttälistana=luo_vastauskenttälista(vastauskenttä)
    voittoarvo = False
    print("Peli alkakoon! Saat arvata 10 kirjainta. Mikä sana on kyseessä?")
    print(vastauskenttä)
    #lista edellisistä vastauksista
    edellisetvastaukset=[]

    for i in range (10):
        arvaus=input("Arvaa kirjain: ")
        if len(arvaus) != 1:
            print("Virhe: syötä yksi kirjain.")
        else:
            if arvaus.upper() in edellisetvastaukset:
                print("Hölmö arvaus, {:1s} on jo arvattu.".format(arvaus))
            else:
                vastauskenttä, vastauskenttälistana, voittoarvo = arvauksentalletus(arvattava, arvaus, vastauskenttä, vastauskenttälistana)
        # lisätään uusi arvaus edellisiin vastauksiin
        edellisetvastaukset.append(arvaus.upper())
        print(vastauskenttä)
        if voittoarvo==True:
            break
    if voittoarvo == False:
        print("Arvauskerrat loppuivat kesken. Sana olisi ollut",arvattava.upper())

    if voittoarvo == True:
        print("Hyvä! Arvasit koko sanan!")
main()