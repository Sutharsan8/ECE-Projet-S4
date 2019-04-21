/**
 * \file      main.cpp
 * \author    Sutharsan Sivapalan / Noor Kardache / Evan Kermorgant
 * \version   1.0
 * \date       semaine du 15 Avril 2019
 * \brief       Les bicyclettes de triville
    Optimisation multi-objectif et circulation douce

 *
 * \details    Dans le main.cpp on  lance les commandes d'affichages definir par le menu et donc par l'utilisateur
 */
#include <iostream>
#include "graphe.h"

using namespace std;

std::vector<std::vector<float>> RECUP_coordmoy(std::string nomFichier,std::vector<std::vector<float>> moycoord);
std::vector<std::vector<double>> RECUP_sommet_c(std::string nomFichier,std::vector<std::vector<double>> sommet_coords);
std::vector<std::vector<double>> RECUP_arete_s(std::string nomFichier,std::vector<std::vector<double>> arete_sommet);
std::vector<std::vector<float>> RECUP_arete_p(std::string nomFichier,std::vector<std::vector<float>> arete_ponderation);

int main()
{
    Svgfile svgout;
    std::vector<std::vector<double>> sommet_c;
    std::vector<std::vector<double>> arete_s;
    std::vector<std::vector<float>> arete_p;
    std::vector<std::vector<double>> arete_pareto_1;
    std::vector<std::vector<float>> moyco;
    std::vector<float> couts;

    sommet_c=RECUP_sommet_c("manhattan.txt",sommet_c);
    arete_s=RECUP_arete_s("manhattan.txt",arete_s);
    arete_p=RECUP_arete_p("manhattan_weights_0.txt",arete_p);
    moyco=RECUP_coordmoy("manhattan.txt",moyco);

    ///Recuperation des coordonnées utiles pour dessiner les figures
    float moyx=(moyco[1][0]-moyco[0][0])/2+moyco[0][0]+250 ;
    float moyy=(moyco[1][1]-moyco[0][1])/2+moyco[0][1]+250 ;

    ///affichage du fond
    svgout.addRectangle(0,0,moyx,0,moyx,moyy,0,moyy,"azure");
    svgout.addRectangle(moyx,moyy,moyx*2,moyy,moyx*2,moyy*2,moyx,moyy*2,"azure");
    svgout.addRectangle(moyx,0,moyx*2,0,moyx*2,moyy,moyx,moyy,"paleturquoise");
    svgout.addRectangle(0,moyy,moyx,moyy,moyx,moyy*2,0,moyy*2,"paleturquoise");

    ///Affichage du graphique avec les id des sommets et les id des aretes
    graphe a{"manhattan.txt",1, svgout,sommet_c,arete_s,arete_p};
    ///Affiche du titre du graph
    svgout.addTexttitre((moyco[1][0]+moyco[0][0])/2,moyco[0][1]-40,"Graphe de manhattan","fill:black;stroke:slategray;font-size:20px; text-anchor:middle;");

    ///Affichage du graphique de Ponderation
    graphe b{"manhattan_weights_0.txt",2, svgout,sommet_c,arete_s,arete_p};
    ///Affiche du titre du graph de ponderation
    svgout.addTexttitre(((moyco[1][0]+moyco[0][0])/2) + 500,moyco[0][1]-40,"Ponderation de manhattan","fill:black;stroke:slategray;font-size:20px; text-anchor:middle;");

    ///On affiche dans la console les données liées au graphe a et b
    a.afficher(1);
    b.afficher(2);

    ///On recupere les données des couts totaux
    couts=a.kruskal(1,"manhattan.txt","manhattan_weights_0.txt",svgout,sommet_c,arete_s,arete_p,couts);///PREMIER ARGUMENT CEST POUR LE POIDS,SI KRUSKAL EN FONTCTION DU PREMIER POIDS METTRE 1, SI EN FONCTION DU DEUXIEME POIDS,METTRE 2

     float moyxK=(moyco[0][0]+moyco[1][0])/2;
     float minyK=moyco[0][1]+500-20;
     float maxyK=moyco[1][1]+500+50;

     ///On affiche ici les couts totaux
     svgout.addText(moyxK-30,minyK,"(","blue");
     svgout.addText(moyxK-20,minyK,couts[0],"blue");
     svgout.addText(moyxK,minyK,";","blue");
     svgout.addText(moyxK+10,minyK,couts[1],"blue");
     svgout.addText(moyxK+30,minyK,")","blue");

     ///Affichage du titre de l'arbre couvrants de poids minimal
     svgout.addTexttitre(moyxK,maxyK,"Arbre pour manhattan selon l'objectif 1","fill:black;stroke:slategray;font-size:20px; text-anchor:middle;");

     ///On affiche ici les grands titres du projet
     svgout.addTexttitre(moyx,moyy-10,"PROJET","fill:lightseagreen;stroke:black;font-size:80px; text-anchor:middle;");
     svgout.addTexttitre(moyx,moyy+20,"Les bicyclettes de manhattan","fill:lightseagreen;stroke:lightseagreen;font-size:20px; text-anchor:middle;");
}


/**
 * \brief       Recuperation des sommmets
 * \details    On stock dans un vecteur de vecteur les donnees des sommets
               extrait du fichier "nomFichier".
 * \param    nomFichier         On prend les données selon un fichier precis.
 * \param    sommet_coords       On stock ici les identifiants des sommets et leurs coordonnées.
 * \return    Un \e std::vector<std::vector<double>> \b sommet_coords qui contient toutes les données voulu.
 */
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

/**
 * \brief       Recuperation des données liés aux sommets adjacents (liés par des aretes).
 * \details    On stock dans un vecteur de vecteur les donnees des aretes
               extrait du fichier "nomFichier".
 * \param    nomFichier         On prend les données selon un fichier precis.
 * \param    aretes_sommet       On stock ici les identifiants des aretes et leurs extrémités.
 * \return    Un \e std::vector<std::vector<double>> \b aretes_sommet qui contient toutes les données voulu.
 */
 std::vector<std::vector<double>> RECUP_arete_s(std::string nomFichier,std::vector<std::vector<double>> arete_sommet)
{
    double id;
    double x,y;
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

/**
 * \brief       Recuperation des coordonnées moyennes pour dessiner le grahique
 * \details    On stock dans un vecteur de vecteur les coordonnées les plus petites et les plus grandes.
               extrait du fichier "nomFichier".
 * \param    nomFichier         On prend les données selon un fichier precis.
 * \param    moycoord       On stock ici les coordonnées les plus grandes et les plus petites.
 * \return    Un \e std::vector<std::vector<double>> \b moycoord qui contient toutes les données voulu.
 */
std::vector<std::vector<float>> RECUP_coordmoy(std::string nomFichier,std::vector<std::vector<float>> moycoord)
{
    double id;
    double x,y;
    double ordre;
    double maxx,maxy=0;
    double minx,miny=1000000;
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
        moycoord.push_back(std::vector<float>(2));
        if (i==0)
        {
            moycoord[0][0]=x;
            moycoord[0][1]=y;
            minx=x;
            std::cout<<minx<<std::endl;
            miny=y;
            std::cout<<miny<<std::endl;
        }
        else if (y<miny)
        {
            moycoord[0][1]=y;
            miny=y;
            std::cout<<miny<<std::endl;
        }
        else if (x<minx)
        {
            moycoord[0][0]=x;
            minx=x;
            std::cout<<minx<<std::endl;
        }
        else if (x>maxx)
        {
            moycoord[1][0]=x;
            maxx=x;
            std::cout<<maxx<<std::endl;
        }
        else if (y>maxy)
        {
            moycoord[1][1]=y;
            maxy=y;
            std::cout<<maxy<<std::endl;
        }
        }

    return moycoord;
}

/**
 * \brief       Recuperation des ponderations des aretes
 * \details    On stock dans un vecteur de vecteur les ponderations des aretes
               extrait du fichier "nomFichier".
 * \param    nomFichier         On prend les données selon un fichier precis.
 * \param    arete_ponderation       On stock ici les identifiants des aretes et leurs ponderations.
 * \return    Un \e std::vector<std::vector<float>> \b arete_ponderation qui contient toutes les données voulu.
 */
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
