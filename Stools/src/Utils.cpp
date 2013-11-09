// Define & include header
#define SCPH_UTILS_STOOLS_NAMESPACE_H_CXX
#include "Utils.hpp"

// Include standard
#include <iostream>

// Include ROOT
#include "TLorentzVector.h"

// Include boost
#include "Spectrum.hpp"

//------------------------------------------------------------------------------
// Sam Hall's Utilities implementation file
//------------------------------------------------------------------------------

// Typedefs
typedef std::vector<std::string> svector;

//==============================================================================
// For the ease of not being in namespace
//==============================================================================
void Progress(const int& entry, const int& entries, const std::string& msg) {
  if (entry % 10000 == 0) {
    std::cout << spectrum::fore::yellow
              << "COUNT   : " << msg << " " << entry << " of " << entries << "  ("
              << Stools::dtos(100. * double(entry) / double(entries), 1) << " %)"
              << "       \r" << spectrum::reset;
    std::cout.flush() ;
  }
  if (entry % entries == entries - 1) {
    std::cout << spectrum::fore::yellow
              << "COUNT   : Finished : " << msg << " " << entries << " entries"
              << "        " << spectrum::reset << std::endl;
  }
  return;
}
//==============================================================================
//
void Count(const int& entry, const int& entries) {
  if (entry % 10000 == 0) {
    std::cout << spectrum::fore::yellow
              << "COUNT   : Analysing " << entry << " of " << entries << "  ("
              << Stools::dtos(100. * double(entry) / double(entries), 1) << " %)"
              << spectrum::reset << std::endl;
  }
  return;
}
//==============================================================================
//
void Linebreak() {
  std::cout << "========================================"
            << "========================================" << std::endl;
  return;
}

//==============================================================================
// Old namespace, being replaced by scph
//==============================================================================
namespace Stools {
  //==============================================================================
  // strings
  //==============================================================================
  std::string replace(std::string str, const std::string& what, const std::string& with) {
    if (str.find(what) == std::string::npos) {
      return str;
    }
    str.replace(str.find(what), what.length(), with);
    return str;
  }
  //
  svector splitString(std::string str, std::string delimiter) {
    svector splitVec;
    boost::split(splitVec, str, boost::is_any_of(delimiter));
    return splitVec;
  }
  //
  //==============================================================================
  // ROOT
  //==============================================================================
  void swapPID(TLorentzVector& p4, double m) {
    double p = p4.Vect().Mag();
    p4.SetE(sqrt(p * p + m * m));
    return;
  }
  //
  TLorentzVector getP4(double* px, double* py, double* pz, double* e) {
    return TLorentzVector(*px, *py, *pz, *e);
  }
  //
  TLorentzVector getSwapPID(const TLorentzVector& p4, double m) {
    TLorentzVector temp = p4;
    double p = temp.Vect().Mag();
    temp.SetE(sqrt(p * p + m * m));
    return temp;
  }
  //
  TLorentzVector getP4SwapPID(double* px, double* py, double* pz, double* e, double m) {
    TLorentzVector temp(*px, *py, *pz, *e);
    return getSwapPID(temp, m);
  }
  //
  // Type stuff for ROOT
  char getBranchType(TTree* tree, std::string branch) {
    char type[50];
    strcpy(type, (tree->GetBranch(branch.c_str()))->GetTitle());
    strcpy(type, strstr(type, "/"));
    return type[1];
  }
  //
  bool isBool(TTree* tree, const std::string& branch) {
    return getBranchType(tree, branch) == 'O';
  }
  //
  bool isInt(TTree* tree, const std::string& branch) {
    return getBranchType(tree, branch) == 'I';
  }
  //
  bool isDouble(TTree* tree, const std::string& branch) {
    return getBranchType(tree, branch) == 'D';
  }
  //
  bool isFloat(TTree* tree, const std::string& branch) {
    return getBranchType(tree, branch) == 'F';
  }
  //
  bool isBranch(TTree* tree, const std::string& var) {
    bool out;
    TBranch* branch = tree->GetBranch(var.c_str());
    if (!branch) {
      out = false;
    } else {
      out = true;
    }
    return out;
  }

} // namespace Stools


//==============================================================================
// New and better namespace
//==============================================================================
namespace scph {
  //==============================================================================
  // strings
  //==============================================================================
  std::string replace(std::string str, const std::string& what, const std::string& with) {
    if (str.find(what) == std::string::npos) {
      return str;
    }
    str.replace(str.find(what), what.length(), with);
    return str;
  }
  //
  svector splitString(std::string str, std::string delimiter) {
    svector splitVec;
    boost::split(splitVec, str, boost::is_any_of(delimiter));
    return splitVec;
  }
  //
  bool endsWith(const std::string& s, const std::string& suffix) {
    return s.rfind(suffix) == (s.size() - suffix.size());
  }
  //
  bool contains(const std::string& s, const std::string& sub) {
    return s.find(sub) != std::string::npos;
  }
  //
  //==============================================================================
  // ROOT
  //==============================================================================
  void swapPID(TLorentzVector& p4, double m) {
    double p = p4.Vect().Mag();
    p4.SetE(sqrt(p * p + m * m));
    return;
  }
  //
  TLorentzVector getP4(double* px, double* py, double* pz, double* e) {
    return TLorentzVector(*px, *py, *pz, *e);
  }
  //
  TLorentzVector getSwapPID(const TLorentzVector& p4, double m) {
    TLorentzVector temp = p4;
    double p = temp.Vect().Mag();
    temp.SetE(sqrt(p * p + m * m));
    return temp;
  }
  //
  TLorentzVector getP4SwapPID(double* px, double* py, double* pz, double* e, double m) {
    TLorentzVector temp(*px, *py, *pz, *e);
    return getSwapPID(temp, m);
  }
  //
  // Type stuff for ROOT
  char getBranchType(TTree* tree, std::string branch) {
    char type[50];
    strcpy(type, (tree->GetBranch(branch.c_str()))->GetTitle());
    strcpy(type, strstr(type, "/"));
    return type[1];
  }
  //
  bool isBool(TTree* tree, const std::string& branch) {
    return getBranchType(tree, branch) == 'O';
  }
  //
  bool isInt(TTree* tree, const std::string& branch) {
    return getBranchType(tree, branch) == 'I';
  }
  //
  bool isDouble(TTree* tree, const std::string& branch) {
    return getBranchType(tree, branch) == 'D';
  }
  //
  bool isFloat(TTree* tree, const std::string& branch) {
    return getBranchType(tree, branch) == 'F';
  }
  //
  bool isBranch(TTree* tree, const std::string& var) {
    bool out;
    TBranch* branch = tree->GetBranch(var.c_str());
    if (!branch) {
      out = false;
    } else {
      out = true;
    }
    return out;
  }

} // namespace scph


