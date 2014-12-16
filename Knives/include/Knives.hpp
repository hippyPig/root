#ifndef KNIVES_CONTAINER_CLASS_H
#define KNIVES_CONTAINER_CLASS_H
#include "Knife.hpp"
#include "KnifeDiffLt.hpp"
#include "KnifeTypeBool.hpp"
#include "KnifeTypeRange.hpp"
#include "KnifeTypeSimple.hpp"
#include "KnifeOr.hpp"
#include "KnifeAnd.hpp"
#include "KnifeDiffGt.hpp"
#include "KnifeLt.hpp"
#include "KnifeEqual.hpp"
#include "KnifeGt.hpp"
#include "KnifeIn.hpp"
#include "KnifeIs.hpp"
#include "KnifeIsNot.hpp"
#include "KnifeNotEqual.hpp"
#include "KnifeOut.hpp"
#include "KnifeType2Vars.hpp"

#include <iostream>

#include "Barrel.hpp"


namespace Knives {

class Knives {
 private:
  std::vector<Knife*> cuts_;
  std::vector<Knife*>::iterator it_cuts_;
  Knife* get_cut(std::string);
 public:
  Knives();
  ~Knives();
  Knives operator+ (Knife*);
  Knives operator+ (Knives);
  Knives operator+ (std::vector<Knife*>);
  void operator+= (Knife*);
  void operator+= (Knives);
  void operator+= (std::vector<Knife*>);
  void setAddresses(TTree*);
  //void setAddresses(std::map<std::string, MonkeyBase*>&);
  void setAddresses(Barrel*);
  void add(Knife*);
  void add(Knives);
  void add(std::vector<Knife*>);
  void clear();
  void print();
  bool eval();
  void update(Knife* cut);
  //void update(std::string, float);
  //void update(std::string, double);
  void update(std::string, double, double);
  void update(std::vector<std::string>, double);
  void update(std::vector<std::string>, float);
  unsigned size();

  std::vector<Knife*> getCuts();
  std::string cut_string();

  // Templated fucntions
  template <class T> void update(std::string cutname, T cut_new) {
    oihello << "Knives::update() " << cutname << " " << cut_new;
    KnifeTypeSimple<T>* cut = (KnifeTypeSimple<T>*)get_cut(cutname);
    cut->update(cut_new);
    update(cut);
    return;
  }


};

}

// Typedefs
typedef Knives::Knives Kcuts; // AT THE BOTTOM

typedef Knives::KnifeGt<double> Kgt;
typedef Knives::KnifeLt<double> Klt;
typedef Knives::KnifeIn<double> Kin;
typedef Knives::KnifeOut<double> Kout;
typedef Knives::KnifeDiffGt<double> Kdiffgt;
typedef Knives::KnifeDiffLt<double> Kdifflt;

typedef Knives::KnifeGt<float> Kfgt;
typedef Knives::KnifeLt<float> Kflt;

typedef Knives::KnifeIs<bool> Kis;
typedef Knives::KnifeIsNot<bool> Kisn;
typedef Knives::KnifeIsNot<bool> Knot;

typedef Knives::KnifeEqual<int> Keq;
typedef Knives::KnifeNotEqual<int> Kneq;

typedef Knives::KnifeOr Kor;
typedef Knives::KnifeAnd Kand;

#endif
