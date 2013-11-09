// Define
#ifndef SCPH_STOOLS_UTILS_NAMESPACE_H
#define SCPH_STOOLS_UTILS_NAMESPACE_H

// Include standard
#include <vector>
#include <string>
#include <iomanip>

// Include ROOT
#include "TLorentzVector.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"

// Include mine
#include "Oi.hpp"

// Include boost
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/function.hpp>

//------------------------------------------------------------------------------
// Sam Hall's Utilities header
//------------------------------------------------------------------------------

// Typedefs
typedef std::vector<std::string> svector;

//==============================================================================
// For the ease of not being in namespace
//==============================================================================
void Count(const int&, const int&);
void Progress(const int&, const int&, const std::string& msg="Analysing");
void Linebreak();


//==============================================================================
// Old namespace, being replaced by scph
//==============================================================================
namespace Stools {

  // Foward declarations:
  std::string replace(std::string, const std::string&, const std::string&);
  svector splitString(std::string str, std::string delimiter);

  void swapPID(TLorentzVector& p4, double m);
  TLorentzVector getP4(double*, double*, double*, double*);
  TLorentzVector getSwapPID(const TLorentzVector& p4, double m);
  TLorentzVector getP4SwapPID(double*, double*, double*, double*, double);

  char getBranchType(TTree*, std::string);
  bool isInt(TTree*, const std::string&);
  bool isBool(TTree*, const std::string&);
  bool isFloat(TTree*, const std::string&);
  bool isDouble(TTree*, const std::string&);
  bool isBranch(TTree*, const std::string&);


  // Templated functions:
  template <typename Type>
  inline std::string ntos(const Type number) {
    return boost::lexical_cast<std::string>(number);
  }

  template <typename Type>
  inline std::string dtos(const Type number, const int& precision) {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(precision);
    ss << number;
    return ss.str();
  }
} // namespace Stools


//==============================================================================
// New and better namespace
//==============================================================================
namespace scph {

  //============================================================================
  // Foward declarations:
  //============================================================================
  /// strings
  std::string replace(std::string, const std::string&, const std::string&);
  svector splitString(std::string str, std::string delimiter);
  bool endsWith(const std::string&, const std::string &);
  bool contains(const std::string&, const std::string &);

  /// ROOT
  void swapPID(TLorentzVector& p4, double m);
  TLorentzVector getP4(double*, double*, double*, double*);
  TLorentzVector getSwapPID(const TLorentzVector& p4, double m);
  TLorentzVector getP4SwapPID(double*, double*, double*, double*, double);
  char getBranchType(TTree*, std::string);
  bool isInt(TTree*, const std::string&);
  bool isBool(TTree*, const std::string&);
  bool isFloat(TTree*, const std::string&);
  bool isDouble(TTree*, const std::string&);
  bool isBranch(TTree*, const std::string&);

  /// Templated functions:
  // ntos
  template <typename Type>  // Number -> String
  inline std::string ntos(const Type& number) {
    return boost::lexical_cast<std::string>(number);
  }

  // dtos
  template <typename Type>  // Number -> String w precision
  inline std::string dtos(const Type& number, const int& precision) {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(precision);
    ss << number;
    return ss.str();
  }

  // ston
  template <typename Type>  //
  inline Type ston(const std::string& snumber) {
    Type number;
    try {
      number = boost::lexical_cast<Type>(snumber);
    } catch (boost::bad_lexical_cast&) {
      oierror << "Cannot convert \"" << snumber << "\" to string.";
      throw;
    }
    return number;
  }

  // flip_map
  template <typename T1, typename T2>
  std::map<T2, T1> flip_map(const std::map<T1, T2>& in) {
    std::map<T2, T1> out;
    typename std::map<T1, T2>::iterator it;
    for (it=in.begin(); it!=in.end(); ++it) {
        out[it->second] = it->first;
    }
    return out;
  }

} // namespace scph

#endif // SCPH_STOOLS_UTILS_NAMESPACE_H
