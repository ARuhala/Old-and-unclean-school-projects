def listaaja(montakolukua):
    lista=[]
    for i in range (montakolukua):
        arvo=int(input())
        lista.append(arvo)
    return lista

def main():
    montakolukua=int(input("Kuinka monta lukua haluat käsitellä: "))
    print("Syötä {:1d} kpl lukuja:".format(montakolukua))
    lista=listaaja(montakolukua)
    mitäetsitään=int(input("Syötä etsittävä luku: "))
    montako=lista.count(mitäetsitään)
    if montako == 0:
        print("{:1d} ei esiinny syöttämiesi lukujen joukossa.".format(mitäetsitään))
    else:
        print("{:1d} esiintyy syöttämiesi lukujen joukossa {:1d} kertaa.".format(mitäetsitään,montako))
main()