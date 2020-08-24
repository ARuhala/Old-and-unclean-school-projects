def main():
    päivä=1
    kuukausi=1
    plaskuri=5
    while kuukausi<=12:
            if kuukausi == 1 or kuukausi == 3 or kuukausi == 5 or kuukausi == 7 or kuukausi == 8 or kuukausi == 10 or kuukausi == 12:
                plaskuri = plaskuri + 1
                päivä = päivä + 1
                if plaskuri % 7 == 0 and päivä !=31:
                    print(päivä,".",kuukausi,".",sep="")
                if päivä==31:
                    if plaskuri % 7 == 0:
                        print(päivä, ".", kuukausi, ".", sep="")
                    kuukausi=kuukausi+1
                    päivä=1
                    plaskuri=plaskuri +1
                    if plaskuri % 7 == 0:
                        print(päivä, ".", kuukausi, ".", sep="")
            elif kuukausi == 4 or kuukausi == 6 or kuukausi == 9 or kuukausi == 11:
                if plaskuri % 7 == 0 and päivä !=30:
                    print(päivä,".",kuukausi,".",sep="")
                päivä = päivä+1
                plaskuri = plaskuri+1
                if päivä == 30:
                    if plaskuri % 7 == 0:
                        print(päivä, ".", kuukausi, ".", sep="")
                    kuukausi=kuukausi+1
                    päivä=1
                    plaskuri=plaskuri+1
                    if plaskuri % 7 == 0:
                        print(päivä, ".", kuukausi, ".", sep="")
            elif kuukausi == 2:
                if plaskuri % 7 == 0 and päivä!=28:
                    print(päivä,".",kuukausi,".",sep="")
                päivä = päivä+1
                plaskuri=plaskuri+1
                if päivä == 28:
                    if plaskuri % 7 == 0:
                        print(päivä, ".", kuukausi, ".", sep="")
                    kuukausi=kuukausi+1
                    päivä=1
                    plaskuri=plaskuri+1
                    if plaskuri % 7 == 0:
                        print(päivä, ".", kuukausi, ".", sep="")
main()




