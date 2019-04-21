#include <fstream>
#include <iostream>
#include <stack>          // std::stack
#include "graphe.h"
#include"sommet.h"
using namespace std;

///code source provenant d'internet, utiliser pour les combinaisons dans void combinatoire!
///http://www.cplusplus.com/reference/algorithm/next_permutation/


graphe::graphe(std::string nomFichier, int choix, Svgfile& svgout,std::vector<std::vector<double>> sommet_coords,std::vector<std::vector<double>> arete_sommet,std::vector<std::vector<float>>arete_ponderation):m_sommet_coords{sommet_coords},m_arete_sommet{arete_sommet},m_arete_ponderation{arete_ponderation}
{
    double tableau_Coordonne[50][3];
    double tableauarete[50][3];
    double tableaupoids[50][3];
    double ordre;

    if(choix==1)
    {
        double x1;double y1;
        double x2;double y2;

        ///fichier 1
        std::ifstream ifs{nomFichier};
        if (!ifs)
            throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );

        ifs >> ordre;
        if ( ifs.fail() )
            throw std::runtime_error("Probleme lecture ordre du graphe");


        double id;
        double x,y;

        //lecture des sommets, chaque ligne contient l'id du sommet, puis les deux coordonees
        for (int i=0; i<ordre; ++i)
        {
            ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture données id");
            ifs>>x; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet1");
            ifs>>y; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet2");

            /// Populer la map des sommets
            m_sommets.insert({id, new Sommet{id,x,y}}); ///premiere partie du fichier 1 recupere

            /// Puis le vecteurs de tous les sommets
            m_sommet_coords[i][0]=id;
            m_sommet_coords[i][1]=x;
            m_sommet_coords[i][2]=y;

            /// ???
            tableauarete[i][0]=id;
            tableauarete[i][1]=x;
            tableauarete[i][2]=y;
        }

        /// Lecture du nombre d'Aretes
        double id_arete;
        double s_1,s_2;
        double taille;
        ifs>>taille;

        /// lecture des aretes, chaque arete est representee par son id, et les deux id des sommets.
        for (int i=0; i<taille; ++i)
        {
            //lecture des ids des deux extrémités
            ifs>>id_arete; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
            ifs>>s_1;if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
            ifs>>s_2; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");

            /// Tout d'abord verifier que les sommets de l'arete existent bien !
            if(m_sommets.find(s_1) == m_sommets.end() ||
                m_sommets.find(s_2) == m_sommets.end())
            {
                throw std::runtime_error( "Arete ayant un sommet non defini" + nomFichier );
            }

            /// Inserer l'arete dans la map des aretes
            m_arete.insert({id_arete, new Arete{id_arete,s_1,s_2,0,0}});

            /// Populer une vecteur d'aretes
            m_arete_sommet[i][0]=id_arete;
            m_arete_sommet[i][1]=s_1;
            m_arete_sommet[i][2]=s_2;

            /// Remplir a nouveau une table d'aretes [areteId, sommetId, sommetId]
            tableau_Coordonne[i][0]=id_arete;
            tableau_Coordonne[i][1]=s_1;
            tableau_Coordonne[i][2]=s_2;

            /// Verifier que les sommets de l'arete existent bien !
            if(m_sommets.find(s_1) != m_sommets.end()) /// si le sommet existe
            {
                Sommet*s0=(m_sommets.find(s_1))->second; ///récupation des valeurs puis affichage
                x1=s0->GetX();y1=s0->GetY();
            }
            if(m_sommets.find(s_2)!=m_sommets.end()) /// si le sommet existe
            {
                Sommet*s0=(m_sommets.find(s_2))->second; ///récupation des valeurs puis affichage
                x2=s0->GetX();y2=s0->GetY();
            }
            svgout.addLine(x1,y1,x2,y2,"black");
            svgout.addCircle(x1,y1,3,5,"black");
            svgout.addLine(x1,y1,x2,y2,"black");
            svgout.addCircle(x1,y1,3,5,"black");
            svgout.addCircle(x2,y2,3,5,"black");
            svgout.addText(x1-5,y1-5,s_1,"red");
            svgout.addText(x2-5,y2-5,s_2,"red");

            if(y1==y2)
            svgout.addText((x1+x2)/2,y1-5,id_arete,"green");
            if(x1==x2)
            svgout.addText(x2-10,(y1+y2)/2,id_arete,"green");
            if(x1==y2 && x2==y1)
            svgout.addText((x1+x2)/2-5,(y2+y1)/2-5,id_arete,"green");
            if(x1!=x2 && y1!=y2)
            svgout.addText((x1+x2)/2-5,(y2+y1)/2-5,id_arete,"green");
        }
    }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(choix==2)
    {
        /// Lire le fichier de ponderation
        std::ifstream ifs{nomFichier};
        if (!ifs)
            throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
        double taille;
        ifs >> taille;

        if ( ifs.fail() )
            throw std::runtime_error("Probleme lecture nombre d'Aretes");
        double valeur;
        ifs>>valeur;
        int marcher=0;
        double id;
        double poids1,poids2;
        double sommet1;double sommet2;
        double x1,x2,y1,y2;
        //lecture de la ponderation des aretes
        for (int i=0; i<taille; ++i){
            ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
            ifs>>poids1; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
            ifs>>poids2; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");

            /// Initialiser u vectuer de ponderation qui sera rempli plus tard
            m_arete_ponderation.push_back(std::vector<float>(3));//vecteur pour faire pareto partie 2

            /// stocker la ponderation des aretes dans la tables de ponderation
            m_arete_ponderation[i][0]=id;
            m_arete_ponderation[i][1]=poids1;
            m_arete_ponderation[i][2]=poids2;

            /// stocker la ponderation des aretes dans la tables de ponderation
            tableaupoids[i][0]=id;
            tableaupoids[i][1]=poids1;
            tableaupoids[i][2]=poids2;

            /// Verifier si l'arete ponderee se trouve au meme index que l'arete deja lue
            /// precedemment dans le fichier de definition du graphe
            /// tableau_Coordonne sous forme  [areteId, sommetId, sommetId]
            if(id==tableau_Coordonne[i][0])
            {
                sommet1=tableau_Coordonne[i][1];
                sommet2=tableau_Coordonne[i][2];
            }

            for(int r=0;r<50;++r)
        {

            if(sommet1==(tableauarete[r][0])) /// si le sommet existe
            {
                if((tableauarete[r][1])>=50){
                x1=tableauarete[r][1];
                y1=tableauarete[r][2];marcher++;}
            }
            if(sommet2==(tableauarete[r][0])) /// si le sommet existe
            {
                x2=tableauarete[r][1];
                y2=tableauarete[r][2];
                marcher++;
            }
        if((marcher%2)==0){//on verifie ici si on pas bien recuperé deux sommets enfin de les dessiners
        svgout.addLine(x1+500,y1,x2+500,y2,"black");
        svgout.addCircle(x1+500,y1,3,5,"black");
        svgout.addCircle(x2+500,y2,3,5,"black");}

        }

        if(y1==y2)
            {
                svgout.addText((x1+x2)/2+500-15,y1-5,tableaupoids[i][1],"yellow");
                svgout.addText((x1+x2)/2+500,y1-5," ; ","yellow");
                svgout.addText((x1+x2)/2+500+5,y1-5,tableaupoids[i][2],"yellow");
            }

        if(x1==x2)
        {
            svgout.addText(x2-15+500,(y1+y2)/2,tableaupoids[i][1],"yellow");
            svgout.addText(x2+500,(y1+y2)/2," ; ","yellow");
            svgout.addText(x2+5+500,(y1+y2)/2,tableaupoids[i][2],"yellow");
        }

        if(x1==y2 && x2==y1)
        {
            svgout.addText((x1+x2)/2-5-10+500,(y2+y1)/2-5,tableaupoids[i][1],"yellow");
            svgout.addText((x1+x2)/2+500,(y2+y1)/2-5," ; ","yellow");
            svgout.addText((x1+x2)/2-5+10+500,(y2+y1)/2-5,tableaupoids[i][2],"yellow");
        }
        if(x1!=x2 && y1!=y2)
        {
            svgout.addText((x1+x2)/2-5-10+500,(y2+y1)/2-5,tableaupoids[i][1],"yellow");
            svgout.addText((x1+x2)/2+500,(y2+y1)/2-5," ; ","yellow");
            svgout.addText((x1+x2)/2-5+10+500,(y2+y1)/2-5,tableaupoids[i][2],"yellow");
        }
            m_arete_poids.insert({id,new Arete{id,sommet1,sommet2,poids1,poids2}});
        }
    }
}


void graphe::afficher(int choix) const
{
    if(choix==1){
    int numero=0;
    int numero1=0;
    int nbsommet=0;
    int nbarete=0;

    std::cout<<"graphe : "<<std::endl;
    std::cout<<"Ordre : "<<m_sommets.size()<<std::endl;
    for(int i=0;i<m_sommets.size();++i)
    while ( nbsommet != m_sommets.size()) /// Tant qu'on a pas trouvé le même nombre de sommet que le graphe comporte
    {
        if(m_sommets.find(numero)!=m_sommets.end()) /// si le sommet existe
        {
            Sommet*s0=(m_sommets.find(numero))->second; ///récupation des valeurs puis affichage
            s0->afficherData();
            nbsommet++;
        }
        numero++;
        std::cout<<std::endl;
    }
    std::cout<<"nombre d'aretes : "<<m_arete.size()<<std::endl;
    while ( nbarete != m_arete.size()) /// Tant qu'on a pas trouvé le même nombre de sommet que le graphe comporte
    {
        if(m_arete.find(numero1)!=m_arete.end()) /// si le sommet existe
        {
            Arete*a0=(m_arete.find(numero1))->second; ///récupation des valeurs puis affichage
            a0->afficherData();
            nbarete++;
        }
        numero1++;
        std::cout<<std::endl;
    }
}

if(choix==2)
{
    int numero2=0;
    int nbarete1=0;

    std::cout<<std::endl;
    std::cout<<"Ordre : "<<m_arete_poids.size()<<std::endl;

    while ( nbarete1 != m_arete_poids.size()) /// Tant qu'on a pas trouvé le même nombre de sommet que le graphe comporte
    {
        if(m_arete_poids.find(numero2)!=m_arete_poids.end()) /// si le sommet existe
        {
            Arete*a0=(m_arete_poids.find(numero2))->second; ///récupation des valeurs puis affichage
            a0->afficherPoids();
            nbarete1++;
        }
        numero2++;
        std::cout<<std::endl;
    }
}
}

std::vector<float> graphe::kruskal(int poids,std::string nomFichier,std::string nomFichier2,Svgfile& svgout,std::vector<std::vector<double>> sommet_coords,std::vector<std::vector<double>> arete_sommet,std::vector<std::vector<float>>arete_ponderation,std::vector<float> m_couts) const
{
    std::ifstream ifs{nomFichier};
    int ordre;
    double tableau_Coordonne[50][3];
    double tableauarete[50][3];
    double tableaupoids[50][3];
    double tableaukruskal[50][3];
    double aff[50][3];
    double tableau_CoordonneINITIALE[50][3];
    double id;
    double poids1,poids2;
    double x1,x2,y1,y2;
    double x,y;
    ifs >> ordre;

    for (int i=0; i<ordre; ++i){
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>x; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>y; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        tableauarete[i][0]=id;
        tableauarete[i][1]=x;
        tableauarete[i][2]=y;
    }

    double id_arete;
    double s_1,s_2;
    double taille;
    ifs>>taille;

    //lecture des aretes
    for (int i=0; i<taille; ++i)
    {
        //lecture des ids des deux extrémités
          ifs>>id_arete; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
          ifs>>s_1;if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
          ifs>>s_2; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");


        tableau_Coordonne[i][0]=id_arete;
        tableau_Coordonne[i][1]=s_1;
        tableau_Coordonne[i][2]=s_2;
        tableau_CoordonneINITIALE[i][0]=id_arete;
        tableau_CoordonneINITIALE[i][1]=s_1;
        tableau_CoordonneINITIALE[i][2]=s_2;

    }
    std::ifstream ifs2{nomFichier2};
    int taille1;
    ifs2 >> taille1;
    int valeur;
    ifs2>>valeur;

    //lecture des sommets
    for (int i=0; i<taille1; ++i)
    {
        ifs2>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs2>>poids1; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs2>>poids2; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        tableaupoids[i][0]=id;
        tableaupoids[i][1]=poids1;
        tableaupoids[i][2]=poids2;
        aff[i][0]=id;
        aff[i][1]=poids1;
        aff[i][2]=poids2;
    }
    for(int y=0;y<taille1;++y)
    for (int i=0; i<taille1; ++i)
    {
        if(tableaupoids[i][poids]>tableaupoids[i+1][poids] && i+1<taille)
        {
            int stock[50][3];
            stock[i][1]=tableaupoids[i][1];//on change juste le poids 1 dont 2ieme colonne
            tableaupoids[i][1]=tableaupoids[i+1][1];
            tableaupoids[i+1][1]=stock[i][1];
            ///
            stock[i][0]=tableaupoids[i][0];
            tableaupoids[i][0]=tableaupoids[i+1][0];
            tableaupoids[i+1][0]=stock[i][0];
            ///
            stock[i][2]=tableaupoids[i][2];
            tableaupoids[i][2]=tableaupoids[i+1][2];
            tableaupoids[i+1][2]=stock[i][2];
        }
    }
    for(int u=0;u<taille1;++u)
    {
        for(int i=0;i<taille1;++i)
        if(tableaupoids[u][0]==tableau_Coordonne[i][0])
        {

            tableaukruskal[u][0]=tableau_Coordonne[i][0];
            tableaukruskal[u][1]=tableau_Coordonne[i][1];
            tableaukruskal[u][2]=tableau_Coordonne[i][2];
        }
    }


    int comparer[taille1][2];
    for(int i=0;i<taille1;++i){
        comparer[i][0]=tableauarete[i][0];
        comparer[i][1]=tableauarete[i][0];
    }

    int finale[ordre-1][3];
    int f,g,r;
    int j=0;
    int stockage;
for(int p=0;p<taille1;++p)
{
    r=tableaukruskal[p][0];
    f=tableaukruskal[p][1];
    g=tableaukruskal[p][2];
    if((comparer[f][1])==(comparer[g][1])){
        }
    else if((comparer[f][1])!=(comparer[g][1]))
    {
            finale[j][0]=r;
            finale[j][1]=f;
            finale[j][2]=g;
            j++;

        stockage=comparer[f][1];
        comparer[f][1]=comparer[g][1];
        for(int a=0;a<ordre;++a)
        if((comparer[a][1])==stockage)
            comparer[a][1]=comparer[g][1];

        for(int j=0;j<ordre;++j)
        if((comparer[f][1])!=f && (comparer[f][1])!=(comparer[g][1]))
        {
            for(int u=0;u<ordre;++u)
            comparer[u][1]=g;

        }
    }

}
float couts,couts2;
int objet=0;
int t;
   for(int l=0;l<ordre-1;++l)
    {

        for(t=0;t<ordre;++t)
        {
            if((finale[l][1])==(sommet_coords[t][0]))
            {
               x1=sommet_coords[t][1];
               y1=sommet_coords[t][2];
               objet=finale[l][0];
               couts+=arete_ponderation[objet][1];
               couts2+=arete_ponderation[objet][2];

            }
            if((finale[l][2])==(sommet_coords[t][0]))
            {
               x2=sommet_coords[t][1];
               y2=sommet_coords[t][2];
            }
        }

        svgout.addLine(x1,y1+500,x2,y2+500,"black");
        svgout.addCircle(x1,y1+500,3,5,"blue");
        svgout.addCircle(x2,y2+500,3,5,"blue");
        if((y1)==(y2))
            {
                svgout.addText((x1+x2)/2-10,y1-5+500,arete_ponderation[objet][1],"blue");
                svgout.addText((x1+x2)/2+5,y1-5+500," ; ","blue");
                svgout.addText((x1+x2)/2+10,y1-5+500,arete_ponderation[objet][2],"blue");
            }

       else if((x1)==(x2))
        {
            svgout.addText(x2-30,(y1+y2)/2+500,arete_ponderation[objet][1],"blue");
            svgout.addText(x2-15,(y1+y2)/2+500," ; ","blue");
            svgout.addText(x2-10,(y1+y2)/2+500,arete_ponderation[objet][2],"blue");

        }
        else if((x1==y2) && (x2==y1))
        {
            svgout.addText((x1+x2)/2-5-10,(y2+y1)/2-5+500,arete_ponderation[objet][1],"blue");
            svgout.addText((x1+x2)/2,(y2+y1)/2-5+500," ; ","blue");
            svgout.addText((x1+x2)/2-5+10,(y2+y1)/2-5+500,arete_ponderation[objet][2],"blue");

        }
        else if((x1!=x2) && (y1!=y2))
        {
            svgout.addText((x1+x2)/2-5-10,(y2+y1)/2-5+500,arete_ponderation[objet][1],"blue");
            svgout.addText((x1+x2)/2,(y2+y1)/2-5+500," ; ","blue");
            svgout.addText((x1+x2)/2-5+10,(y2+y1)/2-5+500,arete_ponderation[objet][2],"blue");
        }

    }
    m_couts.push_back(couts);
    m_couts.push_back(couts2);
    return m_couts;
}


graphe::~graphe(){};

graphe::GetOrdre() const
{
    return m_sommet_coords.size();

}

graphe::GetTaille() const
{
    return m_arete_sommet.size();
}

/// verifie qu'une possibilite est bien connexe dans le graphe
bool graphe::verifierConnexite(std::vector<int> Aretes) const
{
    int j=0;

    /// iterer sur chaque sommer du graphe
    for(int i=0; i<m_sommet_coords.size();++i)
    {
        /// verifier que le sommet se retrouve bien dans ua moins une arete des posibilites
        for( j=0;j<Aretes.size();++j)
        {
            /// Chaque sommet de m_sommet_coords est represente par un tableau [sommetId, Xcoord, Ycoord]
            /// Chaque arete de m_arete_sommet est representee par un tableau [AreteId, sommetId, sommetId]
            if(m_sommet_coords[i][0] == m_arete_sommet[Aretes[j]][1] ||
               m_sommet_coords[i][0] == m_arete_sommet[Aretes[j]][2])
            {
                break;
            }
        }
        if(j==Aretes.size())
        {
            return false;
        }
    }
    return true;
}

/// Calculer le cout d'une possibilite
/// Il peut y avoir plusieurs couts, typiquement 2
double graphe::calculerCout(int type, std::vector<int> Aretes) const
{
    double cost = 0.0;
    /// Prendre touts les aretes du vecteur
    for( int j=0;j<Aretes.size();++j)
    {
        /// Chaque ponderation d'arete est representee par un tableau [AreteId, poids1, poids2]
        cost += m_arete_ponderation[Aretes[j]][type];
    }
    return cost;
}

/// Trouver la liste des aretes adjacentes a une arete dans un graphe
std::vector<int> graphe::areteAdjacentes (int arete, std::vector<int> Aretes) const
{
    std::vector<int> adjacentes;
    /// std::cout << " Adjacence pour l'Arete " << arete << " Sommets " << m_arete_sommet[arete][1] << " ," << m_arete_sommet[arete][2] << std::endl;

    /// je boucle dans le vecteurs d'aretes pour rechercher toutes les aretes
    /// qui partagent un sommet commun avec l'arete donnee
    for(int j=0; j<Aretes.size(); j++)
    {
        /// verifier que je ne me retrouve pas moi-meme
        if(Aretes[j] == arete)
            continue;

        /// std::cout << " \t verif avec " << Aretes[j] << " Sommets " << m_arete_sommet[Aretes[j]][1] << " ," << m_arete_sommet[Aretes[j]][2] << std::endl;
        /// m_arete_sommet est une table d'aretes [areteId, sommetId, sommetId]
        if(m_arete_sommet[Aretes[j]][1] == m_arete_sommet[arete][1] ||
           m_arete_sommet[Aretes[j]][1] == m_arete_sommet[arete][2] ||
           m_arete_sommet[Aretes[j]][2] == m_arete_sommet[arete][1] ||
           m_arete_sommet[Aretes[j]][2] == m_arete_sommet[arete][2])
        {
            adjacentes.push_back(Aretes[j]);
        }
    }
    return(adjacentes);
}

/// Determine si un graphe est connexe
bool graphe::DFS(int ordre, std::vector<int> Aretes) const
{
    int arete;
    /// Au depart aucune arete n'est visitee
    std::vector<bool> aretesVisitees(Aretes.size(), false);
    std::vector<bool> sommetsVisites(ordre, false);

#if 0
    std::cout << "DFS ordre: "<< ordre << " du vecteur (" ;
    for(int i=0; i<Aretes.size(); i++)
    {
        std::cout << " " << Aretes[i] ;
    }
    std::cout << ")" << std::endl;
#endif  //0

    // Creation de notre pile pour effectuer DFS
    std::stack<int> pile;

    /// Commencer par la premiere arete
    pile.push(Aretes[0]);

    while (!pile.empty())
    {

        /// Pop une arete de la pile et l'imprimer
        arete = pile.top();
        pile.pop();

        // Stack may contain same vertex twice. So
        // we need to print the popped item only
        // if it is not visited.
        if (!aretesVisitees[arete])
        {

            /// std::cout << "Arete: " << arete << " visitee"<< std::endl;
            /// std::cout << "Sommets: " << m_arete_sommet[arete][1] << " et " << m_arete_sommet[arete][2] << " visites"<< std::endl;

            aretesVisitees[arete] = true;
            sommetsVisites[m_arete_sommet[arete][1]] = true;
            sommetsVisites[m_arete_sommet[arete][2]] = true;
        }

        /// Retrouver tous les aretes adjacentes a l'arete examinee s
        /// Si unes aretes n'a pas ete deja visite, la rajouter dans la pile
        std::vector<int> adj = areteAdjacentes (arete, Aretes);
#if 0
        std::cout << "les aretes adjacentes a "<< arete << " sont: (" ;
        for(int i=0; i<adj.size(); i++)
        {
            std::cout << " " << adj[i] ;
        }
        std::cout << ")" << std::endl;
#endif //0

        for (auto i = 0; i != adj.size(); ++i)
            if (!aretesVisitees[adj[i]])
                pile.push(adj[i]);
    }
  /// verifier que tous les sommets ont ete inclus
  for(int i=0; i<sommetsVisites.size(); i++)
  {
      if(sommetsVisites[i] == false)
      {
          /// std::cout << " Ce graphe n'est pas connexe car il ne contient pat le point: "<< i <<std::endl;
          return false;
      }
  }
  /// std::cout << " Ce graphe est connexe "<<std::endl;
  return true;
}


