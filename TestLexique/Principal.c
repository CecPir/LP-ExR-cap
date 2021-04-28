#include "TestLexique.h"

void main(void) {
	Message* pLexique = NULL;
	CodeErreur codeErreur;

	codeErreur = chargerLexique(&pLexique);

	if (codeErreur != PAS_D_ERREUR) {
		if (codeErreur == ALLOCATION_MEMOIRE) {
			printf("Erreur memoire/Memory error");
			libererLexique(pLexique);
		}
		else if (codeErreur == FICHIER_INEXISTANT) {
			printf("Erreur ouverture fichier/File opening error");
		}
		PAUSE;
	}
	else {
		afficherMenu(pLexique, MENU_PRINCIPAL);
		getchar();
		afficherTitre(pLexique, TITRE_JOUEUR_AJOUT);
		getchar();
		afficherMessage(pLexique, OBT_POINTS);
		getchar();
		afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + PERSONNAGE_ABSENT);
		libererLexique(pLexique);
	}
}
