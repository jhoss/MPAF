#!/bin/bash

AN=$1
folder=$2

mainFile=${MPAF}/workdir/stats/${AN}/${folder}/merged_12fb_Bkg.dat

## first merge backgrounds
python ${MPAF}/scripts/script_scan/step3/mergeBkgs.py ${mainFile} ${MPAF}/workdir/stats/${AN}/${folder}/3l_v2_scanBkg_

## merge signals and backgrounds
for i in `ls $MPAF/workdir/stats/${AN}/${folder}/3l_scanSig_*.dat`; do

    red=${i#$MPAF/workdir/stats/${AN}/${folder}/3l_scanSig_}
    echo $red
    python ${MPAF}/scripts/script_scan/step3/addSample.py $mainFile $i $MPAF/workdir/stats/${AN}/${folder}/merged_12_$red

done

### merge root files
files="vector<string> tks; tks.push_back(\"$MPAF/workdir/root/${AN}/${folder}/merged_v2_12fb_Bkg.root\");"
for i in `ls $MPAF/workdir/root/${AN}/${folder}/3l_scanSig_*.root`; do
    files=$files" tks.push_back(\"$i\");"
done

#past string to next step
echo $files



