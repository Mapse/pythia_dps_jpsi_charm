from CRABClient.UserUtilities import config
import getpass

############################################################ To edit ############################################################
out_dir_base =  '/store/user/mabarros/'  #'/store/group/uerj/' + getpass.getuser() + '/'
output_dataset = 'CRAB_PrivateMC_Pythia8_DPS' # Comes after /store/user/mabarros/
storage_site = 'T3_CH_CERNBOX' #'T2_US_Caltech'
############################################################ End editing ########################################################

config = config()
config.General.requestName = 'GS_DATASET_DATE'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True

config.JobType.pluginName = 'PrivateMC' 
config.JobType.psetName = 'config/CONFIG'

config.Data.publication = True
config.Data.publishDBS = 'phys03'
config.Data.outputPrimaryDataset = output_dataset
config.Data.outputDatasetTag = 'DATASET' # Comes after outputPrimaryDataset
config.Data.splitting = 'EventBased' 
config.Data.unitsPerJob = EVENTSJOB # multiple of lumisPerFile
config.Data.lumisPerFile = 1000
config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.outLFNDirBase = out_dir_base

config.Site.storageSite = storage_site
