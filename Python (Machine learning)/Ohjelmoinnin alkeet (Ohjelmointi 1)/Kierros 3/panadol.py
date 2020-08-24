# Johdatus ohjelmointiin
# Koodipohja parasetamolin annosmÃ¤Ã¤rÃ¤n laskua varten

def laske_annos(potilaanpaino,aikaedellisestä,aiempivuorokausiannos):
        grammoja=potilaanpaino*15
        päivänmaksimi=4000
        erotus=päivänmaksimi-grammoja
        if aikaedellisestä<6:
            return 0
        elif aikaedellisestä>=6:
            if aiempivuorokausiannos + grammoja > päivänmaksimi:
                return päivänmaksimi - aiempivuorokausiannos
            elif aiempivuorokausiannos + grammoja <= päivänmaksimi:
                return grammoja
def inputti(x):
    syöte=int(input(x))
    while syöte<0:
        syöte = int(input(x))
    return syöte

def main():
    potilaanpaino=int(inputti("Potilaan paino (kg): "))
    aikaedellisestä=int(inputti("Kauanko aikaa edellisestä annoksesta (tasatunteina): "))
    aiempivuorokausiannos=int(inputti("Kokonaisannos viimeisen 24 tunnin aikana (mg): "))
    annos=laske_annos(potilaanpaino,aikaedellisestä,aiempivuorokausiannos)
    print("Potilaalle voi antaa parasetamolia:",annos)
main()