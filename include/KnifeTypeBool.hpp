#ifndef SCPH_KNIVES_KNIFETYPEBOOL_H
#define SCPH_KNIVES_KNIFETYPEBOOL_H
#include "Knife.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "TTree.h"

#include "Barrel.hpp"


namespace Knives {


template <typename T>
class KnifeTypeBool : public Knife {
 public:
  KnifeTypeBool(std::string name) {
    this->set_name(name);
    val = new T;
  };
  ~KnifeTypeBool() {};
  T* val;
  virtual bool eval() {return false;}
  virtual void print()=0;
  virtual std::string cut_string() {return "";}
  void setAddress(TTree* tree) {
    //val = new T;
    tree->SetBranchStatus(this->get_name().c_str(), 1);
    tree->SetBranchAddress(this->get_name().c_str(), val);
  };
  void setAddress(std::string name, T* v) {
    if (name == this->get_name()) {
      val = v;
    }
  };
  void setAddress(Barrel* barrel) {
    val = barrel->getPtr<T>(this->get_name());
  };
};


}
#endif
