#include <iostream>
#include <queue>
#include <stack>
#include <list>
#include<unordered_map>
#include "arete_poids.h"


Arete_poids::Arete_poids(double id,double poids1,double poids2):m_id_arete{id},m_poids1{poids1},m_poids2{poids2}
{
}


 void Arete_poids::afficherPoids() const{
     std::cout<<"  arete numero  "<<m_id_arete<<" : "<<"Poids 1: "<<m_poids1<<", Poids 2: "<<m_poids2<<std::endl;

 }

double Arete_poids::GetPoids1() const
{
    return m_poids1;
}
double Arete_poids::GetPoids2() const
{
    return m_poids2;
}

Arete_poids::~Arete_poids()
{
    //dtor
}
