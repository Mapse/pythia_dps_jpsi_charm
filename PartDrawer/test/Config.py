import FWCore.ParameterSet.Config as cms
# Include varParsing
from FWCore.ParameterSet.VarParsing import VarParsing

process = cms.Process("GENLevelDump")
import FWCore.Utilities.FileUtils as FileUtils

options = VarParsing('analysis')

options.register ('channel',
				  '',
				  VarParsing.multiplicity.singleton,
				  VarParsing.varType.string,
				  "Channel Chosen")

options.parseArguments()

## 2017 geometry 
#from Configuration.Eras.Era_Run2_2018_cff import Run2_2018

## Phase 2
#from Configuration.Eras.Era_Phase2C8_timing_layer_bar_cff import Phase2C8_timing_layer_bar
#process.load('Configuration.StandardSequences.GeometryRecoDB_cff')

## Global tag for 10.6 phase2 mc
#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, '102X_mc2017_realistic_v8', '')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

# Choose the right channel to draw the particle list.

if options.channel == 'Jpsi_D0':
  path = 'jpsi_d0/files_path_jpsi_d0.txt'
  print('-------------- Particle List for Jpsi + D0 fragment at 13 TeV --------------')

elif options.channel == 'Jpsi_Dplus':
  path = 'jpsi_dplus/files_path_jpsi_dplus.txt'
  print('-------------- Particle List for Jpsi + Dplus fragment at 13 TeV --------------')

elif options.channel == 'Jpsi_Dsplus':
  path = 'jpsi_dsplus/files_path_jpsi_dsplus.txt'
  print('-------------- Particle List for Jpsi + Dsplus fragment at 13 TeV --------------')

else:
  print("wrong")

# File source
mylist = FileUtils.loadListFromFile(path) 
process.source = cms.Source(
    "PoolSource",
    #fileNames  = cms.untracked.vstring(options.inputFiles),
    fileNames  = cms.untracked.vstring(*mylist),
    duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
)


## Show GenParticles
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.printTree = cms.EDAnalyzer("ParticleListDrawer",
  maxEventsToPrint = cms.untracked.int32(10),
  printVertex = cms.untracked.bool(True),
  printOnlyHardInteraction = cms.untracked.bool(False), # Print only status=3 particles. This will not work for Pythia8, which does not have any such particles.
  src = cms.InputTag("genParticles"), #genParticles
     
)


#process.genlevel = cms.EDAnalyzer('GenLevelStudies',
# src = cms.InputTag("genParticles")
#)

#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, '106X_upgrade2023_realistic_v2', '')

#process.TFileService = cms.Service("TFileService",
#	fileName = cms.string("mc_dump.root"),#
#	closeFileFast = cms.untracked.bool(True))

# Path and endpath to run the producer and output modules
process.p =  cms.Path(process.printTree) #process.genlevel+

