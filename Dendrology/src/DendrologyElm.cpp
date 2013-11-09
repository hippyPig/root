#define SCPH_DENDROLOGYELM_CLASS_H_CXX
#include "DendrologyElm.hpp"

#include <string>
#include <vector>

#include "TH1D.h"

#include "Elm.hpp"
#include "Easel1D.hpp"
#include "Utils.hpp"

//bool DendrologyElm::weight_ = false;
int DendrologyElm::plotno_ = 0;

DendrologyElm::DendrologyElm() {;}


DendrologyElm::~DendrologyElm() {
  while (!wood_.empty()) {
    delete wood_.back();
    wood_.pop_back();
  }
  return;
}


void DendrologyElm::setWood(std::vector<Elm*> wood) {
  wood_ = wood;
  return;
}


void DendrologyElm::addElm(Elm* elm) {
  wood_.push_back(elm);
  return;
}


