#define SCPH_EASEL_CLASS_H_cxx
#include "Easel.hpp"

#include <ctime>
#include <locale>

#include "Oi.hpp"


std::string Easel::s_output_format_ = ".pdf";
std::string Easel::s_legend_position_ = "tr";
std::string Easel::s_text_position_ = "tr";
int Easel::plot_num_ = 0;


Easel::Easel(std::string canvasname, std::string legname, double width, double height) :
    canvas_(new TCanvas(canvasname.c_str(), canvasname.c_str(), width, height)),
    legend_(0),
    pavetext_(0),
    marginl_(0.11),
    marginr_(0.15),
    margint_(0.11),
    marginb_(0.15) {
  return;
}


Easel::Easel() :
    canvas_(new TCanvas("default_constructor", "default_constructor", 600, 400)),
    legend_(0),
    pavetext_(0),
    marginl_(0.11),
    marginr_(0.15),
    margint_(0.11),
    marginb_(0.15) {
  return;
}


Easel::~Easel() {
  // ADDED
  while (!histograms_.empty()) {
    delete histograms_.back();
    histograms_.pop_back();
  }
  //for (int i=0; i < histograms_.size(); ++i)
  //  delete histograms_[i];
  //while(!objects_.empty()) delete objects_.back(), objects_.pop_back();
  //for(unsigned int i=0; i<objects_.size(); ++i) delete objects_.at(i);
  //for(unsigned int i=0; i<histograms_.size(); i++) delete histograms_.at(i);
  histograms_.clear();
  objects_.clear();
  delete canvas_;
  delete legend_;
  delete pavetext_;
}


void Easel::add(TObject* histogram, std::string legname) {
  histograms_.push_back(histogram);
  if (legname == "") {
    legendnames_.push_back(histogram->GetTitle());
  } else {
    legendnames_.push_back(legname);
  }
  return;
}


void Easel::set_text_position(std::string position) {
  s_text_position_ = position;
  return;
}

//void outputToRootFile() {
//  std::time_t result = std::time(NULL);
//  char mbstr[100];
//  std::strftime(mbstr, 100, "$PLOTPATH/%Y%m%d_%H%M.root", std::localtime(&result));
//  std::string time = (std::string)mbstr;
//  file_plot_ = new TFile(time.c_str(), "recreate");
//  tree_plot_ = new TTree("PlotTree", "PlotTree");
//  return;
//}


void Easel::set_legend_position(std::string pos) {
  if ((pos != "tl") && (pos != "tr") && (pos != "bl") && (pos != "br")) {
    oierror << "Legend position not recognized: " << pos;
  } else {
    s_legend_position_ = pos;
  }
  return;
}



