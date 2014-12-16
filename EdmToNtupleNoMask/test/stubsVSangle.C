#include <fstream>
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"

#include "TLegend.h"
#include "TAxis.h"
#include "TGraphErrors.h"


void stubsVSangle(){

	TCanvas *c1 = new TCanvas("c1","c1",800,600);
	c1->SetTickx();
	c1->SetTicky();

	double angle, MV, sigma;
	int n = 11;
	//int ex = 0;

	TGraphErrors *g1 = new TGraphErrors();

	ifstream fp;
	fp.open("stubsVsAngle.txt");

	TF1 *func = new TF1("fit","[0] + [1]*tan([2]+x)");
	func->SetParNames ("shift","spacing","ang0");

	while(!fp.eof()){
		for (int i = 0 ; i < n ; ++i){
			if(fp >> angle >> MV >> sigma ){
				g1->SetPoint(i,angle*0.0174532925,MV*0.09);
			}
		}
	}

	g1->Fit("fit");
	fp.close();

	g1->SetMarkerStyle(20);
	g1->SetMarkerColor(1);
	g1->Draw("ap");
	g1->SetMinimum(0);
	//g1->SetMaximum(12);
	g1->GetXaxis()->SetTitle("angle [rad]");
	g1->GetYaxis()->SetTitle("Delta strip (mv)[mm]");
	g1->SetTitle("rotated DUT");

	leg = new TLegend(0.3,0.8,0.6,0.9);
	leg->SetFillColor(0);
	//leg->SetLineColor(0);
	leg->AddEntry(g1,"mv","pl");
	leg->AddEntry(func,"Fit","L");
	leg->Draw();

}