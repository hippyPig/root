#ifndef SCPH_KNIVES_KNIVEAND_H
#define SCPH_KNIVES_KNIVEAND_H
#include "Knife.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "TTree.h"

#include "Oi.hpp"

namespace Knives {


class KnifeAnd : public Knife {
 protected:
  Knife* cut1_;
  Knife* cut2_;
 public:
  KnifeAnd(Knife* cut1, Knife* cut2) :
      cut1_(cut1),
      cut2_(cut2) {
    //std::string name = "(" + cut1->get_name() + ")&&(" + cut2->get_name() + ")";
    std::string name = "(" + cut1->cut_string() + ")&&(" + cut2->cut_string() + ")";
    this->set_name(name);
    return;
  };
  ~KnifeAnd() {};
  bool eval() {
    return (cut1_->eval() && cut2_->eval());
  };
  void setAddress(TTree* tree) {
    cut1_->setAddress(tree);
    cut2_->setAddress(tree);
    return;
  };
  void setAddress(Barrel* barrel) {
    cut1_->setAddress(barrel);
    cut2_->setAddress(barrel);
    return;
  };
  void print() {
    oiinfo << "knife " << this->get_name();
    return;
  };
  std::string cut_string() {
    return this->get_name();
  };
};


}
#endif
