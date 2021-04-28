#ifndef FICHIERS_H
#define FICHIERS_H
	#include "Constantes.h"
	#include "Gestion.h"
	#define FIJOUEURS "Joueurs.dat"

	CodeErreur fichierExiste(void);
	CodeErreur chargerJoueurs(Joueur * * pDebJoueurs);	
	CodeErreur sauverJoueurs(Joueur * pDebJoueurs);
#endif
