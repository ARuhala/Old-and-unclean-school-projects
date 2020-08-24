# TIE-02100 Johdatus ohjelmointiin
# Tehtävä: ristinolla, ohjelmakoodipohja
lauta=[[".",".","."],[".",".","."],[".",".","."]]
merkki="x"
def voittotarkastus():
    if lauta[0][1] == lauta[0][2] == lauta [0][0] and lauta[0][0] != ".":

        return True
    elif lauta[1][1] == lauta[1][2] == lauta [1][0] and lauta[1][0] != ".":

        return True
    elif lauta[2][1] == lauta[2][2] == lauta [2][0] and lauta[2][0] != ".":

        return True
    elif lauta[0][0] == lauta[0][1] == lauta [0][2] and lauta[0][0] != ".":

        return True
    elif lauta[1][0] == lauta[1][1] == lauta [1][2] and lauta[1][0] != ".":

        return True
    elif lauta[2][0] == lauta[2][1] == lauta[2][2] and lauta[2][0] != ".":

        return True
    elif lauta[0][0] == lauta[1][1] == lauta [2][2] and lauta[0][0] != ".":

        return True
    elif lauta[2][0] == lauta[1][1] == lauta[0][2] and lauta[2][0] != ".":

        return True
    else:
        return False
def main():

    # TODO luo pelilaudan tietorakenne
    lauta=[[".",".","."],[".",".","."],[".",".","."]]
    print("".join(lauta[0]))
    print("".join(lauta[1]))
    print("".join(lauta[2]))
    vuorot = 0  # Pelattujen vuorojen määrä

    # Peli jatkuu kunnes ruudukko on täynnä.
    # 8 vuoron vaihdon jälkeen laudalle on laitettu 9 merkkiä.
    while vuorot < 9:

        # Päivitetään merkki vuoron mukaan
        if vuorot % 2 == 0:
            merkki = "X"
        else:
            merkki = "O"
        koordinaatit = input("Pelaaja " + merkki + " anna koordinaatit: ")

        try:
            x, y = koordinaatit.split(" ")
            x = int(x)
            y = int(y)

            # TODO toteuta pelaajan vuoro
            while lauta[y][x] != ".":
                    print("Virhe: ruutuun on jo pelattu.")
                    koordinaatit = input("Pelaaja " + merkki + " anna koordinaatit: ")

                    try:
                        x, y = koordinaatit.split(" ")
                        x = int(x)
                        y = int(y)
                    except ValueError:
                        print(
                            "Virhe: syötä kaksi kokonaislukua välilyönnillä erotettuna.")

                    except IndexError:
                        print("Virhe: koordinaattien oltava välillä 0-2.")

            lauta[y][x] = merkki
            print("".join(lauta[0]))
            print("".join(lauta[1]))
            print("".join(lauta[2]))
            vuorot=vuorot+1
            totuus=voittotarkastus()
            if totuus==True:
                print("Peli loppui, voittaja on ", merkki)
                break
        except ValueError:
            print("Virhe: syötä kaksi kokonaislukua välilyönnillä erotettuna.")

        except IndexError:
            print("Virhe: koordinaattien oltava välillä 0-2.")


main()
