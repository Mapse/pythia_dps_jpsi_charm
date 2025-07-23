import os, subprocess, sys
import datetime
today = datetime.date.today()

############################################################ To edit ############################################################
input_file = "Jpsi_Dzero_DPS_13TeV_GS_cfg.py"
njobs = 1000 # Change for the wanted number of jobs 10000
evtsjob = 300000 # Change for the wanted number of evts per job 1200000
############################################################ End editing ########################################################

template = "crab_config_GS"
for config in subprocess.check_output("ls config/", shell=True).decode("utf-8").splitlines(): # 
    if not config.endswith(input_file): # Put only .py for all files
        continue
    dataset = config[0: config.find("_GS")]
    with open(template + ".py", 'r') as f:
        new_file = f.read().replace("DATASET", dataset)
        new_file = new_file.replace("DATE", today.strftime("%d-%m-%Y"))
        new_file = new_file.replace("CONFIG", config)
        new_file = new_file.replace("EVENTSJOB", str(evtsjob))
        new_file = new_file.replace("NJOBS", str(njobs))

        with open(template + "_" + dataset + ".py", 'w') as nf:
            nf.write(new_file)
    os.system("crab submit -c " + template + "_" + dataset + ".py")


