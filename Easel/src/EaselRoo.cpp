#define SCPH_EASEL_EASELROO_CLASS_H_cxx
#include "EaselRoo.hpp"

#include <iostream>
#include <sstream>

#include <boost/algorithm/string.hpp>

#include "RooRealVar.h"

#include "Easel.hpp"
#include "Oi.hpp"
#include "Utils.hpp"


bool EaselRoo::set_style_sw = false;


EaselRoo::EaselRoo(RooPlot* histogram, std::string legname, double width, double height) :
    Easel("canvas_" + (std::string)histogram->GetName(), legname, width, height),
    plot_signal_pdf_(false),
    axisname_x_(histogram->GetXaxis()->GetTitle()),
    axisname_y_(histogram->GetYaxis()->GetTitle()),
    size_axislabel_(0.03),
    size_axistitle_(0.04),
    user_maximum_(-1),
    user_minimum_(-1),
    pdf_(NULL),
    data_(NULL),
    canvas_number_(0),
    colour_number_(0),
    logx_(false),
    logy_(false),
    logz_(false) {
  std::stringstream ss;
  ss << histogram->GetName() << plot_num_++;
  histogram->SetName(ss.str().c_str());
  histogram->SetTitle("");
  histograms_.push_back(histogram);
  if (legname == "") {
    legendnames_.push_back(histogram->GetTitle());
  } else {
    legendnames_.push_back(legname);
  }
  colours_.push_back(kGray);
  colours_.push_back(kGray + 1);
  colours_.push_back(kGray + 2);
  colours_.push_back(kCyan + 3);
  plotname_ = "";
  plotrange_ = "";
}


EaselRoo::~EaselRoo() {
  //delete getHistogram();
}


RooPlot* EaselRoo::getHistogram(int h) {
  return (RooPlot*)histograms_.at(h);
}


std::string EaselRoo::component_string(int number) {
  --number;
  std::stringstream ss;
  ss << components_.at(0);
  for (int comp=0; comp<=number; ++comp) {
    if (components_.at(comp) == "signal") {
      continue;
    }
    ss << "," << components_.at(comp);
  }
  return ss.str();
}


void EaselRoo::set_pdf(RooAbsPdf* pdf) {
  pdf_ = pdf;
  if (plotrange_ == "") {
    pdf_->plotOn(getHistogram(),
                 RooFit::LineColor(kBlue + 2));
  } else {
    pdf_->plotOn(getHistogram(),
                 RooFit::NormRange(plotrange_.c_str()),
                 RooFit::LineColor(kBlue + 2));
  }
  return;
}


void EaselRoo::add_pdf(std::string component) {
  if (component == "signal") {
    plot_signal_pdf_ = true;
  } else {
    components_.push_back(component);
  }
  return;
}


void EaselRoo::drawPdfs() {
  if (pdf_ == NULL) {
    oierror << "add_pdf is for adding components, set_pdf first";
  }
  assert(pdf_);
  int comp_rev;
  if (plotrange_ == "") {
    for (unsigned int comp=0; comp<components_.size(); ++comp) {
      comp_rev = components_.size() - comp;
      pdf_->plotOn(getHistogram(),
          RooFit::Components(component_string(comp_rev).c_str()),
          RooFit::DrawOption("F"),
          RooFit::FillColor(colours_.at(comp_rev)),
          RooFit::LineColor(colours_.at(comp_rev)));
    }
    pdf_->plotOn(getHistogram(),
        RooFit::LineColor(kBlue + 2));
    if (plot_signal_pdf_) {
      pdf_->plotOn(getHistogram(),
          RooFit::Components("signal"),
          RooFit::LineColor(kRed + 2));
    }
  } else {
    for (unsigned int comp=0; comp<components_.size(); ++comp) {
      comp_rev = components_.size() - comp;
      pdf_->plotOn(getHistogram(),
          RooFit::Components(component_string(comp_rev).c_str()),
          RooFit::NormRange(plotrange_.c_str()), // NormRange=>Fill Does not work.
          RooFit::FillColor(colours_.at(comp_rev)),
          RooFit::LineColor(colours_.at(comp_rev)));
    }
    pdf_->plotOn(getHistogram(),
        RooFit::NormRange(plotrange_.c_str()),
        RooFit::LineColor(kBlue + 2));
    if (plot_signal_pdf_) {
      pdf_->plotOn(getHistogram(),
          RooFit::Components("signal"),
          RooFit::NormRange(plotrange_.c_str()),
          RooFit::LineColor(kRed + 2));
    }
  }
  return;
  //for (int comp=0; comp<components_.size(); ++comp) {
  //  if (plotrange_ == "") {
  //    if (component.find("signal") == 0) {
  //      pdf_->plotOn(getHistogram(),
  //          RooFit::Components("signal"),
  //          RooFit::LineColor(kRed + 2));
  //    } else {
  //      pdf_->plotOn(getHistogram(),
  //          RooFit::Components(component.c_str()),
  //          RooFit::DrawOption("F"),
  //          RooFit::FillColor(colours_.at(colour_number_)),
  //          RooFit::LineColor(colours_.at(colour_number_)));
  //    }
  //    //pdf_->plotOn(getHistogram(),
  //    //             RooFit::LineColor(kBlue + 2));
  //  } else {
  //    //if (component == "signal") {
  //    if (component.find("signal") == 0) {
  //      pdf_->plotOn(getHistogram(),
  //          RooFit::Components("signal"),
  //          RooFit::NormRange(plotrange_.c_str()),
  //          RooFit::LineColor(kRed + 2));
  //    } else {
  //      pdf_->plotOn(getHistogram(),
  //          RooFit::Components(component.c_str()),
  //          RooFit::NormRange(plotrange_.c_str()), // NormRange=>Fill Does not work.
  //          RooFit::FillColor(colours_.at(colour_number_)),
  //          RooFit::LineColor(colours_.at(colour_number_)));
  //    }
  //    //pdf_->plotOn(getHistogram(),
  //    //             RooFit::NormRange(plotrange_.c_str()),
  //    //             RooFit::LineColor(kBlue + 2));
  //  }
  //  ++colour_number_;
  //  //if (component == "signal") {
  //  //plot_signal_pdf_ = true;
  //  //} else {
  //  //components_.push_back(component);
  //  //}
  //  //return;
  //  }
  //}
}




void EaselRoo::set_data(RooDataSet* data) {
  data_ = data;
  data_->plotOn(getHistogram());
  return;
}


void EaselRoo::plotPdfs() {
  assert(data_);
  if (!pdf_) {
    return;
  }
  int comp_rev;
  if (plotrange_ == "") {
    for (unsigned int comp=0; comp<components_.size(); ++comp) {
      if (components_.at(comp) == "signal") {
        plot_signal_pdf_ = true;
        continue;
      }
      comp_rev = components_.size() - comp;
      pdf_->plotOn(getHistogram(),
          RooFit::Components(component_string(comp_rev).c_str()),
          RooFit::DrawOption("F"),
          RooFit::FillColor(colours_.at(comp_rev)),
          RooFit::LineColor(colours_.at(comp_rev)));
    }
    if (plot_signal_pdf_) {
      pdf_->plotOn(getHistogram(),
          RooFit::Components("signal"),
          RooFit::LineColor(kRed + 2));
    }
    pdf_->plotOn(getHistogram(),
        RooFit::LineColor(kBlue + 2));
  } else {
    for (unsigned int comp=0; comp<components_.size(); ++comp) {
      comp_rev = components_.size() - comp;
      if (components_.at(comp) == "signal") {
        plot_signal_pdf_ = true;
        continue;
      }
      pdf_->plotOn(getHistogram(),
          RooFit::Components(component_string(comp_rev).c_str()),
          RooFit::NormRange(plotrange_.c_str()), // NormRange=>Fill Does not work.
          RooFit::FillColor(colours_.at(comp_rev)),
          RooFit::LineColor(colours_.at(comp_rev)));
    }
    if (plot_signal_pdf_) {
      pdf_->plotOn(getHistogram(),
          RooFit::Components("signal"),
          RooFit::NormRange(plotrange_.c_str()),
          RooFit::LineColor(kRed + 2));
    }
    pdf_->plotOn(getHistogram(),
        RooFit::NormRange(plotrange_.c_str()),
        RooFit::LineColor(kBlue + 2));
  }
  return;
}



void EaselRoo::add_text(std::string text) {
  std::vector<std::string> strs;
  boost::split(strs, text, boost::is_any_of("\t\n"));
  std::vector<std::string>::iterator it;
  it = strs.begin();
  for (; it!=strs.end(); ++it) {
    text_entries_.push_back(*it);
    plotname_ += (*it);
  }
  return;
}


void EaselRoo::plot() {
  canvas_->cd();
  if (logx_) canvas_->SetLogx();
  if (logy_) canvas_->SetLogy();
  if (logz_) canvas_->SetLogz();
  assert(data_);
  //data_->plotOn(getHistogram());
  //plotPdfs();
  data_->plotOn(getHistogram());
  if (user_minimum_ > 0) getHistogram()->SetMinimum(user_minimum_);
  getHistogram()->Draw();
  if (!pavetext_ && text_entries_.size() > 0) {
    double xmin;
    double xmax;
    double ymin;
    double ymax;
    text_coords(xmin, ymin, xmax, ymax);
    pavetext_ = new TPaveText(xmin, ymin, xmax, ymax);
    pavetext_->SetFillColor(kWhite);
    pavetext_->SetBorderSize(0);
    for (int text=0; text<text_entries_.size(); ++text) {
      pavetext_->AddText(text_entries_.at(text).c_str());
    }
    pavetext_->SetTextColor(kBlack);
    pavetext_->Draw();
  }
  for (int p=0; p<pads_.size(); ++p) {
    pads_.at(p)->DrawClone();
  }

  std::stringstream ss;
  ss << "$PLOTPATH/" << getHistogram()->GetName() << "_" << plotname_ << s_output_format_;
  std::string plotname = ss.str();
  std::string remove = " ^{}#()<>!|";
  int length = plotname.size();
  std::string::iterator end_init = plotname.end();
  std::string::iterator end_last = std::remove_if(plotname.begin(), end_init, boost::is_any_of(remove));
  plotname.resize(length - (end_init - end_last));

  canvas_->SaveAs(plotname.c_str());

  return;
}


TVirtualPad* EaselRoo::plotToCanvas() {
  //canvas_->cd();
  TVirtualPad* pad = canvas_->cd(canvas_number_);
  if (logx_) pad->SetLogx();
  if (logy_) pad->SetLogy();
  if (logz_) pad->SetLogz();
  //plotSame();
  assert(data_);
  //data_->plotOn(getHistogram());
  //plotPdfs();
  data_->plotOn(getHistogram());
  getHistogram()->Draw();
  if (!pavetext_ && text_entries_.size() > 0) {
    double xmin;
    double xmax;
    double ymin;
    double ymax;
    text_coords(xmin, ymin, xmax, ymax);
    pavetext_ = new TPaveText(xmin, ymin, xmax, ymax);
    pavetext_->SetFillColor(kWhite);
    pavetext_->SetBorderSize(0);
    for (int text=0; text<text_entries_.size(); ++text) {
      pavetext_->AddText(text_entries_.at(text).c_str());
    }
    pavetext_->SetTextColor(kBlack);
    pavetext_->Draw();
  }
  for (int p=0; p<pads_.size(); ++p) {
    pads_.at(p)->DrawClone();
  }

  return pad;
}


void EaselRoo::setCanvas(TCanvas* canvas, int canno) {
  delete canvas_;
  canvas_ = canvas;
  canvas_number_ = canno;
  return;
}


void EaselRoo::drawLegend() {
  if (s_legend_position_ == "tr") {
    legend_ = new TLegend(0.70, 0.70, 0.90, 0.90);
  } else if (s_legend_position_ == "tl") {
    legend_ = new TLegend(0.15, 0.60, 0.15, 0.85);
  } else if (s_legend_position_ == "br") {
    legend_ = new TLegend(0.60, 0.15, 0.58, 0.15);
  } else if (s_legend_position_ == "bl") {
    legend_ = new TLegend(0.15, 0.15, 0.15, 0.15);
  }
  if (legend_) {
    legend_->SetFillColor(0);
    for (unsigned int h=0; h<histograms_.size(); ++h) {
      legend_->AddEntry(getHistogram(h), legendnames_.at(h).c_str(), "l");
    }
    legend_->DrawClone();
  }
  return;
}


////void EaselRoo::setLogx() {
//  canvas_->SetLogx();
//}
//
//
//void EaselRoo::setLogy() {
//  canvas_->SetLogy();
//}
//
//
//void EaselRoo::setLogz() {
//  canvas_->SetLogz();
//}



double EaselRoo::getGlobalMax() {
  double global_max;
  //global_max = getHistogram()->GetXaxis()->GetMaximumBin();
  global_max = getHistogram()->GetXaxis()->GetXmax();
  return global_max;
}


double EaselRoo::getGlobalMin() {
  double global_min;
  //global_min = getHistogram()->GetXaxis()->GetMaximumBin();
  global_min = getHistogram()->GetXaxis()->GetXmin();
  return global_min;
}


void EaselRoo::text_coords(double& xmin, double& ymin, double& xmax, double& ymax) {
  xmin = getGlobalMin();
  xmax = getGlobalMax();
  //ymin = getHistogram()->GetYaxis()->GetXmin();
  //ymax = getHistogram()->GetYaxis()->GetXmax();
  ymin = getHistogram()->GetMinimum();
  ymax = getHistogram()->GetMaximum();
  int lines = text_entries_.size();
  lines = lines > 6 ? 6 : lines;
  double xdelta = xmax - xmin;
  double ydelta = ymax - ymin;
  if (s_text_position_ == "tr") {
    xmax = xmin + xdelta * 0.95;
    xmin = xmin + xdelta * 0.75;
    ymax = ymin + ydelta * 0.96;
    ymin = ymin + ydelta * (0.96 - 0.08 * lines);
  } else if (s_text_position_ == "tl") {
    xmax = xmin + xdelta * 0.3;
    xmin = xmin + xdelta * 0.1;
    ymax = ymin + ydelta * 0.9;
    ymin = ymin + ydelta * 0.7;
  } else if (s_text_position_ == "br") {
    xmax = xmin + xdelta * 0.9;
    xmin = xmin + xdelta * 0.7;
    ymax = ymin + ydelta * 0.3;
    ymin = ymin + ydelta * 0.1;
  } else if (s_text_position_ == "bl") {
    xmax = xmin + xdelta * 0.3;
    xmin = xmin + xdelta * 0.1;
    ymax = ymin + ydelta * 0.3;
    ymin = ymin + ydelta * 0.1;
  }
  return;
}


void EaselRoo::add_val(RooWorkspace& ws, std::string name, std::string title, bool err) {
  RooRealVar* var = ws.var(name.c_str());
  assert(var);
  std::stringstream ss;
  ss << title << Stools::dtos(var->getVal(), 2);
  if (err) {
    ss << "#pm" << Stools::dtos(var->getError(), 2);
  }
  text_entries_.push_back(ss.str());
  //if (!pavetext_) {
  //  double xmin;
  //  double xmax;
  //  double ymin;
  //  double ymax;
  //  text_coords(xmin, ymin, xmax, ymax);
  //  pavetext_ = new TPaveText(xmin, ymin, xmax, ymax);
  //  pavetext_->SetFillColor(kWhite);
  //  pavetext_->SetBorderSize(0);
  //}
  //pavetext_->AddText(ss.str().c_str());
  return;
}

void EaselRoo::add_plot_range(std::string plotrange) {
  plotrange_ = plotrange;
  return;
}


void EaselRoo::normalize() {
  oierror << "Cannot normalize EaselRoo.";
  return;
}


void EaselRoo::setLogx(bool apply) {
  logx_ = apply;
  return;
}


void EaselRoo::setLogy(bool apply) {
  logy_ = apply;
  return;
}


void EaselRoo::setLogz(bool apply) {
  logz_ = apply;
  return;
}


void EaselRoo::addLine(double x1, double y1, double x2, double y2, int colour, double width) {
  TLine* line = new TLine(x1, y1, x2, y2);
  line->SetLineColor(colour);
  line->SetLineWidth(width);
  objects_.push_back(line);
  return;
}


void EaselRoo::addHorizontalLine(double y, int colour, double width) {
  double x1 = getHistogram(0)->GetXaxis()->GetBinLowEdge(1);
  double x2 = getHistogram(0)->GetXaxis()->GetBinUpEdge(getHistogram(0)->GetXaxis()->GetNbins());
  addLine(x1, y, x2, y, colour, width);
  return;
}


void EaselRoo::addVerticalLine(double x, int colour, double width) {
  //addLine(x, getGlobalMin(), x, 1.05 * getGlobalMax());
  addLine(x, getHistogram(0)->GetMinimum(), x, 1.05 * getGlobalMax(), colour, width);
  return;
}


void EaselRoo::setMinimum(double minimum) {
  user_minimum_ = minimum;
  return;
}
