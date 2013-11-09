#ifndef SCPH_MONKEY_BARREL_H
#define SCPH_MONKEY_BARREL_H

#include <map>
#include <string>
#include <iostream>
#include <assert.h>
#include "boost/bind.hpp"
#include "boost/function.hpp"

#include "Monkey.hpp"
#include "Gibbon.hpp"

#include "Oi.hpp"


class Barrel {

 private:
  std::map<std::string, Primate*> monkeys_;
  std::map<std::string, Primate*> gibbons_;
  //std::map<std::string, boost::function<void (unsigned)> > cached_functions_;
  std::vector<boost::function<void()> > auto_set_ptrs_;

  TTree* tree_;
  void checkTree();

 public:
  Barrel();
  Barrel(TTree* tree) {
    tree_ = tree;
    assert(tree_);
  };

  ~Barrel();


  // copy //////////////////////////////////////////////////////////////////////
  template<class T>
  void copy(Primate* monkeybase) {
    dynamic_cast<Gibbon<T>* >(monkeybase)->setPtr();
    return;
  }


  // add ///////////////////////////////////////////////////////////////////////
  template <class T>
  void add(const std::string& branchname) {
    checkTree();
    if (!exists(branchname)) { // does the variable exist?
      Monkey<T>* monkey = new Monkey<T>(tree_, branchname);
      monkeys_[branchname] = monkey;
    }
    return;
  };

  template <class T>
  void add(const std::string& branchname, const std::string& name) {
    checkTree();
    if (exists(branchname)) { // does the variable exist?
      oierror << "Barrel contains \"" << branchname
          << "\" no room for \"" << "\"name\"";
      throw;
    }
    if (!exists(name)) { // does the variable exist?
      Monkey<T>* monkey = new Monkey<T>(tree_, branchname);
      monkeys_[name] = monkey;
    }
    return;
  };

  template <class T>
  void add(boost::function<T()> fcn, const std::string& branchname) {
    checkTree();
    if (existsFcn(branchname)) { // does the variable exist?
      oierror << "Barrel contains \"" << branchname
          << "\" no room for \"" << "\"name\"";
      throw;
    } else {
      Gibbon<T>* gibbon = new Gibbon<T>(fcn, branchname);
      //boost::bind(&TreeEvent::Copy<T>,this, branch_name, name, _1);
      gibbons_[branchname] = gibbon;
      auto_set_ptrs_.push_back(
          boost::bind(&Barrel::copy<T>, this, gibbons_[branchname]));
    }
    return;
  };


  // get ///////////////////////////////////////////////////////////////////////
  template <class T>
  T* getPtr(const std::string& branchname) {
    checkTree();
    if (existsFcn(branchname)) {
      return (dynamic_cast<Gibbon<T>* >(gibbons_[branchname]))->getPtr();
    } else {
      add<T>(branchname);
      return (dynamic_cast<Monkey<T>* >(monkeys_[branchname]))->getPtr();
    }
  };

  template <class T>
  T get(const std::string& branchname) {
    checkTree();
    if (existsFcn(branchname)) {
      return (dynamic_cast<Gibbon<T>* >(gibbons_[branchname]))->get();
    } else {
      add<T>(branchname);
      return (dynamic_cast<Monkey<T>* >(monkeys_[branchname]))->get();
    }
  };

  template <class T>
  T* getPtr(const std::string& branchname, const std::string& name) {
    checkTree();
    add<T>(branchname, name);
    return (dynamic_cast<Monkey<T>* >(monkeys_[name]))->getPtr();
  };

  template <class T>
  T get(const std::string& branchname, const std::string& name) {
    checkTree();
    add<T>(branchname, name);
    return (dynamic_cast<Monkey<T>* >(monkeys_[name]))->get();
  };


  // other /////////////////////////////////////////////////////////////////////
  void getEntry(const unsigned& entry);
  void setTree(TTree*);
  bool exists(const std::string&);
  bool existsFcn(const std::string&);
};


#endif
