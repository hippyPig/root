#ifndef SCPH_DENDROLOGYELM_CLASS_H
#define SCPH_DENDROLOGYELM_CLASS_H

#include <string>
#include <vector>

#include "Elm.hpp"
#include "Easel1D.hpp"
#include "Utils.hpp"
#include "Oi.hpp"


class DendrologyElm {
 protected:
  std::vector<Elm*> wood_;
  static int plotno_;
 public:
  DendrologyElm();
  ~DendrologyElm();
  void setWood(std::vector<Elm*>);
  void addElm(Elm*);
  //void addWeights(std::string);
  //void addWeights(std::vector<std::string>);
  //void addWeights(std::vector<std::vector<std::string> >);

  template<class T>
  Easel1D* compare(const std::string& varname,
      const std::string& title,
      const int& bins,
      const double& min,
      const double& max) {
    oihello << "DendrologyElm::compare() " << varname;
    Easel1D* easel = new Easel1D(varname + scph::ntos(plotno_));
    if (wood_.empty()) {
      oierror << "No Elms to compare.";
      throw;
    }
    T* var;
    int entries;
    std::string histname;
    for (unsigned int h=0; h<wood_.size(); ++h) {
      histname = varname + scph::ntos(plotno_) + "_" + scph::ntos(h);
      TH1D* htemp = new TH1D(histname.c_str(), title.c_str(), bins, min, max);
      entries = wood_.at(h)->getEntries();
      var = wood_.at(h)->getPtr<T>(varname);
      for (int entry=0; entry<entries; ++entry) {
        if (wood_.at(h)->getEntry(entry)) {
          htemp->Fill(static_cast<double>(*var));
        }
      }
      if (wood_.at(h)->getName() == "Data") {
        htemp->Sumw2();
      }
      easel->add(htemp, wood_.at(h)->getName());
    }
    plotno_++;
    return easel;
  };


  template<class T>
  Easel1D* compareWeight(const std::string& varname,
      const std::string& title,
      const std::string& weightname,
      const int& bins,
      const double& min,
      const double& max) {
    oihello << "DendrologyElm::compareWeight() " << varname;
    Easel1D* easel = new Easel1D(varname + scph::ntos(plotno_));
    if (wood_.empty()) {
      oierror << "No Elms to compare.";
      throw;
    }
    T* var;
    double* wt;
    int entries;
    std::string histname;
    for (unsigned int h=0; h<wood_.size(); ++h) {
      histname = varname + scph::ntos(plotno_) + "_" + scph::ntos(h);
      TH1D* htemp = new TH1D(histname.c_str(), title.c_str(), bins, min, max);
      entries = wood_.at(h)->getEntries();
      var = wood_.at(h)->getPtr<T>(varname);
      wt = wood_.at(h)->getPtr<double>(weightname);
      for (int entry=0; entry<entries; ++entry) {
        if (wood_.at(h)->getEntry(entry)) {
          htemp->Fill(static_cast<double>(*var), *wt);
        }
      }
      if (wood_.at(h)->getName() == "Data") {
        htemp->Sumw2();
      }
      easel->add(htemp, wood_.at(h)->getName());
    }
    plotno_++;
    return easel;
  };


  template<class T, class TW>
  Easel1D* compareWeight(const std::string& varname,
      const std::string& title,
      const std::string& weightname,
      const int& bins,
      const double& min,
      const double& max) {
    oihello << "DendrologyElm::compareWeight() " << varname;
    Easel1D* easel = new Easel1D(varname + scph::ntos(plotno_));
    if (wood_.empty()) {
      oierror << "No Elms to compare.";
      throw;
    }
    T* var;
    TW* wt;
    int entries;
    std::string histname;
    for (unsigned int h=0; h<wood_.size(); ++h) {
      histname = varname + scph::ntos(plotno_) + "_" + scph::ntos(h);
      TH1D* htemp = new TH1D(histname.c_str(), title.c_str(), bins, min, max);
      entries = wood_.at(h)->getEntries();
      var = wood_.at(h)->getPtr<T>(varname);
      wt = wood_.at(h)->getPtr<TW>(weightname);
      for (int entry=0; entry<entries; ++entry) {
        if (wood_.at(h)->getEntry(entry)) {
          htemp->Fill(static_cast<double>(*var), static_cast<double>(*wt));
        }
      }
      if (wood_.at(h)->getName() == "Data") {
        htemp->Sumw2();
      }
      easel->add(htemp, wood_.at(h)->getName());
    }
    plotno_++;
    return easel;
  };


};


#endif
