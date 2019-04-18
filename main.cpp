#include <iostream>
#include "graphe.h"
using namespace std;

std::vector<std::vector<double>> RECUP_sommet_c(std::string nomFichier,std::vector<std::vector<double>> sommet_coords);
std::vector<std::vector<double>> RECUP_arete_s(std::string nomFichier,std::vector<std::vector<double>> arete_sommet);
std::vector<std::vector<float>> RECUP_arete_p(std::string nomFichier,std::vector<std::vector<float>> arete_ponderation);

int main()
{
    Svgfile svgout;
    std::vector<std::vector<double>> sommet_c; ///METTRE CA EN PARAMETRE DANS TA NOUVELLE FONCTION,CES VECTEURS SONT DEJA REMPLIS !
    std::vector<std::vector<double>> arete_s;
    std::vector<std::vector<float>> arete_p;
    sommet_c=RECUP_sommet_c("manhattan.txt",sommet_c);
    arete_s=RECUP_arete_s("manhattan.txt",arete_s);
    arete_p=RECUP_arete_p("manhattan_weights_0.txt",arete_p);
    graphe a{"manhattan.txt",1, svgout,sommet_c,arete_s,arete_p};
    graphe b{"manhattan_weights_0.txt",2, svgout,sommet_c,arete_s,arete_p};
    a.afficher(1);
    b.afficher(2);
    a.kruskal("manhattan.txt","manhattan_weights_0.txt",svgout,sommet_c,arete_s,arete_p);
    return 0;
}


std::vector<std::vector<double>> RECUP_sommet_c(std::string nomFichier,std::vector<std::vector<double>> sommet_coords)
{
    double id;
    double x,y;
    double ordre;
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    ifs >> ordre;///RECUPER LE NOMBRE DE SOMMETS
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    //lecture des sommets
    for (int i=0; i<ordre; ++i){
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");///RECUPERER LA VALEUR DU SOMMET 1
        ifs>>x; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");///RECUPERER COORD X
        ifs>>y; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");///RECUPERER COORD Y

        sommet_coords.push_back(std::vector<double>(3));///INSERTION DANS LE VECTEUR 2 DIMENSIONS
        sommet_coords[i][0]=id;
        sommet_coords[i][1]=x;
        sommet_coords[i][2]=y;
}
return sommet_coords;
}


std::vector<std::vector<double>> RECUP_arete_s(std::string nomFichier,std::vector<std::vector<double>> arete_sommet)
{
    double id;
    double x,y;
    double x1;double y1;
    double x2;double y2;
    double ordre;
    double id_arete;
    double s_1,s_2;
    double taille;

    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    ifs >> ordre;///RECUPER LE NOMBRE DE SOMMETS
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    //lecture des sommets
    for (int i=0; i<ordre; ++i){
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");///RECUPERER LA VALEUR DU SOMMET 1
        ifs>>x; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");///RECUPERER COORD X
        ifs>>y; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");///RECUPERER COORD Y
    }

    ifs>>taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    //lecture des aretes
    for (int i=0; i<taille; ++i)
    {
        //lecture des ids des deux extrémités
          ifs>>id_arete; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
          ifs>>s_1;if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
          ifs>>s_2; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");

        arete_sommet.push_back(std::vector<double>(3));//vecteur pour faire pareto partie 2
        arete_sommet[i][0]=id_arete;
        arete_sommet[i][1]=s_1;
        arete_sommet[i][2]=s_2;

    }

return arete_sommet;
}

std::vector<std::vector<float>> RECUP_arete_p(std::string nomFichier,std::vector<std::vector<float>> arete_ponderation)
{
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    double ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    double valeur;
    ifs>>valeur;

    float id;
    float poids1,poids2;
    //lecture des aretes
    for (double i=0; i<ordre; ++i){
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>poids1; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>poids2; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");

        arete_ponderation.push_back(std::vector<float>(3));//vecteur pour faire pareto partie 2
        arete_ponderation[i][0]=id;
        arete_ponderation[i][1]=poids1;
        arete_ponderation[i][2]=poids2;
        std::cout<<"valeur float id : "<<arete_ponderation[i][0]<<"valeur float poids1 : "<<arete_ponderation[i][1]<<"valeur float poids2 : "<<arete_ponderation[i][2]<<std::endl;
        }
return arete_ponderation;
}









