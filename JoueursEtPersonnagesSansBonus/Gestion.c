#include "JoueursPerso.h"

bool nouveauJoueur(Joueur** pNouvJoueur) {
	*pNouvJoueur = (Joueur*)malloc(sizeof(Joueur));
	return (*pNouvJoueur != NULL);
}

bool nouveauPersonnage(Personnage** pNouvPerso) {
	*pNouvPerso = (Personnage*)malloc(sizeof(Personnage));
	return (*pNouvPerso != NULL);
}

bool joueurExiste(Joueur* pDebJoueurs, char pseudo[], Joueur** pJoueur, Joueur** pSauvJoueur) {
	*pJoueur = pDebJoueurs;
	while (*pJoueur != NULL && strcmp(pseudo, (*pJoueur)->pseudo) > 0) {
		*pSauvJoueur = *pJoueur;
		*pJoueur = (*pJoueur)->pSuiv;
	}
	return *pJoueur != NULL && strcmp(pseudo, (*pJoueur)->pseudo) == 0;
}

bool personnageExiste(Joueur* pDebJoueurs, char nom[]) {
	Joueur* pJoueur;
	bool persoExiste = false;
	pJoueur = pDebJoueurs;
	while (pJoueur != NULL && !persoExiste) {
		Personnage* pPerso = pJoueur->pDebPersonnages;
		while (pPerso != NULL && strcmp(nom, pPerso->nom) != 0)
			pPerso = pPerso->pSuiv;
		persoExiste = pPerso != NULL && strcmp(nom, pPerso->nom) == 0;
		pJoueur = pJoueur->pSuiv;
	}
	return persoExiste;
}

void libèreJoueur(Joueur* pJoueur) {
	free(pJoueur);
}

void libèrePersonnage(Personnage* pPerso) {
	free(pPerso);
}

void ajouteJoueur(Joueur** pDebJoueurs, char pseudo[], Joueur* pNouvJoueur, Joueur* pJoueur, Joueur* pSauvJoueur) {
	strcpy_s(pNouvJoueur->pseudo, TPSEUDO, pseudo);
	pNouvJoueur->pDebPersonnages = NULL;
	if (pJoueur == *pDebJoueurs)
		*pDebJoueurs = pNouvJoueur;
	else
		pSauvJoueur->pSuiv = pNouvJoueur;
	pNouvJoueur->pSuiv = pJoueur;
}

void ajoutePersonnage(Joueur* pJoueur, char nom[], int points, Personnage* pNouvPerso) {
	strcpy_s(pNouvPerso->nom,TNOM ,nom);
	pNouvPerso->points = points;
	pNouvPerso->pSuiv = pJoueur->pDebPersonnages;
	pJoueur->pDebPersonnages = pNouvPerso;
}

void listeJoueurs(Joueur* pDebJoueurs) {
	Joueur* pJoueur;
	pJoueur = pDebJoueurs;
	while (pJoueur != NULL) {
		printf("%s", pJoueur->pseudo);
		Personnage* pPerso = pJoueur->pDebPersonnages;
		while (pPerso != NULL) {
			printf("\t%s : %d points\n", pPerso->nom, pPerso->points);
			pPerso = pPerso->pSuiv;
		}
		pJoueur = pJoueur->pSuiv;
	}
}

int nbrPersonnages(Joueur* pJoueur) {
	int nbPerso = 0;
	Personnage* pPerso = pJoueur->pDebPersonnages;
	while (pPerso != NULL) {
		nbPerso++;
		pPerso = pPerso->pSuiv;
	}
	return nbPerso;
}

void libèreJoueursPersonnages(Joueur* pDebJoueurs) {
	Joueur* pJoueur = pDebJoueurs;
	while (pJoueur != NULL) {
		Personnage* pPerso = pJoueur->pDebPersonnages;
		while (pPerso != NULL) {
			Personnage* pSauvPerso = pPerso;
			pPerso = pPerso->pSuiv;
			libèrePersonnage(pSauvPerso);
		}
		Joueur* pSauvJoueur = pJoueur;
		pJoueur = pJoueur->pSuiv;
		libèreJoueur(pSauvJoueur);
	}
}