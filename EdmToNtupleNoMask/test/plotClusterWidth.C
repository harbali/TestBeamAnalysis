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

void plotClusterWidth(){

	std::vector<int> *clusters_width_S0= 0;
	std::vector<int> *clusters_width_S1= 0;
 	std::vector<int> *clusters_width_S2= 0;
	std::vector<int> *clusters_width_S3= 0;

	TH1F *h_clusters_width_S0 = new TH1F("clusterswidth_S0","clusters_S0", 20, 0 , 20);
	TH1F *h_clusters_width_S1 = new TH1F("clusterswidth_S1","clusters_S1", 20, 0. , 20.);
	TH1F *h_clusters_width_S2 = new TH1F("clusterswidth_S2","clusters_S2",20, 0. , 20.);
	TH1F *h_clusters_width_S3 = new TH1F("clusterswidth_S3","clusters_S3", 20, 0. , 20.);
	
	TFile *recofile =  TFile::Open("RECO_USC.00000478.0001.A.storageManager.00.0000.root");
	TTree *recotree = (TTree *) recofile->Get("recotree");
	recotree->SetBranchAddress("clusterwidth_S0", &clusters_width_S0);
	recotree->SetBranchAddress("clusterwidth_S1", &clusters_width_S1);
    	recotree->SetBranchAddress("clusterwidth_S2", &clusters_width_S2);
	recotree->SetBranchAddress("clusterwidth_S3", &clusters_width_S3);

	int dutEntries = recotree->GetEntries();

	for (int i =0; i < dutEntries; i++){
		recotree->GetEntry(i);
		
		unsigned int   cluster_size_S0 = clusters_width_S0->size();
		unsigned int   cluster_size_S1 = clusters_width_S1->size();
		unsigned int   cluster_size_S2 = clusters_width_S2->size();
		unsigned int   cluster_size_S3 = clusters_width_S3->size();

		for(unsigned int k = 0 ; k < cluster_size_S0 ; ++k){
		h_clusters_width_S0->Fill(clusters_width_S0->at(k));}
		for(unsigned int k = 0 ; k < cluster_size_S1 ; ++k){
		h_clusters_width_S1->Fill(clusters_width_S1->at(k));}
		for(unsigned int k = 0 ; k < cluster_size_S2 ; ++k){
		h_clusters_width_S2->Fill(clusters_width_S2->at(k));}
		for(unsigned int k = 0 ; k < cluster_size_S3 ; ++k){
		h_clusters_width_S3->Fill(clusters_width_S3->at(k));}
	
	}

	TCanvas *c1 = new TCanvas("c1","c1",700,500);
	h_clusters_width_S0->SetLineColor(1);
	h_clusters_width_S0->Draw();
	h_clusters_width_S1->SetLineColor(2);
	h_clusters_width_S1->Draw("sames");
	h_clusters_width_S2->SetLineColor(3);
	h_clusters_width_S2->Draw("sames");
	h_clusters_width_S3->SetLineColor(4);
	h_clusters_width_S3->Draw("sames");
}
