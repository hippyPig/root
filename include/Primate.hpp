#ifndef SCPH_MONKEY_BASE_H
#define SCPH_MONKEY_BASE_H

#include <string>
#include "TTree.h"
#include "Oi.hpp"


class Primate {
 protected:
  TTree* tree_;

 public:
  Primate() {;}
  virtual ~Primate() {;}

  virtual void setAddress(TTree*, std::string const&)=0;
  virtual void setAddress(std::string const&)=0;

  void setTree(TTree* tree) {
    tree_ = tree;
    return;
  }

};

#endif
