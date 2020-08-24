# TIE-02100 Johdatus ohjelmointiin
# Ohjelmakoodipohja debuggerin testaamista varten

def onko_aikuinen(syntymävuosi):
    ikä = 2015 - syntymävuosi
    if ikä >= 18:
        return True
    else:
        return False


def main():

    viljon_syntymävuosi = 1947
    emilian_syntymävuosi = 1999

    viljo_aikuinen = onko_aikuinen(viljon_syntymävuosi)
    emilia_aikuinen = onko_aikuinen(emilian_syntymävuosi)

    print("Viljo aikuinen:", viljo_aikuinen)
    print("Emilia aikuinen:", emilia_aikuinen)

main()
