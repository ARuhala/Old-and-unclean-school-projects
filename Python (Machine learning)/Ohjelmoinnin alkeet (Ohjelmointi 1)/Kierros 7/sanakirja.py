# TIE-02100 Johdatus ohjelmointiin
# Tehtävä: sanakirja, ohjelmakoodipohja


def main():
    suomi_espanja = {"moi": "hola", "kiitos": "gracias", "ranta": "playa"}
    pilkku = ", "
    print("Sanakirjan sisältö:")
    sisältö=pilkku.join(sorted(suomi_espanja))
    print(sisältö)
    while True:
        komento = input("[S]ana/[L]isää/[P]oista/[T]ulosta/[K]äännä/[Q]uit: ")

        if komento == "S":
            sana = input("Syötä käännettävä sana: ")
            if sana in suomi_espanja:
                print(sana, "espanjaksi on", suomi_espanja[sana])
            else:
                print("Sanaa", sana, "ei löydy sanakirjasta.")

        elif komento == "L":
            suomeksi = input("Syötä lisättävä sana suomeksi: ")
            espanjaksi = input("Syötä lisättävä sana espanjaksi: ")
            suomi_espanja[suomeksi] = espanjaksi
            print("Sanakirjan sisältö:")
            sisältö = pilkku.join(sorted(suomi_espanja))
            print(sisältö)

        elif komento == "P":
            poistettava = input("Syötä poistettava sana suomeksi: ")
            if poistettava in suomi_espanja:
                del suomi_espanja[poistettava]
            else:
                print("Sanaa", poistettava, "ei löydy sanakirjasta.")

        elif komento == "T":
            print()
            print("Suomi-espanja:")
            for alkio in sorted(suomi_espanja):
                print("{:1s} {:1s}".format(alkio,suomi_espanja[alkio]))
            print()


            print("Espanja-suomi:")

            espanja_suomi={}
            for alkio in suomi_espanja:
                suomeksi=alkio
                espanjaksi=suomi_espanja[alkio]
                espanja_suomi[espanjaksi]=alkio

            for alkio in sorted(espanja_suomi):
                print("{:1s} {:1s}".format(alkio, espanja_suomi[alkio]))

            print()

        elif komento == "K":
            inputti = input("Syötä käännettävä teksti suomeksi: ")
            splitlista = inputti.split()
            käännettylause=""
            for sana in splitlista:
                if sana in suomi_espanja:
                    käännettylause=käännettylause+suomi_espanja[sana]
                else:
                    käännettylause=käännettylause + sana
                if not ( sana == splitlista[-1]):
                    käännettylause = käännettylause + " "
            print("Teksti sanakirjan varassa käännettynä:")
            print(käännettylause)

        elif komento == "Q":
            print("Adios!")
            return

        else:
            print("Virheellinen komento, syötä joko S, L, P, T, K tai Q!")


main()
