def main():
    try:
        nimi1 = input("Syötä luettavan tiedoston nimi: ")
        lukutiedosto = open(nimi1,"r",encoding="utf-8")

        #tallentaa tiedoston sisällön listaan
        lista=[]
        for rivi in lukutiedosto:
            lista.append(rivi)


    except:
        print("Virhe tiedoston lukemisessa!")

    #tekee listan jota muutetaan
    käsittelylista = lista[1:]
    aikalista = []
    for alkio in käsittelylista:
        osat=alkio.split(";")
        #osa 0 on aikaa
        ajateritelty=osat[0].split(":")
        osat[0] = int(ajateritelty[0]) * 60 * 60 + int(ajateritelty[1]) * 60 + int(ajateritelty[2])
        index=käsittelylista.index(alkio)
        käsittelylista[index]="{:1d};{:1s};{:1s};{:1s}".format(osat[0],osat[1],osat[2],osat[3])

    #lisätään otsikko takaisin listaan
    käsittelylista.insert(0,lista[0])



    nimi2 = input("Syötä kirjoitettavan tiedoston nimi: ")
    kirjoitustiedosto = open(nimi2,"w",encoding="utf-8")
    for alkio in käsittelylista:
        kirjoitustiedosto.write("{:1s}".format(alkio))
    lukutiedosto.close()
    kirjoitustiedosto.close()
    print("Tietojen tallennus onnistui.")



main()

