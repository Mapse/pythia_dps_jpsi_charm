# Pythia double parton scattering predictions: J/ψ+D⁰, J/ψ+D⁺, and J/ψ+Ds⁺ - 13 and 13.6 TeV

For running the Double Parton Scattering (DPS) simulations, Pythia 8 is used for particle hadronization and EvtGen for particle decays. The fragment files are located at **Configuration/GenProduction/python/**. Is it worth mentioning that all fragments includes J/ψ + prompt and non-prompt charmed meson productions, _i.e._ it includes J/ψ+ $c\bar{c}$ and J/ψ+ $b\bar{b}$ modes.
Their names and characterists are:

### J/ψ + D⁰
- **`Jpsi_Dzero_DPS_13TeV_cfi.py`**: DPS predictions for J/ψ + D⁰ at 13 TeV. 
- **`Jpsi_Dzero_DPS_13p6TeV_cfi.py`**: DPS predictions for J/ψ + D⁰ at 13.6 TeV. 

### J/ψ + D⁺
- **`Jpsi_Dplus_DPS_13TeV_cfi.py`**: DPS predictions for J/ψ + D⁺ at 13 TeV. 
- **`Jpsi_Dplus_DPS_13p6TeV_cfi.py`**: DPS predictions for J/ψ + D⁺ at 13.6 TeV. 

### J/ψ + Dₛ⁺
- **`Jpsi_Dsplus_DPS_13TeV_cfi.py`**: DPS predictions for J/ψ + Dₛ⁺ at 13 TeV. 
- **`Jpsi_Dsplus_DPS_13p6TeV_cfi.py`**: DPS predictions for J/ψ + Dₛ⁺ at 13.6 TeV.

First you must prepare your environment:

```
cmsrel CMSSW_13_0_13
cd CMSSW_13_0_13/src

git clone git@github.com:Mapse/pythia_dps_jpsi_charm.git .

cmsenv
scram b
```

To run the fragments to produce the events you have to use the **sh** (bash script) files. Below, the
syntax is:

`. bash_script.sh <CenterMassEnergy> <NumberOfEvents>`

For each particle channel, the commands are:

### J/ψ + D⁰
`. gen_step_jpsi_dzero.sh 13TeV 100000`: center-of-mass energy of 13 TeV and 100000 events
`. gen_step_jpsi_dzero.sh 13p6TeV 100000`: center-of-mass energy of 13.6 TeV and 100000 events

### J/ψ + D⁺
`. gen_step_jpsi_dplus.sh 13TeV 100000`: center-of-mass energy of 13 TeV and 100000 events
`. gen_step_jpsi_dplus.sh 13p6TeV 100000`: center-of-mass energy of 13.6 TeV and 100000 events

### J/ψ + Dₛ⁺
`. gen_step_jpsi_dsplus.sh 13TeV 100000`: center-of-mass energy of 13 TeV and 100000 events
`. gen_step_jpsi_dsplus.sh 13p6TeV 100000`: center-of-mass energy of 13.6 TeV and 100000 events

## Printing the list of particles produced 

TODO

## Running events with CRAB

TODO

