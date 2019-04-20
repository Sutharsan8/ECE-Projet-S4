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

//#include"arete_poids.h"

class graphe
{
    public:
        ///constructeur qui charge le graphe en mémoire
        //format du fichier ordre/liste des sommets/taille/liste des arêtes
        graphe(std::string, int choix,Svgfile& svgout,std::vector<std::vector<double>>,std::vector<std::vector<double>>,std::vector<std::vector<float>>);
        ~graphe();
        void afficher(int choix) const;
        void kruskal(int,std::string,std::string,Svgfile& svgout,std::vector<std::vector<double>>,std::vector<std::vector<double>>,std::vector<std::vector<float>>) const;
        ///Une partie du code de recuperation en binaire venant d'internet qui est dans la méthode RECUP_binaire
        ///http://www.cplusplus.com/reference/algorithm/next_permutation/
        std::vector<std::vector<bool>> RECUP_binaire(std::string nomFichier,std::string nomFichier1,std::vector<bool> binaire,std::vector<std::vector<bool>> sauvegarde_binaire);
        std::vector<std::vector<double>> Conversion_binaire_arete(std::string nomFichier,std::string nomFichier1,std::vector<std::vector<double>> arete_pareto_1,std::vector<std::vector<bool>> sauvegarde_binaire);
        //std::vector<std::vector<double>> Pareto(std::string nomFichier,std::string nomFichier1,std::vector<std::vector<double>> arete_pareto_1,std::vector<std::vector<double>> arete_sommet);

    private:
        /// Le réseau est constitué d'une collection de sommets
        std::unordered_map<double,Sommet*> m_sommets;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)
        std::unordered_map<double,Arete*> m_arete;
        std::unordered_map<double,Arete*> m_arete_poids;
        std::vector<std::vector<double>> m_sommet_coords;
        std::vector<std::vector<double>> m_arete_sommet;
        std::vector<std::vector<float>> m_arete_ponderation;

};

#endif // GRAPHE_H
