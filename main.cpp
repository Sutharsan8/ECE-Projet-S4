#include <iostream>
#include "graphe.h"
<<<<<<< HEAD
#include <algorithm>
=======

///Une partie du code de recuperation en binaire venant d'internet qui est dans la méthode RECUP_binaire
///http://www.cplusplus.com/reference/algorithm/next_permutation/

>>>>>>> ft_graphfinal
using namespace std;

std::vector<std::vector<double>> RECUP_sommet_c(std::string nomFichier,std::vector<std::vector<double>> sommet_coords);
std::vector<std::vector<double>> RECUP_arete_s(std::string nomFichier,std::vector<std::vector<double>> arete_sommet);
std::vector<std::vector<float>> RECUP_arete_p(std::string nomFichier,std::vector<std::vector<float>> arete_ponderation);
//std::vector<std::vector<double>> Conversion_binaire_arete(std::string nomFichier,std::string nomFichier1,std::vector<std::vector<double>> arete_pareto_1,std::vector<std::vector<bool>> sauvegarde_binaire,std::vector<std::vector<double>> arete_sommet);

int main()
{
    Svgfile svgout;
    svgout.addRectangle(0,0,500,0,500,500,0,500,"skyblue");
    svgout.addRectangle(500,500,1000,500,1000,1000,500,1000,"skyblue");
    svgout.addRectangle(500,0,1000,0,1000,500,500,500,"lightgreen");
    svgout.addRectangle(0,500,500,500,500,1000,0,1000,"lightgreen");
    std::vector<std::vector<double>> sommet_c;
    std::vector<std::vector<double>> arete_s;
    std::vector<std::vector<float>> arete_p;
    std::vector<bool> binaire;
    std::vector<std::vector<bool>> sauvegarde_binaire;
    std::vector<std::vector<double>> arete_pareto_1;

    sommet_c=RECUP_sommet_c("manhattan.txt",sommet_c);
    arete_s=RECUP_arete_s("manhattan.txt",arete_s);
    arete_p=RECUP_arete_p("manhattan_weights_0.txt",arete_p);

   // arete_pareto_1=Conversion_binaire_arete("manhattan.txt","manhattan_weights_0.txt",arete_pareto_1,sauvegarde_binaire,arete_s);


    graphe a{"manhattan.txt",1, svgout,sommet_c,arete_s,arete_p};
    graphe b{"manhattan_weights_0.txt",2, svgout,sommet_c,arete_s,arete_p};

    a.afficher(1);
    b.afficher(2);

    a.kruskal(1,"manhattan.txt","manhattan_weights_0.txt",svgout,sommet_c,arete_s,arete_p);///PREMIER ARGUMENT CEST POUR LE POIDS,SI KRUSKAL EN FONTCTION DU PREMIER POIDS METTRE 1, SI EN FONCTION DU DEUXIEME POIDS,METTRE 2
    sauvegarde_binaire=a.RECUP_binaire("manhattan.txt","manhattan_weights_0.txt",binaire,sauvegarde_binaire);
    arete_pareto_1=a.Conversion_binaire_arete("manhattan.txt","manhattan_weights_0.txt",arete_pareto_1,sauvegarde_binaire);
   /* for(double h=0;h<sauvegarde_binaire.size();++h) ///TEST POUR SAVOIR SI C RECUPER
    {
        std::cout<<"!!!!"<<std::endl;
        for(double m=0;m<5;++m)
        {
            std::cout << arete_pareto_1[h][m]<<";";
        }
    }*/
   /* for(int h=0;h<sauvegarde_binaire.size();++h)
        for(int m=0;m<3;++m)
            std::cout << arete_pareto_1[h][m]<<"//////"<<std::endl;
    return 0;*/
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



/*std::vector<std::vector<bool>> RECUP_binaire(std::string nomFichier,std::string nomFichier1,std::vector<bool> binaire,std::vector<std::vector<bool>> sauvegarde_binaire)
{
    std::vector<bool> tempon;
    int compte=0;
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    int ordre;
    ifs >> ordre;
    std::ifstream ifs2{nomFichier1};
    if (!ifs2)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    int taille;
    ifs2 >> taille;
   // puissance=std::pow(2,ordre-1);
      ///code de recuperation en binaire venant d'internet
      ///http://www.cplusplus.com/reference/algorithm/next_permutation/


    for (int i=0; i<taille; ++i){    ///Pareto, premiere partie afin d'optimiser des le debut ordre-1 arete
    if(i<ordre-1)
    binaire.push_back(1);
    else if(i>=ordre-1)
    binaire.push_back(0);}


std::sort(binaire.begin(),binaire.end());  ///tri du vecteur initialiser precedemment

        do {
        for(int i=0; i<binaire.size() ;++i)
        {
            tempon.push_back(binaire[i]);///on push dans la vecteur tempon les differents cas
        }
        sauvegarde_binaire.push_back(tempon);///on push dans la vecteur finale qui contient tous les differents cas
        tempon.clear();///on supprime le vecteur a une dimension pour pouvoir re-affecter des variables, donc des cas differents de binaire grace a la boucle do while

        } while ( std::next_permutation(binaire.begin(),binaire.end()) );
///FIN DE CODE SOURCE,INSPIRE DU SITE INTERNET


return sauvegarde_binaire;
}*/


/*std::vector<std::vector<double>> Conversion_binaire_arete(std::string nomFichier,std::string nomFichier1,std::vector<std::vector<double>> arete_pareto_1,std::vector<std::vector<bool>> sauvegarde_binaire,std::vector<std::vector<double>> arete_sommet)
{
    int c=0;
     std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    int ordre;
    ifs >> ordre;
    std::ifstream ifs2{nomFichier1};
    if (!ifs2)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier1 );
    int taille;
    ifs2 >> taille;

    for(double h=0;h<sauvegarde_binaire.size();++h)
    {
        std::cout<<std::endl;
        for(double m=0;m<taille;++m)
        {
            std::cout << sauvegarde_binaire[h][m]<<";";
            if((sauvegarde_binaire[h][m])==1)
            {
                arete_pareto_1[h][c]=m;
                ++c;
            }
        }
    }
    for(int h=0;h<sauvegarde_binaire.size();++h)
        for(int m=0;m<ordre-1;++m)
            std::cout << arete_pareto_1[h][m]<<"//////"<<std::endl;
return arete_pareto_1;
}
*/





