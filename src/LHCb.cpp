#define LHCB_CLASS_H_CXX


#include "LHCb.hpp"


namespace lhcb {

void turnon(const bool& twod) {
  TStyle* lhcbStyle_ = getStyle();
  if (twod) {
    lhcbStyle_->SetPadRightMargin(0.20); // increase for colz plots
  } else {
    lhcbStyle_->SetPadRightMargin(0.05); // increase for colz plots
  }

  gROOT->SetStyle("lhcbStyle_");
  gROOT->ForceStyle();
}

TStyle* getStyle() {
  // Use times new roman, precision 2
  Int_t lhcbFont        = 132;  // Old LHCb style: 62;
  // Line thickness
  Double_t lhcbWidth    = 2.00; // Old LHCb style: 3.00;
  // Text size
  Double_t lhcbTSize    = 0.06;

  // use plain black on white colors
  gROOT->SetStyle("Plain");
  TStyle *lhcbStyle_= new TStyle("lhcbStyle_","LHCb plots style");

  //lhcbStyle_->SetErrorX(0); //  don't suppress the error bar along X

  lhcbStyle_->SetFillColor(1);
  lhcbStyle_->SetFillStyle(1001);   // solid
  lhcbStyle_->SetFrameFillColor(0);
  lhcbStyle_->SetFrameBorderMode(0);
  lhcbStyle_->SetPadBorderMode(0);
  lhcbStyle_->SetPadColor(0);
  lhcbStyle_->SetCanvasBorderMode(0);
  lhcbStyle_->SetCanvasColor(0);
  lhcbStyle_->SetStatColor(0);
  lhcbStyle_->SetLegendBorderSize(0);

  // If you want the usual gradient palette (blue -> red)
  lhcbStyle_->SetPalette(1);
  // If you want colors that correspond to gray scale in black and white:
  //int colors[8] = {0,5,7,3,6,2,4,1};
  //lhcbStyle_->SetPalette(8,colors);

  // set the paper & margin sizes
  lhcbStyle_->SetPaperSize(20,26);
  lhcbStyle_->SetPadTopMargin(0.05);
  lhcbStyle_->SetPadBottomMargin(0.16);
  lhcbStyle_->SetPadLeftMargin(0.14);

  // use large fonts
  lhcbStyle_->SetTextFont(lhcbFont);
  lhcbStyle_->SetTextSize(lhcbTSize);
  lhcbStyle_->SetLabelFont(lhcbFont,"x");
  lhcbStyle_->SetLabelFont(lhcbFont,"y");
  lhcbStyle_->SetLabelFont(lhcbFont,"z");
  lhcbStyle_->SetLabelSize(lhcbTSize,"x");
  lhcbStyle_->SetLabelSize(lhcbTSize,"y");
  lhcbStyle_->SetLabelSize(lhcbTSize,"z");
  lhcbStyle_->SetTitleFont(lhcbFont);
  lhcbStyle_->SetTitleFont(lhcbFont,"x");
  lhcbStyle_->SetTitleFont(lhcbFont,"y");
  lhcbStyle_->SetTitleFont(lhcbFont,"z");
  lhcbStyle_->SetTitleSize(1.2*lhcbTSize,"x");
  lhcbStyle_->SetTitleSize(1.2*lhcbTSize,"y");
  lhcbStyle_->SetTitleSize(1.2*lhcbTSize,"z");

  // use medium bold lines and thick markers
  lhcbStyle_->SetLineWidth(lhcbWidth);
  lhcbStyle_->SetFrameLineWidth(lhcbWidth);
  lhcbStyle_->SetHistLineWidth(lhcbWidth);
  lhcbStyle_->SetFuncWidth(lhcbWidth);
  lhcbStyle_->SetGridWidth(lhcbWidth);
  lhcbStyle_->SetLineStyleString(2,"[12 12]"); // postscript dashes
  lhcbStyle_->SetMarkerStyle(20);
  lhcbStyle_->SetMarkerSize(1.0);

  // label offsets
  lhcbStyle_->SetLabelOffset(0.010,"X");
  lhcbStyle_->SetLabelOffset(0.010,"Y");

  // by default, do not display histogram decorations:
  lhcbStyle_->SetOptStat(0);
  //lhcbStyle_->SetOptStat("emr");  // show only nent -e , mean - m , rms -r
  // full opts at http://root.cern.ch/root/html/TStyle.html#TStyle:SetOptStat
  lhcbStyle_->SetStatFormat("6.3g"); // specified as c printf options
  lhcbStyle_->SetOptTitle(0);
  lhcbStyle_->SetOptFit(0);
  //lhcbStyle_->SetOptFit(1011); // order is probability, Chi2, errors, parameters
  //titles
  lhcbStyle_->SetTitleOffset(0.95,"X");
  lhcbStyle_->SetTitleOffset(0.95,"Y");
  lhcbStyle_->SetTitleOffset(1.2,"Z");
  lhcbStyle_->SetTitleFillColor(0);
  lhcbStyle_->SetTitleStyle(0);
  lhcbStyle_->SetTitleBorderSize(0);
  lhcbStyle_->SetTitleFont(lhcbFont,"title");
  lhcbStyle_->SetTitleX(0.0);
  lhcbStyle_->SetTitleY(1.0);
  lhcbStyle_->SetTitleW(1.0);
  lhcbStyle_->SetTitleH(0.05);

  // look of the statistics box:
  lhcbStyle_->SetStatBorderSize(0);
  lhcbStyle_->SetStatFont(lhcbFont);
  lhcbStyle_->SetStatFontSize(0.05);
  lhcbStyle_->SetStatX(0.9);
  lhcbStyle_->SetStatY(0.9);
  lhcbStyle_->SetStatW(0.25);
  lhcbStyle_->SetStatH(0.15);

  // put tick marks on top and RHS of plots
  lhcbStyle_->SetPadTickX(1);
  lhcbStyle_->SetPadTickY(1);

  // histogram divisions: only 5 in x to avoid label overlaps
  lhcbStyle_->SetNdivisions(505,"x");
  lhcbStyle_->SetNdivisions(510,"y");


  // add LHCb label
  TPaveText *lhcbName_ = new TPaveText(gStyle->GetPadLeftMargin() + 0.05,
      0.87 - gStyle->GetPadTopMargin(),
      gStyle->GetPadLeftMargin() + 0.20,
      0.95 - gStyle->GetPadTopMargin(),
      "BRNDC");

  lhcbName_->AddText("LHCb");
  lhcbName_->SetFillColor(0);
  lhcbName_->SetTextAlign(12);
  lhcbName_->SetBorderSize(0);

  TText *lhcbLabel_ = new TText();
  lhcbLabel_->SetTextFont(lhcbFont);
  lhcbLabel_->SetTextColor(1);
  lhcbLabel_->SetTextSize(lhcbTSize);
  lhcbLabel_->SetTextAlign(12);

  TLatex *lhcbLatex_ = new TLatex();
  lhcbLatex_->SetTextFont(lhcbFont);
  lhcbLatex_->SetTextColor(1);
  lhcbLatex_->SetTextSize(lhcbTSize);
  lhcbLatex_->SetTextAlign(12);

  return lhcbStyle_;
}

int getLHCbRed() {
  return TColor::GetColor(204, 84, 62);
}

int getLHCbDB() {
  return TColor::GetColor(43, 78, 142);
}

int getLHCbLB() {
  return TColor::GetColor(216, 235, 242);
}

};
