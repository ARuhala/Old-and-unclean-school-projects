# Johdatus ohjelmointiin
# Koodipohja laulu c, saku sammakko
def ahaa(b):
    for i in range(b):
        print("ahaa")
def säkeistö(a,c):
    print(a)
    ahaa(2)
    print(a)
    ahaa(2)
    print(a)
    print(c)
    ahaa(3)
    print()


def main():
    säkeistö("saku sammakko kosiomatkallaan",
             "hän lauleli kauniita laulujaan")
    säkeistö("hän hillevi hiiren tavatessaan",
             "pyysi mukanaan tulemaan pappilaan")
    säkeistö("mikset kultasein kosinut aikanaan",
             "minut matias myyrälle naitetaan")
    säkeistö("sulle matias sovi ei laisinkaan",
             "sillä multaa on myyrällä varpaissaan")


main()