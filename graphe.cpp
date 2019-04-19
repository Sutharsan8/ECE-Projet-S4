#include <fstream>
#include <iostream>
#include "graphe.h"
#include"sommet.h"



graphe::graphe(std::string nomFichier, int choix, Svgfile& svgout,std::vector<std::vector<double>> sommet_coords,std::vector<std::vector<double>> arete_sommet,std::vector<std::vector<float>>arete_ponderation):m_sommet_coords{sommet_coords},m_arete_sommet{arete_sommet},m_arete_ponderation{arete_ponderation}
{
    double tableau_Coordonne[50][3];
    double tableauarete[50][3];
    double tableaupoids[50][3];
    double ordre;
    if(choix==1){

double x1;double y1;
double x2;double y2;
////////////////////////////////////////////////////////////////////////////////////////////
   ///fichier 1
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );

    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");

////////////////////////////////////////////////////////////////////////////////////////////

    double id;
    double x,y;
    //lecture des sommets
    for (int i=0; i<ordre; ++i){
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture données id");
        ifs>>x; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet1");
        ifs>>y; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet2");
        m_sommets.insert({id,new Sommet{id,x,y}}); ///premiere partie du fichier 1 recupere

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
         m_arete.insert({id_arete, new Arete{id_arete,s_1,s_2,0,0}});

        tableau_Coordonne[i][0]=id_arete;
        tableau_Coordonne[i][1]=s_1;
        tableau_Coordonne[i][2]=s_2;

        if(m_sommets.find(s_1)!=m_sommets.end()) /// si le sommet existe
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
            std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    double taille;
    ifs >> taille;

    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    double valeur;
    ifs>>valeur;
    int marcher=0;
    double id;
    double poids1,poids2;
    double sommet1;double sommet2;
    double x1,x2,y1,y2;
    //lecture des aretes
    for (int i=0; i<taille; ++i){
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>poids1; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>poids2; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");

        arete_ponderation.push_back(std::vector<float>(3));//vecteur pour faire pareto partie 2
        arete_ponderation[i][0]=id;
        arete_ponderation[i][1]=poids1;
        arete_ponderation[i][2]=poids2;

        tableaupoids[i][0]=id;
        tableaupoids[i][1]=poids1;
        tableaupoids[i][2]=poids2;


    if(id==tableau_Coordonne[i][0])
    {
        sommet1=tableau_Coordonne[i][1];
        sommet2=tableau_Coordonne[i][2];
    }
        if(nomFichier=="manhattan_weights_0.txt" || nomFichier=="broadway_weights_0.txt")
        for(int r=0;r<taille;++r)
        {

            if(sommet1==tableauarete[r][0]) /// si le sommet existe
            {
                if(marcher!=0){
                x1=tableauarete[r][1];
                y1=tableauarete[r][2];}
                if(marcher==0){
                x1=sommet_coords[r][1];
                y1=sommet_coords[r][2];marcher++;}

            }
            if(sommet2==tableauarete[r][0]) /// si le sommet existe
            {
                x2=tableauarete[r][1];
                y2=tableauarete[r][2];
            }
        }
        if(nomFichier=="triville_weights_0.txt")
        for(int r=0;r<ordre;++r)
        {

            if(sommet1==tableauarete[r][0]) /// si le sommet existe
            {
                if(marcher!=0){
                x1=tableauarete[r][1];
                y1=tableauarete[r][2];}
                if(marcher==0){
                x1=sommet_coords[r][1];
                y1=sommet_coords[r][2];marcher++;}

            }
            if(sommet2==tableauarete[r][0]) /// si le sommet existe
            {
                x2=tableauarete[r][1];
                y2=tableauarete[r][2];
            }
        }
        if(nomFichier=="cubetown_weights_0.txt")
        for(int r=0;r<10;++r)
        {

            if(sommet1==tableauarete[r][0]) /// si le sommet existe
            {
                if(marcher!=0){
                x1=tableauarete[r][1];
                y1=tableauarete[r][2];}
                if(marcher==0){
                x1=sommet_coords[r][1];
                y1=sommet_coords[r][2];marcher++;}

            }
            if(sommet2==tableauarete[r][0]) /// si le sommet existe
            {
                x2=tableauarete[r][1];
                y2=tableauarete[r][2];
            }
        }


        svgout.addLine(x1+500,y1,x2+500,y2,"black");
        svgout.addCircle(x1+500,y1,3,5,"black");
        svgout.addCircle(x2+500,y2,3,5,"black");

        if(y1==y2)
            {
                svgout.addText((x1+x2)/2+500,y1-5,tableaupoids[i][1],"black");
                svgout.addText((x1+x2)/2+510,y1-5," ; ","black");
                svgout.addText((x1+x2)/2+518,y1-5,tableaupoids[i][2],"black");
            }

        if(x1==x2)
        {
            svgout.addText(x2-10+500,(y1+y2)/2,tableaupoids[i][1],"black");
            svgout.addText(x2-10+510,(y1+y2)/2," ; ","black");
            svgout.addText(x2-10+518,(y1+y2)/2,tableaupoids[i][2],"black");
        }

        if(x1==y2 && x2==y1)
        {
            svgout.addText((x1+x2)/2-5+500,(y2+y1)/2-5,tableaupoids[i][1],"black");
            svgout.addText((x1+x2)/2-5+510,(y2+y1)/2-5," ; ","black");
            svgout.addText((x1+x2)/2-5+518,(y2+y1)/2-5,tableaupoids[i][2],"black");
        }
        if(x1!=x2 && y1!=y2)
        {
            svgout.addText((x1+x2)/2-5+500,(y2+y1)/2-5,tableaupoids[i][1],"black");
            svgout.addText((x1+x2)/2-5+510,(y2+y1)/2-5," ; ","black");
            svgout.addText((x1+x2)/2-5+518,(y2+y1)/2-5,tableaupoids[i][2],"black");
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


void graphe::kruskal(int poids,std::string nomFichier,std::string nomFichier2,Svgfile& svgout,std::vector<std::vector<double>> sommet_coords,std::vector<std::vector<double>> arete_sommet,std::vector<std::vector<float>>arete_ponderation) const
{


    std::ifstream ifs{nomFichier};
    int ordre;
    double tableau_Coordonne[50][3];
    double tableauarete[50][3];
    double tableaupoids[50][3];
    double tableaukruskal[50][3];
    double tableauselection[50][3];
    double aff[50][3];
    double tableau_CoordonneINITIALE[50][3];
    double id;
    double poids1,poids2;
    double sommet1=0;int sommet2=0;
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

    int finale[ordre-1][2];
    int f,g;
    int j=0;
    int stockage;
for(int p=0;p<taille1;++p)
{
    f=tableaukruskal[p][1];
    g=tableaukruskal[p][2];
    if((comparer[f][1])==(comparer[g][1])){
        }
    else if((comparer[f][1])!=(comparer[g][1]))
    {
            finale[j][0]=f;
            finale[j][1]=g;
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

int objet=0;
    std::cout<<"-------------------------KRUSKAL---------------------------------"<<std::endl;
    std::cout<<"FIN"<<std::endl;
int t;
   for(int l=0;l<ordre-1;++l)///CEST L<ORDRE-1 JUSTE POUR TESTER AVEC UNE ARETE
    {

        for(t=0;t<ordre;++t)
        {
            if((finale[l][0])==(sommet_coords[t][0]))
            {
               x1=sommet_coords[t][1];
               y1=sommet_coords[t][2];

            }
            if((finale[l][1])==(sommet_coords[t][0]))
            {
               x2=sommet_coords[t][1];
               y2=sommet_coords[t][2];

            }
            if((finale[l][0])==(arete_sommet[t][1]) && (finale[l][1])==(arete_sommet[t][2])){
               objet=arete_sommet[t][0];
               std::cout<<"valeur de objet : "<<objet<<std::endl;
               }
        }

        svgout.addLine(x1,y1+500,x2,y2+500,"black");
        svgout.addCircle(x1,y1+500,3,5,"black");
        svgout.addCircle(x2,y2+500,3,5,"black");
        if((y1)==(y2))
            {
                svgout.addText((x1+x2)/2,y1-5+500,arete_ponderation[objet][1],"black");
                svgout.addText((x1+x2)/2,y1-5+510," ; ","black");
                svgout.addText((x1+x2)/2,y1-5+518,arete_ponderation[objet][2],"black");
            }

       else if((x1)==(x2))
        {
            svgout.addText(x2-10,(y1+y2)/2+500,arete_ponderation[objet][1],"black");
            svgout.addText(x2-10,(y1+y2)/2+510," ; ","black");
            svgout.addText(x2-10,(y1+y2)/2+518,arete_ponderation[objet][2],"black");

        }
        else if((x1==y2) && (x2==y1))
        {
            svgout.addText((x1+x2)/2-5,(y2+y1)/2-5+500,arete_ponderation[objet][1],"black");
            svgout.addText((x1+x2)/2-5,(y2+y1)/2-5+510," ; ","black");
            svgout.addText((x1+x2)/2-5,(y2+y1)/2-5+518,arete_ponderation[objet][2],"black");

        }
        else if((x1!=x2) && (y1!=y2))
        {
            svgout.addText((x1+x2)/2-5,(y2+y1)/2-5+500,arete_ponderation[objet][1],"black");
            svgout.addText((x1+x2)/2-5,(y2+y1)/2-5+510," ; ","black");
            svgout.addText((x1+x2)/2-5,(y2+y1)/2-5+518,arete_ponderation[objet][2],"black");

        }
    }

    std::cout<<"---------------------AFFICHAGE DU GRAPHE AVEC SVG-----------------"<<std::endl;

}
graphe::~graphe(){};

