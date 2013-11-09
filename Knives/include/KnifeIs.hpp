#ifndef SCPH_KNIVES_KNIFEIS_H
#define SCPH_KNIVES_KNIFEIS_H
#include "KnifeTypeBool.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "TTree.h"

#include "Oi.hpp"

namespace Knives {


template <typename T>
class KnifeIs : public KnifeTypeBool <T> {
 public:
  KnifeIs(std::string name) : KnifeTypeBool<T>(name) {};
  ~KnifeIs();
  bool eval() {
    if (*this->val) {
      return true;
    }
    return false;
  };
  void print() {
    oiinfo << "knife " << this->get_name();
  };
  std::string cut_string() {
    return this->get_name();
  };
};


}
#endif
