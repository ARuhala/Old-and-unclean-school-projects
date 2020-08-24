def main():
    rivi=input("Kuinka monta Fibonaccin lukua haluat: ")
    i=1
    kierrostenlkm=int(rivi)
    for i in range(kierrostenlkm+1):
         if i==0:
             c=1
         elif i==1:
            print(i, ".", " ", 1, sep="")
            a=1
            i=i+1
            c=1
         elif i==2:
             print(i, ".", " ", 1, sep="")
             b=1
             f=1
             i=i+1
             c=1
         else:
            f=c
            c=a + b
            print(i, ".", " ", c, sep="")
            a=c
            b=f
            i=i+1
main()

