#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include <vector>
#include "TROOT.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TH1F.h"

//to execute over all output files run in output/out "./no_rotation_th_occ_scan.sh"


void occDUT(){

	double counter(0);
	double counter1(0);
	double counter2(0);
	double counter3(0);
	double counter4(0);
	double counter5(0);
	double counter6(0);
	double counter7(0);

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
	
		unsigned int   cluster_size_S0 = clusters_position_S0->size();
		unsigned int   cluster_size_S1 = clusters_position_S1->size();
		unsigned int   cluster_size_S2 = clusters_position_S2->size();
		unsigned int   cluster_size_S3 = clusters_position_S3->size();
		
		const double meanOfFit = 596.;
		const double halfWidthOfFit = 570.;

		for(unsigned int k = 0; k < cluster_size_S0; ++k){
			if (  cluster_size_S0 == 1 &&  cluster_size_S1 == 1 && cluster_size_S2 == 1){
				double pos0 = clusters_position_S0->at(k);
				double pos1 = clusters_position_S1->at(k);
				double pos2 = clusters_position_S2->at(k);
				if(TMath::Abs(pos0 - pos1)*90. < 4.*90.){
					if(TMath::Abs((pos0 + pos1)*90./2. - pos2*80. - meanOfFit) <= halfWidthOfFit ){
						counter++;
						if(cluster_size_S3 >= 1){
							for(unsigned int j = 0; j < cluster_size_S3;++j){
								double pos3 = clusters_position_S3->at(j);
								if(TMath::Abs(pos2-pos3)*80. > 4.*80.){
									counter1++;
								}
							}
						}
					}
				}
			}
		}
	
		for(unsigned int k = 0; k < cluster_size_S0; ++k){
			if (  cluster_size_S0 == 1 &&  cluster_size_S1 == 1 && cluster_size_S3 == 1){
				double pos0 =  clusters_position_S0->at(k);
				double pos1 = clusters_position_S1->at(k);
				double pos3 = clusters_position_S3->at(k);
				if(TMath::Abs(pos0 - pos1)*90. < 4.*90.){
					if(TMath::Abs((pos0 + pos1)*90./2. - pos3*80. - meanOfFit) <= halfWidthOfFit){
						counter2++;				
						if(cluster_size_S2 >= 1){
							for(unsigned int j = 0; j < cluster_size_S2;++j){
								double pos2 =clusters_position_S2->at(j);
								if(TMath::Abs(pos2-pos3)*80. > 4.*80.){
									counter3++;
								}
							}
						}
					}
				}
			}
		}
	
		for(unsigned int k = 0; k < cluster_size_S0; ++k){
			if (  cluster_size_S0 == 1 &&  cluster_size_S2 == 1 && cluster_size_S3 == 1){
				double pos0 = clusters_position_S0->at(k);
				double pos2 = clusters_position_S2->at(k);
				double pos3 = clusters_position_S3->at(k);
				if(TMath::Abs(pos2 - pos3)*80. < 4.*80.){
					if(TMath::Abs((pos2+pos3)*80./2. - pos0*90. + meanOfFit) <= halfWidthOfFit ){
						counter4++;
						if(cluster_size_S1 >= 1){
							for(unsigned int j = 0; j < cluster_size_S1;++j){
								double pos1 = clusters_position_S1->at(j);
								if(TMath::Abs(pos1-pos0)*90. > 4.*90.){
									counter5++;
								}
							}
						}
					}
				}
			}
		}
	
		for(unsigned int k = 0; k < cluster_size_S1; ++k){
			if (  cluster_size_S1 == 1 &&  cluster_size_S2 == 1 && cluster_size_S3 == 1){
				double pos1 = clusters_position_S1->at(k);
				double pos2 = clusters_position_S2->at(k);
				double pos3 = clusters_position_S3->at(k);
				if(TMath::Abs(pos2 - pos3)*80. < 4.*80.){
					if(TMath::Abs((pos2+pos3)*80./2. - pos1*90. + meanOfFit) <= halfWidthOfFit ){
						counter6++;
						if(cluster_size_S0 >= 1){
							for(unsigned int j = 0; j < cluster_size_S0 ;++j){
								double pos0 = clusters_position_S0->at(j);
								if(TMath::Abs(pos1-pos0)*90. > 4.*90.){
									counter7++;
								}
							}
						}
					}
				}
			}
		}
	}
	std::cout << std::endl;
	std::cout << "Occ. of S3: (" << counter1 << "/" << counter << ") = " << double(((counter1)/(counter))) << std::endl;
	
	std::cout << std::endl;
	std::cout << "Occ. of S2: (" << counter3 << "/" << counter2 << ") = " << double(((counter3)/(counter2))) << std::endl;

	std::cout << std::endl;
	std::cout << "Occ. of S1: (" << counter5 << "/" << counter4 << ") = " << double(((counter5)/(counter4))) << std::endl;

	std::cout << std::endl;
	std::cout << "Occ. of S0: (" << counter7 << "/" << counter6 << ") = " << double(((counter7)/(counter6))) << std::endl;
}


