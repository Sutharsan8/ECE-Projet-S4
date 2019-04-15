#ifndef ARETE_POIDS_H_INCLUDED
#define ARETE_POIDS_H_INCLUDED

#include"Sommet.h"
class Arete_poids
{
    public:
        ///constructeur qui reçoit en params les données du sommet
        Arete_poids (double,double,double);
        void afficherPoids() const;
        double GetPoids1() const;
        double GetPoids2() const;
        ~Arete_poids();

    protected:

    private:
        /// Données spécifiques du sommet
        double m_id_arete; // Identifiant
        double m_poids1;
        double m_poids2;

};





#endif // ARETE_POIDS_H_INCLUDED
