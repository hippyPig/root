#ifndef SCPH_KNIVES_KNIFETYPESIMPLE_H
#define SCPH_KNIVES_KNIFETYPESIMPLE_H
#include "Knife.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "TTree.h"


namespace Knives {


template <typename T>
class KnifeTypeSimple : public Knife {
 protected:
  T cut_;
  T cut() {return (cut_);}
 public:
  //KnifeTypeSimple() {};
  KnifeTypeSimple(std::string name, T cut) {
    this->set_name(name);
    cut_= cut;
    val = new T;
  };
  ~KnifeTypeSimple() {};
  T* val;
  virtual bool eval() {return false;}
  virtual void print()=0;
  virtual std::string cut_string() {return "";};
  void update(T cut_new) {
    cut_ = cut_new;
  };
  void setAddress(TTree* tree) {
    //val = new T;
    tree->SetBranchStatus(this->get_name().c_str(), 1);
    tree->SetBranchAddress(this->get_name().c_str(), val);
  };
  void setAddress(Barrel* barrel) {
    val = barrel->getPtr<T>(this->get_name());
  };
  void setAddress(std::string name, T* v) {
    if (name == this->get_name()) {
      val = v;
    }
  };
  void set_cut(T cut) {
    cut_ = cut;
  };
};


}
#endif
