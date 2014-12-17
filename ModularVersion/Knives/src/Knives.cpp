#define KNIVES_CONTAINER_CLASS_H_CXX
#include "Knives.hpp"

#include <assert.h>
#include <algorithm>
#include <sstream>

#include "Knife.hpp"

namespace Knives {

Knives::Knives() {;}


Knives::~Knives() {
  return;
}


Knives Knives::operator+ (Knife* knife) {
  Knives knives;
  knives.add(*this);
  knives.add(knife);
  return knives;
}


Knives Knives::operator+ (Knives cuts) {
  Knives knives;
  knives.add(*this);
  knives.add(cuts);
  return knives;
}


Knives Knives::operator+ (std::vector<Knife*> cuts) {
  Knives knives;
  knives.add(*this);
  knives.add(cuts);
  return knives;
}


void Knives::operator+= (Knife* knife) {
  this->add(knife);
  return;
}


void Knives::operator+= (Knives knives) {
  this->add(knives);
  return;
}


void Knives::operator+= (std::vector<Knife*> cuts) {
  this->add(cuts);
  return;
}


Knife* Knives::get_cut(std::string cutname) {
  it_cuts_ = cuts_.begin();
  for (; it_cuts_!=cuts_.end(); ++it_cuts_) {
    if (cutname == (*it_cuts_)->get_name()) {
      return (*it_cuts_);
    }
  }
  if (cuts_.size() == 1) {
    oiwarning << "Knife with name: " << cutname << " DOES NOT EXIST.";
    oiwarning << "   Returning " << cuts_.at(0)->get_name() << ".";
  } else {
    oierror << "Knife with name: " << cutname << " DOES NOT EXIST.";
    assert(cuts_.size() == 1);
  }
  return cuts_.at(0);
}


void Knives::setAddresses(TTree* tree) {
  it_cuts_ = cuts_.begin();
  for (; it_cuts_!=cuts_.end(); ++it_cuts_) {
    (*it_cuts_)->setAddress(tree);
  }
  return;
}


void Knives::setAddresses(Barrel* barrel) {
  it_cuts_ = cuts_.begin();
  for (; it_cuts_!=cuts_.end(); ++it_cuts_) {
    (*it_cuts_)->setAddress(barrel);
  }
  return;
}


void Knives::add(Knife* cut) {
  cuts_.push_back(cut);
  return;
}


void Knives::add(Knives knives) {
  std::vector<Knife*> cuts = knives.getCuts();
  cuts_.insert(cuts_.end(), cuts.begin(), cuts.end());
  return;
}


void Knives::add(std::vector<Knife*> cuts) {
  cuts_.insert(cuts_.end(), cuts.begin(), cuts.end());
  return;
}


void Knives::clear() {
  cuts_.clear();
  return;
}


void Knives::update(Knife* cut) {
  it_cuts_ = cuts_.begin();
  for (; it_cuts_!=cuts_.end(); ++it_cuts_) {
    if (cut->get_name() == (*it_cuts_)->get_name()) {
      (*it_cuts_) = cut;
      return;
    }
  }
  oiwarning << "No cut named " << cut->get_name();
  oiwarning << "ADDING";
  cuts_.push_back(cut);
  return;
}


void Knives::update(std::vector<std::string> cutnames, double cut_new) {
  oihello << "Knives::update() ";
  for (unsigned int cutname=0; cutname<cutnames.size(); ++cutname) {
    KnifeTypeSimple<double>* cut = (KnifeTypeSimple<double>*)get_cut(cutnames.at(cutname));
    cut->update(cut_new);
  }
  return;
}


void Knives::update(std::vector<std::string> cutnames, float cut_new) {
  oihello << "Knives::update() ";
  for (unsigned int cutname=0; cutname<cutnames.size(); ++cutname) {
    KnifeTypeSimple<float>* cut = (KnifeTypeSimple<float>*)get_cut(cutnames.at(cutname));
    cut->update(cut_new);
  }
  return;
}


void Knives::update(std::string cutname, double cut_new_low, double cut_new_high) {
  oihello << "Knives::update() " << cutname << " "
             << cut_new_low << " -> " << cut_new_high;
  KnifeTypeRange<double>* cut = (KnifeTypeRange<double>*)get_cut(cutname);
  cut->update(cut_new_low, cut_new_high);
  update(cut);
  return;
}


void Knives::print() {
  it_cuts_ = cuts_.begin();
  for (; it_cuts_!=cuts_.end(); ++it_cuts_) {
    (*it_cuts_)->print();
  }
  return;
}


bool Knives::eval() {
  if (cuts_.size() == 0) {
    return true;
  }
  it_cuts_ = cuts_.begin();
  for (; it_cuts_!=cuts_.end(); ++it_cuts_) {
    if (!(*it_cuts_)->eval()) {
      return false;
    }
  }
  return true;
}


std::string Knives::cut_string() {
  std::stringstream ss;
  if (cuts_.size() == 0) {
    return "";
  }
  it_cuts_ = cuts_.begin();
  ss << (*it_cuts_)->cut_string();
  ++it_cuts_;
  for (; it_cuts_!=cuts_.end(); ++it_cuts_) {
    ss << "\t" << (*it_cuts_)->cut_string();
  }
  return ss.str();
}


std::vector<Knife*> Knives::getCuts() {
  return cuts_;
}

unsigned Knives::size() {
    return cuts_.size();
}


}
