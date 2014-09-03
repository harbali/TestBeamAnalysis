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


void plotClusters(){

	std::vector<double> *clusters_position_S0= 0;
	std::vector<double> *clusters_position_S1= 0;
 	std::vector<double> *clusters_position_S2= 0;
	std::vector<double> *clusters_position_S3= 0;
 	std::vector<double> *clusters_position_S2_masked= 0;
	std::vector<double> *clusters_position_S3_masked= 0;

	TH1F *h_clusters_S0 = new TH1F("clusters_S0","clusters_S0", 256, 0. , 256.);
	TH1F *h_clusters_S1 = new TH1F("clusters_S1","clusters_S1", 256, 0. , 256.);
	TH1F *h_clusters_S2 = new TH1F("clusters_S2","clusters_S2", 256, 0. , 256.);
	TH1F *h_clusters_S3 = new TH1F("clusters_S3","clusters_S3", 256, 0. , 256.);
	TH1F *h_clusters_S2_masked = new TH1F("clusters_S2_masked","clusters_S2_masked", 256, 0. , 256.);
	TH1F *h_clusters_S3_masked = new TH1F("clusters_S3_masked","clusters_S3_masked", 256, 0. , 256.);

	TFile *recofile =  TFile::Open("RECO_USC.00000478.0001.A.storageManager.00.0000.root");
	TTree *recotree = (TTree *) recofile->Get("recotree");
	recotree->SetBranchAddress("clusters_S0", &clusters_position_S0);
	recotree->SetBranchAddress("clusters_S1", &clusters_position_S1);
    	recotree->SetBranchAddress("clusters_S2", &clusters_position_S2);
	recotree->SetBranchAddress("clusters_S3", &clusters_position_S3);
    	recotree->SetBranchAddress("clusters_S2_masked", &clusters_position_S2);
	recotree->SetBranchAddress("clusters_S3_masked", &clusters_position_S3);

	int dutEntries = recotree->GetEntries();

	for (int i =0; i < dutEntries; i++){
		recotree->GetEntry(i);

		unsigned int   cluster_size_S0 = clusters_position_S0->size();
		unsigned int   cluster_size_S1 = clusters_position_S1->size();
		unsigned int   cluster_size_S2 = clusters_position_S2->size();
		unsigned int   cluster_size_S3 = clusters_position_S3->size();
		unsigned int   cluster_size_S2_masked = clusters_position_S2_masked->size();
		unsigned int   cluster_size_S3_masked = clusters_position_S3_masked->size();

		for(int k = 0 ; k < cluster_size_S0 ; ++k){
			h_clusters_S0->Fill(clusters_position_S0->at(k));}
		for(int k = 0 ; k < cluster_size_S1 ; ++k){
			h_clusters_S0->Fill(clusters_position_S1->at(k));}
		for(int k = 0 ; k < cluster_size_S2 ; ++k){
			h_clusters_S0->Fill(clusters_position_S2->at(k));}
		for(int k = 0 ; k < cluster_size_S3 ; ++k){
			h_clusters_S0->Fill(clusters_position_S3->at(k));}

	}

		h_clusters_S0->Draw();
		h_clusters_S1->Draw("sames");
		h_clusters_S2->Draw("sames");
		h_clusters_S3->Draw("sames");

}
