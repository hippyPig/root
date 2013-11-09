#ifndef SCPH_EASEL_EASELROO_CLASS_H
#define SCPH_EASEL_EASELROO_CLASS_H

#include "TLine.h"
#include "TLegend.h"
#include "RooPlot.h"
#include "RooDataSet.h"
#include "RooAbsPdf.h"
#include "RooWorkspace.h"

#include "Easel.hpp"

class EaselRoo : public Easel {
 protected:
  static bool set_style_sw;
  bool plot_signal_pdf_;
  std::string axisname_x_;
  std::string axisname_y_;
  std::string plotname_;
  std::string plotrange_;
  double size_axislabel_;
  double size_axistitle_;
  double user_maximum_;
  double user_minimum_;
  RooAbsPdf* pdf_;
  RooDataSet* data_;
  int canvas_number_;
  int colour_number_;
  bool logx_;
  bool logy_;
  bool logz_;

  std::vector<std::string> components_;
  std::vector<std::string> text_entries_;
  std::string component_string(int);

  RooPlot* getHistogram(int h=0);
  void text_coords(double&, double&, double&, double&);

 public:
  EaselRoo(RooPlot*, std::string legname="", double width=600, double height=400);
  ~EaselRoo();

  //virtual void LHCbStyle()=0;
  //virtual void setHistogramStyle(RooPlot*)=0;
  virtual double getGlobalMax();
  virtual double getGlobalMin();

  //void plotSame();
  //void addLine(double, double, double, double);
  void drawLegend();
  void set_pdf(RooAbsPdf*);
  void add_pdf(std::string);
  void set_data(RooDataSet*);
  void plotPdfs();
  void add_val(RooWorkspace&, std::string, std::string, bool err=true);
  void add_text(std::string);
  void add_plot_range(std::string);
  void drawPdfs();
  void addLine(double, double, double, double, int colour=1, double width=1.0);
  void addVerticalLine(double, int, double);
  void addHorizontalLine(double, int, double);
  void setCanvas(TCanvas*, int);
  void normalize();
  virtual void plot();
  virtual TVirtualPad* plotToCanvas();
  //void draw(RooDataSet*);
  //void draw(RooAbsPdf*);

  void setLogx(bool);
  void setLogy(bool);
  void setLogz(bool);
  void setMinimum(double);

};



#endif
