#ifndef SCPH_KNIVES_KNIFETYPERANGE_H
#define SCPH_KNIVES_KNIFETYPERANGE_H
#include "Knife.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "TTree.h"


namespace Knives {


template <typename T>
class KnifeTypeRange : public Knife {
 protected:
  T cut_low_;
  T cut_high_;
  T cut_low() {return (cut_low_);}
  T cut_high() {return (cut_high_);}
 public:
  //KnifeTypeRange() {};
  KnifeTypeRange(std::string name, T a, T b) {
    this->set_name(name);
    set_cuts(a, b);
    val = new T;
  };
  ~KnifeTypeRange() {};
  T* val;
  virtual bool eval() {return false;}
  virtual void print()=0;
  virtual std::string cut_string() {return "";};
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
  void set_cuts(T a, T b) {
    if (a < b) {
      cut_low_ = a;
      cut_high_ = b;
    } else {
      cut_low_ = b;
      cut_high_ = a;
    }
  };
  void update(T a, T b) {
    if (a < b) {
      cut_low_ = a;
      cut_high_ = b;
    } else {
      cut_low_ = b;
      cut_high_ = a;
    }
  };

};


}
#endif
