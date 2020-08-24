def main():
    mittaustenmäärä_str=input("Syötä mittausten lukumäärä: ")
    mittaustenmäärä=int(mittaustenmäärä_str)
    if mittaustenmäärä > 0:
        kierrosluku = 1
        näytepilalla = 0
        kaksiputkeen = 0
        while kierrosluku <= mittaustenmäärä:
            #Otetaan mittausten määrän verran kierroksia joilla:
            #katsotaan sopimattomien suhde mittaustenmäärään (10% max -> pilalla)
                #toteutetaan tähän erillinen laskuri
            #katsotaan tuliko 2 sopimatonta putkeen ( ->pilalla)
                # toteutetaan tähän erillinen laskuri
            #jos ei kumpaakaan näistä satu -> onnistui -> erillinen lopetus
            mittaustulos_str=input("Syötä {:1d}. mittaustulos: ".format(kierrosluku))
            mittaustulos=int(mittaustulos_str)
            kierrosluku = kierrosluku + 1
            #Jos mittaustulos on sopiva eli 20-25
            #Jos Erikoislopetus: aivan viimeinen syöte on sopimaton
            if (20 <= mittaustulos <= 25):
                kaksiputkeen = 0
                if kierrosluku == mittaustenmäärä +1:
                    onnistui=True

            #Jos mittaustulos ei ole sopiva
            elif not (20 <=mittaustulos <= 25):
                #kaksiputkeen laskuri
                kaksiputkeen = kaksiputkeen +1
                #10% laskuri
                näytepilalla=näytepilalla +1
                kymppilaskuri = näytepilalla / mittaustenmäärä
                #Jos 10% täynnä tai 2 putkeen, suoritetaan epäonnistumislopetus
                if kymppilaskuri > 0.1 or kaksiputkeen == 2:
                    print("Viinisi on pilalla.")
                    onnistui = False
                    #pakotetaan lopetus
                    kierrosluku = mittaustenmäärä +1
                #lopetus jossa viimeinen oli yli rajan, mutta 10% ei mennyt yli
                elif kierrosluku==mittaustenmäärä +1:
                    onnistui = True



        if onnistui==True:
            print("Viinisi on hyvää.")



    else:
        print("Mittausten lukumäärän tulee olla positiivinen kokonaisluku.")

main()