#include "Gestion.h"
	
bool joueurExiste(Joueur * pDebJoueurs, char * pseudo,
					Joueur ** pJoueur, Joueur ** pSauvJoueur){	
	Joueur * pJoueurTrouv� = pDebJoueurs;
	//OU *pJoueurTrouv� = pDebJoueurs; 
	//   en rempla�ant tous les pJoueur par (*pJoueurTrouv�)
	while(pJoueurTrouv� != NULL && strcmp(pseudo, pJoueurTrouv�->pseudo) > 0) {
		*pSauvJoueur = pJoueurTrouv�;
		pJoueurTrouv� = pJoueurTrouv�->pSuiv;
	}
	*pJoueur = pJoueurTrouv�;
	return pJoueurTrouv� != NULL && strcmp(pseudo, pJoueurTrouv�->pseudo) == 0;
}

bool nouveauJoueur(Joueur * * pNouvJoueur) {
	*pNouvJoueur = (Joueur *)malloc(sizeof(Joueur));
	return *pNouvJoueur != NULL;
}

void libererJoueur(Joueur * pJoueur) {
	free(pJoueur);
}

//ordre alphab�tique pseudo
Joueur * ajouteJoueur(Joueur * pDebJoueurs, char * pseudo,
		Joueur * pNouvJoueur, Joueur * pJoueur, Joueur * pSauvJoueur) {
	strcpy_s(pNouvJoueur->pseudo, TPSEUDO, pseudo);
	pNouvJoueur->pDebPersonnages = NULL;

	if (pJoueur == pDebJoueurs) {
		pDebJoueurs = pNouvJoueur;
	} else {
		pSauvJoueur->pSuiv = pNouvJoueur;
	}
	pNouvJoueur->pSuiv = pJoueur;
	return pDebJoueurs;
}

bool personnageExiste(Joueur * pJoueur, char * nom, 
							Personnage * * pPerso, Personnage * * pSauvPerso) {
	Personnage * pPersoTrouv� = pJoueur->pDebPersonnages;
	while (pPersoTrouv� != NULL && strcmp(nom, pPersoTrouv�->nom) != 0) {
		*pSauvPerso = pPersoTrouv�;
		pPersoTrouv� = pPersoTrouv�->pSuiv;
	}
	*pPerso = pPersoTrouv�;
	return pPersoTrouv� != NULL;
}

bool nouveauPersonnage(Personnage * * pNouvPerso) {
	*pNouvPerso = (Personnage *)malloc(sizeof(Personnage));
	return *pNouvPerso != NULL;
}

void libererPersonnage(Personnage * pPerso) {
	free(pPerso);
}

void ajoutePersonnage(Joueur * pJoueur, char * nom, int points, 
		Personnage * pNouvPerso, Personnage * pPerso, Personnage * pSauvPerso) {
	strcpy_s(pNouvPerso->nom, TNOM, nom);
	pNouvPerso->points = points;
	pNouvPerso->pSuiv = NULL;

	if (pJoueur->pDebPersonnages == NULL) {
		pJoueur->pDebPersonnages = pNouvPerso;
	} else {
		pSauvPerso->pSuiv = pNouvPerso;
	}
}

Joueur *  supprimeJoueur(Joueur * pDebJoueurs, Joueur * pJoueur, Joueur * pSauvJoueur) {
	Personnage * pPerso = pJoueur->pDebPersonnages;
	Personnage * pSauvPerso;
	while (pPerso != NULL) {	
		pSauvPerso = pPerso->pSuiv;
		libererPersonnage(pPerso);
		//supprimePersonnage(pJoueur, pPerso, NULL);
		pPerso = pSauvPerso;
	}
	if (pJoueur == pDebJoueurs) {
		pDebJoueurs = pJoueur->pSuiv;
	} else {
		pSauvJoueur->pSuiv = pJoueur->pSuiv;
	}
	libererJoueur(pJoueur);
	return pDebJoueurs;
}

/*void supprimePersonnage(Joueur * pJoueur, Personnage * pPerso, Personnage * pSauvPerso) {
	if (pPerso == pJoueur->pDebPersonnages) {
		pJoueur->pDebPersonnages = pPerso->pSuiv;
	} else {
		pSauvPerso->pSuiv = pPerso->pSuiv;
	}
	free(pPerso);
}*/

void listeJoueurs(Joueur * pDebJoueurs){	
	Joueur * pJoueur = pDebJoueurs;
	while (pJoueur != NULL) {
		Personnage * pPerso;
		puts(pJoueur->pseudo);
		pPerso = pJoueur->pDebPersonnages;
		while (pPerso != NULL) {
			printf("--> %s (%d)\n", pPerso->nom, pPerso->points);
			pPerso = pPerso->pSuiv;
		}
		pJoueur = pJoueur->pSuiv;
		if (pJoueur != NULL) {
			puts("--------------------------------------------------");
		}
	}
}

int nbPersonnages(Joueur * pJoueur){
	int nbrPerso = 0;
	Personnage * pPerso = pJoueur->pDebPersonnages;
	while (pPerso != NULL) {
		nbrPerso++;
		pPerso = pPerso->pSuiv;
	}
	return nbrPerso;
}

void libereJoueurs(Joueur * pDebJoueurs) {
	Joueur * pJoueur;
	Joueur * pSauvJoueur;

	pJoueur = pDebJoueurs;
	while (pJoueur != NULL) {
		pSauvJoueur = pJoueur->pSuiv;
		pDebJoueurs = supprimeJoueur(pDebJoueurs, pJoueur, pSauvJoueur);
		pJoueur = pSauvJoueur;
	}
}
