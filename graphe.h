 /**
 * \details    Dans le graphe.h on declares les methodes et les variables necessaire pour traiter un graph et appliquer un Kruskal sur un Graphe
  */

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
#include <algorithm>
#include<sstream>
#include<fstream>

class graphe
{
    public:
        ///constructeur qui charge le graphe en mémoire
        //format du fichier ordre/liste des sommets/taille/liste des arêtes
        graphe(std::string, int choix,Svgfile& svgout,std::vector<std::vector<double>>,std::vector<std::vector<double>>,std::vector<std::vector<float>>);
        ~graphe();
        void afficher(int choix) const;

        std::vector<float> kruskal(int,std::string,std::string,Svgfile& svgout,std::vector<std::vector<double>>,std::vector<std::vector<double>>,std::vector<std::vector<float>>,std::vector<float>) const;


    private:
        /// Le réseau est constitué d'une collection de sommets
        std::unordered_map<double,Sommet*> m_sommets;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)
        std::unordered_map<double,Arete*> m_arete;
        std::unordered_map<double,Arete*> m_arete_poids;
        std::vector<std::vector<double>> m_sommet_coords;
        std::vector<std::vector<double>> m_arete_sommet;
        std::vector<std::vector<float>> m_arete_ponderation;
        std::vector<float> m_couts;

};

#endif // GRAPHE_H
