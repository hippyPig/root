// Define & include header
#define SCPH_UTILS_STOOLS_NAMESPACE_H_CXX
#include "Utils.hpp"


//------------------------------------------------------------------------------
// Sam Hall's Utilities implementation file
//------------------------------------------------------------------------------


namespace scph {
  //============================================================================
  // strings
  //============================================================================
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
    if (suffix.size() > s.size()) return false;
    return std::equal(s.begin() + s.size() - suffix.size(), s.end(), suffix.begin());
    //return s.rfind(suffix) == (s.size() - suffix.size());
  }
  //
  bool startsWith(const std::string& s, const std::string& prefix) {
    if (prefix.size() > s.size()) return false;
    if (s.compare(0, prefix.length(), prefix) == 0) {
      return true;
    }
    return false;
    //return s.rfind(suffix) == (s.size() - suffix.size());
  }
  //
  bool contains(const std::string& s, const std::string& sub) {
    return s.find(sub) != std::string::npos;
  }
  //
  //============================================================================
  // ROOT
  //============================================================================
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
  void getTFileTree(
      const std::string& filename,
      TFile*& file,
      TTree*& tree,
      const std::string& options,
      const std::string& treename) {
    file = new TFile(filename.c_str(), options.c_str());
    tree = static_cast<TTree*>(file->Get(treename.c_str()));
    if (!tree) {
      std::cout << "No TTree : " << treename << std::endl;
      throw;
    }
    return;
  }

} // namespace scph


