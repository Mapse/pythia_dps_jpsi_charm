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

To see the list of particles you have to provide the **.root** files created in the end of the simulation. For this, you should create a **.txt** file for each particle channel that points to the **.root** created. The main work directory for this step is called PartDrawer. There you can see the directories:

**jpsi_d0:** contains the **.txt** files for that points to the **.root** files -> files_path_jpsi_d0_13TeV.txt and files_path_jpsi_d0_13p6TeV.txt

**jpsi_dplus:** contains the **.txt** files for that points to the **.root** files -> files_path_jpsi_dplus_13TeV.txt and files_path_jpsi_dplus_13p6TeV.txt

**jpsi_dsplus:** contains the **.txt** files for that points to the **.root** files -> files_path_jpsi_dsplus_13TeV.txt and files_path_jpsi_dsplus_13p6TeV.txt

**test:** contains the code for producint he particle list -> Config.py

If you open **files_path_jpsi_d0_13TeV.txt** you will see that the correct syntax to point to the root file is (note that the path is accessible via afs! it means that your files are in a different place, like a T2/T3 grid, you have to use XrootD to get them!):

`file:/eos/user/m/mabarros/CRAB_PrivateMC_Pythia8_DPS/Jpsi_Dzero_DPS_13TeV/250723_134055/0000/Jpsi_Dzero_DPS_13TeV_100.root`

To run the particle list, you do:

### J/ψ + D⁰

`cmsRun test/Config.py nevents=1 channel=Jpsi_D0 energy=13TeV`

`cmsRun test/Config.py nevents=1 channel=Jpsi_D0 energy=13p6TeV`

### J/ψ + D⁺

`cmsRun test/Config.py nevents=1 channel=Jpsi_Dplus energy=13TeV`

`cmsRun test/Config.py nevents=1 channel=Jpsi_Dplus energy=13p6TeV`

### J/ψ + Dₛ⁺

`cmsRun test/Config.py nevents=1 channel=Jpsi_Dsplus energy=13TeV`

`cmsRun test/Config.py nevents=1 channel=Jpsi_Dsplus energy=13p6TeV`

In the example above you will produce the list for the first event, because nevents=1. If you want to see more events, you simply put more events. 
As the code is processed, you should see an output similar to this one:

<img width="1817" height="395" alt="image" src="https://github.com/user-attachments/assets/7856c49d-9554-4c03-b955-8f617b81ba8a" />

## Running events with CRAB

As the filter efficiency for the processes is low the number of events produced is low. Therefore, to produce events with enough statistics for analyzing them, CRAB3 is used. Two files are used and they are located at GS/ folder:

`crab_config_GS.py`

`submit_GS.py`

Before editing the files, you have to produce the "cgf" files:

J/ψ + D⁰: **Jpsi_Dzero_DPS_13TeV_GS_cfg.py** and **Jpsi_Dzero_DPS_13p6TeV_GS_cfg.py**

J/ψ + D⁺: **Jpsi_Dplus_DPS_13TeV_GS_cfg.py** and **Jpsi_Dplus_DPS_13p6TeV_GS_cfg.py**

J/ψ + Dₛ⁺: **Jpsi_Dsplus_DPS_13TeV_GS_cfg.py** and **Jpsi_Dsplus_DPS_13p6TeV_GS_cfg.py**

To produce and move them to **GS/config/**, you just need to run the sh files requiring 1 event:

J/ψ + D⁰: 

`. gen_step_jpsi_dzero.sh 13TeV 1`

`. gen_step_jpsi_dzero.sh 13p6TeV 1`

J/ψ + D⁺: 

`. gen_step_jpsi_dplus.sh 13TeV 1`

`. gen_step_jpsi_dplus.sh 13p6TeV 1`

J/ψ + Dₛ⁺:

`. gen_step_jpsi_dsplus.sh 13TeV 1`

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

## Getting the cross-sections

Once the CRAB jobs are finished and you have enough statistics you can obtain the cross-sections for each generated process. Go to **/genXana**
directory. The first thing to do is to create a **.txt** file that points to the files. Note that the text files must be one of the following:

`path_jpsi_dzero_13TeV.txt`
`path_jpsi_dzero_13p6TeV.txt`
`path_jpsi_dplus_13TeV.txt`
`path_jpsi_dplus_13p6TeV.txt`
`path_jpsi_dsplus_13TeV.txt`
`path_jpsi_dsplus_13p6TeV.txt`

As an example, to create produce the text file, you can do:

`voms-proxy-init --rfc --voms cms -valid 192:00`

`xrdfs eosuser.cern.ch ls -u /eos/user/m/mabarros/CRAB_PrivateMC_Pythia8_DPS/Jpsi_Dzero_DPS_13TeV/250723_134055/0000 > path_jpsi_dzero_13TeV.txt`

Once you have your required path, run the main script:

`cmsRun genXsec.py`

It will ask for the path, just choose your option and wait until it processes. In the end, you should see something like this:

<img width="932" height="179" alt="image" src="https://github.com/user-attachments/assets/c9aac597-c10d-4186-ab0d-d1deec90ed7c" />

The important values are:

**Filter efficiency (event-level)= (42937) / (2.991e+08) = 1.436e-04 +- 6.927e-07    [TO BE USED IN MCM]** -> the filter efficiency for your events
**After filter: final cross section = 1.747e+00 +- 8.434e-03 pb** -> the wanted cross-section (in this case, the DPS cross-section for J/ψ + D⁰)

## Getting an analyzer to skim the data

### Center-of-mass energy: 13 TeV

Go to *GenLevel13TeV/Genplots13TeV*. The first thing to do is to create a *.txt* file that contains the paths that points to the files. Again, you need grid credentials:

`voms-proxy-init --rfc --voms cms -valid 192:00`

Now, edit the file *get_path.sh*:

The default path is
`/eos/user/m/mabarros/CRAB_PrivateMC_Pythia8_DPS/Jpsi_Dzero_DPS_13TeV/250723_134055/0000`

Change the path according to your needs. Now, choose an appropriate file name (the default is test_file.txt) and do:

`source get_path.sh`

With the text file created, you need to call the *genlevel_13TeV.py* script. This is a configuration file used in the CMSSW enviroment to run the *.cc* files that are in the plugins directory: GenLevelJpsiDzero13TeV.cc, GenLevelJpsiDplus13TeV.cc, GenLevelJpsiDsplus13TeV.cc (I suggest you take a look at them as they contain the analysis code itself.) Before running *genlevel_13TeV.py* script, you need to provide the arguments:

**nevents:** number of events you want to produce

**channel:** particle channel you want to process

**path:** the text file created with get_path.sh

Now, just do (please, be sure that scram b was used to compile the *.cc* files that are in the plugins directory!):

`cmsenv`

J/ψ + D⁰: `cmsRun test/genlevel_13TeV.py nevents=1 channel=GenLevelJpsiDzero13TeV path=test_file.txt`

J/ψ + D⁺: `cmsRun test/genlevel_13TeV.py nevents=1 channel=GenLevelJpsiDplus13TeV path=test_file.txt`

J/ψ + Dₛ⁺: `cmsRun test/genlevel_13TeV.py nevents=1 channel=GenLevelJpsiDsplus13TeV path=test_file.txt`

With these commands you create root files with the following names:

**control_plots_jpsidzero_13TeV.root**

**control_plots_Jpsidplus_13TeV.root**

**control_plots_Jpsidsplus_13TeV.root**

These files will be used in the section _producing the plots_.

### Center-of-mass energy: 13.6 TeV

The steps are the same as in the 13 TeV step. The difference is that the directory is *GenLevel13TeV/Genplots13TeV*. The final commands to run the scripts are: 

J/ψ + D⁰: `cmsRun test/genlevel_13p6TeV.py nevents=1 channel=GenLevelJpsiDzero13p6TeV path=test_file.txt`

J/ψ + D⁺: `cmsRun test/genlevel_13p6TeV.py nevents=1 channel=GenLevelJpsiDplus13p6TeV path=test_file.txt`

J/ψ + Dₛ⁺: `cmsRun test/genlevel_13p6TeV.py nevents=1 channel=GenLevelJpsiDsplus13p6TeV path=test_file.txt`

With these commands you create root files with the following names:

**control_plots_jpsidzero_13p6TeV.root**

**control_plots_Jpsidplus_13p6TeV.root**

**control_plots_Jpsidsplus_13p6TeV.root**

These files will be used in the next section

## Producing the plots

TBD


