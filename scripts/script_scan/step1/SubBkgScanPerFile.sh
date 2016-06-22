#!/bin/bash

if [[ ! -d $MPAF/cfg/tmpFiles ]]; then
    mkdir -p $MPAF/cfg/tmpFiles
fi


#all
#80X
#DATASETS=("GGHZZ4L" "VHToNonbb" "WWZ" "WZZ" "ZZZ" "TTTT" "tZq_ll" "ZZTo4L" "WGToLNuG" "ZGTo2LG" "TTGJets" "TGJets" "TTWToLNu" "TTZToLLNuNu" "TTHnobb_pow" "TTLLJets_m1to10" "WZTo3LNu" "DYJetsToLL_M50" "DYJetsToLL_M10to50" "TTJets" "WJetsToLNu" "T_tWch" "TToLeptons_sch" "TBar_tWch" "DoubleEG_Run2016B_PromptReco_v2_runs_273150_274443" "DoubleMuon_Run2016B_PromptReco_v2_runs_273150_274443" "MuonEG_Run2016B_PromptReco_v2_runs_273150_274443" )

#76X
#DATASETS=("GGHZZ4L" "WWZ" "WZZ" "ZZZ" "TTTT" "tZq_ll" "ZZTo4L" "WGToLNuG" "ZGTo2LG" "TTGJets" "TGJets" "TTWToLNu" "TTZToLLNuNu_LO" "TTHnobb" "TTLLJets_m1to10" "WZTo3LNu" "DYJetsToLL_M50" "DYJetsToLL_M10to50" "TTJets" "TToLeptons_sch" "TToLeptons_tch_powheg" "TBarToLeptons_tch_powheg" "TBar_tWch" "T_tWch" "WJetsToLNu" "WWTo2L2Nu" "ZZTo2L2Nu" "T1tttt_mGo1200_mChi800" "T1tttt_mGo1500_mChi100")


#all
#DIRS=( "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June9" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June10" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June10" "/pnfs/psi.ch/cms/trivcat/store/user/mmarionn/heppyTrees/809_June10" )

#skims
#80X
#DIRS=("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_14_skim80X_3LepGood" )

#76X
#DIRS=("/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" "/mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/workdir/skims/2016_06_08_skim76X_3LepGood" )

#all
#74X
DATASETS=("DoubleEG_Run2015C_Oct05_runs_254231_254914" "DoubleEG_Run2015D_Oct05_runs_256630_258158" "DoubleEG_Run2015D_PromptV4_runs_258159_260627" "DoubleMuon_Run2015C_Oct05_runs_254231_254914" "DoubleMuon_Run2015D_Oct05_runs_256630_258158" "MuonEG_Run2015C_Oct05_runs_254231_254914" "MuonEG_Run2015D_Oct05_runs_256630_258158" "MuonEG_Run2015D_PromptV4_runs_258159_260627" "GGHZZ4L" "VHToNonbb" "WWZ" "WZZ" "ZZZ" "TTTT" "tZq_ll" "WGToLNuG" "ZGTo2LG" "TTGJets" "TGJets" "TTWToLNu" "TTZToLLNuNu" "TTHnobb" "TTLLJets_m1to10" "WZTo3LNu" "T1tttt_mGo1200_mChi800" "T1tttt_mGo1500_mChi100" "T5ttttDeg_mGo1000_mStop300_mCh285_mChi280" "T6ttWW_mSbot600_mCh425_mChi50" "T6ttWW_mSbot650_mCh150_mChi50" "T5qqqqWZDeg_mGo1000_mCh315_mChi300_dilep" "T5qqqqWZDeg_mGo1000_mCh325_mChi300_dilep" "T5qqqqWZ_mGo1500_mCh800_mChi100_lep" "T5qqqqWZ_mGo1200_mCh1000_mChi800_lep")

#74X
#all
DIRS=("/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2016-01-30-09-39-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2016-01-30-09-39-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2016-01-30-09-39-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2016-01-30-09-39-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2016-01-30-09-39-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2016-01-30-09-39-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2016-01-30-09-39-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2016-01-30-09-39-00/" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00" "/pnfs/psi.ch/cms/trivcat/store/user/cheidegg/sea/11/2015-11-21-20-23-00")





N=0
echo $MPAF
for ds in ${DATASETS[@]}; do

	cp $MPAF/cfg/3l_scan.cfg $MPAF/cfg/tmpFiles/3l_scanBkg_${ds}.cfg

	dir=${DIRS[$N]}

	sed -i 's|FILE|'$ds'|' $MPAF/cfg/tmpFiles/3l_scanBkg_${ds}.cfg
	sed -i 's|PATH|'$dir'|' $MPAF/cfg/tmpFiles/3l_scanBkg_${ds}.cfg
	sed -i 's|SIMFLAG|0|' $MPAF/cfg/tmpFiles/3l_scanBkg_${ds}.cfg

    #analysis -c $MPAF/cfg/tmpFiles/3l_scanBkg_${ds}.cfg
	#qsub -q all.q -N MPAFjob -o $MPAF/workdir/logs/SUSY3L/3l_scanBkg_${ds}.out -e $MPAF/workdir/logs/SUSY3L/3l_scanBkg_${ds}.err $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/3l_scanBkg_${ds}.cfg
	qsub -q long.q -N MPAFjob $MPAF/scripts/submit.sh $MPAF/cfg/tmpFiles/3l_scanBkg_${ds}.cfg
	#bsub -q 8nh source submitLxbatch.sh $MPAF/cfg/tmpFiles/ssdlBkg_${ds}.cfg

	N=`echo $N + 1 | bc`
    #break
done



