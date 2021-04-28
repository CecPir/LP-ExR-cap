#include "JoueursPerso.h"

void dialogue(Message* pLexique) {
	CodeErreur codeErreur = PAS_D_ERREUR;
	Joueur* pDebJoueurs = NULL;
	ChoixMenu choix;

	choix = choixObtenu(pLexique, MENU_PRINCIPAL);
	while (choix != QUITTER) {
		switch (choix) {
		case CHARGER_JOUEURS_PERSONNAGES:
			codeErreur = chargerJoueursPersonnages(pLexique, &pDebJoueurs);
			break;
		case AJOUTER_JOUEUR_PERSONNAGES:
			codeErreur = ajouterJoueurPersonnages(pLexique, &pDebJoueurs);
			break;
		case AJOUTER_PERSONNAGE_PERSONNAGES:
			puts("ajoutP");
			//codeErreur = ajouterPersonnage(pLexique, pDebJoueurs);
			break;
		case SUPPRIMER_JOUEUR:
			puts("supp");
			//codeErreur = supprimerJoueurPersonnages(pLexique, &pDebJoueurs);
			break;
		case AFFICHER_JOUEURS_PERSONNAGES:
			afficherJoueursPersonnages(pLexique, pDebJoueurs);
			break;
		case SAUVER_JOUEURS_PERSONNAGES:
			codeErreur = sauverJoueursPersonnages(pLexique, pDebJoueurs);
			break;
		}
		if (codeErreur != PAS_D_ERREUR) {
			afficherMessage(pLexique, (NumMessage)(NUM_DEB_MESSAGE_ERREUR + codeErreur));
			PAUSE;
			codeErreur = PAS_D_ERREUR;
		}
		choix = choixObtenu(pLexique, MENU_PRINCIPAL);
	}
	//libérerJoueursPersonnages(pDebJoueurs);
}

ChoixMenu choixObtenu(Message* pLexique, NumMessage numMenu) {
	bool choixValide;
	ChoixMenu choix;
	do {
		ChoixMenu maxChoix = afficherMenu(pLexique, numMenu);
		NumMessage numMessage = OBT_CHOIX;
		afficherMessage(pLexique, numMessage);
		scanf_s("%d", &choix);
		choixValide = choix >= 1 && choix <= maxChoix;
		if (!choixValide) {
			CodeErreur codeErreur = MAUVAIS_CHOIX;
			numMessage = NUM_DEB_MESSAGE_ERREUR + codeErreur;
			afficherMessage(pLexique, numMessage);
			FF;
			PAUSE;
		}
	} while (!choixValide);
	FF;
	return choix;
}

CodeErreur ajouterJoueurPersonnages(Message* pLexique, Joueur** pDebJoueurs) {
	CodeErreur codeErreur;
	bool allocationOK;
	Joueur* pNouvJoueur;
	Joueur* pJoueur, * pSauvJoueur;

	allocationOK = nouveauJoueur(&pNouvJoueur);
	if (!allocationOK) {
		codeErreur = ALLOCATION_MEMOIRE;
	}
	else {
		int numTitre = TITRE_JOUEUR_AJOUT;
		char pseudo[TPSEUDO];
		codeErreur = PAS_D_ERREUR;
		afficherTitre(pLexique, numTitre);
		pseudoObtenu(pLexique, pseudo);
		bool pseudoExiste = joueurExiste(*pDebJoueurs, pseudo, &pJoueur, &pSauvJoueur);
		if (pseudoExiste) {
			codeErreur = JOUEUR_DEJA_PRESENT;
			libèreJoueur(pNouvJoueur);
		}
		else {
			int réponse;
			ajouteJoueur(pDebJoueurs, pseudo, pNouvJoueur, pJoueur, pSauvJoueur);

			do {
				Personnage* pNouvPerso;
				if (!nouveauPersonnage(&pNouvPerso))
					return ALLOCATION_MEMOIRE;

				codeErreur = ajouterPersonnageAJoueur(pLexique, *pDebJoueurs, pNouvJoueur, pNouvPerso);
				if (codeErreur == PAS_D_ERREUR)
					réponse = reponseObtenue(pLexique, OBT_ENCORE);
				else
					réponse = NON;

			} while (allocationOK && réponse == OUI);
		}
	}
	return codeErreur;
}

CodeErreur ajouterPersonnageAJoueur(Message* pLexique, Joueur* pDebJoueurs, Joueur* pJoueur, Personnage* pNouvPerso) {
	char nom[TNOM];
	CodeErreur codeErreur = PAS_D_ERREUR;

	nomObtenu(pLexique, nom);
	if (personnageExiste(pDebJoueurs, nom)) {
		afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + PERSONNAGE_DEJA_PRESENT);
		libèrePersonnage(pNouvPerso);
	}
	else {
		if (nbrPersonnages(pJoueur) < NBMAXPERSO) {
			int points = pointsObtenus(pLexique);
			ajoutePersonnage(pJoueur, nom, points, pNouvPerso);
		}
		else
			codeErreur = NB_MAX_PERSO_ATTEINT;
	}
	return codeErreur;
}

void afficherJoueursPersonnages(Message* pLexique, Joueur* pDebJoueurs) {
	if (pDebJoueurs == NULL)
		afficherMessage(pLexique, AUCUN_JOUEUR);
	else {
		afficherTitre(pLexique, TITRE_LISTE_JOUEURS);
		listeJoueurs(pDebJoueurs);
	}
	PAUSE;
}

CodeErreur sauverJoueursPersonnages(Message* pLexique, Joueur* pDebJoueurs) {
	CodeErreur codeErreur = PAS_D_ERREUR;
	if (pDebJoueurs == NULL) {
		afficherMessage(pLexique, AUCUN_JOUEUR);
	}
	else {
		afficherTitre(pLexique, SAUVEGARDE);
		codeErreur = sauverJoueurs(pDebJoueurs);
	}
	return codeErreur;
}

CodeErreur chargerJoueursPersonnages(Message* pLexique, Joueur** pDebJoueurs) {
	CodeErreur codeErreur = PAS_D_ERREUR;
	
	codeErreur = fichierExiste();
	if (codeErreur == PAS_D_ERREUR) {
		afficherTitre(pLexique, CHARGEMENT);
		if (*pDebJoueurs != NULL) {
			int réponse;
			afficherMessage(pLexique, MODIFICATIONS_ANNULEES);
			réponse = reponseObtenue(pLexique, OBT_CONTINUER);
			if (réponse == OUI) {
				libèreJoueursPersonnages(*pDebJoueurs);
				codeErreur = chargerJoueurs(pDebJoueurs);
			}
		}
		else {
			codeErreur = chargerJoueurs(pDebJoueurs);
		}
	}
	return codeErreur;
}

void pseudoObtenu(Message* pLexique, char pseudo[]) {
	bool pseudoValide;
	do {
		NumMessage numMessage = OBT_PSEUDO;
		afficherMessage(pLexique, numMessage);
		gets_s(pseudo, TPSEUDO);
		pseudoValide = isupper(pseudo[0]);
		if (!pseudoValide) {
			CodeErreur codeErreur = PSEUDO_NON_VALIDE;
			numMessage = NUM_DEB_MESSAGE_ERREUR + codeErreur;
			afficherMessage(pLexique, numMessage);
			
		}
	} while (!pseudoValide);
}

void nomObtenu(Message* pLexique, char nom[]) {
	bool nomValide;
	do {
		afficherMessage(pLexique, OBT_NOM);
		gets_s(nom, TNOM);
		nomValide = isalpha(nom[0]);
		if (!nomValide) {
			CodeErreur codeErreur = NOM_NON_VALIDE;
			NumMessage numMessage = NUM_DEB_MESSAGE_ERREUR + codeErreur;
			afficherMessage(pLexique, numMessage);
			
		}
	} while (!nomValide);	
}

int pointsObtenus(Message* pLexique) {
	int points;
	bool pointsValides;
	do {
		NumMessage numMessage = OBT_POINTS;
		afficherMessage(pLexique, numMessage);
		scanf_s("%d", &points);
		pointsValides = points >= 0 && points <= MAXPOINTS;
		if (!pointsValides) {
			CodeErreur codeErreur = POINTS_NON_VALIDES;
			numMessage = NUM_DEB_MESSAGE_ERREUR + codeErreur;
			afficherMessage(pLexique, numMessage);
			
		}
	} while (!pointsValides);
	return points;
}

int reponseObtenue(Message* pLexique, NumMessage numMessage) {
	int réponse;
	bool réponseValide;
	do {
		afficherMessage(pLexique, numMessage);
		FF;
		scanf_s("%d",&réponse);
		réponseValide = réponse == OUI || réponse == NON;
		if (!réponseValide) {
			CodeErreur codeErreur = REPONSE_NON_VALIDE;
			numMessage = NUM_DEB_MESSAGE_ERREUR + codeErreur;
			afficherMessage(pLexique, numMessage);
			
		}
	} while (!réponseValide);
	FF;
	return réponse;
}