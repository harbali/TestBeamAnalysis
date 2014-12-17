#include <fstream>
#include "TCanvas.h"
#include "TH1F.h"
#include "TEfficiency.h"
#include "TLegend.h"
#include "TStyle.h"

void Teff(){

	TEfficiency* pEff = 0;
	TEfficiency* pEff1 = 0;

	double thr,CBC0sel,CBC0tot,CBC1sel,CBC1tot;

 	TH1F *h_CBC0sel = new TH1F("cbc0","cbc0",19.,30.,125.);
 	TH1F *h_CBC0tot = new TH1F("cbc0","cbc0",19.,30.,125.);
	TH1F *h_CBC1sel = new TH1F("cbc1","cbc1",19.,30.,125.);
 	TH1F *h_CBC1tot = new TH1F("cbc1","cbc1",19.,30.,125.);

	ifstream fp;
	fp.open("S1_selected_total.txt");
	
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

	TCanvas * c1 = new TCanvas("c1","c1",400,400);
// 	c1->Divide(3,1);

	gStyle->SetOptStat(00000);
// 	c1->cd(1);
	

	h_CBC0tot->SetLineColor(kBlack);
	h_CBC0tot->SetFillStyle(3001);
	h_CBC0tot->SetFillColor(kBlack);
	h_CBC0tot->Draw();

	h_CBC0sel->SetLineColor(kGreen);
	h_CBC0sel->SetFillStyle(3001);
	h_CBC0sel->SetFillColor(kGreen);
	h_CBC0sel->Draw("same");

	TLegend* leg = new TLegend(0.3,0.8,0.6,0.9);
	leg->SetFillColor(0);
	leg->AddEntry(h_CBC0sel,"CBC0_S1 selected","l");
	leg->AddEntry(h_CBC0tot,"CBC0_S1 total","l");
	leg->Draw();

	
	TCanvas * c2 = new TCanvas("c2","c2",400,400);
// 	c1->cd(2);

	h_CBC1tot->SetLineColor(kBlack);
	h_CBC1tot->SetFillStyle(3001);
	h_CBC1tot->SetFillColor(kBlack);
	h_CBC1tot->Draw();

	h_CBC1sel->SetLineColor(kGreen);
	h_CBC1sel->SetFillStyle(3001);
	h_CBC1sel->SetFillColor(kGreen);
	h_CBC1sel->Draw("same");


	TLegend* leg1 = new TLegend(0.3,0.8,0.6,0.9);
	leg1->SetFillColor(0);
	leg1->AddEntry(h_CBC0sel,"CBC1_S1 selected","l");
	leg1->AddEntry(h_CBC0tot,"CBC1_S1 total","l");
	leg1->Draw();

// 	c1->cd(3);

	TCanvas * c3 = new TCanvas("c3","c3",400,400);
	pEff->SetMarkerStyle(1);
	pEff->SetLineColor(kRed-3);
	pEff->SetMarkerColor(kRed-3);
	pEff->Draw("AP");

	pEff1->SetMarkerStyle(1);
	pEff1->SetLineColor(kRed+3);
	pEff1->SetMarkerColor(kRed+3);
	pEff1->Draw("same");

	TLegend* leg2 = new TLegend(0.3,0.8,0.6,0.9);
	leg2->SetFillColor(0);
	leg2->AddEntry(pEff,"CBC0_S1 ","l");
	leg2->AddEntry(pEff1,"CBC1_S1 ","l");
	leg2->Draw();
	

 }

