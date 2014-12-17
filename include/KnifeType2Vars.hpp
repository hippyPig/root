#ifndef SCPH_KNIVES_KNIFE2VARS_H
#define SCPH_KNIVES_KNIFE2VARS_H
#include "Knife.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "TTree.h"


namespace Knives {


template <typename T>
class KnifeType2Vars : public Knife {
 protected:
  T cut_;
  T cut() {return cut_;}
  std::string val_name1_;
  std::string val_name2_;
 public:
  KnifeType2Vars() {;};
  KnifeType2Vars(std::string name1, std::string name2, T a) {
    val_name1_ = name1;
    val_name2_ = name2;
    std::string name = name1 + "o" + name2;
    this->set_name(name);
    set_cuts(a);
    val1 = new T;
    val2 = new T;
  };
  ~KnifeType2Vars() {};
  T* val1;
  T* val2;
  virtual bool eval() {return false;}
  virtual void print()=0;
  virtual std::string cut_string() {return "";};
  std::string name1() {return val_name1_;}
  std::string name2() {return val_name2_;}
  void setAddress(TTree* tree) {
    //val1 = new T;
    //val2 = new T;
    tree->SetBranchStatus(this->name1().c_str(), 1);
    tree->SetBranchStatus(this->name2().c_str(), 1);
    tree->SetBranchAddress(this->name1().c_str(), val1);
    tree->SetBranchAddress(this->name2().c_str(), val2);
  };
  void setAddress(Barrel* barrel) {
    val1 = barrel->getPtr<T>(this->name1());
    val2 = barrel->getPtr<T>(this->name2());
  };
  void setAddress(std::string name, T* v) {
    if (name == val_name1_) {
      val1 = v;
    } else if (name == val_name2_) {
      val2 = v;
    }
  };
  void set_cuts(T a) {
    cut_ = a;
  };
};


}
#endif
