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


void BeamDiv(){

	std::vector<double> *clusters_position_S0= 0;
	std::vector<double> *clusters_position_S1= 0;
 	std::vector<double> *clusters_position_S2= 0;
	std::vector<double> *clusters_position_S3= 0;

	TH1F *h_div = new TH1F("","; #mum; Events", 100, -2000. , 2000.);


	TFile *recofile =  TFile::Open("RECO_USC.00000478.0001.A.storageManager.00.0000.root");
	TTree *recotree = (TTree *) recofile->Get("recotree");
	recotree->SetBranchAddress("clusters_S0", &clusters_position_S0);
	recotree->SetBranchAddress("clusters_S1", &clusters_position_S1);
    	recotree->SetBranchAddress("clusters_S2", &clusters_position_S2);
	recotree->SetBranchAddress("clusters_S3", &clusters_position_S3);

	int dutEntries = recotree->GetEntries();

	for (int i =0; i < dutEntries; i++){
		recotree->GetEntry(i);

		unsigned int   cluster_size_S0 = clusters_position_S0->size();
		unsigned int   cluster_size_S1 = clusters_position_S1->size();
		unsigned int   cluster_size_S2 = clusters_position_S2->size();
		unsigned int   cluster_size_S3 = clusters_position_S3->size();

		if (  cluster_size_S0 == 1 &&  cluster_size_S1 == 1 && cluster_size_S2 == 1 &&  cluster_size_S3 == 1){
			for(size_t iStrip = 0; iStrip < cluster_size_S0; ++iStrip){
				
	if(TMath::Abs(clusters_position_S0->at(0) - clusters_position_S1->at(0)) < 4. && TMath::Abs(clusters_position_S2->at(0) - clusters_position_S3->at(0)) < 4.){
					h_div->Fill((((clusters_position_S0->at(0)+clusters_position_S1->at(0))/2.)*90.) - (((clusters_position_S2->at(0)+clusters_position_S3->at(0))/2.)*80.) - 6.01015e+02);
				}
			}
		}
	}

	gStyle->SetOptFit(1011);
	h_div->Draw();

}