#ifndef SCPH_KNIVES_KNIFEDIFFGT_H
#define SCPH_KNIVES_KNIFEDIFFGT_H
#include "KnifeType2Vars.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "TTree.h"

#include "Oi.hpp"

namespace Knives {


template <typename T>
class KnifeDiffGt : public KnifeType2Vars <T> {
 public:
  //KnifeIn() : KnifeTypeRange<T>() {};
  KnifeDiffGt(std::string name1, std::string name2, T a) : KnifeType2Vars<T>(name1, name2, a) {
    std::string name = name1 + "-" + name2;
    this->set_name(name);
    return;
  };
  ~KnifeDiffGt();
  bool eval() {
    return ((*this->val1 - *this->val2) > this->cut());
  };
  void print() {
    oiinfo << "knife " << this->get_name() << ">" << this->cut();
    return;
  };
  virtual std::string cut_string() {
    std::stringstream ss;
    ss << this->get_name() << ">" << this->cut();
    return ss.str();
  };
};


}
#endif
