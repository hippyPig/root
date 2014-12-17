#define SCPH_DENDROLOGY_SAPLING_CXX
#include "Sapling.hpp"

Sapling::Sapling()
  : file_(NULL)
  , tree_(NULL)
  , elm_(NULL)
{;}


Sapling::Sapling(Elm* elm, const std::string& filename)
  : file_(NULL)
  , tree_(NULL)
  , elm_(NULL)
{
  file_ = new TFile(filename.c_str(), "recreate");
  elm_ = elm;
  tree_ = elm->getTree()->CloneTree(0);
}


Sapling::~Sapling() {
}


void Sapling::fill() {
  std::map<std::string, TBranch*>::iterator it = branches_.begin();
  tree_->Fill();
  for (; it!=branches_.end(); ++it) {
    it->second->Fill();
  }
  return;
}


void Sapling::write() {
  file_->cd();
  tree_->Write();
  file_->Close();
  return;
}

