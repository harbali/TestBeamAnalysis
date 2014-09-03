// -*- C++ -*-
//
// Package:    EdmToNtupleNoMask
// Class:      EdmToNtupleNoMask
// 
/**\class EdmToNtupleNoMask EdmToNtupleNoMask.cc TestBeamAnalysis/EdmToNtupleNoMask/plugins/EdmToNtupleNoMask.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Ali Harb
//         Created:  Tue, 19 Aug 2014 13:49:02 GMT
// $Id$
//
//


#include "DataFormats/Common/interface/DetSetVector.h"
#include "DataFormats/SiPixelDigi/interface/PixelDigiCollection.h"
#include "Phase2TrackerDAQ/SiStripDigi/interface/SiStripCommissioningDigi.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "boost/filesystem.hpp"

#include "TFile.h"
#include "TTree.h"

struct EventInfo {EventInfo(): run_(999999), lumiSection_(999999), event_(999999), 
time_(999999), unixtime_(999999), dt_(999999),
tdcPhase_(999999){}
	
	unsigned int run_;
	unsigned int lumiSection_;
	unsigned int event_;
	unsigned long long time_;
	unsigned long int unixtime_;
	unsigned long int dt_;
	uint32_t key_;
	uint32_t value_;
	unsigned int tdcPhase_;
	//unsigned int HVsettings_;
	//unsigned int DUTangle_;

	std::vector<int> dut0_channel_;
	std::vector<int> dut0_row_;
	std::vector<unsigned short> dut0_adc_;
	
	std::vector<int> dut1_channel_;
	std::vector<int> dut1_row_;
	std::vector<unsigned short> dut1_adc_;
	
	std::vector<int> dut2_channel_;
	std::vector<int> dut2_row_;
	std::vector<unsigned short> dut2_adc_;
	
	std::vector<int> dut3_channel_;
	std::vector<int> dut3_row_;
	std::vector<unsigned short> dut3_adc_;
	
};
	
class EdmToNtupleNoMask : public edm::EDAnalyzer
{
	public:
		explicit EdmToNtupleNoMask(const edm::ParameterSet&);
		~EdmToNtupleNoMask();

	private:
		virtual void beginJob() ;
		virtual void analyze(const edm::Event&, const edm::EventSetup&);
		virtual void endJob() ;

	std::vector<EventInfo> v_evtInfo_;
	const std::string m_output_file_name;
	TFile* m_output_file;

	unsigned long long time_prev;

};
	
	// constructors and destructor
	EdmToNtupleNoMask::EdmToNtupleNoMask(const edm::ParameterSet& iConfig)
	:m_output_file_name(iConfig.getUntrackedParameter<std::string>("output_file_name")),
	m_output_file(NULL){}

	EdmToNtupleNoMask::~EdmToNtupleNoMask(){}

	// ------------ method called once each job just before starting event loop  ------------
void EdmToNtupleNoMask::beginJob()
{
	const std::string full_file_name = boost::filesystem::current_path().string() + "/" + m_output_file_name;
	try
	{
		const boost::filesystem::path file(full_file_name);
		const boost::filesystem::path directory(file.parent_path());
		if (not boost::filesystem::exists(directory))
		{
		boost::filesystem::create_directories(directory);
		}
	}
	catch (boost::filesystem::filesystem_error& e)
	{
		std::cerr << e.what() << std::endl;
	}

	// initialize ROOT file and tree
	try
	{
		// create the ROOT file
		m_output_file = TFile::Open(full_file_name.c_str(), "RECREATE");
		if (not m_output_file or m_output_file->IsZombie())
		{
		throw std::runtime_error("[EdmToNtupleNoMask] Error: could not open " + 
full_file_name);
		}
	
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	
	time_prev = 0;

}
	
	// ------------ method called for each event  ------------
void EdmToNtupleNoMask::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	EventInfo evtInfo;

	// event info
	evtInfo.run_   = iEvent.id().run();
	evtInfo.event_ = iEvent.id().event();
	evtInfo.lumiSection_ = iEvent.luminosityBlock();
	
	edm::Timestamp itime = iEvent.time();
	evtInfo.time_  = itime.value();
	evtInfo.unixtime_  = itime.unixTime();
	
	edm::Handle < edm::DetSet<SiStripCommissioningDigi> > conditions;
	iEvent.getByLabel("SiStripDigiCondDataproducer", "ConditionData",  conditions);
	if( !conditions.isValid() )
	{
		std::cout << "condition data not found" << std::endl;
		exit(1);
	}

	//std::cout<<"\n\nsize: "<<conditions->size()<<" , "<<conditions->id<<"\n\n";

	//unsigned int tdcPhase(999);
	edm::DetSet<SiStripCommissioningDigi>::const_iterator i_detSet;
	for(i_detSet = conditions->begin(); i_detSet != conditions->end(); ++i_detSet){
		uint32_t key = i_detSet->getKey();
		uint32_t value = i_detSet->getValue();
		//std::cout <<"key, value: " << key << " , " <<value<< "\n";
		if(key == 0x030000FF) evtInfo.tdcPhase_ = value;
		//if(key == 0x050000FF) evtInfo.HVsettings_ = value;
		//if(key == 0x040000FF) evtInfo.DUTangle_ = value;
	}

	//std::cout<<"tdc: "<<evtInfo.tdcPhase_<<"\n";
	//std::cout<<"DUTangle: "<<evtInfo.DUTangle_<<"\n";

	edm::Handle< edm::DetSetVector<PixelDigi> > input;
	iEvent.getByLabel( "SiStripDigitestproducer", "ProcessedRaw", input);
	
	if( !input.isValid() )
	{
		std::cout << "PixelDigis not found" << std::endl;
		exit(1);
	}
	

	edm::DetSetVector<PixelDigi>::const_iterator it;
	// loop over modules
	for(it = input->begin() ; it != input->end(); ++it) 
	{
		int detId = it->id;
		int id = -1;
		switch( detId ) {
		case 51001: id = 0; break; // DUT top
		case 51002: id = 1; break; // DUT bottom
		case 51011: id = 2; break; // FIX top
		case 51012: id = 3; break; // FIX bottom
		}
	
		if( id < 0 )
		{
		std::cout << "Unknown detector ID" << std::endl;
		exit(1);
		}	
		
		// loop over hits in the module
		for(edm::DetSet<PixelDigi>::const_iterator hit = it->begin(); 
		hit!=it->end(); hit++ ) 
		{
			if(id == 0){
				evtInfo.dut0_channel_.push_back(hit->channel());
				evtInfo.dut0_adc_.push_back(hit->adc());
				evtInfo.dut0_row_.push_back(hit->row());
			}
			if(id == 1){
				evtInfo.dut1_channel_.push_back(hit->channel());
				evtInfo.dut1_adc_.push_back(hit->adc());
				evtInfo.dut1_row_.push_back(hit->row());
				}
			
			if(id == 2){
				evtInfo.dut2_channel_.push_back(hit->channel());
				evtInfo.dut2_adc_.push_back(hit->adc());
				evtInfo.dut2_row_.push_back(hit->row());
			}
			if(id == 3){
				evtInfo.dut3_channel_.push_back(hit->channel());
				evtInfo.dut3_adc_.push_back(hit->adc());
				evtInfo.dut3_row_.push_back(hit->row());
			}
	
		}
	}
	v_evtInfo_.push_back(evtInfo);
}
	
	// ------------ method called once each job just after ending the event loop  ------------
void EdmToNtupleNoMask::endJob() 
{
	std::vector<EventInfo> v_evtInfo_sorted;
	
	for(std::vector<EventInfo>::iterator i_evtInfo = v_evtInfo_.begin(); i_evtInfo != 
v_evtInfo_.end(); ++i_evtInfo){
		if(i_evtInfo == v_evtInfo_.begin()){
			v_evtInfo_sorted.push_back(*i_evtInfo);
			continue;
		}
	
		bool isInserted(false);
		for(std::vector<EventInfo>::iterator j_evtInfo = v_evtInfo_sorted.begin(); 
j_evtInfo != v_evtInfo_sorted.end(); ++j_evtInfo){
			if(i_evtInfo->time_ < j_evtInfo->time_){
				v_evtInfo_sorted.insert(j_evtInfo, *i_evtInfo);
				isInserted = true;
				break;
			}
		}
		if(!isInserted) v_evtInfo_sorted.push_back(*i_evtInfo);
	}
			
	unsigned int run;
	unsigned int lumiSection;
	unsigned int event;
	unsigned long long time;
	//unsigned long long dt;
	unsigned long int unixtime;
	
	unsigned int tdcPhase;
	//unsigned int HVsettings;
	//unsigned int DUTangle;


	std::vector<int> dut0_channel;
	std::vector<int> dut0_row;
	std::vector<unsigned short> dut0_adc;
	
	std::vector<int> dut1_channel;
	std::vector<int> dut1_row;
	std::vector<unsigned short> dut1_adc;
	
	std::vector<int> dut2_channel;
	std::vector<int> dut2_row;
	std::vector<unsigned short> dut2_adc;
	
	std::vector<int> dut3_channel;
	std::vector<int> dut3_row;
	std::vector<unsigned short> dut3_adc;
	
	TTree* m_tree = new TTree("tree", "Simple Tracking Tree");
	m_tree->SetDirectory(m_output_file);
	m_tree->Branch("event" , &event );
	m_tree->Branch("run" , &run );
	m_tree->Branch("lumiSection" , &lumiSection );
	m_tree->Branch("time" , &time, "time/L" );
	//m_tree->Branch("dt" , &dt, "dt/L" );
	m_tree->Branch("unixtime" , &unixtime, "unixtime/L" );
	
	m_tree->Branch("dut0_row", &dut0_row);
	m_tree->Branch("dut1_row", &dut1_row);
	m_tree->Branch("dut2_row", &dut2_row);
	m_tree->Branch("dut3_row", &dut3_row);
	
	m_tree->Branch("dut0_channel", &dut0_channel);
	m_tree->Branch("dut1_channel", &dut1_channel);
	m_tree->Branch("dut2_channel", &dut2_channel);
	m_tree->Branch("dut3_channel", &dut3_channel);
	
	m_tree->Branch("tdcPhase", &tdcPhase);
	//m_tree->Branch("HVsettings", &HVsettings);
	//m_tree->Branch("DUTangle", &DUTangle);


	for(size_t i = 0; i < v_evtInfo_sorted.size(); ++i){
		
		run = v_evtInfo_sorted.at(i).run_;
		event = v_evtInfo_sorted.at(i).event_;
		lumiSection = v_evtInfo_sorted.at(i).lumiSection_;
		unixtime = v_evtInfo_sorted.at(i).unixtime_;
		time = v_evtInfo_sorted.at(i).time_;
		//dt = v_evtInfo_sorted.at(i).dt_;
	
		dut0_row = v_evtInfo_sorted.at(i).dut0_row_;
		dut1_row = v_evtInfo_sorted.at(i).dut1_row_;
		dut2_row = v_evtInfo_sorted.at(i).dut2_row_;
		dut3_row = v_evtInfo_sorted.at(i).dut3_row_;
	
		dut0_channel = v_evtInfo_sorted.at(i).dut0_channel_;
		dut1_channel = v_evtInfo_sorted.at(i).dut1_channel_;
		dut2_channel = v_evtInfo_sorted.at(i).dut2_channel_;
		dut3_channel = v_evtInfo_sorted.at(i).dut3_channel_;
	
		tdcPhase = v_evtInfo_sorted.at(i).tdcPhase_;
		//HVsettings = v_evtInfo_sorted.at(i).HVsettings_;
		//DUTangle = v_evtInfo_sorted.at(i).DUTangle_;

		m_tree->Fill();

	}
	
	m_output_file->cd();
	m_tree->Write();
	m_output_file->Close();
	
}

//define this as a plug-in
DEFINE_FWK_MODULE(EdmToNtupleNoMask);

