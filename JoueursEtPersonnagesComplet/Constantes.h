#ifndef CONSTANTES_H
#define CONSTANTES_H
	#include <stdbool.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	
	#define TPSEUDO		30
	#define TNOM		30

	#define NBMAXCHOIXMENU 100
	#define OUI 1
	#define NON 2

	#define PAUSE printf("\n"); system("pause")
	#define CLEAR system("cls")	
	#define ENTER printf("\n")
	#define TAB printf("\t")

	typedef enum codeErreur CodeErreur;
	enum codeErreur  {
		PAS_D_ERREUR,
		//Erreurs logiques...
		MAUVAIS_CHOIX,
		JOUEUR_ABSENT,
		JOUEUR_DEJA_PRESENT,
		PERSONAGE_ABSENT,
		PERSONAGE_DEJA_PRESENT,
		POINTS_NON_VALIDE,
		PSEUDO_NON_VALIDE,
		NOM_NON_VALIDE,
		REPONSE_NON_VALIDE,
		OUVERTURE_FICHIER,
		ALLOCATION_MEMOIRE
	};

	typedef enum choixMenu ChoixMenu;
	enum choixMenu {
		CHOIX_MIN,
		CHARGER,
		AJOUTER_JOUEUR,
		AJOUTER_PERSONNAGE,
		SUPPRIMER_JOUEUR,
		AFFICHER,
		SAUVER,
		QUITTER
	};
#endif
