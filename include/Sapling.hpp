#ifndef SCPH_DENDROLOGY_SAPLING_H
#define SCPH_DENDROLOGY_SAPLING_H

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"

#include "Elm.hpp"
#include "Oi.hpp"


class Sapling {
 private:
  TFile* file_;
  TTree* tree_;
  Elm* elm_;
  std::map<std::string, TBranch*> branches_;

 public:
  Sapling();
  Sapling(Elm*, const std::string&);
  ~Sapling();
  void fill();
  void write();

  template <class T>
  void add(std::string branchname) {
    elm_->add<T>(branchname);
    branches_[branchname] =
      tree_->Branch(branchname.c_str(), elm_->getPtr<T>(branchname));
    return;
  }

  template <class T>
  void add(std::string branchname, std::string name) {
    elm_->add<T>(branchname, name);
    branches_[name] =
      tree_->Branch(name.c_str(), elm_->getPtr<T>(name));
    return;
  }

  template <class T>
  void add(std::string branchname, boost::function<T()>& fcn) {
    elm_->add<T>(branchname, fcn);
    branches_[branchname] =
      tree_->Branch(branchname.c_str(), elm_->getPtr<T>(branchname));
    return;
  }

  template <class T>
  void add(std::string branchname, T* val) {
    branches_[branchname] =
      tree_->Branch(branchname.c_str(), val);
    return;
  }


};

#endif
