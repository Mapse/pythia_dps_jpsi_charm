
import FWCore.ParameterSet.Config as cms
process = cms.Process("GENLevelDump")

import FWCore.Utilities.FileUtils as FileUtils

from FWCore.ParameterSet.VarParsing import VarParsing

## Parsing arguments

options = VarParsing('analysis')

# Number of events
options.register ('nevents',
				  '',
				  VarParsing.multiplicity.singleton,
				  VarParsing.varType.int,
				  "number of events")

# Particle channel
options.register ('channel',
				  '',
				  VarParsing.multiplicity.singleton,
				  VarParsing.varType.string,
				  "Channel Chosen")

# file with paths
options.register ('path',
				  '',
				  VarParsing.multiplicity.singleton,
				  VarParsing.varType.string,
				  "Path to root files")

options.parseArguments()

print(f"Number of events to process: {options.nevents}")

## 2017 geometry 
## Phase 2
#from Configuration.Eras.Era_Phase2C8_timing_layer_bar_cff import Phase2C8_timing_layer_bar
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')

## Global tag for 10_6 phase2 mc
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '106X_upgrade2023_realistic_v2', '')

process.load("FWCore.MessageService.MessageLogger_cfi")
# Suppress unnecessary output
process.MessageLogger.cerr.FwkReport.reportEvery = 10000  # Only report every millionth event, essentially never
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(int(options.nevents)))

# File source (local files)
""" mylist = FileUtils.loadListFromFile('mylist.txt') 
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(*mylist)

) """

## For CRAB generation
# Configure the source with the list of files from DAS 
""" process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    
    #[line.strip() for line in open("test_file.txt").readlines()]
     
     )) """

## For tests 
# Configure the source with the list of files from DAS 
with open(options.path) as f:
    file_list = [line.strip() for line in f.readlines()]

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(*file_list)
)

process.genlevel = cms.EDAnalyzer(options.channel)

#process.TFileService = cms.Service("TFileService",
#	fileName = cms.string("peak_study.root"),
#	closeFileFast = cms.untracked.bool(True))

process.p = cms.Path(process.genlevel)