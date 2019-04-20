#include <iostream>
#include "graphe.h"
#include <algorithm>
using namespace std;

std::vector<std::vector<double>> RECUP_sommet_c(std::string nomFichier,std::vector<std::vector<double>> sommet_coords);
std::vector<std::vector<double>> RECUP_arete_s(std::string nomFichier,std::vector<std::vector<double>> arete_sommet);
std::vector<std::vector<float>> RECUP_arete_p(std::string nomFichier,std::vector<std::vector<float>> arete_ponderation);
std::vector<std::vector<double>> RECUP_binaire(std::string nomFichier,std::string nomFichier1,std::vector<std::vector<double>> arete_sommet,std::vector<std::vector<double>> binaire);

int main()
{
    Svgfile svgout;
    std::vector<std::vector<double>> sommet_c; ///METTRE CA EN PARAMETRE DANS TA NOUVELLE FONCTION,CES VECTEURS SONT DEJA REMPLIS !
    std::vector<std::vector<double>> arete_s;
    std::vector<std::vector<float>> arete_p;
    std::vector<std::vector<double>> binaire;
    sommet_c=RECUP_sommet_c("manhattan.txt",sommet_c);
    arete_s=RECUP_arete_s("manhattan.txt",arete_s);
    arete_p=RECUP_arete_p("manhattan_weights_0.txt",arete_p);
    binaire=RECUP_binaire("manhattan.txt","manhattan_weights_0.txt",arete_s,binaire);
    graphe a{"manhattan.txt",1, svgout,sommet_c,arete_s,arete_p};
    graphe b{"manhattan_weights_0.txt",2, svgout,sommet_c,arete_s,arete_p};
    a.afficher(1);
    b.afficher(2);
    a.kruskal(1,"manhattan.txt","manhattan_weights_0.txt",svgout,sommet_c,arete_s,arete_p);///PREMIER ARGUMENT CEST POUR LE POIDS,SI KRUSKAL EN FONTCTION DU PREMIER POIDS METTRE 1, SI EN FONCTION DU DEUXIEME POIDS,METTRE 2
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
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture données id");///RECUPERER LA VALEUR DU SOMMET 1
        ifs>>x; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet1");///RECUPERER COORD X
        ifs>>y; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet2");///RECUPERER COORD Y

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

        }
return arete_ponderation;
}



std::vector<std::vector<double>> RECUP_binaire(std::string nomFichier,std::string nomFichier1,std::vector<std::vector<double>> arete_sommet,std::vector<double> binaire)
{

    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    double ordre;
    ifs >> ordre;
    std::ifstream ifs2{nomFichier1};
    if (!ifs2)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    double taille;
    ifs2 >> taille;
      ///code de recuperation en binaire venant d'internet
      ///http://www.cplusplus.com/reference/algorithm/next_permutation/


    for (int i=0; i<(ordre-1); ++i){
        binaire.push_back(1);//vecteur pour faire pareto partie 2
        for(int o=0;o<taille;++o)
                {
                std::cout << binaire[i][o];
                }
            std::cout<<std::endl;
    }
    for (int i=ordre-1; i<taille; ++i){
        binaire.push_back(0);//vecteur pour faire pareto partie 2
    }

  /*  for(int i=0;i<taille;++i)
    std::sort(arete_sommet.begin(),arete_sommet.end());

  std::cout << "The n possible permutations with n elements:\n";*/


          /*  do {
                std::cout << binaire[0] << ' ' << binaire[1] << ' ' << binaire[2] << '\n';
            } while ( std::next_permutation(myints,myints+3) );*/

        /*    for(int i=0;i<ordre-1;++i)
            {
                for(int o=0;o<taille;++o)
                {
                std::cout << binaire[i][o] << ' ';
                }
            std::cout<<std::endl;
            }
*/

  //std::cout << "After loop: " << myints[0] << ' ' << myints[1] << ' ' << myints[2] << '\n';

return arete_sommet;
}








