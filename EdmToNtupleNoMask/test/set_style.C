void set_style() {
  gROOT -> LoadMacro("./tdrstyle.C");
  setTDRStyle();
  
  tdrStyle->SetOptTitle(0);
  tdrStyle->SetPadBottomMargin(0.14);
  tdrStyle->SetPadLeftMargin(0.18);
  tdrStyle->SetTitleXOffset(1.0);
  tdrStyle->SetTitleYOffset(1.3);
  tdrStyle->SetNdivisions(505, "X");
  tdrStyle->SetErrorX(0.5);
  tdrStyle->SetPalette(1,0);
  
  tdrStyle->SetOptStat("nemr");
 
  gROOT->ForceStyle();
}
