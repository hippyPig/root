#ifndef SCPH_DENDROLOGY_PARTICLE_H 
#define SCPH_DENDROLOGY_PARTICLE_H 
#include "Elm.hpp"

class Particle {
 private:
  Elm* elm_;
  bool mc_;
  bool track_;
  bool id_;
  TLorentzVector p4_;
  std::string name_;
  double m;
  std::vector<Particle*> daughters;

 public:
  Particle() {;}
  Particle(Elm*, const std::string&);

  void init(Elm*, const std::string&);
  void addDaug(const std::string&);

  TLorentzVector p4();
  double m();

};


#endif
