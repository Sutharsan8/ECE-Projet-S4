#include <iostream>
#include "graphe.h"
using namespace std;

int main()
{
    Svgfile svgout;
    graphe a{"manhattan.txt",1, svgout};
    graphe b{"manhattan_weights_0.txt",2, svgout};
    a.afficher(1);
    b.afficher(2);
    a.kruskal("manhattan.txt","manhattan_weights_0.txt",svgout);
    return 0;
}
