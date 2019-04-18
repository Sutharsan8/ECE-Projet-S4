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

        graphe(std::string, int choix,Svgfile& svgout,std::vector<std::vector<double>>,std::vector<std::vector<double>>,std::vector<std::vector<float>>);
        ~graphe();
        void afficher(int choix) const;
        void kruskal(std::string,std::string,Svgfile& svgout,std::vector<std::vector<double>>,std::vector<std::vector<double>>,std::vector<std::vector<float>>) const;


    private:
        /// Le r�seau est constitu� d'une collection de sommets
        std::unordered_map<double,Sommet*> m_sommets;//stock�e dans une map (cl�=id du sommet, valeur= pointeur sur le sommet)
        std::unordered_map<double,Arete*> m_arete;
        std::unordered_map<double,Arete*> m_arete_poids;

        std::vector<std::vector<double>> m_sommet_coords;
        std::vector<std::vector<double>> m_arete_sommet;
        std::vector<std::vector<float>> m_arete_ponderation;


};

#endif // GRAPHE_H
