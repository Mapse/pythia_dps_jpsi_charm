import FWCore.ParameterSet.Config as cms
# Include varParsing
from FWCore.ParameterSet.VarParsing import VarParsing

process = cms.Process("GENLevelDump")
import FWCore.Utilities.FileUtils as FileUtils

## Parsing arguments

options = VarParsing('analysis')

# Number of events
options.register ('nevents',
				  '',
				  VarParsing.multiplicity.singleton,
				  VarParsing.varType.string,
				  "number of events")

# Particle channel
options.register ('channel',
				  '',
				  VarParsing.multiplicity.singleton,
				  VarParsing.varType.string,
				  "Channel Chosen")

# Energy (13TeV or 13p6TeV)
options.register ('energy',
				  '',
				  VarParsing.multiplicity.singleton,
				  VarParsing.varType.string,
				  "Energy Chosen")

options.parseArguments()

# Number of events
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(int(options.nevents)) )

## Choose the right channel as well as the energy to draw the particle list.

channel = options.channel

# Jpsi + D0
if channel == 'Jpsi_D0':
  # 13 TeV
  if options.energy == '13TeV':
    path = 'jpsi_d0/files_path_jpsi_d0_13TeV.txt'
    print('-------------- Particle List for Jpsi + D0 fragment at 13 TeV --------------')
  # 13.6 TeV
  elif options.energy == '13TeV':
    path = 'jpsi_d0/files_path_jpsi_d0_13p6TeV.txt'
    print('-------------- Particle List for Jpsi + D0 fragment at 13.6 TeV --------------')
  else:
    path = ''
    print("Please, choose the available energies: 13TeV and 13p6TeV")

# Jpsi + D+
elif channel == 'Jpsi_Dplus':
  # 13 TeV
  if options.energy == '13TeV':
    path = 'jpsi_dplus/files_path_jpsi_dplus_13TeV.txt'
    print('-------------- Particle List for Jpsi + Dplus fragment at 13 TeV --------------')
  # 13.6 TeV
  elif options.energy == '13TeV':
    path = 'jpsi_dplus/files_path_jpsi_dplus_13p6TeV.txt'
    print('-------------- Particle List for Jpsi + Dplus fragment at 13.6 TeV --------------')
  else:
    path = ''
    print("Please, choose the available energies: 13TeV and 13p6TeV")

# Jpsi + Ds+
elif channel == 'Jpsi_Dsplus':
  # 13 TeV
  if options.energy == '13TeV':
    path = 'jpsi_dsplus/files_path_jpsi_dsplus_13TeV.txt'
    print('-------------- Particle List for Jpsi + Dsplus fragment at 13 TeV --------------')
  # 13.6 TeV
  elif options.energy == '13TeV':
    path = 'jpsi_dsplus/files_path_jpsi_dsplus_13p6TeV.txt'
    print('-------------- Particle List for Jpsi + Dsplus fragment at 13.6 TeV --------------')
  else:
    path = ''
    print("Please, choose the available energies: 13TeV and 13p6TeV")

else:
  channel = ''
  print("Please, choose the available channels: Jpsi_D0, Jpsi_Dplus, Jpsi_Dsplus")

# File source
if path != '' and  channel != '':
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

  # Path and endpath to run the producer and output modules
  process.p =  cms.Path(process.printTree) #process.genlevel+

