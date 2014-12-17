#ifndef SCPH_KNIVES_KNIFE_H
#define SCPH_KNIVES_KNIFE_H

#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "TTree.h"

#include "Barrel.hpp"
#include "Oi.hpp"


namespace Knives {

////////////////////////////////////////////////////////////////////////////////
// Knife base class

class Knife {
 protected:
  std::string name_;
  void set_name(std::string name) {
    name_ = name;
  }
 public:
  Knife() {};
  ~Knife() {};
  //std::vector<Knife*> operator+ (Knife*);
  std::string get_name() {
    return name_;
  };
  virtual bool eval() {return false;}
  virtual void setAddress(TTree*)=0;
  virtual void setAddress(Barrel*)=0;
  //virtual void setAddress(std::map<std::string, MonkeyBase*>&)=0;
  virtual void print()=0;
  virtual std::string cut_string() {return "";};
};


}

#endif
