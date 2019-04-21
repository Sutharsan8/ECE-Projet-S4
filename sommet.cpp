#include <iostream>
#include <queue>
#include <stack>
#include <list>
#include<unordered_map>
#include "sommet.h"

Sommet::Sommet(double id,double x,double y):m_id{id},m_x{x},m_y{y}
{
}
void Sommet::ajouterVoisin(const Sommet* voisin){
    m_voisins.push_back(voisin);
}
 void Sommet::afficherData() const{
     std::cout<<"    "<<m_id<<" : "<<"(x,y)=("<<m_x<<","<<m_y<<")"<<std::endl;

 }
void Sommet::afficherVoisins() const{
    std::cout<<"  voisins :"<<std::endl;
    for(auto v:m_voisins) {
        v->afficherData();
    }
}

double Sommet::GetX() const
{
    return m_x;
}
double Sommet::GetY() const
{
    return m_y;
}

Sommet::~Sommet()
{
}
