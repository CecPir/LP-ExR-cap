#include "Principal.h"

void main(void) {
	Message * pLexique = NULL;
	CodeErreur codeErreur;

	codeErreur = chargerLexique(&pLexique);

	if (codeErreur != PAS_D_ERREUR) {
		if (codeErreur == ALLOCATION_MEMOIRE) {
			printf("Erreur memoire/Memory error");
			libererLexique(pLexique);
		} else if (codeErreur == OUVERTURE_FICHIER) {
			printf("Erreur ouverture fichier/File opening error");
		}
		PAUSE;
	} else {
		dialogues(pLexique);
		libererLexique(pLexique);
	}
}
