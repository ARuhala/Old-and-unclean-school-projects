def main():
    päivä=1
    kuukausi=1
    while kuukausi<=12:
            if kuukausi == 1 or kuukausi == 3 or kuukausi == 5 or kuukausi == 7 or kuukausi == 8 or kuukausi == 10 or kuukausi == 12:
                print(päivä,".",kuukausi,".",sep="")
                päivä = päivä+1
                if päivä == 31:
                    print(päivä, ".", kuukausi, ".", sep="")
                    kuukausi=kuukausi+1
                    päivä=1
            elif kuukausi == 4 or kuukausi == 6 or kuukausi == 9 or kuukausi == 11:
                print(päivä,".",kuukausi,".",sep="")
                päivä = päivä+1
                if päivä == 30:
                    print(päivä, ".", kuukausi, ".", sep="")
                    kuukausi=kuukausi+1
                    päivä=1
            elif kuukausi == 2:
                print(päivä,".",kuukausi,".",sep="")
                päivä = päivä+1
                if päivä == 28:
                    print(päivä, ".", kuukausi, ".", sep="")
                    kuukausi=kuukausi+1
                    päivä=1
main()




