#ifndef SCPH_EASEL_EASEL2D_CLASS_H
#define SCPH_EASEL_EASEL2D_CLASS_H

#include "EaselRoot.hpp"

class Easel2D : public EaselRoot {
 private:
  static bool set_style_sw;
 public:
  Easel2D(TH2* histogram, std::string legname="", double width=600, double height=400);
  ~Easel2D();

  virtual double getGlobalMax();
  virtual double getGlobalMin();
  //virtual void plot();
  void setHistogramStyle(TH1*);
  void normalize();

  virtual void addHorizontalLine(double, int colour=1, double width=1.0);
  virtual void addVerticalLine(double, int colour=1, double width=1.0);
  virtual void LHCbStyle();
  virtual void setMargins(TVirtualPad*);
  virtual void setMinimum(const double&);
  virtual void setMaximum(const double&);

};





#endif
