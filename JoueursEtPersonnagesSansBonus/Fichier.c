#include "JoueursPerso.h"

CodeErreur sauverJoueurs(Joueur* pDebJoueurs) {
	CodeErreur codeErreur;
	FILE* pFiJoueurs;

	fopen_s(&pFiJoueurs, FIJOUEURS, "wb");
	if (pFiJoueurs == NULL)
		codeErreur = FICHIER_INEXISTANT;
	else {
		codeErreur = PAS_D_ERREUR;
		EnregJoueur joueur;
		Joueur* pJoueur = pDebJoueurs;
		while (pJoueur != NULL) {
			strcpy_s(joueur.pseudo, TPSEUDO, pJoueur->pseudo);
			joueur.nbPersonnages = nbrPersonnages(pJoueur);
			fwrite(&joueur, sizeof(joueur), 1, pFiJoueurs);
			Personnage* pPerso = pJoueur->pDebPersonnages;
			while (pPerso != NULL) {
				EnregPerso perso;
				strcpy_s(perso.nom, TNOM, pPerso->nom);
				perso.points = pPerso->points;
				fwrite(&perso, sizeof(perso), 1, pFiJoueurs);
				pPerso = pPerso->pSuiv;
			}
			pJoueur = pJoueur->pSuiv;
		}
		fclose(pFiJoueurs);
	}
	return codeErreur;
}

CodeErreur fichierExiste(void) {
	FILE* pFiJoueurs;
	CodeErreur codeErreur = PAS_D_ERREUR;

	fopen_s(&pFiJoueurs, FIJOUEURS, "rb");
	if (pFiJoueurs == NULL)
		codeErreur = FICHIER_INEXISTANT;
	else
		fclose(pFiJoueurs);
	return codeErreur;
}

CodeErreur chargerJoueurs(Joueur** pDebJoueurs) {
	FILE* pFiJoueurs;
	CodeErreur codeErreur = PAS_D_ERREUR;

	fopen_s(&pFiJoueurs, FIJOUEURS, "rb");
	if (pFiJoueurs == NULL)
		codeErreur = FICHIER_INEXISTANT;
	else {
		Joueur* pJoueur = NULL;
		Joueur* pSauvJoueur = NULL;
		
		bool allocationOK = true;
		EnregJoueur joueur;
		EnregPerso perso;

		*pDebJoueurs = NULL;

		fread_s(&joueur, sizeof(joueur), sizeof(joueur), 1, pFiJoueurs);
		while (!feof(pFiJoueurs) && allocationOK) {
			Joueur* pNouvJoueur;
			allocationOK = nouveauJoueur(&pNouvJoueur);
			if (!allocationOK) {
				codeErreur = ALLOCATION_MEMOIRE;
			}
			else {
				Personnage* pNouvPerso;
				codeErreur = PAS_D_ERREUR;
				ajouteJoueur(pDebJoueurs, joueur.pseudo, pNouvJoueur,pJoueur, pSauvJoueur);
				pSauvJoueur = pNouvJoueur;

				int iPerso = 0;
				while (iPerso < joueur.nbPersonnages && allocationOK) {
					allocationOK = nouveauPersonnage(&pNouvPerso);
					if (!allocationOK)
						codeErreur = ALLOCATION_MEMOIRE;
					else {
						codeErreur = PAS_D_ERREUR;
						fread_s(&perso, sizeof(perso), sizeof(perso), 1, pFiJoueurs);
						ajoutePersonnage(pNouvJoueur, perso.nom, perso.points, pNouvPerso);
						iPerso++;
					}
				}
				if (allocationOK) {
					fread_s(&joueur, sizeof(joueur), sizeof(joueur), 1, pFiJoueurs);
				}
			}
		}
		fclose(pFiJoueurs);
	}
	return codeErreur;
}