#define SCPH_EASEL_EASELASSEMBLE_H_CXX
#include "EaselAssemble.hpp"

#include "EaselRoot.hpp"
#include "Oi.hpp"
#include "Utils.hpp"


std::string EaselAssemble::ext_ = ".pdf";


EaselAssemble::EaselAssemble() :
    plotname_("$PLOTPATH/easeltest.pdf"),
    canvas_x_(-1),
    canvas_y_(-1),
    logx_(false),
    logy_(false),
    logz_(false) {
  oihello << "EaselAssemble::EaselAssemble()";
}


EaselAssemble::EaselAssemble(std::string plotname) :
    plotname_(plotname),
    canvas_x_(-1),
    canvas_y_(-1),
    logx_(false),
    logy_(false),
    logz_(false) {
  oihello << "EaselAssemble::EaselAssemble()";
}


EaselAssemble::~EaselAssemble() {
  //while (!easels_.empty()) {
  //  delete easels_.back();
  //  easels_.pop_back();
  //}
  return;
}


void EaselAssemble::operator+= (Easel* easel) {
  this->add(easel);
  return;
}


void EaselAssemble::add(Easel* easel) {
  easels_.push_back(easel);
  return;
}


void EaselAssemble::divide(int x, int y) {
  canvas_x_ = x;
  canvas_y_ = y;
  oiinfo << "EaselAssemble::divide " << canvas_x_ << " " << canvas_y_;
  return;
}


void EaselAssemble::plot() {
  oihello << "EaselAssemble::plot()";
  TVirtualPad* pad;
  unsigned int can = 0;
  if (canvas_x_ <= 0 || canvas_y_ <= 0) {
    canvas_x_ = 2;
    canvas_y_ = ((easels_.size() + 1) / 2 > 4) ? 4 : (easels_.size() + 1) / 2;
  }
  if (canvas_x_ * canvas_y_ < easels_.size()) {
    plotname_ = Stools::replace(plotname_, ext_, Stools::ntos(0) + ext_);
  }
  int ext_next = 0;
  while (can < easels_.size()) {
    TCanvas* canvas = new TCanvas("canvas", "", 600 * canvas_x_, 400 * canvas_y_);
    canvas->Divide(canvas_x_, canvas_y_);
    for (int x=0; x<canvas_x_; ++x) {
      for (int y=0; y<canvas_y_; ++y) {
        if (can < easels_.size()) {
          easels_.at(can)->setCanvas(canvas, can % (canvas_x_ * canvas_y_) + 1);
          pad = easels_.at(can)->plotToCanvas();
          if (logx_) pad->SetLogx(logx_);
          if (logy_) pad->SetLogy(logy_);
          if (logz_) pad->SetLogz(logz_);
          //pad->SetTopMargin(0.01);
          //pad->SetBottomMargin(0.1);
          //pad->SetLeftMargin(0.08);
          //pad->SetRightMargin(0.14);
        }
        can++;
      }
    }
    canvas->SaveAs(plotname_.c_str());
    canvas->Clear();
    canvas->Divide(canvas_x_, canvas_y_);
    ext_next++;
    plotname_ = Stools::replace(plotname_, Stools::ntos(ext_next - 1) + ext_,
                                           Stools::ntos(ext_next) + ext_);
    delete canvas;
  }
  return;
}


void EaselAssemble::setLogz(bool apply) {
  logz_ = apply;
  //for (int easel=0; easel<easels_.size(); ++easel) {
    //easels_.at(easel)->setLogz(apply);
  //}
  return;
}

void EaselAssemble::setLogy(bool apply) {
  //for (int easel=0; easel<easels_.size(); ++easel) {
    //easels_.at(easel)->setLogy(apply);
  //}
  logy_ = apply;
  return;
}

void EaselAssemble::setLogx(bool apply) {
  //for (int easel=0; easel<easels_.size(); ++easel) {
    //easels_.at(easel)->setLogx(apply);
  //}
  logx_ = apply;
  return;
}


void EaselAssemble::normalize() {
  for (int easel=0; easel<easels_.size(); ++easel) {
    easels_.at(easel)->normalize();
  }
  return;
}


