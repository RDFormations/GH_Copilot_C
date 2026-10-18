def verifier():
    lues = lire_factures("factures.csv")
    reelles = [item for item in lues if item.id != -1]
    if len(reelles) != 15 or lues[-1].id != -1:
        raise SystemExit("le tableau lu doit contenir 15 factures puis id -1")

    journal = [
        Facture(1, "FAC-1042"),
        Facture(2, "FAC-1043"),
        Facture(3, "FAC-1044"),
        Facture(4, "FAC-1045"),
    ]
    comptabiliser("factures.csv", journal)
    ids = [item.id for item in journal]
    if ids != list(range(1, 16)):
        raise SystemExit("attendu : les ids 1 à 15, dans l'ordre")
    for deja in range(1, 5):
        if ids.count(deja) != 1:
            raise SystemExit(f"la facture {deja} ne doit apparaître qu'une fois")

    for item in journal:
        print(item.id, item.reference)
    print("ok")


if __name__ == "__main__":
    verifier()
