#ifndef SCPH_GIBBON_H
#define SCPH_GIBBON_H
// Func(tion)y Gibbon.  That's enough Ed.

#include "boost/bind.hpp"
#include "boost/function.hpp"

#include "TTree.h"
#include "TBranch.h"

#include "Primate.hpp"
#include "Oi.hpp"


template <class T>
class Gibbon : public Primate {
 private:
  T* ptr_;
  boost::function<T()> fcn_;

 public:
  Gibbon() {
    ptr_ = new T;
  };

  Gibbon(boost::function<T()> fcn, const std::string& branchname) {
    fcn_ = fcn;
    ptr_ = new T;
    oierror << "Constructor Gibbon(oost::function<T()>, const std::string&) "
      << "for \"" << branchname << "\" not available in Gibbon";
    throw;
  };

  ~Gibbon() {
    delete ptr_;
  };

  void setAddress(TTree* tree, const std::string& branchname) {
    if (tree) {
      oierror << "function setAddress(TTree*, const std::string&) "
        << "for \"" << branchname << "\" and TTree "
        << tree->GetName() << " not available in Gibbon";
    } else {
      oierror << "function setAddress(TTree*, const std::string&) "
        << "for \"" << branchname << "\" and (undefined) TTree "
        << " not available in Gibbon";
    }
    throw;
    return;
  };

  void setAddress(const std::string& branchname) {
    oierror << "function setAddress(const std::string&) "
      << "for \"" << branchname << "\" not available in Gibbon";
    throw;
    return;
  };

  T* getPtr() {
    *ptr_ = fcn_();
    return ptr_;
  };

  T get() {
    return fcn_();
  };

  void setPtr() {
    *ptr_ = fcn_();
  }

};


#endif
