#ifndef SCPH_EASEL_CLASS_H
#define SCPH_EASEL_CLASS_H

#include <string>
#include <iostream>

#include "TH1.h"
#include "TH2.h"
#include "TObject.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TPaveText.h"
#include "TVirtualPad.h"


class Easel {
 protected:
  static std::string s_output_format_;
  static std::string s_legend_position_;
  static std::string s_text_position_;
  static int plot_num_;

  TPad* canvas_;
  TLegend* legend_;
  TPaveText* pavetext_;

  double marginl_;
  double marginr_;
  double margint_;
  double marginb_;

  std::vector<TObject*> histograms_;
  //std::map<TObject*, std::string> objects_;
  std::vector<TObject*> objects_;
  std::vector<TPad*> pads_;
  std::vector<int> colours_;
  std::vector<std::string> legendnames_;

 public:
  Easel();
  Easel(std::string, std::string, double, double);
  ~Easel();
  virtual void plot()=0;
  virtual TVirtualPad* plotToCanvas() {return NULL;}
  virtual void setCanvas(TCanvas*, int) {return;}
  virtual void normalize() {;};
  //virtual void setLogx(bool)=0;
  //virtual void setLogy(bool)=0;
  //virtual void setLogz(bool)=0;
  void add(TObject*, std::string legname="");
  void outputToRootFile();
  void set_text_position(std::string);
  void set_legend_position(std::string);

  void addPad(TPad* pad) {
    pads_.push_back(pad);
    return;
  }

};


#endif
