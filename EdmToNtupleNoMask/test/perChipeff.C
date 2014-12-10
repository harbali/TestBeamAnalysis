#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include <vector>
#include "TROOT.h"
#include "TMath.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TAxis.h"

void perChipeff(){

	double window = 4.;
	double edge = 4.;
	
	double cbc0_edge_a = 0. + edge;
	double cbc0_edge_b = 127. - edge;

	double cbc1_noise = 160. + edge;

	double cbc1_edge_a = 127. + edge;
	double cbc1_edge_b = 254. - edge;
	
	double counter0(0);
	double counter1(0);
	
	unsigned int    run(-9999);
	std::vector<double> *clusters_position_S0= 0;
	std::vector<double> *clusters_position_S1= 0;
	std::vector<double> *clusters_position_S2= 0;
	std::vector<double> *clusters_position_S3= 0;
	
	TH1F *h1 = new TH1F("",";strip # ;eff.", 2, 0. , 256.);
	TH1F *h2 = new TH1F("",";strip # ;eff.", 2, 0. , 256.);
	
	TH1F *control = new TH1F("",";strip # ;", 256, 0. , 256.);
	
	
	TFile *recofile =  TFile::Open("/nfs/dust/cms/user/harbali/output/recoFiles/RECO_run_496_30vcth.root");
	TTree *recotree = (TTree *) recofile->Get("recotree");
	recotree->SetBranchAddress("clusters_S0", &clusters_position_S0);
	recotree->SetBranchAddress("clusters_S1", &clusters_position_S1);
	recotree->SetBranchAddress("clusters_S2", &clusters_position_S2);
	recotree->SetBranchAddress("clusters_S3", &clusters_position_S3);
	recotree->SetBranchAddress("run", &run);
	
	//recotree->SetBranchAddress("tdc", &tdc);
	
	
	
	int dutEntries = recotree->GetEntries();

	for (int i = 0; i < dutEntries; i++){
		recotree->GetEntry(i);
	
		unsigned int   cluster_size_S0 = clusters_position_S0->size();
		unsigned int   cluster_size_S1 = clusters_position_S1->size();
		unsigned int   cluster_size_S2 = clusters_position_S2->size();
		unsigned int   cluster_size_S3 = clusters_position_S3->size();
	
		const double meanOfFit = 598.37;
		const double halfWidthOfFit = 576.4;
	
		for(unsigned int k = 0; k < cluster_size_S1; ++k){
	
						//control->Fill(clusters_position_S1->at(k));
	
			if (  cluster_size_S1 == 1 &&  cluster_size_S2 == 1 && cluster_size_S3 == 1){	
			if((clusters_position_S1->at(k) > cbc0_edge_a && clusters_position_S1->at(k) < cbc0_edge_b) || (clusters_position_S1->at(k)> cbc1_edge_a && clusters_position_S1->at(k)< cbc1_edge_b)){
			if((clusters_position_S2->at(k) > cbc0_edge_a && clusters_position_S2->at(k)< cbc0_edge_b)  || (clusters_position_S2->at(k)> cbc1_noise && clusters_position_S2->at(k)< cbc1_edge_b)){
			if((clusters_position_S3->at(k) > cbc0_edge_a && clusters_position_S3->at(k)< cbc0_edge_b)  || (clusters_position_S3->at(k)> cbc1_noise && clusters_position_S3->at(k)< cbc1_edge_b)){
	
				double pos1 = clusters_position_S1->at(k);
				double pos2 = clusters_position_S2->at(k);
				double pos3 = clusters_position_S3->at(k);
	
				//control->Fill(clusters_position_S2->at(k));
				
				if(TMath::Abs(pos2 - pos3)*80. < window*80.){
					if(TMath::Abs((pos2+pos3)*80./2. - pos1*90. + meanOfFit) <= halfWidthOfFit ){
						counter0++;
						h1->Fill(pos1);
						if(cluster_size_S0 >= 1){
							for(unsigned int j = 0; j < cluster_size_S0;++j){
								//if((clusters_position_S0->at(j) > cbc0_edge_a && clusters_position_S0->at(j) < cbc0_edge_b) || (clusters_position_S0->at(j)> cbc1_edge_a && clusters_position_S0->at(j)< cbc1_edge_b)){
									double pos0 = clusters_position_S0->at(j);
									if(TMath::Abs(pos1-pos0)*90. < window*90.){
										counter1++;
										h2->Fill(pos0);
										control->Fill(clusters_position_S0->at(j));

										break;
									}
								//}
							}
						}
					}
				}
			}}}}
		}
	}


	std::cout << "total :" << counter0 << std::endl;
	std::cout << "selected :" << counter1 << std::endl;
	
	TCanvas * c1 = new TCanvas("c1","c1",1200,1200);
	c1->Divide(2,2);
	
	TH1F * h3 = (TH1F*)h2->Clone();
	
	c1->cd(1);
	h1->Draw();
	c1->cd(2);
	h2->Draw();
	c1->cd(3);
	//gStyle->SetOptStat(0);
	h3->Divide(h1);
	
	double binCBC0a = h2->GetBinContent(1);
	double binCBC1a = h2->GetBinContent(2);
	
	double binCBC0b = h1->GetBinContent(1);
	double binCBC1b = h1->GetBinContent(2);
	
	double binCBC0 = h3->GetBinContent(1);
	double binCBC1 = h3->GetBinContent(2);
	
	h3->Draw();
	std::cout << std::endl;
	std::cout << "run: " << run << std::endl;
	std::cout << "CBC0 selected: " << binCBC0a << " CBC1selected: " << binCBC1a << std::endl;
	std::cout << "CBC0all:       " << binCBC0b << " CBC1all:      " << binCBC1b << std::endl;
	std::cout << std::endl;
	
	std::cout << std::endl;
	std::cout << "cbc0 eff: " <<h3->GetBinContent(1)<< std::endl;
	std::cout << "cbc1 eff: " <<h3->GetBinContent(2)<< std::endl;
	
	c1->cd(4);
	control->Draw();

}

