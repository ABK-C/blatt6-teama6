#include "Vektor.hh"
#include "Zylindermantel.hh"
#include "Vollzylinder.hh"
#include "Koerper.hh"
#include <iostream>
#include <memory>
#include <cmath>
#include <fstream>




double traegheit(Koerper* k, Vektor a, Vektor u, double M){
    std :: cout << " berechne  fuer " << k -> name () << std::endl;
    const int N = 10000;


    double J = 0;
    double m = M/N;

    for (int i = 0; i < N; ++i) 
    {
      Vektor x = k->punkt();
      Vektor n = (x-a).kreuz(u);
      double r = n.betrag()/u.betrag();

      J += m * r * r;
    }
    return J;
}







int main() {
  const int N = 10000;     // Anzahl Integrationspunkte
  const double M = 1;      // Masse des Zylindermantels
  const double ZM_R = 1.0; // Radius der Zylindermantels
  const double VZ_R = 1.0;
  const double ZM_L = 1.0; // Laenge des Zylindermantels
  const double VZ_L = 1.0;

  using namespace std;

  ofstream fout("TreageKoerper.txt");
  fout << "|R     " << "|L      " << "|M     " << "|      a|" << "|      u|" << "|J_ZM ana. |" << "J_ZM berechnet |" << "|J_VZ ana. " << "|J_VZ berechnet |"<< std::endl;
 


  Vektor a; // Punkt auf der Rotationsachse
  std::cout << "Aufpunkt:";
  std::cin >> a;
  Vektor u; // Richtung der Rotationsachse
  std::cout << "Richtung:";
  std::cin >> u;


//Blatt  6
/* std::unique_ptr<Zylindermantel> zm(new Zylindermantel(ZM_R, ZM_L));

  double J_ZM = 0;     // Massentraegheitsmoment
  double m = M / N; // Masse eines Massenpunktes
  for (int i = 0; i < N; ++i) {
    Vektor x = zm->punkt();
    // Abstand Punkt x und Gerade a + t*u
    Vektor n = (x-a).kreuz(u);//Normalenvektor x-a kreuz u
    double r = n.betrag()/u.betrag(); //|n|/|u|
    // std::cout << x << " :" << r << std::endl;
    // addiere Beitrag des Massenpunktes zum Traegheitsmoment
    J_ZM += m * r * r;
  }
  std::cout << "Massentraegheitsmoment fuer einen Zylindermantel"
            << " mit a = " << a << " und u = " << u << ": " << J_ZM << std::endl;
            
  


  std::unique_ptr<Vollzylinder> vz(new Vollzylinder(ZM_R, ZM_L));


  double J_VZ = 0;     // Massentraegheitsmoment Vollzylinder
  
  for (int i = 0; i < N; ++i) {
    Vektor x = vz->punkt();
    // Abstand Punkt x und Gerade a + t*u
    Vektor n = (x-a).kreuz(u);//Normalenvektor x-a kreuz u
    double r = n.betrag()/u.betrag(); //|n|/|u|
    // std::cout << x << " :" << r << std::endl;
    // addiere Beitrag des Massenpunktes zum Traegheitsmoment
    J_VZ += m * r * r;
  }
  std::cout << "Massentraegheitsmoment fuer einen Vollzylinder"
            << " mit a = " << a << " und u = " << u << ": " << J_VZ << std::endl;
            
  

  }*/



  for (double M = 1; M <= 2; M++) {
    for (double Radius = 1; Radius <= 2; Radius++){
      std::unique_ptr<Koerper> k(new Zylindermantel(Radius, ZM_L));
      double J_ZM = traegheit(k.get(),a,u,M);

      std::unique_ptr<Koerper> k_vz(new Vollzylinder(Radius, VZ_L));
      double J_VZ = traegheit(k_vz.get(),a,u,M);

      double J_ZM_ana = M*pow(Radius,2)+M*a.betrag()*a.betrag();
      double J_VZ_ana = 0.5*M*pow(Radius,2)+M*a.betrag()*a.betrag();

      if(Radius != 2 || M != 2){
        fout << "|" << Radius<< "m   " << "|1 m     " << "|"<< M << "kg   " << "|(0,0,0)|" << "|(0,0,1)|" << "|    "<< J_ZM_ana<<"     |" << J_ZM  << "          "    <<       "    ||      "<<    J_VZ_ana       <<    " |" <<  J_VZ  << "   "      << std::endl;

      }
      
    }
  }



  Vektor a2; // Punkt auf der Rotationsachse
  std::cout << "Aufpunkt:";
  std::cin >> a2;
  Vektor u2; // Richtung der Rotationsachse
  std::cout << "Richtung:";
  std::cin >> u2;


  for (double M = 1; M <= 2; M++) {
    for (double Radius = 1; Radius <= 2; Radius++){
      std::unique_ptr<Koerper> k(new Zylindermantel(Radius, ZM_L));
      double J_ZM = traegheit(k.get(),a2,u2,M);

      std::unique_ptr<Koerper> k_vz(new Vollzylinder(Radius, VZ_L));
      double J_VZ = traegheit(k_vz.get(),a2,u2,M);

      double J_ZM_ana = M*pow(Radius,2)+M*a2.betrag()*a2.betrag();
      double J_VZ_ana = 0.5*M*pow(Radius,2)+M*a2.betrag()*a2.betrag();

      if(Radius != 2 || M != 2){
        fout << "|" << Radius<< "m   " << "|1 m     " << "|"<< M << "kg   " << "|(0,1,0)|" << "|(0,0,1)|" << "|    "<< J_ZM_ana<<"     |" << J_ZM  << "       "    <<       " ||      "<<    J_VZ_ana       <<    "  |" <<  J_VZ  << "   "      << std::endl;

      }
      
    }
  }



 fout.close();


}