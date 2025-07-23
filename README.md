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

As the filter efficiency for the processes is low the number of events produced is low. Therefore, to produce events with enough statistics for analyzing them, CRAB3 is used. Two files are used and they are located at GS/ folder:

`crab_config_GS.py`

`submit_GS.py`

Before editing the files, you have to produce the "cgf" files:

J/ψ + D⁰: **Jpsi_Dzero_DPS_13TeV_GS_cfg.py** and **Jpsi_Dzero_DPS_13p6TeV_GS_cfg.py**

J/ψ + D⁺: **Jpsi_Dplus_DPS_13TeV_GS_cfg.py** and **Jpsi_Dplus_DPS_13p6TeV_GS_cfg.py**

J/ψ + Dₛ⁺: **Jpsi_Dsplus_DPS_13TeV_GS_cfg.py** and **Jpsi_Dsplus_DPS_13p6TeV_GS_cfg.py**

To produce and move them to **GS/config/**, you just need to run the sh files requiring 1 event:

J/ψ + D⁰: `. gen_step_jpsi_dzero.sh 13TeV 1`
`. gen_step_jpsi_dzero.sh 13p6TeV 1`

J/ψ + D⁺: `. gen_step_jpsi_dplus.sh 13TeV 1`
`. gen_step_jpsi_dplus.sh 13p6TeV 1`

J/ψ + Dₛ⁺: `. gen_step_jpsi_dsplus.sh 13TeV 1`
`. gen_step_jpsi_dsplus.sh 13p6TeV 1`

#### Running CRAB3

Now, go to crab_config_GS.py. In this file, you need to modify the parameters in lines 5-7:

**out_dir_base:** this is the name of your path in the tier you are producing your CRAB output (it could be UERJ, Caltech, or CERNBOX, for instance). The template considers CERNBOX.

**output_dataset:** you named it whatever you want. In the case of **mabarros** (my nicelogin) it will create a directory at /eos/user/m/mabarros/.

**storage_site:** The tier you are going to produce the files. The template considers CERNBOX.

Now, go to submit_GS.py. In this file, you need to modify the parameters in lines 6-8:

**input_file:** This is the name of the **cfg** file you created requiring 1 event. Note that the caracteres that are before **_GS** you compose the directory name. For example, if you choose **Jpsi_Dzero_DPS_13TeV_GS_cfg.py**, **Jpsi_Dzero_DPS_13TeV** will be part of the final path (see the complete path in the end of the tutorial), between the out_dir_base and the seed number(_e.g._ 250723_134055).

**njobs:** The number of jobs you want to produce.

**evtsjob:** The number of events of each job.

Finally, to run the program you need to get the grid certificate:

`voms-proxy-init --rfc --voms cms -valid 192:00`

Now, lunch the script:

`python submit_GS.py`

Each time you run CRAB3 it will produce (in this example) a directory for each seed (_e.g._ 250723_134055). In this example, you should have something like:

`/eos/user/m/mabarros/CRAB_PrivateMC_Pythia8_DPS/Jpsi_Dzero_DPS_13TeV/250723_134055/0000`




