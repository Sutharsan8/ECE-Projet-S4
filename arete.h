#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED
#include"Sommet.h"
class Arete
{
    public:
        ///constructeur qui reçoit en params les données du sommet
        Arete (double,double,double,double,double);
        void ajouterVoisin(const Arete*);
        void afficherData() const;
        void afficherPoids() const;
        double GetPoids1() const;
        double GetPoids2() const;
        double GetS1() const;
        double GetS2() const;
        ~Arete();

    protected:

    private:
        /// Voisinage : liste d'adjacence
        std::vector<const Arete*> m_voisins_arete;

        /// Données spécifiques du sommet
        double m_id_arete; // Identifiant
        double m_s1;
        double m_s2; // Sommets qui doivent etre relie par larete
        double m_poids1;
        double m_poids2;

};


#endif // ARETE_H_INCLUDED
