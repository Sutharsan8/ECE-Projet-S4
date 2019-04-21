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

///code source provenant d'internet, utiliser pour les combinaisons dans void combinatoire!
///http://www.cplusplus.com/reference/algorithm/next_permutation/

class graphe
{
    public:
        ///constructeur qui charge le graphe en mémoire
        //format du fichier ordre/liste des sommets/taille/liste des arêtes
        graphe(std::string, int choix,Svgfile& svgout,std::vector<std::vector<double>>,std::vector<std::vector<double>>,std::vector<std::vector<float>>);
        ~graphe();
        void afficher(int choix) const;
        int GetOrdre() const;
        int GetTaille() const;
        Arete* getArete(int i) const;
         std::vector<float> kruskal(int,std::string,std::string,Svgfile& svgout,std::vector<std::vector<double>>,std::vector<std::vector<double>>,std::vector<std::vector<float>>,std::vector<float>) const;
        bool verifierConnexite(std::vector<int> v) const;
        double calculerCout(int , std::vector<int> ) const;
        bool DFS(int ordre, std::vector<int> Aretes) const;
        std::vector<int> areteAdjacentes (int arete, std::vector<int> Aretes) const;


    private:
        /// Le réseau est constitué d'une collection de sommets
        std::unordered_map<double,Sommet*> m_sommets;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)
        std::unordered_map<double,Arete*> m_arete;
        std::unordered_map<double,Arete*> m_arete_poids;

        /// Chaque sommet est represente par un tableau [sommetId, Xcoord, Ycoord]
        std::vector<std::vector<double>> m_sommet_coords;

        /// Chaque arete est representee par un tableau [AreteId, sommetId, sommetId]
        std::vector<std::vector<double>> m_arete_sommet;
        /// Chaque ponderation d'arete est representee par un tableau [AreteId, poids1, poids2]
        std::vector<std::vector<float>> m_arete_ponderation;

        std::vector<float> m_couts;

};

#endif // GRAPHE_H
