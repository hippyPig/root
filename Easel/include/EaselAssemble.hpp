#ifndef SCPH_EASEL_EASELASSEMBLE_H
#define SCPH_EASEL_EASELASSEMBLE_H

#include "EaselRoot.hpp"
#include "EaselRoo.hpp"

class EaselAssemble {
 protected:
  static std::string ext_;

  //std::vector<EaselRoot*> easels_;
  std::vector<Easel*> easels_;
  //std::vector<EaselRoot*> easels_;
  //std::vector<EaselRoo*> rooeasels_;
  std::string plotname_;
  int canvas_x_;
  int canvas_y_;
  bool logx_;
  bool logy_;
  bool logz_;

 public:
  EaselAssemble();
  EaselAssemble(std::string);
  ~EaselAssemble();

  //void operator+= (EaselRoot*);
  void operator+= (Easel*);

  //void add(EaselRoot*);
  //void add(EaselRoo*);
  void add(Easel*);

  void plot();
  void divide(int, int);
  void normalize();
  void setLogx(bool);
  void setLogy(bool);
  void setLogz(bool);

};


#endif
