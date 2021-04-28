#include "JoueursPerso.h"

void main(void) {
	CodeErreur codeErreur;
	Message* pLexique = NULL;

	codeErreur = chargerLexique(&pLexique);
	if (codeErreur != PAS_D_ERREUR) {
		if (codeErreur == ALLOCATION_MEMOIRE) {
			puts("Erreur memoire/Memory error");
			libererLexique(pLexique);
		}
		else {
			if (codeErreur == FICHIER_INEXISTANT)
				puts("Erreur ouverture fichier/File opening error");
		}
	}
	else {
		/*afficherMenu(pLexique, MENU_PRINCIPAL);
		getchar();
		afficherTitre(pLexique, TITRE_JOUEUR_AJOUT);
		getchar();
		afficherMessage(pLexique, OBT_POINTS);
		getchar();
		afficherMessage(pLexique, NUM_DEB_MESSAGE_ERREUR + PERSONAGE_ABSENT);*/

		dialogue(pLexique);

		libererLexique(pLexique);
	}
	
}