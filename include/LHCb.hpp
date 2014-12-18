#ifndef LHCB_CLASS_H
#define LHCB_CLASS_H


#include "TStyle.h"
#include "TROOT.h"
#include "TLatex.h"
#include "TPaveText.h"
#include "TColor.h"


namespace lhcb {
void turnon(const bool& twod=false);
TStyle* getStyle();
int getLHCbRed();
int getLHCbDB();
int getLHCbLB();
};



#endif
