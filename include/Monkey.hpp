#ifndef SCPH_MONKEY_H
#define SCPH_MONKEY_H

#include "TTree.h"
#include "TBranch.h"

#include "Oi.hpp"
#include "Primate.hpp"

template <class T>
class Monkey : public Primate {
 private:
  T* ptr_;

 public:
  Monkey() {
    ptr_ = new T;
  };

  Monkey(TTree* tree, const std::string& branchname) {
    tree_ = tree;
    if (!tree->GetBranch(branchname.c_str())) {
      oierror << "Monkey::Monkey() Branch: " << branchname
        << " not found in tree.";
      throw;
    }
    ptr_ = new T;
    this->setAddress(branchname);
  };

  ~Monkey() {
    delete ptr_;
  };

  virtual void setAddress(TTree* tree, const std::string& branchname) {
    tree_ = tree;
    tree_->SetBranchStatus(branchname.c_str(), 1);
    tree_->SetBranchAddress(branchname.c_str(), ptr_);
    return;
  };

  virtual void setAddress(const std::string& branchname) {
    if (!tree_) {
      oierror << "Error in Monkey: no TTree";
      throw;
    }
    tree_->SetBranchStatus(branchname.c_str(), 1);
    tree_->SetBranchAddress(branchname.c_str(), ptr_);
    return;
  };

  T* getPtr() {
    return ptr_;
  };

  T get() {
    return *ptr_;
  };

  //void print() {
  //std::cout << "MONKEY: " << std::endl;
  //};

};


#endif
