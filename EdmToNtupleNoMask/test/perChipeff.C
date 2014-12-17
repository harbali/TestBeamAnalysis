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
	double counter2(0);
	double counter3(0);


	unsigned int    run(-9999);
	std::vector<double> *clusters_position_S0= 0;
	std::vector<double> *clusters_position_S1= 0;
	std::vector<double> *clusters_position_S2= 0;
	std::vector<double> *clusters_position_S3= 0;
	
	TH1F *h1 = new TH1F("",";strip # ;eff.", 2, 0. , 256.);
	TH1F *h2 = new TH1F("",";strip # ;eff.", 2, 0. , 256.);
	
	TH1F *control = new TH1F("",";strip # ;", 256, 0. , 256.);
	
	TH1F *h4 = new TH1F("",";strip # ;eff.", 2, 0. , 256.);
	TH1F *h5 = new TH1F("",";strip # ;eff.", 2, 0. , 256.);
	
	TH1F *control1 = new TH1F("",";strip # ;", 256, 0. , 256.);
	
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
	
		for(unsigned int k = 0; k < cluster_size_S0; ++k){
	
						//control->Fill(clusters_position_S1->at(k));
	
			if (  cluster_size_S0 == 1 &&  cluster_size_S2 == 1 && cluster_size_S3 == 1){

			if((clusters_position_S0->at(k) > cbc0_edge_a && clusters_position_S0->at(k) < cbc0_edge_b) || (clusters_position_S0->at(k)> cbc1_edge_a && clusters_position_S0->at(k)< cbc1_edge_b)){
			
			if((clusters_position_S2->at(k) > cbc0_edge_a && clusters_position_S2->at(k)< cbc0_edge_b)  || (clusters_position_S2->at(k)> cbc1_noise && clusters_position_S2->at(k)< cbc1_edge_b)){
			
			if((clusters_position_S3->at(k) > cbc0_edge_a && clusters_position_S3->at(k)< cbc0_edge_b)  || (clusters_position_S3->at(k)> cbc1_noise && clusters_position_S3->at(k)< cbc1_edge_b)){
	
				double pos0 = clusters_position_S0->at(k);
				double pos2 = clusters_position_S2->at(k);
				double pos3 = clusters_position_S3->at(k);
	
				//control->Fill(clusters_position_S2->at(k));
				
				if(TMath::Abs(pos2 - pos3)*80. < window*80.){
					if(TMath::Abs((pos2 + pos3)*80./2. - pos0*90. + meanOfFit) <= halfWidthOfFit ){
						counter0++;
						h1->Fill(pos0);
						if(cluster_size_S1 >= 1){
							for(unsigned int j = 0; j < cluster_size_S1;++j){
								//if((clusters_position_S0->at(j) > cbc0_edge_a && clusters_position_S0->at(j) < cbc0_edge_b) || (clusters_position_S0->at(j)> cbc1_edge_a && clusters_position_S0->at(j)< cbc1_edge_b)){
									double pos1 = clusters_position_S1->at(j);
									if(TMath::Abs(pos1-pos0)*90. < window*90.){
										counter1++;
										h2->Fill(pos1);
										control->Fill(clusters_position_S1->at(j));

										break;
									}
								//}
							}
						}
					}
				}
			}}}}
		}


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
					if(TMath::Abs((pos2 + pos3)*80./2. - pos1*90. + meanOfFit) <= halfWidthOfFit ){
						counter2++;
						h4->Fill(pos1);
						if(cluster_size_S1 >= 1){
							for(unsigned int j = 0; j < cluster_size_S0;++j){
								//if((clusters_position_S0->at(j) > cbc0_edge_a && clusters_position_S0->at(j) < cbc0_edge_b) || (clusters_position_S0->at(j)> cbc1_edge_a && clusters_position_S0->at(j)< cbc1_edge_b)){
									double pos0 = clusters_position_S0->at(j);
									if(TMath::Abs(pos1-pos0)*90. < window*90.){
										counter3++;
										h5->Fill(pos0);
										control1->Fill(clusters_position_S0->at(j));

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

 	std::cout << std::endl;
	std::cout << "total S1:" << counter0 << std::endl;
	std::cout << "selected S1 :" << counter1 << std::endl;
	std::cout << std::endl;

	//TCanvas * c1 = new TCanvas("c1","c1",1200,1200);
	//c1->Divide(2,2);
	
	TH1F * h3 = (TH1F*)h2->Clone();
	
	//c1->cd(1);
	//h1->Draw();
	//c1->cd(2);
	//h2->Draw();
	//c1->cd(3);
	//gStyle->SetOptStat(0);
	h3->Divide(h1);
	
	double binCBC0a_S1 = h2->GetBinContent(1);
	double binCBC1a_S1 = h2->GetBinContent(2);
	
	double binCBC0b_S1 = h1->GetBinContent(1);
	double binCBC1b_S1 = h1->GetBinContent(2);
	
	double binCBC0_S1 = h3->GetBinContent(1);
	double binCBC1_S1 = h3->GetBinContent(2);
	
	//h3->Draw();
	std::cout << std::endl;
	std::cout << "run: " << run << std::endl;
	std::cout << "CBC0 selected_S1 : " << binCBC0a_S1 << " CBC1selected_S1 : " << binCBC1a_S1 << std::endl;
	std::cout << "CBC0all_S1 :       " << binCBC0b_S1 << " CBC1all_S1 :      " << binCBC1b_S1 << std::endl;
	std::cout << std::endl;
	
	std::cout << std::endl;
	std::cout << "cbc0 eff_S1: " <<h3->GetBinContent(1)<< std::endl;
	std::cout << "cbc1 eff_S1: " <<h3->GetBinContent(2)<< std::endl;
	std::cout << std::endl;

	//c1->cd(4);
	//control->Draw();


//====================================

	std::cout << std::endl;
	std::cout << "total_S0 :" << counter2 << std::endl;
	std::cout << "selected_S0 :" << counter3 << std::endl;
	std::cout << std::endl;

	//TCanvas * c2 = new TCanvas("c2","c2",1200,1200);
	//c2->Divide(2,2);
	
	TH1F * h6 = (TH1F*)h5->Clone();
	
	//c2->cd(1);
	//h4->Draw();
	//c2->cd(2);
	//h5->Draw();
	//c2->cd(3);
	//gStyle->SetOptStat(0);
	h6->Divide(h4);
	
	double binCBC0aa_S0 = h5->GetBinContent(1);
	double binCBC1aa_S0 = h5->GetBinContent(2);
	
	double binCBC0bb_S0 = h4->GetBinContent(1);
	double binCBC1bb_S0 = h4->GetBinContent(2);
	
	double binCBC00_S0 = h6->GetBinContent(1);
	double binCBC11_S0 = h6->GetBinContent(2);
	
 	//h6->Draw();
	std::cout << std::endl;
	std::cout << "run: " << run << std::endl;
	std::cout << "CBC0 selected_S0: " << binCBC0aa_S0 << " CBC1selected_S0: " << binCBC1aa_S0 << std::endl;
	std::cout << "CBC0all_S0:       " << binCBC0bb_S0 << " CBC1all_S0:      " << binCBC1bb_S0 << std::endl;
	std::cout << std::endl;
	
	std::cout << std::endl;
	std::cout << "cbc0 eff_S0: " <<h6->GetBinContent(1)<< std::endl;
	std::cout << "cbc1 eff_S0: " <<h6->GetBinContent(2)<< std::endl;
	
	//c2->cd(4);
	//control1->Draw();

}

