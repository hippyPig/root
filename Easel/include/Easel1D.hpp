#ifndef SCPH_EASEL_EASEL1D_CLASS_H
#define SCPH_EASEL_EASEL1D_CLASS_H

#include "TH1D.h"

#include "EaselRoot.hpp"

class Easel1D : public EaselRoot {
 private:
  static bool set_style_sw;
 public:
  Easel1D(TH1* histogram, std::string legname="", double width=600, double height=400);
  Easel1D(std::string, std::string legname="", double width=600, double height=400);
  Easel1D();
  ~Easel1D();

  virtual double getGlobalMax();
  virtual double getGlobalMin();
  //virtual void plot();
  void setHistogramStyle(TH1*);
  void normalize();
  void normalize(double);

  virtual void addHorizontalLine(double, int colour=1, double width=1);
  virtual void addVerticalLine(double, int colour=1, double width=1);
  virtual void LHCbStyle();
  virtual void setMargins(TVirtualPad*);
  virtual void setMinimum(const double&);
  virtual void setMaximum(const double&);

};


#endif
