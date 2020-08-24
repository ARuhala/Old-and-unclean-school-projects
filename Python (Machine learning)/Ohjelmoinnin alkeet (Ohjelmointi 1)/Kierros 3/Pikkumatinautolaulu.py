# Johdatus ohjelmointiin
# Koodipohja laulu b


def tulosta_säkeistö(a,b):
    for i in range(3):
        print("pikku-matin autosta on",a)
    print(b)
    print()


def main():

    tulosta_säkeistö("kumi puhjennut", "purukumilla me paikkaamme sen")
    tulosta_säkeistö("lasi särkynyt", "muovipussilla me korjaamme sen")
    tulosta_säkeistö("ovi irronnut", "jeesusteipillä me kiinnitämme sen")
    tulosta_säkeistö("vilkku rikkunut", "taskulampulla me korvaamme sen")


main()