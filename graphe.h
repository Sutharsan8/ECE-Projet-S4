#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include <vector>
#include "sommet.h"
#include "util/util.h"
#include "couleur.h"
#include "svgfile.h"
#include"arete.h"
//#include"arete_poids.h"

class graphe
{
    public:
        ///constructeur qui charge le graphe en m�moire
        //format du fichier ordre/liste des sommets/taille/liste des ar�tes
        graphe(std::string, int choix,Svgfile& svgout);
        ~graphe();
        void afficher(int choix) const;

    private:
        /// Le r�seau est constitu� d'une collection de sommets
        std::unordered_map<double,Sommet*> m_sommets;//stock�e dans une map (cl�=id du sommet, valeur= pointeur sur le sommet)
        std::unordered_map<double,Arete*> m_arete;
        std::unordered_map<double,Arete*> m_arete_poids;

};

#endif // GRAPHE_H
