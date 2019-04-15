#include <iostream>
#include <queue>
#include <stack>
#include <list>
#include<unordered_map>
#include<unordered_set>
#include "sommet.h"

Sommet::Sommet(std::string id,double x,double y):m_id{id},m_x{x},m_y{y}
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

int Sommet::getDegre() const{
    int degre=0;
    for (auto s: m_voisins) /// Pour chaque voisin on incremente la valeur de degre
    {
        degre++;
    }
    return degre;
}

std::unordered_map<std::string,std::string> Sommet::parcoursBFS() const{
    Sommet*sommetpremier=new Sommet(m_id,m_x,m_y); /// on créé un sommet qui prend les valeurs de l'appelant
    sommetpremier->m_voisins=m_voisins;
    std::unordered_map<std::string,std::string> l_pred;
    std::unordered_set<std::string> marquage;
    marquage.insert(m_id);
    std::queue<const Sommet*> file; ///on créé une file de sommmet
    file.push(sommetpremier);       /// on ajoute le sommet à la file
    while(!file.empty()) /// tant que la fille n'est pas vide
    {
        const Sommet*sommetactuel=file.front();
        marquage.insert({sommetactuel->m_id});
        file.pop(); /// on supprime le premier élément de la file
        for (const Sommet* it : sommetactuel->m_voisins) /// Parcours de tous les voisins
        {
            std::unordered_set<std::string>::const_iterator got = marquage.find (it->m_id);
            if (got == marquage.end())  /// Si le sommet voisin n'est pas marqué
            {
                file.push(it);          /// on l'ajoute à la file
                l_pred.insert({it->m_id,sommetactuel->m_id});    /// on le place dans l'unordered map
            }
        }
    }
    delete sommetpremier; /// libère la mémoire
    return l_pred;
}

std::unordered_map<std::string,std::string> Sommet::parcoursDFS() const{
    Sommet*sommetpremier=new Sommet(m_id,m_x,m_y); /// Même principe que le parcours BFS
    sommetpremier->m_voisins=m_voisins;
    std::unordered_map<std::string,std::string> l_pred;
    std::unordered_set<std::string> marquage;
    marquage.insert(m_id);
    std::stack<const Sommet*> pile;  /// Création d'une pile
    pile.push(sommetpremier);
    while(!pile.empty())
    {
        const Sommet*sommetactuel=pile.top();
        marquage.insert({sommetactuel->m_id});
        pile.pop();
        for (const Sommet* it : sommetactuel->m_voisins)
        {
            std::unordered_set<std::string>::const_iterator got = marquage.find (it->m_id);
            if (got == marquage.end())  /// si le sommet est non marqué
            {
                pile.push(it);
                l_pred.insert({it->m_id,sommetactuel->m_id});
            }
        }
    }
    delete sommetpremier;
    return l_pred;
}
std::unordered_set<std::string> Sommet::rechercherCC() const{
    std::unordered_set<std::string> cc;
    std::unordered_map<std::string,std::string> l_pred;
    l_pred=parcoursBFS();
    for(auto s:l_pred) ///parcours de l'unordered map récupérée du parcours BFS
        {
            cc.insert(s.first); ///premier element
            std::pair<std::string,std::string> pred=s;
            while(pred.second!=m_id) /// tous les suivants
            {
                pred=*l_pred.find(pred.second);
                cc.insert(pred.first);
            }
            cc.insert(m_id); ///sommet de départ
        }
    if (l_pred.size()==0) /// si le sommet de départ n'a pas de voisin
    {
        cc.insert(m_id);
    }
    return cc;
}
Sommet::~Sommet()
{
    //dtor
}
