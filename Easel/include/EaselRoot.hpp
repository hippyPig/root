#ifndef SCPH_EASEL_EASELROOT_CLASS_H
#define SCPH_EASEL_EASELROOT_CLASS_H

#include <map>

#include "TLine.h"
#include "TLegend.h"
#include "TVirtualPad.h"
#include "TGraph.h"

#include "Easel.hpp"

class EaselRoot : public Easel {
 protected:
  static bool set_style_sw;
  //static int divisions_x_;
  //static int divisions_y_;
  //static int pad_number_;
  static bool draw_text_;
  std::string axisname_x_;
  std::string axisname_y_;
  std::string options_;
  double size_axislabel_;
  double size_axistitle_;
  double size_marker_;
  int canvas_number_;
  bool logx_;
  bool logy_;
  bool logz_;
  bool set_global_min_;
  bool set_global_max_;
  double global_min_;
  double global_max_;

  void setColours();
  TH1* getHistogram(int);
  std::vector<std::string> text_entries_;
  std::map<TGraph*, std::string> graphs_;
  void text_coords(double&, double&, double&, double&);

 public:
  EaselRoot(TH1*, std::string legname="", double width=600, double height=400);
  EaselRoot(std::string, std::string legname="", double width=600, double height=400);
  EaselRoot();
  ~EaselRoot();

  virtual void LHCbStyle()=0;
  virtual void setHistogramStyle(TH1*)=0;
  virtual double getGlobalMax() {return 0.0;}
  virtual double getGlobalMin() {return 0.0;}
  virtual void setMaximum(const double&)=0;
  virtual void setMinimum(const double&)=0;

  void plotSame();
  void drawLegend();
  void addLine(double, double, double, double, int colour=1, double width=1.0);
  void add_text(std::string);
  void setCanvas(TCanvas*, int);
  virtual void addVerticalLine(double, int, double)=0;
  virtual void addHorizontalLine(double, int, double)=0;
  virtual void plot();
  virtual void normalize() {;}
  virtual TVirtualPad* plotToCanvas();
  virtual void setMargins(TVirtualPad*)=0;
  void setLogx(bool);
  void setLogy(bool);
  void setLogz(bool);
  void drawText(bool);
  void drawText(bool, double);
  void setMarker(bool);
  void setMarker(bool, double);
  void drawOptions(std::string);
  void addGraph(TGraph*, std::string);

};



#endif
