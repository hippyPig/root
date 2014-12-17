#define SCPH_ELM_CLASS_H_cxx
#include "Elm.hpp"

#include "TFile.h"
#include "TH1.h"
#include "TRandom3.h"
#include "TTree.h"
#include "Utils.hpp"

#include <assert.h>

#include <iostream>

Elm::Elm(TTree* tree) :
    pass_all_(true),
    tree_(tree),
    file_new_(NULL),
    tree_new_(NULL) {
  barrel_ = new Barrel(tree_);
  pass_.resize(this->tree_->GetEntries());
  save_state_.resize(this->tree_->GetEntries());
  tree_->SetBranchStatus("*", 0);
  if (isBranch("Bplus_MM")) {
    tree_->SetBranchStatus("Bplus_MM", 1);
  } else if (isBranch("lab0_MM")) {
    tree_->SetBranchStatus("lab0_MM", 1);
  }
  setName("None");
  revertTree();
  return;
}


Elm::Elm(TTree* tree, std::string name) :
    pass_all_(true),
    tree_(tree),
    file_new_(NULL),
    tree_new_(NULL) {
  barrel_ = new Barrel(tree_);
  pass_.resize(this->tree_->GetEntries());
  save_state_.resize(this->tree_->GetEntries());
  tree_->SetBranchStatus("*", 0);
  if (isBranch("Bplus_MM")) {
    tree_->SetBranchStatus("Bplus_MM", 1);
  } else if (isBranch("lab0_MM")) {
    tree_->SetBranchStatus("lab0_MM", 1);
  }
  setName(name);
  revertTree();
  return;
}


Elm::~Elm() {;}


void Elm::setTree(TTree* tree) {
  pass_all_ = true;
  tree_ = tree;
  delete barrel_;
  barrel_ = new Barrel(tree);
  oiinfo << "TTree added: " << this->tree_->GetName();
  pass_.resize(this->tree_->GetEntries());
  save_state_.resize(this->tree_->GetEntries());
  oiwarning << "Constructor of Elm sets all branch addresses off.";
  tree_->SetBranchStatus("*", 0);
  if (isBranch("Bplus_MM")) {
    tree_->SetBranchStatus("Bplus_MM", 1);
  } else if (isBranch("lab0_MM")) {
    tree_->SetBranchStatus("lab0_MM", 1);
  }
  setName("None");
  revertTree();
  return;
}


void Elm::applyCuts(Kcuts& cuts) {
  oihello << "Elm::applyCuts()";
  oiinfo << cuts.cut_string();
  cuts.setAddresses(barrel_);
  oiinfo << "Addresses set";
  pass_entries_ = 0;
  pass_all_ = true;
  int entries = this->tree_->GetEntries();
  for (int entry=0; entry<entries; ++entry) {
    barrel_->getEntry(entry);
    oiinfo.count(entry, entries, "Applying cuts to Elm");
    if (cuts.eval()) {
      pass_.at(entry) = true;
      ++pass_entries_;
    } else {
      pass_.at(entry) = false;
      pass_all_ = false;
    }
  }
  oiinfo << "Entries, entries passed: " << entries << ", " << pass_entries_;
  oiinfo << "Efficiency: " << (double)pass_entries_ / entries * 100. << " %";
  oibye << "Elm::applyCuts()";
}


void Elm::addCuts(Kcuts& cuts) {
  oihello << "Elm::addCuts()";
  oiinfo << cuts.cut_string();
  cuts.setAddresses(barrel_);
  oiinfo << "Addresses set";
  pass_entries_ = 0;
  pass_all_ = true;
  int entries = this->tree_->GetEntries();
  if (cuts.size() == 0) {
    oiinfo << "No Knife in Knives";
    return;
  }
  for (int entry=0; entry<entries; ++entry) {
    oiinfo.count(entry, entries, "Adding cuts to Elm");
    if (this->getEntry(entry)) {
      if (cuts.eval()) {
        pass_.at(entry) = true;
        ++pass_entries_;
      } else {
        pass_.at(entry) = false;
        pass_all_ = false;
      }
    }
  }
  oiinfo << "Entries, entries passed: " << entries << ", " << pass_entries_;
  oiinfo << "Efficiency: " << (double)pass_entries_ / entries * 100. << " %";
  oibye << "Elm::addCuts()";
  return;
}


void Elm::revertTree() {
  pass_all_ = true;
  for (unsigned int entry=0; entry<pass_.size(); ++entry) {
    pass_.at(entry) = true;
  }
  save_state_ = pass_;
  return;
}


bool Elm::getEntry(const unsigned& entry) {
  if (this->pass_.at(entry)) {
    //this->tree_->GetEntry(entry);
    this->barrel_->getEntry(entry);
  }
  return this->pass_.at(entry);
}


bool Elm::getEntryForce(const unsigned& entry) {
  this->barrel_->getEntry(entry);
  return this->pass_.at(entry);
}


int Elm::getEntries() {
  return this->tree_->GetEntries();
}


int Elm::getPassEntries() {
  return pass_entries_;
}


bool Elm::passAll() {
  return pass_all_;
}


TTree* Elm::getTree() {
  return tree_;
}


void Elm::multipleCandidates() {
  oihello << "Elm::multipleCandidates()";
  ULong64_t nevt_current;
  ULong64_t nevt_previous;
  tree_->SetBranchAddress("eventNumber", &nevt_current);
  nevt_previous = 0;
  unsigned int candidates = 0;
  std::vector<int> cands;
  cands.resize(10);
  for (int i=0; i<10; ++i) {
    cands.at(i) = 0;
  }
  int entries = this->tree_->GetEntries();
  int events = 0;
  unsigned int total_candidates = 0;
  for (int entry=0; entry<entries; ++entry) {
    oiinfo.count(entry, entries, "Looking for multiple candidates");
    if (getEntry(entry)) {
      total_candidates++;
      if (nevt_previous == nevt_current) {
        candidates++;
      } else {
        if (candidates > cands.size() - 1) {
          cands.at(cands.size() - 1)++;
        } else {
          cands.at(candidates)++;
        }
        candidates = 0;
        events++;
      }
      nevt_previous = nevt_current;
    }
  }
  oiinfo << "Total number of entries: " << entries;
  oiinfo << "Total number of events:  " << events;
  oiinfo << "Total number of candidates:  " << total_candidates;
  oiinfo << "cands\t\tevent";
  for (unsigned int i=0; i<cands.size()-1; ++i) {
    oiinfo << i + 1 << "\t\t" << cands.at(i);
  }
  oiinfo << ">=" << cands.size() << "\t\t" << cands.at(cands.size() - 1);
  oiinfo << "Candidates per event: " << (double)total_candidates / (double)events;
  return;
}


void Elm::removeMultipleCandidates() {
  oihello << "Elm::removeMultipleCandidates()";
  //ULong64_t nevt;
  std::vector<ULong64_t> nevt_vec;
  std::vector<int> entry_vec;
  TRandom3 random3;
  random3.SetSeed(4357);
  int random;
  int entries = this->tree_->GetEntries();
  int candidates = 0;
  int events = 0;
  //ULong64_t* nevt = this->getPtr<ULong64_t>("eventNumber");
  ULong64_t nevt = 0;
  if (!this->isBranch("eventNumber")) {
    oierror << "No eventNumber in the tree!";
    throw;
  }
  this->tree_->SetBranchStatus("eventNumber", 1);
  this->tree_->SetBranchAddress("eventNumber", &nevt);
  for (int entry=0; entry<entries; ++entry) {
    events++;
    if(this->getEntry(entry)) {
      //oiinfo << nevt;
      if (nevt_vec.size() == 0) {
        //nevt_vec.push_back(*nevt);
        nevt_vec.push_back(nevt);
        entry_vec.push_back(entry);
        pass_.at(entry) = false;
        //} else if (nevt_vec.back() == *nevt) {
      } else if (nevt_vec.back() == nevt) {
        //nevt_vec.push_back(*nevt);
        nevt_vec.push_back(nevt);
        entry_vec.push_back(entry);
        pass_.at(entry) = false;
      } else {
        random = (int)random3.Uniform(0, entry_vec.size());
        //this->tree_->GetEntry(entry_vec[random]);
        this->barrel_->getEntry(entry_vec[random]);
        candidates++;
        pass_.at(random) = true;
        nevt_vec.clear();
        entry_vec.clear();
        //this->tree_->GetEntry(entry);
        this->barrel_->getEntry(entry);
        //nevt_vec.push_back(*nevt);
        nevt_vec.push_back(nevt);
        entry_vec.push_back(entry);
      }
    }
  }
  if (nevt_vec.size() > 0) {
    random = (int)random3.Uniform(0, entry_vec.size());
    this->barrel_->getEntry(entry_vec[random]);
    //this->tree_->GetEntry(entry_vec[random]);
    candidates++;
    pass_.at(random) = true;
    nevt_vec.clear();
    entry_vec.clear();
  }
  oiinfo << "Candidates: " << candidates << "   Events: " << events
            << "  Candidates/Event: " << static_cast<double>(candidates) / events;
  oibye << "Elm::removeMulitpleCandidates()";
  pass_entries_ = candidates;
  return;
}


void Elm::setName(std::string name) {
  name_ = name;
  return;
}


std::string Elm::getName() {
  return name_;
}


bool Elm::isBranch(const std::string& var) {
  TBranch* branch = this->tree_->GetBranch(var.c_str());
  if (!branch) {
    return false;
  } else {
    return true;
  }
}


bool Elm::isBool(const std::string& branch) {
  return scph::isBool(this->tree_, branch);
}


bool Elm::isDouble(const std::string& branch) {
  return scph::isDouble(this->tree_, branch);
}


bool Elm::isInt(const std::string& branch) {
  return scph::isInt(this->tree_, branch);
}


bool Elm::isFloat(const std::string& branch) {
  return scph::isFloat(this->tree_, branch);
}


void Elm::outTree(std::string filename) {
  oihello << "Elm::outTree()";
  oiinfo << "Creating new file: " << filename;
  TFile* file_out = new TFile(filename.c_str(), "recreate");
  TTree* tree_out = this->tree_->CloneTree(0);
  assert(tree_out);
  int entries = this->tree_->GetEntries();
  for (int entry=0; entry<entries; ++entry) {
    oiinfo.count(entry, entries);
    if (this->getEntry(entry)) {
      tree_out->Fill();
    }
  }
  file_out->cd();
  tree_out->Write();
  file_out->Close();
  delete file_out;
  oiinfo << "Entries in new tree: " << tree_out->GetEntries();
  oibye << "Elm::outTree()";
  return;
}


void Elm::saveState() {
  save_state_ = pass_;
  return;
}


void Elm::revertState() {
  pass_ = save_state_;
  pass_entries_ = 0;
  int entries = this->tree_->GetEntries();
  for (int entry=0; entry<entries; ++entry) {
    if (pass_.at(entry)) {
      pass_entries_++;
    }
  }
  return;
}


void Elm::setBranch(const std::string& branchname) {
  if (isBranch(branchname)) {
    this->tree_->SetBranchStatus(branchname.c_str());
  }
  return;
}


void Elm::setBranch(const char* branchname) {
  if (isBranch(branchname)) {
    this->tree_->SetBranchStatus(branchname);
  }
  return;
}


void Elm::setBranch(const std::vector<std::string>& branchname) {
  for (unsigned branch=0; branch<branchname.size(); ++branch) {
    setBranch(branchname.at(branch));
  }
  return;
}


void Elm::setBranch(const bool& set) {
  this->tree_->SetBranchStatus("*", set);
  return;
}


void Elm::setBranchEndsWith(const std::string& set, const bool& apply) {
  TObjArray* arr = this->tree_->GetListOfBranches();
  TIter nextbranch(arr);
  TBranch* branch;
  while ((branch = static_cast<TBranch*>(nextbranch()))) {
    if (scph::endsWith(branch->GetName(), set)) {
      tree_->SetBranchStatus(branch->GetName(), apply);
    }
  }
  return;
}


void Elm::setBranchStartsWith(const std::string& set, const bool& apply) {
  TObjArray* arr = this->tree_->GetListOfBranches();
  TIter nextbranch(arr);
  TBranch* branch;
  while ((branch = static_cast<TBranch*>(nextbranch()))) {
    if (scph::startsWith(branch->GetName(), set)) {
      tree_->SetBranchStatus(branch->GetName(), apply);
    }
  }
  return;
}


void Elm::setBranchContains(const std::string& set, const bool& apply) {
  TObjArray* arr = this->tree_->GetListOfBranches();
  TIter nextbranch(arr);
  TBranch* branch;
  while ((branch = static_cast<TBranch*>(nextbranch()))) {
    if (scph::contains(branch->GetName(), set)) {
      tree_->SetBranchStatus(branch->GetName(), apply);
    }
  }
  return;
}


void Elm::setCuts(Kcuts& cuts) {
  cuts.setAddresses(barrel_);
  return;
}


bool Elm::eval(const int& entry, Kcuts& cuts) {
  this->getEntryForce(entry);
  if (cuts.eval()) {
    pass_.at(entry) = true;
    return true;
  } else {
    pass_.at(entry) = false;
    pass_all_ = false;
    return false;
  }
}


void Elm::write(const std::string& filename) {
  oihello << "Elm::write()";
  oiinfo << "Write Elm to file " << filename;
  TFile* file_new = new TFile(filename.c_str(), "recreate");
  assert(file_new);
  TTree* tree_new = this->tree_->CloneTree(0);
  assert(tree_new);
  int entries = getEntries();
  for (int entry=0; entry<entries; ++entry) {
    oiinfo.count(entry, entries);
    if (getEntry(entry)) {
      tree_new->Fill();
    }
  }
  tree_new->Write();
  file_new->Close();
  oiinfo << "Elm written to file";
  delete file_new;
  return;
}


RooDataSet* Elm::getDataSet(RooRealVar*& rrv, const std::string& vname, const std::string& name) {
  unsigned entries = getEntries();
  double* var = this->getPtr<double>(vname);
  RooDataSet* data = new RooDataSet(name.c_str(), "", RooArgSet(*rrv));
  for (unsigned entry=0; entry<entries; ++entry) {
    if (getEntry(entry)) {
      if (*var > rrv->getMin() && *var < rrv->getMax()) {
        rrv->setVal(*var);
        data->add(*rrv);
      }
    }
  }
  return data;
}

