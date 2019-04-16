#ifndef SOMMET_H
#define SOMMET_H
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "util/util.h"
#include "couleur.h"
#include "svgfile.h"

class Sommet
{
    public:
        ///constructeur qui reçoit en params les données du sommet
        Sommet(double,double,double);
        void ajouterVoisin(const Sommet*);
        void afficherData() const;
        void afficherVoisins() const;
        double GetX() const;
        double GetY() const;

        ~Sommet();

    protected:

    private:
        /// Voisinage : liste d'adjacence
        std::vector<const Sommet*> m_voisins;

        /// Données spécifiques du sommet
        double m_id; // Identifiant
        double m_x, m_y; // Position

};

#endif // SOMMET_H
