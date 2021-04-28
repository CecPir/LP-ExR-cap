#ifndef JOUEURSPERSO_H
#define JOUEURSPERSO_H
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdbool.h>
	#include <string.h>
	#include <ctype.h>
	#include "Constantes.h"
	#include "Lexique.h"

	// structures
	typedef struct personnage Personnage;
	struct personnage {
		char nom[TNOM];
		int points;
		Personnage* pSuiv;
	};

	typedef struct joueur Joueur;
	struct joueur {
		char pseudo[TPSEUDO];
		Personnage* pDebPersonnages;
		Joueur* pSuiv;
	};

	typedef struct enregJoueur EnregJoueur;
	struct enregJoueur {
		char pseudo[TPSEUDO];
		int nbPersonnages;
	};

	typedef struct enregPerso EnregPerso;
	struct enregPerso {
		char nom[TNOM];
		int points;
	};


	// interface
	void dialogue(Message* pLexique);
	ChoixMenu choixObtenu(Message* pLexique, NumMessage numMenu);
	CodeErreur ajouterJoueurPersonnages(Message* pLexique, Joueur** pDebJoueurs);
	void pseudoObtenu(Message* pLexique, char pseudo[]);
	void nomObtenu(Message* pLexique, char nom[]);
	int pointsObtenus(Message* pLexique);
	int reponseObtenue(Message* pLexique, NumMessage numMessage);
	CodeErreur ajouterPersonnageAJoueur(Message* pLexique, Joueur* pDebJoueurs, Joueur* pJoueur, Personnage* pNouvPerso);
	void ajoutePersonnage(Joueur* pJoueur, char nom[], int points, Personnage* pNouvPerso);
	void afficherJoueursPersonnages(Message* pLexique, Joueur* pDebJoueurs);
	CodeErreur sauverJoueursPersonnages(Message* pLexique, Joueur* pDebJoueurs);
	CodeErreur chargerJoueursPersonnages(Message* pLexique, Joueur** pDebJoueurs);

	// gestion
	bool nouveauJoueur(Joueur** pNouvJoueur);
	bool nouveauPersonnage(Personnage** pNouvPerso);
	bool joueurExiste(Joueur* pDebJoueurs, char pseudo[], Joueur** pJoueur, Joueur** pSauvJoueur);
	bool personnageExiste(Joueur* pDebJoueurs, char nom[]);
	void libèreJoueur(Joueur* pJoueur);
	void libèrePersonnage(Personnage* pPerso);
	void libèreJoueursPersonnages(Joueur* pDebJoueurs);
	void ajouteJoueur(Joueur** pDebJoueurs, char pseudo[], Joueur* pNouvJoueur, Joueur* pJoueur, Joueur* pSauvJoueur);
	void listeJoueurs(Joueur* pDebJoueurs);
	int nbrPersonnages(Joueur* pJoueur);

	// fichier
	CodeErreur sauverJoueurs(Joueur* pDebJoueurs);
	CodeErreur fichierExiste(void);
	CodeErreur chargerJoueurs(Joueur** pDebJoueurs);

#endif
