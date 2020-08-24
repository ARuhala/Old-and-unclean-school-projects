def main():
    viidensarja=[]
    print("Anna 5 lukua:")
    for i in range (5):
        arvo=int(input("Seuraava luku: "))
        viidensarja.append(arvo)
    print("Syöttämäsi luvut päinvastaisessa järjestyksessä:")
    for i in range(4,-1,-1):
        print(viidensarja[i])
main()