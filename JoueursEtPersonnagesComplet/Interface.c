#include "Interface.h"

int optionChoisie(Message * pLexique, int numMenu);

CodeErreur chargerJoueursPersonnages(Message * pLexique, Joueur ** pDebJoueurs);
CodeErreur ajouterJoueurPersonnages(Message * pLexique, Joueur ** pDebJoueurs);
void ajouterPersonnageAJoueur(Message * pLexique, Joueur * pJoueur, Personnage * pNouvPerso);
CodeErreur ajouterPersonnage(Message * pLexique, Joueur * pDebJoueurs);
CodeErreur supprimerJoueurPersonnages(Message * pLexique, Joueur ** pDebJoueurs);
void afficherJoueursPersonnages(Message * pLexique, Joueur * pDebJoueurs);
CodeErreur sauverJoueursPersonnages(Message * pLexique, Joueur * pDebJoueurs);

int pointsObtenus(Message * pLexique);
void pseudoObtenu(Message * pLexique, char pseudo[]);
void nomObtenu(Message * pLexique, char nom[]);
int reponseObtenue(Message * pLexique, NumMessage numMessage);

void viderTampon(void) {
	int c = getchar();
	while (c != '\n' && c != EOF) {
		c = getchar();
	}
}

void dialogues(Message * pLexique) {
	CodeErreur codeErreur = PAS_D_ERREUR;
	Joueur * pDebJoueurs = NULL;
	ChoixMenu choix;

	choix = optionChoisie(pLexique, MENU_PRINCIPAL);
	while (choix != QUITTER) {
		switch (choix) {
		case CHARGER:
			codeErreur = chargerJoueursPersonnages(pLexique, &pDebJoueurs);
			break;
		case AJOUTER_JOUEUR:
			codeErreur = ajouterJoueurPersonnages(pLexique, &pDebJoueurs);
			break;
		case AJOUTER_PERSONNAGE:
			codeErreur = ajouterPersonnage(pLexique, pDebJoueurs);
			break;
		case SUPPRIMER_JOUEUR:
			codeErreur = supprimerJoueurPersonnages(pLexique, &pDebJoueurs);
			break;
		case AFFICHER:
			afficherJoueursPersonnages(pLexique, pDebJoueurs);
			break;
		case SAUVER:
			codeErreur = sauverJoueursPersonnages(pLexique, pDebJoueurs);
			break;
		}
		if (codeErreur != PAS_D_ERREUR) {
			afficherMessage(pLexique, (NumMessage)(NUM_DEB_MESSAGE_ERREUR + codeErreur));
			PAUSE;
			codeErreur = PAS_D_ERREUR;
		}
		choix = optionChoisie(pLexique, MENU_PRINCIPAL);
	}
	libereJoueurs(pDebJoueurs);
}

int optionChoisie(Message * pLexique, int numMenu) {
	int choix, maxChoix;
	bool choixValide;
	do {
		maxChoix = afficherMenu(pLexique, numMenu);
		afficherMessage(pLexique, OBT_CHOIX);
		scanf_s("%d", &choix);
		viderTampon();
		choixValide = choix >= 1 && choix <= maxChoix;
		if (!choixValide) {
			afficherMessage(pLexique, (NumMessage)(NUM_DEB_MESSAGE_ERREUR + MAUVAIS_CHOIX));
			PAUSE;
			CLEAR;
		}
	} while (!choixValide);
	return choix;
}

CodeErreur chargerJoueursPersonnages(Message * pLexique, Joueur ** pDebJoueurs) {
	CodeErreur codeErreur = PAS_D_ERREUR;
	int reponse;
	codeErreur = fichierExiste();
	if (codeErreur == PAS_D_ERREUR) {
		afficherTitre(pLexique, CHARGEMENT);
		if (*pDebJoueurs != NULL) {
			afficherMessage(pLexique, MODIFICATIONS_ANNULEES);
			reponse = reponseObtenue(pLexique, OBT_CONTINUER);
			if (reponse == OUI) {
				libereJoueurs(*pDebJoueurs);
				codeErreur = chargerJoueurs(pDebJoueurs);
				getchar();
			}
		} else {
			codeErreur = chargerJoueurs(pDebJoueurs);
			getchar();
		}
	}
	return codeErreur;
}

CodeErreur ajouterJoueurPersonnages(Message * pLexique, Joueur ** pDebJoueurs) {
	Joueur * pJoueur;
	Joueur * pSauvJoueur;
	Joueur * pNouvJoueur;
	char pseudo[TNOM];
	int reponse;

	if (!nouveauJoueur(&pNouvJoueur))
		return ALLOCATION_MEMOIRE;

	afficherTitre(pLexique, TITRE_JOUEUR_AJOUT);

	pseudoObtenu(pLexique, pseudo);

	if (joueurExiste(*pDebJoueurs, pseudo, &pJoueur, &pSauvJoueur)) {
		libererJoueur(pNouvJoueur);
		return JOUEUR_DEJA_PRESENT;
	}

	*pDebJoueurs = ajouteJoueur(*pDebJoueurs, pseudo, pNouvJoueur, pJoueur, pSauvJoueur);

	do {
		Personnage * pNouvPerso;

		if (!nouveauPersonnage(&pNouvPerso))
			return ALLOCATION_MEMOIRE;

		ajouterPersonnageAJoueur(pLexique, pNouvJoueur, pNouvPerso);

		reponse = reponseObtenue(pLexique, OBT_ENCORE);
	} while (reponse == OUI);

	return PAS_D_ERREUR;
}

void ajouterPersonnageAJoueur(Message * pLexique, Joueur * pJoueur, Personnage * pNouvPerso) {
	Personnage * pPerso;
	Personnage * pSauvPerso;
	char nom[TNOM];
	int points;

	nomObtenu(pLexique, nom);

	if (personnageExiste(pJoueur, nom, &pPerso, &pSauvPerso)) {
		afficherMessage(pLexique, (NumMessage)(NUM_DEB_MESSAGE_ERREUR + PERSONAGE_DEJA_PRESENT));
		viderTampon();
		PAUSE;
		libererPersonnage(pNouvPerso);
	} else {

		points = pointsObtenus(pLexique);

		ajoutePersonnage(pJoueur, nom, points, pNouvPerso, pPerso, pSauvPerso);
	}
}

CodeErreur ajouterPersonnage(Message * pLexique, Joueur * pDebJoueurs) {
	Joueur * pJoueur;
	Joueur * pSauvJoueur;
	char pseudo[TPSEUDO];
	Personnage * pNouvPerso;

	if (!nouveauPersonnage(&pNouvPerso))
		return ALLOCATION_MEMOIRE;

	afficherTitre(pLexique, TITRE_PERSO_AJOUT);

	pseudoObtenu(pLexique, pseudo);

	if (!joueurExiste(pDebJoueurs, pseudo, &pJoueur, &pSauvJoueur)) {
		libererPersonnage(pNouvPerso);
		return JOUEUR_ABSENT;
	}

	ajouterPersonnageAJoueur(pLexique, pJoueur, pNouvPerso);

	return PAS_D_ERREUR;
}

CodeErreur supprimerJoueurPersonnages(Message * pLexique, Joueur ** pDebJoueurs) {
	Joueur * pJoueur;
	Joueur * pSauvJoueur;
	char pseudo[TPSEUDO];

	afficherTitre(pLexique, TITRE_JOUEUR_SUPPR);

	pseudoObtenu(pLexique, pseudo);

	if (!joueurExiste(*pDebJoueurs, pseudo, &pJoueur, &pSauvJoueur))
		return JOUEUR_ABSENT;

	*pDebJoueurs = supprimeJoueur(*pDebJoueurs, pJoueur, pSauvJoueur);
	return PAS_D_ERREUR;
}

void afficherJoueursPersonnages(Message * pLexique, Joueur * pDebJoueurs) {
	if (pDebJoueurs == NULL) {
		CLEAR;
		afficherMessage(pLexique, AUCUN_JOUEUR);
	} else {
		afficherTitre(pLexique, TITRE_LISTE_JOUEURS);
		listeJoueurs(pDebJoueurs);
	}
	getchar();
}

CodeErreur sauverJoueursPersonnages(Message * pLexique, Joueur * pDebJoueurs) {
	CodeErreur codeErreur = PAS_D_ERREUR;

	if (pDebJoueurs == NULL) {
		CLEAR;
		afficherMessage(pLexique, AUCUN_JOUEUR);
	} else {
		afficherTitre(pLexique, SAUVEGARDE);
		codeErreur = sauverJoueurs(pDebJoueurs);
	}
	getchar();
	return codeErreur;
}

int pointsObtenus(Message * pLexique) {
	int points;
	int nbSucces;
	bool pointsValides;
	do {
		afficherMessage(pLexique, OBT_POINTS);
		nbSucces = scanf_s("%d", &points);
		if(nbSucces != 1) viderTampon();
		pointsValides = nbSucces == 1 && points >= 1 && points <= 999;
		if (!pointsValides) {
			afficherMessage(pLexique, (NumMessage)(NUM_DEB_MESSAGE_ERREUR + POINTS_NON_VALIDE));
		}
	} while (!pointsValides);
	viderTampon();
	return points;
}

void pseudoObtenu(Message * pLexique, char pseudo[]) {
	bool pseudoValide;
	do {
		afficherMessage(pLexique, OBT_PSEUDO);
		scanf_s("%s", pseudo, TPSEUDO);
		pseudoValide = isupper(pseudo[0]);
		if (!pseudoValide) {
			afficherMessage(pLexique, (NumMessage)(NUM_DEB_MESSAGE_ERREUR + PSEUDO_NON_VALIDE));
		}
	} while (!pseudoValide);
}

void nomObtenu(Message * pLexique, char nom[]) {
	bool nomValide;
	do {
		afficherMessage(pLexique, OBT_NOM);
		scanf_s("%s", nom, TNOM);
		nomValide = isalpha(nom[0]);
		if (!nomValide) {
			afficherMessage(pLexique, (NumMessage)(NUM_DEB_MESSAGE_ERREUR + NOM_NON_VALIDE));
		}
	} while (!nomValide);
}

int reponseObtenue(Message * pLexique, NumMessage numQuestion) {
	int reponse;
	int nbSucces;
	bool reponseValide;
	do {
		afficherMessage(pLexique, numQuestion);
		nbSucces = scanf_s("%d", &reponse);
		if (nbSucces != 1) viderTampon();
		reponseValide = nbSucces == 1 && reponse == OUI || reponse == NON;
		if (!reponseValide) {
			afficherMessage(pLexique, (NumMessage)(NUM_DEB_MESSAGE_ERREUR + REPONSE_NON_VALIDE));
		}
	} while (!reponseValide);
	return reponse;
}