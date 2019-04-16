#include <fstream>
#include <iostream>
#include "graphe.h"
#include"sommet.h"

graphe::graphe(std::string nomFichier, int choix, Svgfile& svgout){
    double tableausommet[50][3];
    double tableauarete[50][3];
    double tableaupoids[50][3];
    if(choix==1){

double x1;double y1;
double x2;double y2;
////////////////////////////////////////////////////////////////////////////////////////////
   ///fichier 1
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");

////////////////////////////////////////////////////////////////////////////////////////////

    double id;
    double x,y;
    //lecture des sommets
    for (int i=0; i<ordre; ++i){
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>x; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>y; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        m_sommets.insert({id,new Sommet{id,x,y}}); ///premiere partie du fichier 1 recupere
        tableauarete[i][0]=id;
        tableauarete[i][1]=x;
        tableauarete[i][2]=y;
    }

    double id_arete;
    int s_1,s_2;
    int taille;
    ifs>>taille;

    //lecture des aretes
    for (int i=0; i<taille; ++i)
    {
        //lecture des ids des deux extrémités
          ifs>>id_arete; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
          ifs>>s_1;if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
          ifs>>s_2; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");
        m_arete.insert({id_arete, new Arete{id_arete,s_1,s_2,0,0}});
        tableausommet[i][0]=id_arete;
        tableausommet[i][1]=s_1;
        tableausommet[i][2]=s_2;

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
        svgout.addLine(x1+500,y1,x2+500,y2,"black");
        svgout.addCircle(x1+500,y1,3,5,"black");
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
    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    int valeur;
    ifs>>valeur;

    double id;
    double poids1,poids2;
    int sommet1=0;int sommet2=0;
    double x1,x2,y1,y2;
    //lecture des sommets
    for (int i=0; i<ordre; ++i){
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>poids1; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>poids2; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        tableaupoids[i][0]=id;
        tableaupoids[i][1]=poids1;
        tableaupoids[i][2]=poids2;


    if(id==tableausommet[i][0])
    {
        sommet1=tableausommet[i][1];
        sommet2=tableausommet[i][2];
    }

        for(int i=0;i<50;++i)
        {
            if(sommet1==tableauarete[i][0]) /// si le sommet existe
        {
            x1=tableauarete[i][1];
            y1=tableauarete[i][2];

        }
            if(sommet2==tableauarete[i][0]) /// si le sommet existe
        {
            x2=tableauarete[i][1];
            y2=tableauarete[i][2];
        }
        }
        std::cout<<x1<<","<<y1<<std::endl;


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

        //ajouter chaque extrémité à la liste des voisins de l'autre (graphe non orienté)

        //(m_sommets.find(id))->second->ajouterVoisin((m_sommets.find(id_voisin))->second);
        //(m_sommets.find(id_voisin))->second->ajouterVoisin((m_sommets.find(id))->second);//remove si graphe orienté
        m_arete_poids.insert({id,new Arete{id,sommet1,sommet2,poids1,poids2}});
    }
    }

}


void graphe::afficher(int choix) const{
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


graphe::~graphe(){};
