#include "Fichiers.h"

typedef struct persoFichier PersoFi;
struct persoFichier {
	char nom[TNOM];
	int points;
};

typedef struct joueurFichier JoueurFi;
struct joueurFichier {
	char pseudo[TPSEUDO];
	int nbPersonnages;
};

CodeErreur fichierExiste(void) {
	FILE * pFiJoueurs;
	fopen_s(&pFiJoueurs, FIJOUEURS, "rb");
	if (pFiJoueurs == NULL) return OUVERTURE_FICHIER;
	fclose(pFiJoueurs);
	return PAS_D_ERREUR;
}

CodeErreur sauverJoueurs(Joueur * pDebJoueurs) {
	FILE * pFiJoueurs;
	Joueur * pJoueur;
		
	fopen_s(&pFiJoueurs, FIJOUEURS, "wb");
	if (pFiJoueurs == NULL) {
		//perror("error");
		return OUVERTURE_FICHIER;
	}

	pJoueur = pDebJoueurs;
	while (pJoueur != NULL) {
		JoueurFi joueurAEcrire;
		Personnage * pPerso;

		strcpy_s(joueurAEcrire.pseudo, TPSEUDO, pJoueur->pseudo);
		joueurAEcrire.nbPersonnages = nbPersonnages(pJoueur);

		fwrite(&joueurAEcrire, sizeof(joueurAEcrire), 1, pFiJoueurs);

		pPerso = pJoueur->pDebPersonnages;
		while (pPerso != NULL) {
			PersoFi persoAEcrire;

			strcpy_s(persoAEcrire.nom, TNOM, pPerso->nom);
			persoAEcrire.points = pPerso->points;

			fwrite(&persoAEcrire, sizeof(persoAEcrire), 1, pFiJoueurs);

			pPerso = pPerso->pSuiv;
		}
		pJoueur = pJoueur->pSuiv;
	}
	fclose(pFiJoueurs);
	return PAS_D_ERREUR;
}

CodeErreur chargerJoueurs(Joueur * * pDebJoueurs) {
	FILE * pFiJoueurs;
	JoueurFi joueurLu;
	Joueur * pSauvJoueur = NULL;
	*pDebJoueurs = NULL;

	fopen_s(&pFiJoueurs, FIJOUEURS, "rb");
	if (pFiJoueurs == NULL) return OUVERTURE_FICHIER;

	fread_s(&joueurLu, sizeof(joueurLu), sizeof(joueurLu), 1, pFiJoueurs);
	while (!feof(pFiJoueurs)) {
		Joueur * pNouvJoueur;
		Personnage * pSauvPerso;
		int iPersos;

		if (!nouveauJoueur(&pNouvJoueur)) {
			fclose(pFiJoueurs);
			return ALLOCATION_MEMOIRE;
		}

		*pDebJoueurs = ajouteJoueur(*pDebJoueurs, joueurLu.pseudo, pNouvJoueur, NULL, pSauvJoueur);
		pSauvJoueur = pNouvJoueur;

		pSauvPerso = NULL;
		iPersos = 0;
		while (iPersos < joueurLu.nbPersonnages) {
			PersoFi persoLu;
			Personnage * pNouvPerso;

			if (!nouveauPersonnage(&pNouvPerso)) {
				fclose(pFiJoueurs);
				return ALLOCATION_MEMOIRE;
			}

			fread_s(&persoLu, sizeof(joueurLu), sizeof(joueurLu), 1, pFiJoueurs);

			ajoutePersonnage(pNouvJoueur, persoLu.nom, persoLu.points, pNouvPerso, NULL, pSauvPerso);
			pSauvPerso = pNouvPerso;
			iPersos++;
		}
		fread_s(&joueurLu, sizeof(joueurLu), sizeof(joueurLu), 1, pFiJoueurs);
	}
	fclose(pFiJoueurs);
	return PAS_D_ERREUR;
}