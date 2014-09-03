import FWCore.ParameterSet.Config as cms

process = cms.Process("EdmToNtupleNoMask")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 10000
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))


inFile = 'USC.00000478.0001.A.storageManager.00.0000.root'

process.source = cms.Source("PoolSource",
	fileNames = cms.untracked.vstring( 'file:///nfs/dust/cms/user/harbali/data/%s'%inFile)
			          #'file:///nfs/dust/cms/user/harbali/data/USC.00000542.0001.A.storageManager.00.0000.root',
			          #'file:///nfs/dust/cms/user/harbali/data/USC.00000543.0001.A.storageManager.00.0000.root',
				  #'file:///nfs/dust/cms/user/harbali/data/USC.00000544.0001.A.storageManager.00.0000.root'
			              )

#mylist = FileUtils.loadListFromFile ('runInputList.txt') 
#readFiles = cms.untracked.vstring( *mylist)

#import FWCore.Utilities.FileUtils as FileUtils
#readFiles = cms.untracked.vstring( FileUtils.loadListFromFile ('///nfs/dust/cms/user/harbali/data/runInputList.txt') )
#process.source = cms.Source ("PoolSource",fileNames = readFiles)

outFile = "RAW_%s"%(inFile)

process.simple = cms.EDAnalyzer('EdmToNtupleNoMask'
    , output_file_name = cms.untracked.string(outFile)
		   # 'file:///nfs/dust/cms/user/harbali/data/output.root')
)
process.p = cms.Path(process.simple)

