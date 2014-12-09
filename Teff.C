#include <fstream>
#include "TCanvas.h"
#include "TH1F.h"
#include "TEfficiency.h"

void Teff(){

	TEfficiency* pEff = 0;
	TEfficiency* pEff1 = 0;

	double thr,CBC0sel,CBC0tot,CBC1sel,CBC1tot;

 	TH1F *h_CBC0sel = new TH1F("","",19,20,120);
 	TH1F *h_CBC0tot = new TH1F("","",19,20,120);
	TH1F *h_CBC1sel = new TH1F("","",19,20,120);
 	TH1F *h_CBC1tot = new TH1F("","",19,20,120);

	ifstream fp;
	fp.open("eff.txt");
	
	while(!fp.eof()){
		if(fp >> thr >> CBC0sel >> CBC0tot >> CBC1sel >> CBC1tot ){
		h_CBC0sel->Fill(thr,CBC0sel);
		h_CBC0tot->Fill(thr,CBC0tot);
		h_CBC1sel->Fill(thr,CBC1sel);
		h_CBC1tot->Fill(thr,CBC1tot);
		//std::cout << thr << "  " <<  CBC0sel<< "  "  <<
		// CBC0tot <<"  "  << CBC1sel << "  "  <<CBC1tot << std::endl;
		}
	}
	fp.close();

	pEff = new TEfficiency(*h_CBC0sel,*h_CBC0tot);
	pEff1 = new TEfficiency(*h_CBC1sel,*h_CBC1tot);

	TCanvas * c1 = new TCanvas("c1","c1",1100,400);
	c1->Divide(3,1);


	c1->cd(1);
	h_CBC0sel->Draw();
	h_CBC0tot->SetLineColor(2);
	h_CBC0tot->Draw("same");
	
	c1->cd(2);
	h_CBC1sel->Draw();
	h_CBC1tot->SetLineColor(2);
	h_CBC1tot->Draw("same");
	
	c1->cd(3);

	pEff->Draw("AP");
	pEff1->SetLineColor(kRed);
	pEff1->Draw("same");

 }

