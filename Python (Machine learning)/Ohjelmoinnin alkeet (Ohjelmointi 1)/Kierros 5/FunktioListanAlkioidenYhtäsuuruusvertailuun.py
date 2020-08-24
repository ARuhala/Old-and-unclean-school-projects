
def ovatko_kaikki_alkiot_samoja(a):
    if a==[]or len(a)==1:
        return True
    c=a[1]
    for b in a:
        if b==c:
            if b==a[-1]:
                return True

            else:
                c=b
                continue


        elif b!=c:
            return False

