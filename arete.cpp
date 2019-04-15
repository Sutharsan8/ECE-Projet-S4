#include <iostream>
#include <queue>
#include <stack>
#include <list>
#include<unordered_map>
#include "arete.h"
#include "Sommet.h"

Arete::Arete(double id,double s1,double s2,double poids1,double poids2):m_id_arete{id},m_s1{s1},m_s2{s2},m_poids1{poids1},m_poids2{poids2}
{
}
void Arete::ajouterVoisin(const Arete* voisin){
    m_voisins_arete.push_back(voisin);
}
 void Arete::afficherData() const{
     std::cout<<"  arete numero  "<<m_id_arete<<" : "<<"Sommet Initiale "<<m_s1<<", Sommet Finale "<<m_s2<<std::endl;

 }
 void Arete::afficherPoids() const{
     std::cout<<"  arete numero  "<<m_id_arete<<" : "<<"Poids 1: "<<m_poids1<<", Poids 2: "<<m_poids2<<std::endl;

 }

double Arete::GetS1() const
{
    return m_s1;
}
double Arete::GetS2() const
{
    return m_s2;
}

double Arete::GetPoids1() const
{
    return m_poids1;
}
double Arete::GetPoids2() const
{
    return m_poids2;
}

Arete::~Arete()
{
    //dtor
}
