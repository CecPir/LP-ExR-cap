#ifndef GESTION_H
#define GESTION_H
	#include "Constantes.h"

	typedef struct personnage Personnage;
	struct personnage {
		char nom[TNOM];
		int points;
		Personnage * pSuiv;
	};	
	
	typedef struct joueur Joueur;
	struct joueur {
		char pseudo[TPSEUDO];
		Personnage * pDebPersonnages;
		Joueur * pSuiv;
	};	
	
	bool joueurExiste(Joueur * pDebJoueurs, char * pseudo, 
							Joueur * * pJoueur, Joueur * * pSauvJoueur);
	bool nouveauJoueur(Joueur * * pNouvJoueur);
	void libererJoueur(Joueur * pJoueur);
	Joueur * ajouteJoueur(Joueur * pDebJoueurs, char * pseudo, Joueur * pNouvJoueur,
							Joueur * pJoueur, Joueur * pSauvJoueur);
	Joueur * supprimeJoueur(Joueur * pDebJoueurs, Joueur * pJoueur, Joueur * pSauvJoueur);
	bool personnageExiste(Joueur * pJoueur, char * nom, 
								Personnage * * pPerso, Personnage * * pSauvPerso);	
	bool nouveauPersonnage(Personnage * * pNouvPerso);
	void libererPersonnage(Personnage * pPerso);
	void ajoutePersonnage(Joueur * pJoueur, char * nom, int points,
		Personnage * pNouvPerso, Personnage * pPerso, Personnage * pSauvPerso);
	//void supprimePersonnage(Joueur * pJoueur, Personnage * pPerso, Personnage * pSauvPerso);
	void listeJoueurs(Joueur * pDebJoueurs);
	int nbPersonnages(Joueur * pJoueur);
	void libereJoueurs(Joueur * pDebJoueurs);

#endif
