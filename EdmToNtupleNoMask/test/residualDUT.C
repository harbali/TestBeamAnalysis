#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include <vector>
#include "TROOT.h"
#include "TSystem.h"
#include "TMath.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TStyle.h"


#include "gsl/gsl_fit.h"
#include "gsl/gsl_poly.h"

// Before compiling do!!!!
// gSystem->AddLinkedLibs("/cvmfs/cms.cern.ch/slc5_amd64_gcc472/external/gsl/1.10/lib/libgslcblas.so");
// gSystem->AddLinkedLibs("/cvmfs/cms.cern.ch/slc5_amd64_gcc472/external/gsl/1.10/lib/libgsl.so");

 




void residualDUT(){

	gStyle->SetOptStat(1110);
	
	//f1 = TFile::Open(fin1);
	//duttree = (TTree*)f1->Get("tree");

	TH1F *h_res1 = new TH1F("h_res1","h_res1", 50, -1,1);
	TH1F *h_hit1 = new TH1F("h_hit1","h_hit1", 350, -1,24);
	TH1F *h_trk1 = new TH1F("h_trk1","h_trk1", 350, -1,24);

	std::vector<double> *clusters_position_S0= 0;
	std::vector<double> *clusters_position_S1= 0;
 	std::vector<double> *clusters_position_S2= 0;
	std::vector<double> *clusters_position_S3= 0;
	
	TFile *recofile =  TFile::Open("RECO_USC.00000478.0001.A.storageManager.00.0000.root");
	TTree *recotree = (TTree *) recofile->Get("recotree");
	recotree->SetBranchAddress("clusters_S0", &clusters_position_S0);
	recotree->SetBranchAddress("clusters_S1", &clusters_position_S1);
    	recotree->SetBranchAddress("clusters_S2", &clusters_position_S2);
	recotree->SetBranchAddress("clusters_S3", &clusters_position_S3);

	int dutEntries = recotree->GetEntries();

	for (int i =0; i < dutEntries; i++){
		recotree->GetEntry(i);	
	
		//if(event_dut <1000){

		unsigned int   cluster_size_S0 = clusters_position_S0->size();
		unsigned int   cluster_size_S1 = clusters_position_S1->size();
		unsigned int   cluster_size_S2 = clusters_position_S2->size();
		unsigned int   cluster_size_S3 = clusters_position_S3->size();
		
		const double meanOfFit = 6.01015e+02; //beam divergence mean
		const double halfWidthOfFit = 570.;

		for(unsigned int k = 0; k < cluster_size_S0; ++k){
			if (  cluster_size_S0 == 1 &&  cluster_size_S2 == 1 && cluster_size_S3 == 1){
				double pos0 = clusters_position_S0->at(0);
				double pos2 = clusters_position_S2->at(0);
				double pos3 = clusters_position_S3->at(0);
	
				static const double pitch1 = 90.;
				static const double pitch2 = 80.;
	
				if(TMath::Abs(pos3 - pos2)*pitch2 < 4.*pitch2){
					if(TMath::Abs((pos3 + pos2)*pitch2/2. - pos0*pitch1 + meanOfFit) < halfWidthOfFit){
						if(cluster_size_S1 == 1){
							double pos1 = clusters_position_S1->at(0);
	
							double ypos[3];
							ypos[0] = pos0*pitch1 + meanOfFit;
							ypos[1] = pos2*pitch2;
							ypos[2] = pos3*pitch2;
							const double xpos[3] {0.,233000.,236000.};
							
							double c0,c1,cov00,cov01,cov11,sumsq;
							
							gsl_fit_linear(xpos,1,ypos,1,3, &c0,&c1,&cov00,&cov01,&cov11,&sumsq);
							
							double c[2];
							c[0] = c0;
							c[1] = c1;
							
							double pos1predict = gsl_poly_eval(c, 2, 3000.);
							double r = (pos1*pitch1 - pos1predict + meanOfFit)/1000.;
							h_hit1->Fill(pos1*pitch1/1000.);
							h_trk1->Fill(pos1predict/1000.);
							h_res1->Fill(r);
						}
					}
				}
			}
		}
	//}
			
	}

	TCanvas * c2 = new TCanvas("c4","c4",1300,500);
	c2->Divide(3,1);
	c2->cd(1);
	h_hit1->Draw();
	c2->cd(2);
	h_trk1->Draw();
	c2->cd(3);
	c2->cd(3)->SetLogy();
	h_res1->Draw();
}


