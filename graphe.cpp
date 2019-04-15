#include <fstream>
#include <iostream>
#include "graphe.h"

graphe::graphe(std::string nomFichier){
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    std::string id;
    double x,y;
    //lecture des sommets
    for (int i=0; i<ordre; ++i){
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>x; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>y; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        m_sommets.insert({id,new Sommet{id,x,y}});
    }
    int taille;
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    std::string id_voisin;
    //lecture des aretes
    for (int i=0; i<taille; ++i){
        //lecture des ids des deux extrémités
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
        ifs>>id_voisin; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");
        //ajouter chaque extrémité à la liste des voisins de l'autre (graphe non orienté)
        (m_sommets.find(id))->second->ajouterVoisin((m_sommets.find(id_voisin))->second);
        (m_sommets.find(id_voisin))->second->ajouterVoisin((m_sommets.find(id))->second);//remove si graphe orienté
    }
}
void graphe::afficher() const{
    int numero=0;
    int nbsommet=0;
    std::cout<<"graphe : "<<std::endl;
    std::cout<<"Ordre : "<<m_sommets.size()<<std::endl;
    while ( nbsommet != m_sommets.size()) /// Tant qu'on a pas trouvé le même nombre de sommet que le graphe comporte
    {
        if(m_sommets.find(std::to_string(numero))!=m_sommets.end()) /// si le sommet existe
        {
            Sommet*s0=(m_sommets.find(std::to_string(numero)))->second; ///récupation des valeurs puis affichage
            s0->afficherData();
            s0->afficherVoisins();
            nbsommet++;
        }
        numero++;
        std::cout<<std::endl;
    }
}

void graphe::parcoursBFS(std::string id) const{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    l_pred=s0->parcoursBFS();
}
void graphe::afficherBFS(std::string id) const{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    std::cout<<"parcoursBFS a partir de "<<id<<" :"<<std::endl;
    l_pred=s0->parcoursBFS();
    for(auto s:l_pred){
        std::cout<<s.first<<" <--- ";
        std::pair<std::string,std::string> pred=s;
        while(pred.second!=id){
            pred=*l_pred.find(pred.second);
            std::cout<<pred.first<<" <--- ";
        }
        std::cout<<id<<std::endl;
    }
}
void graphe::parcoursDFS(std::string id) const{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    l_pred=s0->parcoursDFS();
}
void graphe::afficherDFS(std::string id) const{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    std::cout<<"parcoursDFS a partir de "<<id<<" :"<<std::endl;
    l_pred=s0->parcoursDFS();
    for(auto s:l_pred){
        std::cout<<s.first<<" <--- ";
        std::pair<std::string,std::string> pred=s;
        while(pred.second!=id){
            pred=*l_pred.find(pred.second);
            std::cout<<pred.first<<" <--- ";
        }
        std::cout<<id<<std::endl;
    }
}
int graphe::rechercher_afficherToutesCC() const{
    int i=0;
    int compteursommet=0;
    int nbsommet=0;
    std::cout<<"composantes connexes :"<<std::endl;
    std::unordered_set<std::string> recup;
    std::unordered_set<std::string> save;
    while (nbsommet != m_sommets.size())
    {
        if (save.find(std::to_string(compteursommet))==save.end()) /// si le sommet est non marqué
        {
            i++;
            Sommet*s0=(m_sommets.find(std::to_string(compteursommet)))->second;
            recup=s0->rechercherCC();  ///on récupère une composante connexe
            std::unordered_set<std::string> :: iterator itr;
            std::cout<<"cc"<<i<<std::endl;
            for (itr = recup.begin(); itr != recup.end(); itr++)
            {
                std::cout << (*itr) <<"    "; ///affichage de la composante connexe
                save.insert(*itr);   ///marquage des sommets de cette composante dans un unordered_set
                nbsommet++;
            }
            std::cout<<std::endl;
            compteursommet++;
        }
        else compteursommet++;
    }
    return i;
}

int graphe::isEulerien()const
{
    int numero=0;
    int degreimpair=0;
    int nbsommet=0;
    int degre=0;
    std::vector<std::string> liste_impair;
    std::unordered_set<std::string> recup;
    while (nbsommet != m_sommets.size())
    {
        if(m_sommets.find(std::to_string(numero))!=m_sommets.end()) /// si le sommet existe dans m_sommets
        {
            Sommet*s0=(m_sommets.find(std::to_string(numero)))->second;
            degre=s0->getDegre(); /// on recupre son degre
            if (degre%2 != 0) ///si le degre est impair
            {
                degreimpair++;  ///on incremente degreimpair
                liste_impair.push_back(std::to_string(numero));   ///et on sauvegarde l'id du sommet en question
            }
            nbsommet++;
        }
        numero++;
    }
    if (degreimpair == 0) /// cycle eulérien
        return 2;
    if (degreimpair ==2)  /// chaine eulérienne
    {
        std::vector<std::string> :: iterator itr;
        std::cout <<"Les extremites sont : ";
        for (itr = liste_impair.begin(); itr != liste_impair.end(); itr++) /// affichage des extrémités
        {
           std::cout <<(*itr) <<"    ";
        }
        return 1;
    }
    if (degreimpair!=0 && degreimpair!=2) /// rien d'eulerien
        return 0;
}

graphe::~graphe()
{
    //dtor
}
