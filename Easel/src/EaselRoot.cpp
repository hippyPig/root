#define ROOTPLOTTER_CLASS_H_cxx
#include "EaselRoot.hpp"

#include <iostream>
#include <sstream>

#include <boost/algorithm/string.hpp>

#include "Easel.hpp"
#include "Oi.hpp"

bool EaselRoot::draw_text_ = false; // only works at the moment for TH2


EaselRoot::EaselRoot(TH1* histogram, std::string legname, double width, double height) :
    Easel("canvas_" + (std::string)histogram->GetName(), legname, width, height),
    axisname_x_(histogram->GetXaxis()->GetTitle()),
    axisname_y_(histogram->GetYaxis()->GetTitle()),
    size_axislabel_(0.03),
    size_axistitle_(0.04),
    canvas_number_(0),
    logx_(false),
    logy_(false),
    logz_(false),
    set_global_min_(false),
    set_global_max_(false),
    global_min_(-1),
    global_max_(-1) {
  histograms_.push_back(histogram);
  if (legname == "") {
    //legendnames_.push_back(histogram->GetTitle());
  } else {
    legendnames_.push_back(legname);
  }
  options_ = "";
  setColours();
}


EaselRoot::EaselRoot(std::string name, std::string legname, double width, double height) :
    Easel("canvas_" + name, legname, width, height),
    axisname_x_(""),
    axisname_y_(""),
    size_axislabel_(0.03),
    size_axistitle_(0.04),
    canvas_number_(0),
    logx_(false),
    logy_(false),
    logz_(false),
    set_global_min_(false),
    set_global_max_(false),
    global_min_(-1),
    global_max_(-1) {
  if (legname == "") {
    //legendnames_.push_back(histogram->GetTitle());
  } else {
    legendnames_.push_back(legname);
  }
  options_ = "";
  setColours();
}


EaselRoot::EaselRoot() :
    Easel(),
    axisname_x_(""),
    axisname_y_(""),
    size_axislabel_(0.03),
    size_axistitle_(0.04),
    canvas_number_(0),
    logx_(false),
    logy_(false),
    logz_(false),
    set_global_min_(false),
    set_global_max_(false),
    global_min_(-1),
    global_max_(-1) {
  options_ = "";
  setColours();
}


EaselRoot::~EaselRoot() {;}


void EaselRoot::setColours() {
  colours_.push_back(kBlack);
  colours_.push_back(kRed);
  colours_.push_back(kBlue);
  colours_.push_back(kGreen + 2);
  colours_.push_back(kCyan + 2);
  colours_.push_back(kOrange + 2);
  colours_.push_back(kAzure + 2);
  colours_.push_back(kRed + 3);
  colours_.push_back(kBlue + 3);
  return;
}


TH1* EaselRoot::getHistogram(int h) {
  return (TH1*)histograms_.at(h);
}


void EaselRoot::plotSame() {
  //canvas_->cd();
  //LHCbStyle();
  this->setHistogramStyle(getHistogram(0));
  getHistogram(0)->SetMaximum(1.05 * getGlobalMax());
  if (getHistogram(0)->InheritsFrom("TH2")) {
    getHistogram(0)->DrawClone("colz");
    if (options_ != "") {
      getHistogram(0)->DrawClone(options_.c_str());
    } else if (draw_text_) {
      getHistogram(0)->DrawClone("same text");
    }
    //return;
  } else {
    //getHistogram(0)->DrawClone("e");
    getHistogram(0)->DrawClone();
    for (unsigned int hist_no=0; hist_no<histograms_.size(); ++hist_no) {
      getHistogram(hist_no)->SetLineColor(colours_.at(hist_no));
      getHistogram(hist_no)->SetMarkerColor(colours_.at(hist_no));
      getHistogram(hist_no)->DrawClone("same");
    }
  }
  for (unsigned int object=0; object<objects_.size(); ++object) {
    objects_.at(object)->Draw("same");
  }
  //std::map<TObject*, std::string>::iterator it_obj = objects_.begin();
  //for (; it_obj!=objects_.end(); ++it_obj) {
  //  it_obj->first->Draw(it->second);
  //  objects_.(object)->Draw("same");
  //}
  std::map<TGraph*, std::string>::iterator it_gr = graphs_.begin();
  for (; it_gr!=graphs_.end(); ++it_gr) {
    it_gr->first->Draw(it_gr->second.c_str());
  }
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
      oidebug << text_entries_.at(text);
    }
    pavetext_->SetTextColor(kBlack);
    pavetext_->Draw();
  }



  return;
}


void EaselRoot::text_coords(double& xmin, double& ymin, double& xmax, double& ymax) {
  xmin = getGlobalMin();
  xmax = getGlobalMax();
  //ymin = getHistogram()->GetYaxis()->GetXmin();
  //ymax = getHistogram()->GetYaxis()->GetXmax();
  ymin = getHistogram(0)->GetMinimum();
  ymax = getHistogram(0)->GetMaximum();
  oidebug << "xmin " << xmin;
  oidebug << "ymin " << ymin;
  oidebug << "xmax " << xmax;
  oidebug << "ymax " << ymax;
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


void EaselRoot::plot() {
  TVirtualPad* pad = canvas_->cd(canvas_number_);
  this->setMargins(pad);
  if (logx_) pad->SetLogx();
  if (logy_) pad->SetLogy();
  if (logz_) pad->SetLogz();
  plotSame();
  if (histograms_.size() > 1) {
    drawLegend();
  }
  std::stringstream ss;
  ss << "$PLOTPATH/" << getHistogram(0)->GetName() << s_output_format_;
  std::string plotname = ss.str();
  std::string remove = " ^{}#()|!";
  int length = plotname.size();
  std::string::iterator end_init = plotname.end();
  std::string::iterator end_last = std::remove_if(plotname.begin(), end_init, boost::is_any_of(remove));
  plotname.resize(length - (end_init - end_last));
  //std::replace_if(plotname.begin(), plotname.end(), boost::is_any_of(replace), '_');
  //std::replace_if(plotname.begin(), plotname.end(), (std::string)"__", '_');
  //std::bind(std::less<int>(), std::placeholders::_1, 5)
  //std::replace_if(plotname.begin(), plotname.end(), "__", '_');
  boost::replace_all(plotname, "rightarrow", "to");
  canvas_->SaveAs(plotname.c_str());
  //boost::replace_all(plotname, "pdf", "root");
  //oidebug << plotname;
  //canvas_->SaveAs(plotname.c_str());
  return;
}


TVirtualPad* EaselRoot::plotToCanvas() {
  TVirtualPad* pad = canvas_->cd(canvas_number_);
  this->setMargins(pad);
  if (logx_) pad->SetLogx();
  if (logy_) pad->SetLogy();
  if (logz_) pad->SetLogz();
  plotSame();
  if (histograms_.size() > 1) {
    drawLegend();
  }
  return pad;
}


void EaselRoot::addLine(double x1, double y1, double x2, double y2, int colour, double width) {
  TLine* line = new TLine(x1, y1, x2, y2);
  line->SetLineColor(colour);
  line->SetLineWidth(width);
  objects_.push_back(line);
  return;
}


void EaselRoot::drawLegend() {
  if (legendnames_.size() != histograms_.size()) {
    legend_ = NULL;
  } else if (s_legend_position_ == "tr") {
    legend_ = new TLegend(0.70, 0.70, 0.90, 0.90);
  } else if (s_legend_position_ == "tl") {
    legend_ = new TLegend(0.20, 0.70, 0.40, 0.90);
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


void EaselRoot::setLogx(bool apply) {
  logx_ = apply;
  //canvas_->SetLogx();
  return;
}


void EaselRoot::setLogy(bool apply) {
  logy_ = apply;
  //canvas_->SetLogy();
  return;
}


void EaselRoot::setLogz(bool apply) {
  logz_ = apply;
  //canvas_->SetLogz();
  return;
}


void EaselRoot::setCanvas(TCanvas* canvas, int canno) {
  delete canvas_;
  canvas_ = canvas;
  canvas_number_ = canno;
  return;
}


void EaselRoot::add_text(std::string text) {
  std::vector<std::string> strs;
  boost::split(strs, text, boost::is_any_of("\t\n"));
  std::vector<std::string>::iterator it;
  it = strs.begin();
  for (; it!=strs.end(); ++it) {
    text_entries_.push_back(*it);
  }
  return;
}


void EaselRoot::drawText(bool apply) {
  draw_text_ = apply;
  if (apply) {
    getHistogram(0)->SetMarkerSize(3.0);
  } else {
    getHistogram(0)->SetMarkerSize(1.0);
  }
  return;
}


void EaselRoot::setMarker(bool apply, double marker_size) {
  for (unsigned h=0; h<histograms_.size(); ++h) {
    getHistogram(h)->SetMarkerSize(marker_size);
    getHistogram(h)->Sumw2();
  }
  return;
}


void EaselRoot::setMarker(bool apply) {
  for (unsigned h=0; h<histograms_.size(); ++h) {
    getHistogram(h)->Sumw2();
  }
  return;
}


void EaselRoot::drawText(bool apply, double marker_size) {
  draw_text_ = apply;
  getHistogram(0)->SetMarkerSize(marker_size);
  return;
}


void EaselRoot::drawOptions(std::string options) {
  options_ = options;
  return;
}


void EaselRoot::addGraph(TGraph* gr, std::string opts) {
  graphs_.insert(std::pair<TGraph*, std::string>(gr, opts));
  return;
}
