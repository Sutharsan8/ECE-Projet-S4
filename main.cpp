#include <iostream>
#include "graphe.h"
using namespace std;

int main()
{
    Svgfile svgout;
    graphe a{"broadway.txt",1, svgout};
    graphe b{"broadway_weights_0.txt",2,svgout};
    a.afficher(1);
    b.afficher(2);
    return 0;
}