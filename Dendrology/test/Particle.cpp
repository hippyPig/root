#define SCPH_DENDROLOGY_PARTICLE_H_CXX
#include "Particle.hpp"

//Particle() {;}

Particle::Particle(Elm* elm, const std::string& name) :
    name_(name),
    elm_(elm) {
  p4_ = elm_->getTLorentzVector(name_);
}

//void init(Elm*, const std::string&);
//void addDaug(const std::string&);

TLorentzVector p4();
double m();

