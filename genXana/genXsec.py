import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing
import FWCore.Utilities.FileUtils as FileUtils

# Function to pick up the path for running the script
def pick_path():
    path_options = {1: 'path_jpsi_dzero_13TeV.txt',
                    2: 'path_jpsi_dzero_13p6TeV.txt',
                    3: 'path_jpsi_dplus_13TeV.txt',
                    4: 'path_jpsi_dplus_13p6TeV.txt',
                    5: 'path_jpsi_dsplus_13TeV.txt',
                    6: 'path_jpsi_dsplus_13p6TeV.txt'}

    print("Paths available:")
    for number, pt in path_options.items():
        print(f"{number}:{pt}")

    # Select the path
    try:
        path = int(input("\nEnter the number of the desired path in the list above:").strip())
        if path not in path_options:
            raise ValueError("Invalid number.")
    except ValueError as e:
        print(f"Error: {e}. Please enter a valid number from the list.")
    else:
    # Get the configuraton name from the selected number
        active_path = path_options[path]
        print(f"You selected: {active_path}")
        return(active_path)

options = VarParsing ('analysis')
options.parseArguments()
process = cms.Process('XSec')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents)
)

process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 100000

secFiles = cms.untracked.vstring()
mylist = FileUtils.loadListFromFile(pick_path()) 
process.source = cms.Source ("PoolSource",
    fileNames = cms.untracked.vstring(*mylist),
    secondaryFileNames = secFiles)
process.xsec = cms.EDAnalyzer("GenXSecAnalyzer")

process.ana = cms.Path(process.xsec)
process.schedule = cms.Schedule(process.ana)
    