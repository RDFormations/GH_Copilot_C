NOM_MAX = 64


class Employe:
    def __init__(self, id=0, nom=""):
        self.id = id
        self.nom = nom


def compter_lignes(chemin):
    pass


def allouer_employes(nombre):
    pass


def remplir_employe(ligne, table, index):
    pass


def marquer_sentinelle(table, nombre):
    pass


def lire_employes(chemin):
    pass


def employe_existe(annuaire, employe):
    pass


def ajouter_employe(annuaire, employe):
    pass


def importer(chemin, annuaire):
    pass


def main():
    annuaire = [
        Employe(1, "Camille"),
        Employe(2, "Louis"),
        Employe(3, "Ines"),
        Employe(4, "Hugo"),
    ]
    importer("employes.csv", annuaire)
    ids = [employe.id for employe in annuaire]
    if ids != list(range(1, 16)):
        raise SystemExit("attendu : les ids 1 a 15, dans l'ordre")
    for employe in annuaire:
        print(employe.id, employe.nom)
    print("ok")


if __name__ == "__main__":
    main()
