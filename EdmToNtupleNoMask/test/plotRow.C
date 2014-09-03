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


void plotRow(){

	std::vector<int> *row_S0= 0;
	std::vector<int> *row_S1= 0;
 	std::vector<int> *row_S2= 0;
	std::vector<int> *row_S3= 0;
 	std::vector<int> *row_S2_masked= 0;
	std::vector<int> *row_S3_masked= 0;

	TH1F *h_row_S0 = new TH1F("row_S0","row_S0", 256, 0. , 256.);
	TH1F *h_row_S1 = new TH1F("row_S1","row_S1", 256, 0. , 256.);
	TH1F *h_row_S2 = new TH1F("row_S2","row_S2", 256, 0. , 256.);
	TH1F *h_row_S3 = new TH1F("row_S3","row_S3", 256, 0. , 256.);
	TH1F *h_row_S2_masked = new TH1F("row_S2_masked","row_S2_masked", 256, 0. , 256.);
	TH1F *h_row_S3_masked = new TH1F("row_S3_masked","row_S3_masked", 256, 0. , 256.);

	TFile *recofile =  TFile::Open("RECO_USC.00000478.0001.A.storageManager.00.0000.root");
	TTree *recotree = (TTree *) recofile->Get("recotree");
	recotree->SetBranchAddress("row_S0", &row_S0);
	recotree->SetBranchAddress("row_S1", &row_S1);
    	recotree->SetBranchAddress("row_S2", &row_S2);
	recotree->SetBranchAddress("row_S3", &row_S3);
    	recotree->SetBranchAddress("row_S2_masked", &row_S2_masked);
	recotree->SetBranchAddress("row_S3_masked", &row_S3_masked);

	int dutEntries = recotree->GetEntries();

	for (int i =0; i < dutEntries; i++){
		recotree->GetEntry(i);

		unsigned int   size_S0 = row_S0->size();
		unsigned int   size_S1 = row_S1->size();
		unsigned int   size_S2 = row_S2->size();
		unsigned int   size_S3 = row_S3->size();
		unsigned int   size_S2_masked = row_S2_masked->size();
		unsigned int   size_S3_masked = row_S3_masked->size();

		for(unsigned int k = 0 ; k < size_S0 ; ++k){
			h_row_S0->Fill(row_S0->at(k));}
		for(unsigned int k = 0 ; k < size_S1 ; ++k){
			h_row_S1->Fill(row_S1->at(k));}
		for(unsigned int k = 0 ; k < size_S2 ; ++k){
			h_row_S2->Fill(row_S2->at(k));}
		for(unsigned int k = 0 ; k < size_S3 ; ++k){
			h_row_S3->Fill(row_S3->at(k));}
		for(unsigned int k = 0 ; k < size_S2_masked ; ++k){
			h_row_S2_masked->Fill(row_S2_masked->at(k));}
		for(unsigned int k = 0 ; k < size_S3_masked ; ++k){
			h_row_S3_masked->Fill(row_S3_masked->at(k));}

	}

		TCanvas *c1 = new TCanvas("c1","c1",700,500);
		h_row_S0->SetLineColor(1);
		h_row_S0->Draw();
		h_row_S1->SetLineColor(2);
		h_row_S1->Draw("sames");
		h_row_S2->SetLineColor(3);
		h_row_S2->Draw("sames");
		h_row_S3->SetLineColor(4);
		h_row_S3->Draw("sames");


		TCanvas *c2 = new TCanvas("c2","c2",700,500);
		h_row_S2_masked->SetLineColor(3);
		h_row_S2_masked->Draw();
		h_row_S3_masked->SetLineColor(4);
		h_row_S3_masked->Draw("sames");

}
