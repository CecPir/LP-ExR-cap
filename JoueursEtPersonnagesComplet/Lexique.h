#ifndef LEXIQUE_H
#define LEXIQUE_H
	#include <windows.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <errno.h>
	#include "Constantes.h"

	#define FIFRANCAIS "Francais.txt"
	#define FIENGLISH "English.txt"

	#define TNOMFICHIER 20
	#define TTITRE		100
	#define TMENU		100
	#define TTXT		150

	typedef enum numMessage NumMessage;
	enum numMessage {
		// Menu
		MENU_PRINCIPAL = 1001,
		// Message d'obtention
		OBT_PSEUDO = 2001,
		OBT_NOM,
		OBT_POINTS,
		OBT_ENCORE = 2101,
		OBT_CHOIX,
		OBT_CONTINUER,
		// Titres
		TITRE_PRINCIPAL = 3000,
		TITRE_JOUEUR = 3001,
		TITRE_PERSONNAGE = 3002,
		TITRE_AFFICHAGE = 3003,
		TITRE_JOUEUR_AJOUT = 3101,
		TITRE_JOUEUR_SUPPR = 3102,
		TITRE_PERSO_AJOUT = 3201,
		TITRE_PERSO_SUPPR = 3202,
		TITRE_LISTE_JOUEURS = 3301,
		CHARGEMENT = 3401,
		SAUVEGARDE,
		AUCUN_JOUEUR,
		AUCUN_PERSONNAGE,
		MODIFICATIONS_ANNULEES,
		// Numéro de début des messages d'erreur
		NUM_DEB_MESSAGE_ERREUR = 5000,
	};

	typedef struct message Message;

	// Fonctions publiques
	CodeErreur chargerLexique(Message ** pPLexique);
	void afficherMessage(Message * pLexique, int numMessage);
	int afficherMenu(Message * pLexique, int debMenu);
	void afficherTitre(Message * pLexique, int numTitre);	
	void libererLexique(Message * pLexique);
#endif
