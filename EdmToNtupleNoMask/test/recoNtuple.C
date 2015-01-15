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
#include <iomanip>
#include <string>
 
TFile *f1;
TTree *duttree;
//const char* fin1, const char* fout
void recoNtuple(const char* fin1,int RUN, int angle, int threshold_0, int threshold_1){
	//open rawfile

	f1 = TFile::Open(fin1);
	duttree = (TTree*)f1->Get("tree");

	unsigned int    events(-9999);
	unsigned int    run(-9999);
	unsigned int    tdcPhase(9999);

	std::vector<int> *strip_S0 = 0;
	std::vector<int> *strip_S1 = 0;
	std::vector<int> *strip_S2 = 0;
	std::vector<int> *strip_S3 = 0;
	std::vector<int> *channel_S0 = 0;
	std::vector<int> *channel_S1 = 0;
	std::vector<int> *channel_S2 = 0;
	std::vector<int> *channel_S3 = 0;

	//TFile *dutFile = TFile::Open("../../output/rawFiles/RAW_USC.00000478.0001.A.storageManager.00.0000.root");
	//TTree *duttree = (TTree *) dutFile->Get("tree");
	duttree->SetBranchAddress("event", &events);
	duttree->SetBranchAddress("run", &run);
	duttree->SetBranchAddress("dut0_row", &strip_S0);
	duttree->SetBranchAddress("dut1_row", &strip_S1);
	duttree->SetBranchAddress("dut2_row", &strip_S2);
	duttree->SetBranchAddress("dut3_row", &strip_S3);
	duttree->SetBranchAddress("dut0_channel", &channel_S0);
	duttree->SetBranchAddress("dut1_channel", &channel_S1);
	duttree->SetBranchAddress("dut2_channel", &channel_S2);
	duttree->SetBranchAddress("dut3_channel", &channel_S3);
	duttree->SetBranchAddress("tdcPhase", &tdcPhase);
	
	int dutEntries = duttree->GetEntries();

	TH1F *h_row_S0 = new TH1F("row_S0","row_S0", 256, 0. , 256.);
	TH1F *h_row_S1 = new TH1F("row_S1","row_S1", 256, 0. , 256.);
	TH1F *h_row_S2 = new TH1F("row_S2","row_S2", 256, 0. , 256.);
	TH1F *h_row_S3 = new TH1F("row_S3","row_S3", 256, 0. , 256.);
	TH1F *h_row_S2_masked = new TH1F("row_S2_masked","row_S2_masked", 256, 0. , 256.);
	TH1F *h_row_S3_masked = new TH1F("row_S3_masked","row_S3_masked", 256, 0. , 256.);

	TH1F *h_clusters_S2 = new TH1F("clusters_S2","clusters_S2", 256, 0. , 256.);
	TH1F *h_clusters_S3 = new TH1F("clusters_S3","clusters_S3", 256, 0. , 256.);

	//creat recofile
	std::vector<double> clusters_position_S0;
	std::vector<double> clusters_position_S1;
	std::vector<double> clusters_position_S2;
	std::vector<double> clusters_position_S3;
	std::vector<double> stubs_module_1;
	std::vector<double> stubs_module_2;
	std::vector<int> clusterwidth_S0;
	std::vector<int> clusterwidth_S1;
	std::vector<int> clusterwidth_S2;
	std::vector<int> clusterwidth_S3;
    	std::vector<int> *row_S2_masked = 0;
   	std::vector<int> *row_S3_masked = 0;


	std::string fout = "RECO_";
	//fout += std::to_string(angle);
	fout += "Run_" + std::to_string(RUN) + "_cnmAngle_" + std::to_string(angle) + "_cnmThr_" + std::to_string(threshold_0) + "_infThr_" + std::to_string(threshold_1) + ".root";


	TFile *recofile = new TFile(fout.c_str(),"RECREATE");
	TTree *recotree = new TTree("recotree","reconstructed");
	TTree *metaData = new TTree("metaData","reconstructed");
	recotree->Branch("events" , &events );
	recotree->Branch("run" , &run );
	recotree->Branch("row_S0", &strip_S0);
	recotree->Branch("row_S1", &strip_S1);
	recotree->Branch("row_S2", &strip_S2);
	recotree->Branch("row_S3", &strip_S3);
    	recotree->Branch("row_S2_masked", &row_S2_masked);
	recotree->Branch("row_S3_masked", &row_S3_masked);
	recotree->Branch("channel_S0", &channel_S0);
	recotree->Branch("channel_S1", &channel_S1);
	recotree->Branch("channel_S2", &channel_S2);
	recotree->Branch("channel_S3", &channel_S3);
	recotree->Branch("clusters_S0", &clusters_position_S0);
	recotree->Branch("clusters_S1", &clusters_position_S1);
	recotree->Branch("clusters_S2", &clusters_position_S2);
	recotree->Branch("clusters_S3", &clusters_position_S3);
	recotree->Branch("clusterwidth_S0", &clusterwidth_S0);
	recotree->Branch("clusterwidth_S1", &clusterwidth_S1);
	recotree->Branch("clusterwidth_S2", &clusterwidth_S2);
	recotree->Branch("clusterwidth_S3", &clusterwidth_S3);
	recotree->Branch("stubs_module_1",&stubs_module_1);
	recotree->Branch("stubs_module_2",&stubs_module_2);
	recotree->Branch("tdc", &tdcPhase);

	metaData->Branch("angle", &angle);
	metaData->Branch("threshold_module_0", &threshold_0);
	metaData->Branch("threshold_module_1", &threshold_1);


	//events loop
	for (int i =0; i < dutEntries; i++){

		duttree->GetEntry(i);
		if(tdcPhase >= 5 && tdcPhase <= 11){

		int   size_S0 = strip_S0->size();
		int   size_S1 = strip_S1->size();
		int   size_S2 = strip_S2->size();
		int   size_S3 = strip_S3->size();

		//masking noisy strips
		std::vector<int> strip_S0_masked ;
		std::vector<int> strip_S1_masked ;
		std::vector<int> strip_S2_masked ;
		std::vector<int> strip_S3_masked ;


		for(int j = 0; j < size_S0; ++j){
			if(strip_S0->at(j) <= 257 ||  strip_S0->at(j) > -1){
			strip_S0_masked.push_back(strip_S0->at(j));
			}
		}
		for(int j = 0; j < size_S1; ++j){
			if(strip_S1->at(j) <= 257 ||  strip_S1->at(j) > -1){
			strip_S1_masked.push_back(strip_S1->at(j));
			}
		}
		for(int j = 0; j < size_S2; ++j){
			if(strip_S2->at(j) <= 130 ||  strip_S2->at(j) >= 160){
			strip_S2_masked.push_back(strip_S2->at(j));
			row_S2_masked->push_back(strip_S2->at(j));
			h_row_S2_masked->Fill(strip_S2->at(j));
			}
		}
		for(int j = 0; j < size_S3; ++j){
			if(strip_S3->at(j) <= 130 ||  strip_S3->at(j) >= 160){
			strip_S3_masked.push_back(strip_S3->at(j));
			row_S3_masked->push_back(strip_S3->at(j));
			h_row_S3_masked->Fill(strip_S3->at(j));
			}
		}

		int size_S0_masked = strip_S0_masked.size();
		int size_S1_masked = strip_S1_masked.size();
		int size_S2_masked = strip_S2_masked.size();
		int size_S3_masked = strip_S3_masked.size();

		std::vector<int> v_firstStripOfCluster;
		std::vector<int> v_lastStripOfCluster;
		std::vector<int> v_firstStripOfCluster1;
		std::vector<int> v_lastStripOfCluster1;
		std::vector<int> v_firstStripOfCluster2;
		std::vector<int> v_lastStripOfCluster2;
		std::vector<int> v_firstStripOfCluster3;
		std::vector<int> v_lastStripOfCluster3;
	
		int firstStripOfCluster(-999);
		int lastStripOfCluster(-999);
		int stripCounter(0);
		int firstStripOfCluster1(-999);
		int lastStripOfCluster1(-999);
		int stripCounter_S1(0);
		int firstStripOfCluster2(-999);
		int lastStripOfCluster2(-999);
		int stripCounter_S2(0);
		int firstStripOfCluster3(-999);
		int lastStripOfCluster3(-999);
		int stripCounter_S3(0);

		//clustering S0
		for(int k = 0; k < size_S0_masked; ++k){
			++stripCounter;
			int stripUnderStudy = strip_S0_masked.at(k);
			if(k == 0){
				firstStripOfCluster = stripUnderStudy;
				lastStripOfCluster = stripUnderStudy;
			}
			else if(stripUnderStudy == lastStripOfCluster+1){
				lastStripOfCluster = stripUnderStudy;
			}
			else{
				v_firstStripOfCluster.push_back(firstStripOfCluster);
				v_lastStripOfCluster.push_back(lastStripOfCluster);
				firstStripOfCluster = stripUnderStudy;
				lastStripOfCluster = stripUnderStudy;
			}
			if(stripCounter == size_S0_masked){
				v_firstStripOfCluster.push_back(firstStripOfCluster);
				v_lastStripOfCluster.push_back(lastStripOfCluster);
			}
		}
		//clustering S1
		for(int k = 0; k < size_S1_masked ; k++){
			++stripCounter_S1;
			int stripUnderStudy1 = strip_S1_masked.at(k);
			if(k == 0){
				firstStripOfCluster1 = stripUnderStudy1;
				lastStripOfCluster1 = stripUnderStudy1;
			}
			else if(stripUnderStudy1 == lastStripOfCluster1+1){
				lastStripOfCluster1 = stripUnderStudy1;
			}
			else{
				v_firstStripOfCluster1.push_back(firstStripOfCluster1);
				v_lastStripOfCluster1.push_back(lastStripOfCluster1);
				firstStripOfCluster1 = stripUnderStudy1;
				lastStripOfCluster1 = stripUnderStudy1;
			}
			if(stripCounter_S1== size_S1_masked){
				v_firstStripOfCluster1.push_back(firstStripOfCluster1);
				v_lastStripOfCluster1.push_back(lastStripOfCluster1);
			}
		}
		//clustering S2
		for(int k = 0; k < size_S2_masked ; k++){
			++stripCounter_S2;
			int stripUnderStudy2 = strip_S2_masked.at(k);
			if(k == 0){
				firstStripOfCluster2 = stripUnderStudy2;
				lastStripOfCluster2 = stripUnderStudy2;
			}
			else if(stripUnderStudy2 == lastStripOfCluster2+1){
				lastStripOfCluster2 = stripUnderStudy2;
			}
			else{
				v_firstStripOfCluster2.push_back(firstStripOfCluster2);
				v_lastStripOfCluster2.push_back(lastStripOfCluster2);
				firstStripOfCluster2 = stripUnderStudy2;
				lastStripOfCluster2 = stripUnderStudy2;
			}
			if(stripCounter_S2== size_S2_masked){
				v_firstStripOfCluster2.push_back(firstStripOfCluster2);
				v_lastStripOfCluster2.push_back(lastStripOfCluster2);
			}
		}
		//clustering S3
		for(int k = 0; k < size_S3_masked ; k++){
			++stripCounter_S3;
			int stripUnderStudy3 = strip_S3_masked.at(k);
			if(k == 0){
				firstStripOfCluster3 = stripUnderStudy3;
				lastStripOfCluster3 = stripUnderStudy3;
			}
			else if(stripUnderStudy3 == lastStripOfCluster3+1){
				lastStripOfCluster3 = stripUnderStudy3;
			}
			else{
				v_firstStripOfCluster3.push_back(firstStripOfCluster3);
				v_lastStripOfCluster3.push_back(lastStripOfCluster3);
				firstStripOfCluster3 = stripUnderStudy3;
				lastStripOfCluster3 = stripUnderStudy3;
			}
			if(stripCounter_S3== size_S3_masked){
				v_firstStripOfCluster3.push_back(firstStripOfCluster3);
				v_lastStripOfCluster3.push_back(lastStripOfCluster3);
			}
		}

		if(v_firstStripOfCluster.size() != v_lastStripOfCluster.size()){
			std::cerr<<"ERROR! Not same vector size_S0for cluster first/last strip\n";
			exit(583);
		}
		//cluster width and position for all sensors
		for(size_t iStrip = 0; iStrip < v_firstStripOfCluster.size(); ++iStrip){
			int width = v_lastStripOfCluster.at(iStrip) - v_firstStripOfCluster.at(iStrip) +1;
			clusterwidth_S0.push_back(width);
			clusters_position_S0.push_back(double(v_firstStripOfCluster.at(iStrip) + v_lastStripOfCluster.at(iStrip))/2.);
		}

		for(size_t iStrip = 0; iStrip < v_firstStripOfCluster1.size(); ++iStrip){
			int width1 = v_lastStripOfCluster1.at(iStrip) - v_firstStripOfCluster1.at(iStrip) +1;
			clusterwidth_S1.push_back(width1);
			clusters_position_S1.push_back(double(v_firstStripOfCluster1.at(iStrip) + v_lastStripOfCluster1.at(iStrip))/2.);	
		}
		for(size_t iStrip = 0; iStrip < v_firstStripOfCluster2.size(); ++iStrip){
			int width2 = v_lastStripOfCluster2.at(iStrip) - v_firstStripOfCluster2.at(iStrip) +1;
			clusterwidth_S2.push_back(width2);
			double clustPos2 = (v_firstStripOfCluster2.at(iStrip) + v_lastStripOfCluster2.at(iStrip))/2.;
			clusters_position_S2.push_back(clustPos2);
			h_clusters_S2->Fill(clustPos2);
		}
		for(size_t iStrip = 0; iStrip < v_firstStripOfCluster3.size(); ++iStrip){
			int width3 = v_lastStripOfCluster3.at(iStrip) - v_firstStripOfCluster3.at(iStrip) +1;
			clusterwidth_S3.push_back(width3);
			double clustPos3 = (v_firstStripOfCluster3.at(iStrip) + v_lastStripOfCluster3.at(iStrip))/2.;
			clusters_position_S3.push_back(clustPos3);
			h_clusters_S3->Fill(clustPos3);
		}
		
		//stubs module 1
		if ( v_firstStripOfCluster.size() == 1 &&  v_firstStripOfCluster1.size() == 1){
			for(size_t iStrip = 0; iStrip < v_firstStripOfCluster.size() && 	v_firstStripOfCluster1.size(); ++iStrip){
				double pos_S0 = (double(v_firstStripOfCluster.at(0) + v_lastStripOfCluster.at(0))/2.);
				double pos_S1 = (double(v_firstStripOfCluster1.at(0) + v_lastStripOfCluster1.at(0))/2.);
				stubs_module_1.push_back(pos_S1 - pos_S0);
			}
		}
		//stubs module 2
		if ( v_firstStripOfCluster2.size() == 1 && v_firstStripOfCluster3.size() == 1){
			for(size_t iStrip = 0; iStrip < v_firstStripOfCluster2.size() && v_firstStripOfCluster3.size(); ++iStrip){
				double pos_S2 = (double(v_firstStripOfCluster2.at(0) + v_lastStripOfCluster2.at(0))/2.);
				double pos_S3 = (double(v_firstStripOfCluster3.at(0) + v_lastStripOfCluster3.at(0))/2.);
				stubs_module_2.push_back(pos_S3 - pos_S2);
			}
		}

		//histograms signal position by strip number in the recotree
		for(int k = 0 ; k < size_S0 ; ++k){
			h_row_S0->Fill(strip_S0->at(k));}
		for(int k = 0 ; k < size_S1 ; ++k){
			h_row_S1->Fill(strip_S1->at(k));}
		for(int k = 0 ; k < size_S2 ; ++k){
			h_row_S2->Fill(strip_S2->at(k));}
		for(int k = 0 ; k < size_S3 ; ++k){
			h_row_S3->Fill(strip_S3->at(k));}

		recotree->Fill();

		clusters_position_S0.clear();
		clusters_position_S1.clear();
		clusters_position_S2.clear();
		clusters_position_S3.clear();

		clusterwidth_S0.clear();
		clusterwidth_S1.clear();
		clusterwidth_S2.clear();
		clusterwidth_S3.clear();

		stubs_module_1.clear();
		stubs_module_2.clear();

		row_S2_masked->clear();
		row_S3_masked->clear();

	//end of events loop
	}
}


	metaData->Fill();

	recofile->cd();

	h_row_S0->Write();
	h_row_S1->Write();
	h_row_S2->Write();
	h_row_S3->Write();
	h_row_S2_masked->Write();
	h_row_S3_masked->Write();
	h_clusters_S2->Write();
	h_clusters_S3->Write();
	recotree->Write();
	metaData->Write();
	recofile->Close();
	f1->Close();
	//h_position->Draw();
}

