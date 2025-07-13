
#!/bin/bash

# cmssw environment
cmsenv

# Test if the arguments were provided
if [ $# -ne 2 ]; then
    echo "Usage: source gen_step_jpsi_dzero.sh <EnergyTag> <NumberOfEvents>"
    echo "Example: source gen_step_jpsi_dzero.sh 13TeV 100000"
fi

# Get energy from argument
energy=$1
# Get the number of events for gs step from argument
nevt=$2

echo "Running simulation for energy: $energy"

## Path to gs frameng
path_gs=Configuration/GenProduction/python/Jpsi_Dzero_DPS_${energy}_cfi.py

# GS cfg fragment 
py_gs=Jpsi_Dzero_DPS_${energy}_cfg.py
# For MC Gen parameters 
REPORT_NAME=Jpsi_Dzero_DPS_${energy}_report.xml

# GS root
root_gs=Jpsi_Dzero_DPS_${energy}.root

## CmsDriver for GS step

# Run 2 (13 TeV): using 2017 as base
if [[ "$energy" == "13TeV" ]]; then
  cmsDriver.py $path_gs --fileout file:$root_gs --mc --eventcontent RAWSIM --datatier GEN --conditions 106X_mc2017_realistic_v8 --beamspot Realistic25ns13TeVEarly2017Collision --step GEN --customise Configuration/DataProcessing/Utils.addMonitoring --geometry DB:Extended --era Run2_2017 --python_filename $py_gs -n $nevt --no_exec
  cmsRun -e -j $REPORT_NAME $py_gs
# Run 3 (13.6 TeV): uning 2022 as base
elif [[ "$energy" == "13p6TeV" ]]; then
  cmsDriver.py $path_gs --fileout file:$root_gs --mc --eventcontent RAWSIM --datatier GEN --conditions 124X_mcRun3_2022_realistic_v12 --beamspot Realistic25ns13p6TeVEarly2022Collision --step GEN --customise Configuration/DataProcessing/Utils.addMonitoring --geometry DB:Extended --era Run3 --python_filename $py_gs -n $nevt --no_exec
  cmsRun -e -j $REPORT_NAME $py_gs
else
  echo "Unknown energy tag!"
fi
