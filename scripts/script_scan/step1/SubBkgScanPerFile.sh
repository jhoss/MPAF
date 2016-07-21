#!/bin/bash

if [[ ! -d $MPAF/cfg/tmpFiles ]]; then
    mkdir -p $MPAF/cfg/tmpFiles
fi


#all
#80X
#DATASETS=("GGHZZ4L" "VHToNonbb" "WWW" "WWZ" "WZZ" "ZZZ" "TTTT" "tZq_ll" "ZZTo4L" "WGToLNuG" "ZGTo2LG" "TTGJets" "TGJets" "TTWToLNu" "TTZToLLNuNu" "TTHnobb_pow" "TTLLJets_m1to10" "WZTo3LNu" "DYJetsToLL_M50" "DYJetsToLL_M10to50" "TTJets" "WJetsToLNu" "T_tWch" "TToLeptons_sch" "TBar_tWch" "TTZ_LO" "TTW_LO" "DoubleEG_Run2016B_PromptReco_v2_runs_273150_275125" "DoubleMuon_Run2016B_PromptReco_v2_runs_273150_275125" "MuonEG_Run2016B_PromptReco_v2_runs_273150_275125"  )
#skims
##80X
#DIRS=( "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/SUSY3L/skim80X_3LepGood_110715" )

#data
DATASETS=( "DoubleEG_Run2016B_PromptReco_v2_runs_273150_275125" "DoubleEG_Run2016B_PromptReco_v2_runs_275126_275783" "DoubleEG_Run2016C_PromptReco_v2_runs_271350_275783" "DoubleMuon_Run2016B_PromptReco_v2_runs_273150_275125" "DoubleMuon_Run2016B_PromptReco_v2_runs_275126_275783" "DoubleMuon_Run2016C_PromptReco_v2_runs_271350_275783" "MuonEG_Run2016B_PromptReco_v2_runs_273150_275125" "MuonEG_Run2016B_PromptReco_v2_runs_275126_275783" "MuonEG_Run2016C_PromptReco_v2_runs_271350_275783" )

DIRS=( "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/8011_July5" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/8011_July5" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/8011_July5" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/8011_July5" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/8011_July5" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/8011_July5" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/8011_July5" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/8011_July5" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/8011_July5" )


N=0
echo $MPAF
for ds in ${DATASETS[@]}; do

	cp $MPAF/cfg/3l_scan.cfg $MPAF/cfg/tmpFiles/3l_v2_scanBkg_${ds}.cfg

	dir=${DIRS[$N]}
	#dir="/mnt/t3nfs01/data01/shome/mmarionn/dev/MPAF_Jan/workdir/skims/skim80X_3LepGood_110715"

	sed -i 's|FILE|'$ds'|' $MPAF/cfg/tmpFiles/3l_v2_scanBkg_${ds}.cfg
	sed -i 's|PATH|'$dir'|' $MPAF/cfg/tmpFiles/3l_v2_scanBkg_${ds}.cfg
	sed -i 's|SIMFLAG|0|' $MPAF/cfg/tmpFiles/3l_v2_scanBkg_${ds}.cfg

    #analysis -c $MPAF/cfg/tmpFiles/3l_scanBkg_${ds}.cfg
	#qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/SUSY3L/3l_scanBkg_${ds}.out -e $MPAF/workdir/logs/SUSY3L/3l_scanBkg_${ds}.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/3l_scanBkg_${ds}.cfg
	qsub -q long.q -N MPAFjob${ds} $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/3l_v2_scanBkg_${ds}.cfg -o $MPAF/workdir/logs/SUSY3L/3l_v2_scanBkg_${ds}.out -e $MPAF/workdir/logs/SUSY3L/3l_v2_scanBkg_${ds}.err
	#bsub -q 8nh source submitLxbatch.sh $MPAF/cfg/tmpFiles/ssdlBkg_${ds}.cfg

	N=`echo $N + 1 | bc`
    #break
done



