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
        ///constructeur qui charge le graphe en mémoire
        //format du fichier ordre/liste des sommets/taille/liste des arêtes
        graphe(std::string, int choix,Svgfile& svgout);
        ~graphe();
        void afficher(int choix) const;

    private:
        /// Le réseau est constitué d'une collection de sommets
        std::unordered_map<double,Sommet*> m_sommets;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)
        std::unordered_map<double,Arete*> m_arete;
        std::unordered_map<double,Arete*> m_arete_poids;

};

#endif // GRAPHE_H
