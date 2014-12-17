#ifndef SCPH_STOOLS_SAFE_EMNUM_h
#define SCPH_STOOLS_SAFE_EMNUM_h


#include <vector>
#include <set>
#include <map>
#include <string>
#include <iostream>
#include "boost/assign/list_of.hpp"

namespace scph {


// We define a "type-safe" enum class
// It stops us from doing something like Color c = Shape::square
template<typename def, typename inner=typename def::type>
class safe_enum : public def {
 
 public:
  typedef typename def::type type;
  inner val;
  safe_enum(type v) : val(v) {}
  safe_enum() : val()  {}

  //inner underlying() const {return val;}
  inner value() const {return val;}
 
  bool operator == (const safe_enum& s) const {return this->val == s.val;}
  bool operator != (const safe_enum& s) const {return this->val != s.val;}
  bool operator <  (const safe_enum& s) const {return this->val <  s.val;}
  bool operator <= (const safe_enum& s) const {return this->val <= s.val;}
  bool operator >  (const safe_enum& s) const {return this->val >  s.val;}
  bool operator >= (const safe_enum& s) const {return this->val >= s.val;}
};

}

#endif
