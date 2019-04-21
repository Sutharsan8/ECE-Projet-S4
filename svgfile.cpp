 /**
 * \details    Dans le svgfile.cpp on defini les methodes necessaire pour affichées les données des graphes
  */
#include "svgfile.h"
#include <iostream>
#include <sstream>
#include "util/util.h"


const std::string svgHeader =
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
    "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" " ;

const std::string svgEnding = "\n\n</svg>\n";

/// Effets "Boule en relief", voir données à la fin de ce fichier
extern const std::string svgBallGradients;

std::set<std::string> Svgfile::s_openfiles;

bool Svgfile::s_verbose = true;

Svgfile::Svgfile(std::string _filename, int _width, int _height) :
    m_filename{_filename}, m_width{_width}, m_height{_height}
{

    if (s_verbose)
        std::cout << "Opening SVG output file : "
                  << m_filename << std::endl;

    if ( s_openfiles.count(m_filename) )
        throw std::runtime_error( "File " + m_filename + " already open !" );

    m_ostrm.open(m_filename);
    s_openfiles.insert(m_filename);

    if (!m_ostrm)
    {
        std::cout << "Problem opening " << m_filename << std::endl;
        throw std::runtime_error("Could not open file " + m_filename );
    }

    if (s_verbose)
        std::cout << "OK" << std::endl;

    // Writing the header into the SVG file
    m_ostrm << svgHeader;
    m_ostrm << "width=\"" << m_width << "\" height=\"" << m_height << "\">\n\n";
}

Svgfile::~Svgfile()
{
    // Writing the ending into the SVG file
    m_ostrm << svgEnding;

    // Removing this file from the list of open files
    s_openfiles.erase(m_filename);

    // No need to explicitly close the ofstream object (automatic upon destruction)
}

// Helper templated function
template<typename T>
std::string attrib(std::string name, T val)
{
    std::ostringstream oss;
    oss << name << "=\"" << val << "\" ";
    return oss.str();
}



/*
void Svgfile:: addSoleil(double x, double y, double r, std::string color)
{
    <!DOCTYPE html>
<html>
<body>

<svg height="210" width="400">
  <path id="motionPath" stroke="none" fill="none" d="M 100 100 Q 150 50 200 100"/>
    <circle id="circle" r="10" cx="0" cy="0" fill="tomato" />

  <animateMotion
           xlink:href="#circle"
           dur="5s"
           begin="0s"
           fill="freeze"
           repeatCount="indefinite">
    <mpath xlink:href="#motionPath" />
  </animateMotion>
</svg>
</svg>

</body>
</html>
}
*/

void Svgfile:: addCloud(double x, double y, double r, std::string color)
{
    addDisk(x, y, r, color);
    //addCircle(x,y, r,1, "black");
    addDisk(x+r, y-r, r, color);
    // addCircle(x+r,y-r, r,1, "black");
    addDisk(x+r, y+r, r, color);
    //  addCircle(x+r,y+r, r,1, "black");
    addDisk(x+2*r, y, r, color);
    // addCircle(x+2*r, y, r,1, "black");
    addDisk(x+3*r, y-r, r, color);
    //  addCircle(x+3*r,y-r, r,1, "black");
    addDisk(x+3*r, y+r, r, color);
    //   addCircle(x+3*r,y+r, r,1, "black");
    addDisk(x+4*r, y, r, color);
    //  addCircle(x+4*r, y, r,1, "black");
}



/*void Svgfile::addBush(double x, double y, double taille,std::string color )
{
    for (double i=0; i<30; ++i)
    {
        double a= x+util::alea(-taille/6,taille/6);
        double b= y+util::alea(taille/1000,taille);


        addLine(x, y,a, b, color);
    }
}*/

void Svgfile::addDisk(double x, double y, double r, std::string color)
{
    m_ostrm << "<circle "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("r",  r)
            << attrib("fill", color )
            << "/>\n";
}

void Svgfile::addCircle(double x, double y, double r, double ep, std::string color)
{
    m_ostrm << "<circle "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("r",  r)
            << attrib("fill", "none")
            << attrib("stroke", color )
            << attrib("stroke-width", ep )
            << "/>\n";
}
/*
void Svgfile::addSoleil( double r, std::string color)
{
  m_ostrm <<"<path"
    <<attrib("id", "motionPath")
    <<attrib("fill","none")
    <<attrib("stroke","black")
  //  <<attrib("d","M 100 100 Q 500 0 1000 100")
    <<attrib("d","M 100 100 Q150 50 1000 100")
    <<"/>\n"
    <<"<circle"
    << attrib("id", "soleil" )
    <<attrib("r",r)
    <<attrib("fill", color)
     <<"/>\n"
    <<"<animateMotion "
    <<"xlink:href=\"#soleil\""
    <<attrib("begin","0s")
    <<attrib("fill","freeze")
     <<attrib("dur","5")
    <<attrib("repeatCount","indefinite")
    <<">\n"
    <<"<mpath xlink:href=\"#motionPath\" "
    <<"/>\n"
    <<"</animateMotion>\n";

}*/

void Svgfile::addCurve()
{
    m_ostrm<<"<path "
           <<attrib("d","M 100 100 Q 200 300 300 100")
           <<attrib("stroke","red")
//   <<attrib("stroke-width","5")
           <<attrib("fill","black");
}
void Svgfile::addSoleil( double r, std::string color)
{
    m_ostrm <<"<path "
            <<attrib("id","test")
            <<attrib("fill","none")
            <<attrib("stroke","none")
            // <<attrib("d","M 100 100 Q150 50 1000 100")
            <<attrib("d","M -100 300 Q 1000 -250 2100 300")
            //     <<attrib("d","M 100 100 L 200 200")
            << "/>\n"
            << "<circle "
            <<attrib("id","soleil")
            << attrib("r",  r)
            << attrib("fill",color)
            << "/>\n"

            <<"<animateMotion "
            <<"xlink:href=\"#soleil\" "
            <<attrib("begin","0s")
            <<attrib("fill","freeze")
            <<attrib("dur","20")
            <<attrib("repeatCount","indefinite")
            << ">\n"
            <<"<mpath xlink:href=\"#test\""
            << "/>\n"
            <<"</animateMotion>\n";
}


void Svgfile::addEllipse(double x, double y, double rx,double ry,double ep, std::string color)
{
    m_ostrm << "<ellipse "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("rx", rx)
            << attrib("ry", ry)
            << attrib("fill", color )
            << attrib("stroke", "none" )
            << attrib("stroke-width", ep )
            << "/>\n";
}

void Svgfile::addEllipseB(double x, double y, double rx,double ry,double ep, std::string color)
{
    m_ostrm << "<ellipse "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("rx", rx)
            << attrib("ry", ry)
            << attrib("fill", color )
            << attrib("stroke", "black" )
            << attrib("stroke-width", ep )
            << "/>\n";
}




/// <polygon points="200,10 250,190 160,210" style="fill:lime;stroke:purple;stroke-width:1" />
void Svgfile::addTriangle(double x1, double y1, double x2, double y2,
                          double x3, double y3, std::string colorFill,
                          double thickness, std::string colorStroke)
{

    m_ostrm << "<polygon points=\" "
            << x1 << "," << y1 << " "
            << x2 << "," << y2 << " "
            << x3 << "," << y3
            << "\" style=\"fill:" << colorFill
            << ";stroke:" << colorStroke
            << ";stroke-width:" << thickness
            << "\" />\n";
}



void Svgfile::addRectangle(double x1, double y1, double x2, double y2,
                           double x3, double y3,double x4, double y4, std::string colorFill)
{
    m_ostrm << "<polygon points=\" "
            << x1 << "," << y1 << " "
            << x2 << "," << y2 << " "
            << x3 << "," << y3 << " "
            << x4 << "," << y4
            << "\" style=\"fill:" << colorFill
            << "\" />\n";
}


void Svgfile::addTriangle(double x1, double y1, double x2, double y2,
                          double x3, double y3, std::string colorFill)
{
    m_ostrm << "<polygon points=\" "
            << x1 << "," << y1 << " "
            << x2 << "," << y2 << " "
            << x3 << "," << y3
            << "\" style=\"fill:" << colorFill
            << "\" />\n";
}

void Svgfile::addLine(double x1, double y1, double x2, double y2, std::string color)
{
    m_ostrm << "<line "
            << attrib("x1", x1)
            << attrib("y1", y1)
            << attrib("x2", x2)
            << attrib("y2", y2)
            << attrib("stroke", color)

            << "/>\n";
}

void Svgfile::addLineEp(double x1, double y1, double x2, double y2, double ep, std::string color)
{
    m_ostrm << "<line "
            << attrib("x1", x1)
            << attrib("y1", y1)
            << attrib("x2", x2)
            << attrib("y2", y2)
            << attrib("stroke", color)

            << attrib("stroke-width", ep )

            << "/>\n";
}
void Svgfile::addCross(double x, double y, double span, std::string color)
{
    addLine(x-span, y-span, x+span, y+span, color);
    addLine(x-span, y+span, x+span, y-span, color);
}

void Svgfile::addText(double x, double y, std::string text, std::string color)
{
    /// <text x="180" y="60">Un texte</text>
    m_ostrm << "<text "
            << attrib("x", x)
            << attrib("y", y)
            << attrib("fill", color)
            << ">" << text << "</text>\n";
}

void Svgfile::addTexttitre(double x, double y, std::string text , std::string style)
{
    /// <text x="180" y="60" style="fill:yellow;stroke:#abcdef;font-size:50px;">Un texte</text> //on recupere cette stucture sur https://openclassrooms.com/fr/courses/201787-le-svg/201785-le-texte
    m_ostrm << "<text "
            << attrib("x", x)
            << attrib("y", y)
            << attrib("style", style)
            << ">" << text << "</text>\n";
}

void Svgfile::addText(double x, double y, double val, std::string color)
{
    std::ostringstream oss;
    oss << val;
    addText(x, y, oss.str(), color);
}

void Svgfile::addGrid(double span, bool numbering, std::string color)
{
    double y=0;
    while (y<=m_height)
    {
        addLine(0, y, m_width, y, color);
        if (numbering)
            addText(5, y-5, y, color);
        y+=span;
    }

    double x=0;
    while (x<=m_width)
    {
        addLine(x, 0, x, m_height, color);
        if (numbering)
            addText(x+5, 15, x, color);
        x+=span;
    }
}

std::string Svgfile::makeRGB(int r, int g, int b)
{
    std::ostringstream oss;
    oss << "rgb(" << r << "," << g << "," << b << ")";
    return oss.str();
}

