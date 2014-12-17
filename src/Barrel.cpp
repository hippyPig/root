#define SCPH_MONKEY_BARREL_H_CXX
#include "Barrel.hpp"



Barrel::Barrel() {;}

Barrel::~Barrel() {
  std::map<std::string, Primate*>::iterator it = monkeys_.begin();
  std::vector<std::string> monkeynames;
  for (; it!=monkeys_.end(); ++it) {
    monkeynames.push_back(it->first);
    delete it->second;
  }
  for (unsigned int m=0; m<monkeynames.size(); ++m) {
    monkeys_.erase(monkeynames.at(m));
  }
  return;
}


void Barrel::checkTree() {
  if (!tree_) {
    if (gibbons_.size() == 0) {
      oierror << "Error in Barrel: no TTree";
      throw;
    } else {
      oiwarning << "Barrel designed for use with TTree. "
        << "No TTree given, so assuming only MonkeyFcns are required.";
    }
  }
  return;
}


void Barrel::setTree(TTree* tree) {
  tree_ = tree;
  assert(tree_);
  return;
}


bool Barrel::exists(std::string const& name) {
  if (monkeys_.count(name)) {
    return true;
  } else {
    return false;
  }
}

bool Barrel::existsFcn(std::string const& name) {
  if (gibbons_.count(name)) {
    return true;
  } else {
    return false;
  }
}

void Barrel::getEntry(const unsigned& entry) {
  tree_->GetEntry(entry);
  for (unsigned function=0; function<auto_set_ptrs_.size(); ++function) {
    auto_set_ptrs_[function]();
  }
  return;
}

