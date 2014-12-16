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
#include "TStyle.h"
#include "stdio.h"
#include "TProfile.h"

void clusterWidthVsPosition(){

	std::vector<int> *clusters_width_S0= 0;
	std::vector<double> *clusters_position_S0= 0;

	TH2D *h_width_position_S0 = new TH2D("clusterswidth_S0","clusters_S0 run 488",256,0,256,20, 0 , 20);
	
	TProfile *p_width_position_S0 = new TProfile("clusterswidth_S0",";cluster position;cluster width",256,0,256);
	TProfile *p1_width_position_S0 = new TProfile("clusterswidth_S0",";cluster position;cluster width",256,0,256);

	TFile *recofile =  TFile::Open("/nfs/dust/cms/user/harbali/output/recoFiles/RECO_run_488_70vcth.root");
	TTree *recotree = (TTree *) recofile->Get("recotree");

	recotree->SetBranchAddress("clusterwidth_S0", &clusters_width_S0);
	recotree->SetBranchAddress("clusters_S0", &clusters_position_S0);

	int dutEntries = recotree->GetEntries();

	for (int i =0; i < dutEntries; i++){
		recotree->GetEntry(i);
		
		unsigned int   cluster_size_S0 = clusters_width_S0->size();
		//unsigned int   cluster_position_S0 = clusters_position_S0->size();

		for(unsigned int k = 0 ; k < cluster_size_S0 ; ++k){
		h_width_position_S0->Fill(clusters_position_S0->at(k),clusters_width_S0->at(k));
		p_width_position_S0->Fill(clusters_position_S0->at(k),clusters_width_S0->at(k));}

	
	}

	TFile *recofile1 =  TFile::Open("/nfs/dust/cms/user/harbali/output/recoFiles/RECO_run_478_120vcth.root");
	TTree *recotree1 = (TTree *) recofile1->Get("recotree");

	recotree1->SetBranchAddress("clusterwidth_S0", &clusters_width_S0);
	recotree1->SetBranchAddress("clusters_S0", &clusters_position_S0);

	int dutEntries1 = recotree1->GetEntries();

	for (int i =0; i < dutEntries1; i++){
		recotree1->GetEntry(i);
		
		unsigned int   cluster_size_S0 = clusters_width_S0->size();
		//unsigned int   cluster_position_S0 = clusters_position_S0->size();

		for(unsigned int k = 0 ; k < cluster_size_S0 ; ++k){
		p1_width_position_S0->Fill(clusters_position_S0->at(k),clusters_width_S0->at(k));}

	
	}
	
	//gStyle->SetOptStat(0);
	TCanvas *c1 = new TCanvas("c1","c1",700,500);
	//c1->Divide(1,2);
	//c1->cd(1);
	//h_width_position_S0->SetLineColor(1);
	//h_width_position_S0->Draw("colz");
	//c1->cd(2);
	p_width_position_S0->Draw();
	p1_width_position_S0->SetMarkerColor(kRed);
	p1_width_position_S0->SetLineColor(kRed);
	p1_width_position_S0->Draw("same");

	TLegend *leg = new TLegend(0.1,0.7,0.48,0.9);
	leg->SetFillColor(0);
	//leg->SetLineColor(0);
	leg->AddEntry(p_width_position_S0,"Vcth = 70","lep");
	leg->AddEntry(p1_width_position_S0,"Vcth = 120","lep");
	leg->Draw();
	
}
