#ifndef SCPH_ELM_CLASS_H
#define SCPH_ELM_CLASS_H
#include <map>
#include <string>
#include <vector>
#include <boost/bind.hpp>
#include <boost/function.hpp>

#include "TTree.h"
#include "TLorentzVector.h"
#include "RooDataSet.h"
#include "RooRealVar.h"

#include "Knives.hpp"
#include "Barrel.hpp"
#include "Utils.hpp"


class Elm {
 protected:
  Barrel* barrel_;

  std::vector<bool> pass_;
  std::vector<bool> save_state_;
  std::string name_;
  bool pass_all_;
  int pass_entries_;
  TTree* tree_;
  TFile* file_new_;
  TTree* tree_new_;
  std::map<std::string, TBranch*> branches_;

 public:
  Elm() {};
  Elm(TTree*);
  Elm(TTree*, std::string);
  ~Elm();
  bool getEntry(const unsigned&);
  bool getEntryForce(const unsigned&);
  void applyCuts(Kcuts&);
  void addCuts(Kcuts&);
  void revertTree();
  int getEntries();
  int getPassEntries();
  bool passAll();
  bool isBranch(const std::string&);
  bool isDouble(const std::string&);
  bool isFloat(const std::string&);
  bool isBool(const std::string&);
  bool isInt(const std::string&);
  TTree* getTree();
  void removeMultipleCandidates();
  void multipleCandidates();
  std::string getName();
  void setName(std::string);
  void outTree(std::string);
  void saveState();
  void revertState();
  void setTree(TTree*);
  void setBranch(const std::string&);
  void setBranch(const char*);
  void setBranch(const std::vector<std::string>&);
  void setBranch(const bool&);
  void setBranchEndsWith(const std::string&, const bool& apply=true);
  void setBranchStartsWith(const std::string&, const bool& apply=true);
  void setBranchContains(const std::string&, const bool& apply=true);
  void write(const std::string&);
  void setCuts(Kcuts& cuts);
  bool eval(const int& entry, Kcuts&);
  RooDataSet* getDataSet(RooRealVar*&, const std::string&, const std::string&);

  Barrel* getBarrel() { return barrel_; }
  void setBarrel(Barrel* barrel) {
    barrel_ = barrel;
  }

  template <class T>
  void add(std::string branchname) {
    barrel_->add<T>(branchname);
    return;
  }

  template <class T>
  void add(std::string branchname, std::string name) {
    barrel_->add<T>(branchname, name);
    return;
  }

  template <class T>
  void add(std::string branchname, boost::function<T()>& fcn) {
    barrel_->add<T>(fcn, branchname);
    return;
  }

  template <class T>
  T* getPtr(std::string branchname) {
    return barrel_->getPtr<T>(branchname);
  }

  template <class T>
  T get(std::string branchname) {
    return barrel_->get<T>(branchname);
  }

  boost::function<TLorentzVector()> getTLorentzVector(const std::string& name) {
    return boost::bind(scph::getP4,
        this->getPtr<double>(name + "_PX"), this->getPtr<double>(name + "_PY"),
        this->getPtr<double>(name + "_PZ"), this->getPtr<double>(name + "_PE"));
  }
  boost::function<TLorentzVector()> getTLorentzVector(const std::string& name, const bool& trueth) {
    if (trueth) {
      return boost::bind(scph::getP4,
          this->getPtr<double>(name + "_PX"), this->getPtr<double>(name + "_PY"),
          this->getPtr<double>(name + "_PZ"), this->getPtr<double>(name + "_PE"));
    } else {
      return boost::bind(scph::getP4,
          this->getPtr<double>(name + "_TRUEP_X"), this->getPtr<double>(name + "_TRUEP_Y"),
          this->getPtr<double>(name + "_TRUEP_Z"), this->getPtr<double>(name + "_TRUEP_E"));
    }
  }

};


#endif
