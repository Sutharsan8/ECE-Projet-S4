/**
 * \file      main.cpp
 * \author    Sutharsan Sivapalan / Noor Kardache / Evan Kermorgant
 * \version   1.0
 * \date       semaine du 15 Avril 2019
 * \brief       Les bicyclettes de triville
    Optimisation multi-objectif et circulation douce

 *
 * \details    Dans le main.cpp on  lance les commandes d'affichages defini par le menu et donc par l'utilisateur
    code source provenant d'internet, utiliser pour les combinaisons !
    http://www.cplusplus.com/reference/algorithm/next_permutation/
 */

#include "graphe.h"
///#include"recuperation.h"

using namespace std;

std::vector<std::vector<float>> RECUP_coordmoy(std::string nomFichier,std::vector<std::vector<float>> moycoord);
std::vector<std::vector<double>> RECUP_sommet_c(std::string nomFichier,std::vector<std::vector<double>> sommet_coords);
std::vector<std::vector<double>> RECUP_arete_s(std::string nomFichier,std::vector<std::vector<double>> arete_sommet);
std::vector<std::vector<float>> RECUP_arete_p(std::string nomFichier,std::vector<std::vector<float>> arete_ponderation);

        int nb_possibilites=0;
int nb_possibilites_rejetees=0;
 ///   std::vector<std::vector<int>> possibilites;
std::unordered_map<int,std::vector<int>> possibilites;

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
            miny=y;
        }
        else if (y<miny)
        {
            moycoord[0][1]=y;
            miny=y;
        }
        else if (x<minx)
        {
            moycoord[0][0]=x;
            minx=x;
        }
        else if (x>maxx)
        {
            moycoord[1][0]=x;
            maxx=x;
        }
        else if (y>maxy)
        {
            moycoord[1][1]=y;
            maxy=y;
        }
        }

    return moycoord;
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


/// Construire les combinatoire d'un graphe d'ordre N de nombres d'aretes
void combinatoire(graphe a, int nbAretes, int ordre) ///code source provenant d'internet, utiliser pour les combinaisons !
{


    int K = ordre - 1;
    int N = nbAretes;

    std::string bitmask(ordre-1, 1); // K leading 1's
    bitmask.resize(N, 0); // N-K trailing 0's

    // print integers and permute bitmask
    do {
        std::vector<int> combinaison;
        for (int i = 0; i < N; ++i) // [0..N-1] integers
        {
            if (bitmask[i])
            combinaison.push_back(i);

        }

        // possibilites.insert(std::make_pair(nb_possibilites, combinaison)).second;
        ///std::cout<< "combinaison " << combinaison[0] << " "<< combinaison[1] << " "<< combinaison[2] << std::endl;
#if 1
         if(a.DFS(ordre, combinaison)) ///verifier connexite
         {
            possibilites[nb_possibilites] = combinaison;
            nb_possibilites ++;
           /* if(!(nb_possibilites %100))
                std::cout << "nb possibilites = " << nb_possibilites << "rejetes = " << nb_possibilites_rejetees << std::endl;*/
         }
         else
            nb_possibilites_rejetees++;
#else
        possibilites[nb_possibilites] = combinaison;
        nb_possibilites ++;

#endif
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
}




int main()
{
   Svgfile svgout;
    cout<<endl<<" ----------------------- PROJET -----------------------"<<endl;
    cout<<endl<<" -------------Les bicyclettes de triville---------------"<<endl<<endl;
    cout<<endl<<" Bienvenue! "<<endl;
    cout<<endl<<" Etudier des approches pour optimiser la mise en place "<<endl;
    cout<<endl<<" d’aretes sur un reseau de circulation a construire "<<endl<<endl;
    cout<<endl<<" -------------------------------------------------------"<<endl;
    cout<<endl<<" -------------------------------------------------------"<<endl<<endl;
    std::vector<std::vector<double>> sommet_c; ///METTRE CA EN PARAMETRE DANS TA NOUVELLE FONCTION,CES VECTEURS SONT DEJA REMPLIS !
    std::vector<std::vector<double>> arete_s;
    std::vector<std::vector<float>> arete_p;
    std::vector<int> binaire;
    std::vector<std::vector<int>> sauvegarde_binaire;
    std::vector<std::vector<float>> moyco;
    std::vector<float> couts;

    sommet_c=RECUP_sommet_c("triville.txt",sommet_c);
    arete_s=RECUP_arete_s("triville.txt",arete_s);
    arete_p=RECUP_arete_p("triville_weights_0.txt",arete_p);
    moyco=RECUP_coordmoy("triville.txt",moyco);


    ///Recuperation des coordonnées utiles pour dessiner les figures
    float moyx=(moyco[1][0]-moyco[0][0])/2+moyco[0][0]+250 ;
    float moyy=(moyco[1][1]-moyco[0][1])/2+moyco[0][1]+250 ;

    ///affichage du fond
    svgout.addRectangle(0,0,moyx,0,moyx,moyy,0,moyy,"azure");
    svgout.addRectangle(moyx,moyy,moyx*2,moyy,moyx*2,moyy*2,moyx,moyy*2,"azure");
    svgout.addRectangle(moyx,0,moyx*2,0,moyx*2,moyy,moyx,moyy,"paleturquoise");
    svgout.addRectangle(0,moyy,moyx,moyy,moyx,moyy*2,0,moyy*2,"paleturquoise");
    svgout.addLine(550,900,550,550,"blue");///axe ordonnees
    svgout.addLine(550,550,540,560,"blue");///fleches qui pointe vers le haut. PARTIE DE GAUCHE
    svgout.addLine(550,550,560,560,"blue");///fleches qui pointe vers le haut. PARTIE DE DROITE
    svgout.addText(530,550,"Couts 2","blue");///texte COUTS2
    svgout.addLine(550,900,900,900,"blue");///axe abscisses
    svgout.addLine(900,900,890,890,"blue");///fleches qui pointe vers la droite. PARTIE DE GAUCHE
    svgout.addLine(900,900,890,910,"blue");///fleches qui pointe vers la droite. PARTIE DE DROITE
    svgout.addText(910,910,"Couts 1","blue");///texte COUTS1

    ///Affichage du graphique avec les id des sommets et les id des aretes
    graphe a{"triville.txt",1, svgout,sommet_c,arete_s,arete_p};
    ///Affiche du titre du graph
    svgout.addTexttitre((moyco[1][0]+moyco[0][0])/2,moyco[0][1]-40,"Graphe de triville","fill:black;stroke:slategray;font-size:20px; text-anchor:middle;");

    ///Affichage du graphique de Ponderation
    graphe b{"triville_weights_0.txt",2, svgout,sommet_c,arete_s,arete_p};
    ///Affiche du titre du graph de ponderation
    svgout.addTexttitre(((moyco[1][0]+moyco[0][0])/2) + 500,moyco[0][1]-40,"Ponderation de triville","fill:black;stroke:slategray;font-size:20px; text-anchor:middle;");

    ///On affiche dans la console les données liées au graphe a et b
    a.afficher(1);
    b.afficher(2);

    ///On recupere les données des couts totaux
    int krusk;
    do{
    std::cout<<"En fonction de quel POIDS pour Kruskal : Poids 1 : 1; Poids 2 : 2"<<std::endl;
    cin>>krusk;}while(krusk>2);
    couts=a.kruskal(krusk,"triville.txt","triville_weights_0.txt",svgout,sommet_c,arete_s,arete_p,couts);///PREMIER ARGUMENT CEST POUR LE POIDS,SI KRUSKAL EN FONTCTION DU PREMIER POIDS METTRE 1, SI EN FONCTION DU DEUXIEME POIDS,METTRE 2

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
     svgout.addTexttitre(moyxK,maxyK+10,"Arbre pour triville selon l'objectif ","fill:black;stroke:slategray;font-size:20px; text-anchor:middle;");

     ///On affiche ici les grands titres du projet
     svgout.addTexttitre(moyx,moyy-10,"PROJET","fill:lightseagreen;stroke:black;font-size:80px; text-anchor:middle;");
     svgout.addTexttitre(moyx,moyy+20,"Les bicyclettes de triville","fill:lightseagreen;stroke:lightseagreen;font-size:20px; text-anchor:middle;");



    cout<< "Calcule des combinatoires: Ordre du graphe: "<<a.GetOrdre()<<" Nombre d'Aretes: "<<a.GetTaille()<<"\n";
    combinatoire(a, a.GetTaille(),a.GetOrdre());
    cout<<"Fin du calcul: Nombre de possibilitees : " << nb_possibilites << std::endl;


#if 0
    /// Afficher la liste de toutes les possibilites quand c'est raisonnable
    for(std::unordered_map<int,std::vector<int>>::iterator it=possibilites.begin(); it!=possibilites.end(); ++it)
    {
        std::vector<int> v = it->second;
        std::cout<<"Possibilite : " << v[0] <<" " << v[1]<< " " << v[2]<<  ". Cout : (" << a.calculerCout(1, v) << ", " << a.calculerCout(2, v) << ")"<< std::endl;
    }
#endif

    /// mainenant on s'attaque a Paretto
            int aff;
            do{
            std::cout<<"Voulez vous afficher le nuage de points pour pareto? OUI : 1 ; NON : 2"<<std::endl;
            std::cin>>aff;}while(aff>2);
    cout<<"Calcul de la domination : " << std::endl;
    for(std::unordered_map<int,std::vector<int>>::iterator it1=possibilites.begin(); it1!=possibilites.end(); ++it1)
    {
        /// calculer les deux couts
        double cout1_1 = a.calculerCout(1, it1->second);
        double cout1_2 = a.calculerCout(2, it1->second);

        /// std::cout << "possibilite: " << it1->first << " cout1: "<< cout1_1 << " cout2: "<< cout1_2 << std::endl;

        std::unordered_map<int,std::vector<int>>::iterator it2=possibilites.begin();
        do
        {
            ///Verifier si it2 est domine par it1
            /// Chaque sommet est represente par un tableau [sommetId, Xcoord, Ycoord]
            /// Chaque arete est representee par un tableau [AreteId, sommetId, sommetId]
            /// Chaque ponderation d'arete est representee par un tableau [AreteId, poids1, poids2]
            double cout2_1 = a.calculerCout(1, it2->second);
            double cout2_2 = a.calculerCout(2, it2->second);

        if(aff==1)
       svgout.addCircle(550+3*cout2_1,900-3*cout2_2,1,2,"red");


            /// std::cout << "\t compare avec possibilite: " << it2->first  << " cout1: "<< cout2_1 << " cout2: " << cout2_2 << std::endl;
            if(cout1_1 < cout2_1 && cout1_2 <= cout2_2 ||
                cout1_1 == cout2_1 && cout1_2 < cout2_2)
            {
                /// Le deuxieme element est domine par le premier retirer le deuxieme element de la map
                /// std::cout << "\t " << it2->first  << " est domine. On le retire" << std::endl;
                std::unordered_map<int,std::vector<int>>::iterator it3 = it2;
                it3 ++;
                possibilites.erase (it2);
                it2 = it3;
                nb_possibilites --;
            }
            else
                it2 ++;
        } while (it2!=possibilites.end());
    }

    cout<<"nb de possibilitees de Pareto: " << nb_possibilites << std::endl;

#if 1
    /// donner la liste des possibilites quand c'est raisonnable
    for(std::unordered_map<int,std::vector<int>>::iterator it=possibilites.begin(); it!=possibilites.end(); ++it)
    {
        std::vector<int> v = it->second;
        std::cout<<"Possibilite :";
        for(int i=0; i<v.size(); i++)
        std::cout<< " " << v[i] ;
       std::cout << " . Cout : (" << a.calculerCout(1, v) << ", " << a.calculerCout(2, v) << ")"<< std::endl;
       ///AFFICHAGE DES POINTS VERT QUI SIGNIFIE QUILS SONT SELECTIONNEES
       if(aff==1)
       svgout.addCircle(550+3*(a.calculerCout(1, v)),900-3*(a.calculerCout(2, v)),3,6,"lawngreen");
    }
#endif
}



