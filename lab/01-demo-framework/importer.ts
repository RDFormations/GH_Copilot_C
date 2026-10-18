export const NOM_MAX = 64;

export type Employe = {
  id: number;
  nom: string;
};

export function compterLignes(chemin: string): number {
}

export function allouerEmployes(nombre: number): Employe[] {
}

export function remplirEmploye(ligne: string, table: Employe[], index: number): void {
}

export function marquerSentinelle(table: Employe[], nombre: number): void {
}

export function lireEmployes(chemin: string): Employe[] {
}

export function employeExiste(annuaire: Employe[], employe: Employe): boolean {
}

export function ajouterEmploye(annuaire: Employe[], employe: Employe): void {
}

export function importer(chemin: string, annuaire: Employe[]): void {
}

const annuaire: Employe[] = [
  { id: 1, nom: "Camille" },
  { id: 2, nom: "Louis" },
  { id: 3, nom: "Ines" },
  { id: 4, nom: "Hugo" },
];
importer("employes.csv", annuaire);
const ids = annuaire.map((employe) => employe.id);
const attendu = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15];
if (ids.length !== attendu.length || ids.some((id, index) => id !== attendu[index])) {
  throw new Error("attendu : les ids 1 a 15, dans l'ordre");
}
for (const employe of annuaire) {
  console.log(employe.id, employe.nom);
}
console.log("ok");
