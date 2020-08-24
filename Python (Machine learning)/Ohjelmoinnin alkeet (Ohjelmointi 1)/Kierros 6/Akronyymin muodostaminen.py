def tee_akronyymi(a):
    splita = a.split()
    akronyymi = ""
    for alkio in splita:
        merkkialkionindeksi = splita.index(alkio)
        merkkialkio = splita[merkkialkionindeksi]
        isomerkkialkio = merkkialkio.upper()
        isomerkkialkionekakirjain = isomerkkialkio[0]
        akronyymi = akronyymi + isomerkkialkionekakirjain
    return akronyymi