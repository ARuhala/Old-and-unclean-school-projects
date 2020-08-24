def main():
    viidensarja=[]
    print("Anna 5 lukua:")
    for i in range (5):
        arvo=int(input("Seuraava luku: "))
        viidensarja.append(arvo)
    print("Syöttämäsi nollaa suuremmat luvut olivat:")
    for i in range (5):
        if viidensarja[i]>0:
            print(viidensarja[i])
main()
