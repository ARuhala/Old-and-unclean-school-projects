def vokaalilaskuri(sana):
    vokaalilista = "aeiouyäöAEIOUYÄÖ"
    vokaalienmäärä = 0
    for a in sana:
        if a in vokaalilista:
            vokaalienmäärä = vokaalienmäärä + 1
    return vokaalienmäärä

def konsonanttilaskuri (sana,vokaalienmäärä):
    konsonanttienmäärä = len(sana) - vokaalienmäärä
    return konsonanttienmäärä

def main():
    sana = input("Syötä sana: ")
    vokaalit=vokaalilaskuri(sana)
    konsonantit=konsonanttilaskuri(sana,vokaalit)

    print("Sana {:1s} sisältää {:1d} vokaalia ja {:1d} konsonanttia".format(sana,vokaalit,konsonantit))

main()