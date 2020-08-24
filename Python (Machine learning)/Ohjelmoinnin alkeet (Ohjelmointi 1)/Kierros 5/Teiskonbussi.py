aikataulu=[630,1015,1415,1620,1720,2000]

def etsiseuraavaaika(annettuaika):
    #Kun kellonaika on kysytty käyttäjältä, pitää etsiä tietorakenteesta se kohta (indeksi)
    # jossa on seuraavaksi lähtevän bussin aika.
    aikataulu = [630, 1015, 1415, 1620, 1720, 2000]
    if annettuaika <=630:
        return aikataulu[0]
    elif 630<annettuaika<=1015:
        return aikataulu[1]
    elif 1015<annettuaika<=1415:
        return aikataulu[2]
    elif 1415<annettuaika<=1620:
        return aikataulu[3]
    elif 1620<annettuaika<=1720:
        return aikataulu[4]
    elif 1720<annettuaika<=2000:
        return aikataulu[5]
    elif 2000<annettuaika:
        return aikataulu[0]

def tulostin(seuraavaaika):
    aikataulu = [630, 1015, 1415, 1620, 1720, 2000]
    seuraavani=int(aikataulu.index(seuraavaaika))
    tulostuskerroin=0
    print("Seuraavat bussivuorot lähtevät:")

    for i in range(seuraavani,seuraavani+3,1):
        tulostuskerroin=tulostuskerroin+1
        print(aikataulu[i])
        if i == 5:
            for i in range(0, 3-tulostuskerroin, 1):
                print(aikataulu[i])

            return



def main():
    annettuaika=int(input("Mitä kello on nyt? (kokonaislukuna): "))
    seuraavaaika=etsiseuraavaaika(annettuaika)
    tulostin(seuraavaaika)

main()