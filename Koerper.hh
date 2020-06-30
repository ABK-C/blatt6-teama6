#ifndef Koerper_HH
#define Koerper_HH

#include "Vektor.hh"

class Koerper {
public:

  virtual Vektor punkt() = 0;
  virtual std :: string name () { return " Koerper ";}
  //virtual double M() = 0;
  


};

#endif
