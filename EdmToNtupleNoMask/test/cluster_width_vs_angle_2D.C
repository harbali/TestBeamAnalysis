#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include <vector>
#include "TH2F.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TMath.h"
#include "TLegend.h"
	
void cluster_width_vs_angle_2D(){


	TH1F *h_clusterwidth = new TH1F(""," 0 [deg];cluster width;Entries", 20., 0. , 20.);
	TH1F *h_clusterwidth1 = new TH1F("","10[deg];cluster width;Entries", 20., 0. , 20.);
	TH1F *h_clusterwidth2 = new TH1F("","20[deg];cluster width;Entries", 20., 0. , 20.);
	TH1F *h_clusterwidth3 = new TH1F("","30[deg];cluster width;Entries", 20., 0. , 20.);

	TH2D *clust_angle = new TH2D("",";angle[deg];cluster width;Entries", 4, -5. , 35.,8.,-0.5,7.5);
	TH2D *clust_angle1 = new TH2D("",";angle[deg];cluster width;Entries", 4, -5. , 35.,8.,-0.5,7.5);
	TH2D *clust_angle2 = new TH2D("",";angle[deg];cluster width;Entries", 4, -5. , 35.,8.,-0.5,7.5);
	TH2D *clust_angle3 = new TH2D("",";angle[deg];cluster width;Entries", 4, -5. , 35.,8.,-0.5,7.5);

	TH1F *h_clustermultiplicity = new TH1F(""," 0 [deg];Cluster/event;Events", 20, 0 , 20);
	TH1F *h_clustermultiplicity1 = new TH1F("","10[deg];Cluster/event;Events", 20, 0 , 20);
	TH1F *h_clustermultiplicity2 = new TH1F("","20[deg];Cluster/event;Events", 20, 0 , 20);
	TH1F *h_clustermultiplicity3 = new TH1F("","30[deg];Cluster/event;Events", 20, 0 , 20);


	TH2D *h2d_clustermultiplicity = new TH2D(""," 0 [deg];angle[deg];cluster size;Entries", 4, -5. , 35.,8.,-0.5,7.5);
	TH2D *h2d_clustermultiplicity1 = new TH2D("","10[deg];angle[deg];cluster size;Entries", 4, -5. , 35.,8.,-0.5,7.5);
	TH2D *h2d_clustermultiplicity2 = new TH2D("","20[deg];angle[deg];cluster size;Entries", 4, -5. , 35.,8.,-0.5,7.5);
	TH2D *h2d_clustermultiplicity3 = new TH2D("","30[deg];angle[deg];cluster size;Entries", 4, -5. , 35.,8.,-0.5,7.5);

	
	Double_t x0[4]  = {0,10,20,30};
	Double_t ex0[4]  = {0};

	Double_t y0[4]  = {1.158,1.395,1.723,2.134};
	Double_t ey0[4]  = {0.4857,0.6087,0.6047,0.5997};

	//gStyle->SetOptFit(0001);
	
	TGraphErrors *g1 = new TGraphErrors(4,x0,y0,ex0,ey0);
	g1->SetTitle("S0");
	g1->SetLineColor(0);
	g1->SetMarkerStyle(4);
	g1->SetMarkerColor(0);

	
	std::vector<int> *clusters_width_S0= 0;

	
	TFile *recofile =  TFile::Open("/nfs/dust/cms/user/harbali/output/recoFiles/RECO_run_478_02deg_120vcth.root");
	TTree *recotree = (TTree *) recofile->Get("recotree");
	recotree->SetBranchAddress("clusterwidth_S0", &clusters_width_S0);


	int dutEntries = recotree->GetEntries();

	for (int i =0; i < dutEntries; i++){

		recotree->GetEntry(i);
		unsigned int   cluster_size_S0 = clusters_width_S0->size();
		for(unsigned int k = 0 ; k < cluster_size_S0 ; ++k){
			h_clusterwidth->Fill(clusters_width_S0->at(k));
			h_clustermultiplicity->Fill(cluster_size_S0);
			clust_angle->Fill(0,clusters_width_S0->at(k),1);
			h2d_clustermultiplicity->Fill(0,cluster_size_S0);
		}

	}
	
	TFile *recofile1 =  TFile::Open("/nfs/dust/cms/user/harbali/output/recoFiles/RECO_run_504_12deg_120vcth.root");
	TTree *recotree1 = (TTree *) recofile1->Get("recotree");
	recotree1->SetBranchAddress("clusterwidth_S0", &clusters_width_S0);


	int dutEntries1 = recotree1->GetEntries();

	for (int i =0; i < dutEntries1; i++){

		recotree1->GetEntry(i);
		unsigned int   cluster_size_S0 = clusters_width_S0->size();
		for(unsigned int k = 0 ; k < cluster_size_S0 ; ++k){
			h_clusterwidth1->Fill(clusters_width_S0->at(k));
			h_clustermultiplicity1->Fill(cluster_size_S0);
			clust_angle1->Fill(10,clusters_width_S0->at(k),1);
			h2d_clustermultiplicity1->Fill(10,cluster_size_S0);
		}
	}
	
	TFile *recofile2 =  TFile::Open("/nfs/dust/cms/user/harbali/output/recoFiles/RECO_run_526_22deg_120vcth.root");
	TTree *recotree2 = (TTree *) recofile2->Get("recotree");
	recotree2->SetBranchAddress("clusterwidth_S0", &clusters_width_S0);


	int dutEntries2 = recotree2->GetEntries();

	for (int i =0; i < dutEntries2; i++){

		recotree2->GetEntry(i);
		unsigned int   cluster_size_S0 = clusters_width_S0->size();
		for(unsigned int k = 0 ; k < cluster_size_S0 ; ++k){
			h_clusterwidth2->Fill(clusters_width_S0->at(k));
			h_clustermultiplicity2->Fill(cluster_size_S0);
			clust_angle2->Fill(20,clusters_width_S0->at(k),1);
			h2d_clustermultiplicity2->Fill(20,cluster_size_S0);
		}
	}
	
	TFile *recofile3 =  TFile::Open("/nfs/dust/cms/user/harbali/output/recoFiles/RECO_run_533_32deg_120vcth.root");
	TTree *recotree3 = (TTree *) recofile3->Get("recotree");
	recotree3->SetBranchAddress("clusterwidth_S0", &clusters_width_S0);


	int dutEntries3 = recotree3->GetEntries();

	for (int i =0; i < dutEntries3; i++){

		recotree3->GetEntry(i);
		unsigned int   cluster_size_S0 = clusters_width_S0->size();
		for(unsigned int k = 0 ; k < cluster_size_S0 ; ++k){
			h_clusterwidth3->Fill(clusters_width_S0->at(k));
			h_clustermultiplicity3->Fill(cluster_size_S0);
			clust_angle3->Fill(30,clusters_width_S0->at(k),1);
			h2d_clustermultiplicity3->Fill(30,cluster_size_S0);
		}
	}

	gStyle->SetOptStat(0);
	TCanvas *c1 = new TCanvas("c1","DUT Histos",700,500);
	c1->SetLogy();
	Double_t scale = 1/h_clusterwidth->Integral();
  	h_clusterwidth->Scale(scale);
	h_clusterwidth->Draw();
	Double_t scale1 = 1/h_clusterwidth1->Integral();
  	h_clusterwidth1->Scale(scale1);
	h_clusterwidth1->SetLineColor(2);
	//h_clusterwidth1->SetMarkerStyle(22);
	h_clusterwidth1->Draw("sames");
	Double_t scale2 = 1/h_clusterwidth2->Integral();
  	h_clusterwidth2->Scale(scale2);
	h_clusterwidth2->SetLineColor(3);
	h_clusterwidth2->Draw("sames");
	Double_t scale3 = 1/h_clusterwidth3->Integral();
  	h_clusterwidth3->Scale(scale3);
	h_clusterwidth3->SetLineColor(6);
	h_clusterwidth3->Draw("sames");
   	c1->BuildLegend();

	const Int_t NRGBs = 5;
	const Int_t NCont = 255;
	
	Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
	Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
	Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
	Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
	TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
	gStyle->SetNumberContours(NCont);
	
	TCanvas *c2 = new TCanvas("c2","DUT Histos",700,500);

	Double_t scale = 1/clust_angle->Integral();
  	clust_angle->Scale(scale);
	Double_t scale1 = 1/clust_angle1->Integral();
  	clust_angle1->Scale(scale1);
	Double_t scale2 = 1/clust_angle2->Integral();
  	clust_angle2->Scale(scale2);
	Double_t scale3 = 1/clust_angle3->Integral();
  	clust_angle3->Scale(scale3);

	clust_angle->Draw("colz4");
	clust_angle->Draw("TEXT0 SAME");
	clust_angle1->Draw("col,same");
	clust_angle1->Draw("TEXT0 SAME");
	clust_angle2->Draw("col,same");
	clust_angle2->Draw("TEXT0 SAME");
	clust_angle3->Draw("col,same");	
	clust_angle3->Draw("TEXT0 SAME");


	c2->SetLogz();
	g1->Draw("PL,same");

	TCanvas *c3 = new TCanvas("c3","DUT Histos",700,500);
	c3->SetLogy();

	Double_t scale = 1/h_clustermultiplicity->Integral();
  	h_clustermultiplicity->Scale(scale);
	Double_t scale1 = 1/h_clustermultiplicity1->Integral();
  	h_clustermultiplicity1->Scale(scale1);
	Double_t scale2 = 1/h_clustermultiplicity2->Integral();
  	h_clustermultiplicity2->Scale(scale2);
	Double_t scale3 = 1/h_clustermultiplicity3->Integral();
  	h_clustermultiplicity3->Scale(scale3);

	h_clustermultiplicity->Draw();
	h_clustermultiplicity1->SetLineColor(2);
	h_clustermultiplicity1->Draw("sames");
	h_clustermultiplicity2->SetLineColor(3);
	h_clustermultiplicity2->Draw("sames");
	h_clustermultiplicity3->SetLineColor(6);
	h_clustermultiplicity3->Draw("sames");
   	c3->BuildLegend();


	Double_t scale = 1/h2d_clustermultiplicity->Integral();
  	h2d_clustermultiplicity->Scale(scale);
	Double_t scale1 = 1/h2d_clustermultiplicity1->Integral();
  	h2d_clustermultiplicity1->Scale(scale1);
	Double_t scale2 = 1/h2d_clustermultiplicity2->Integral();
  	h2d_clustermultiplicity2->Scale(scale2);
	Double_t scale3 = 1/h2d_clustermultiplicity3->Integral();
  	h2d_clustermultiplicity3->Scale(scale3);

	TCanvas *c4 = new TCanvas("c4","DUT Histos",700,500);
	h2d_clustermultiplicity->Draw("colz4");
	h2d_clustermultiplicity->Draw("TEXT0 SAME");
	h2d_clustermultiplicity1->Draw("col,same");
	h2d_clustermultiplicity1->Draw("TEXT0 SAME");
	h2d_clustermultiplicity2->Draw("col,same");
	h2d_clustermultiplicity2->Draw("TEXT0 SAME");
	h2d_clustermultiplicity3->Draw("col,same");
	h2d_clustermultiplicity3->Draw("TEXT0 SAME");
	c4->SetLogz();

	c2->SetLogz();

}