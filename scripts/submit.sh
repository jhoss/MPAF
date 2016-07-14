#!/bin/bash
source /mnt/t3nfs01/data01/swshare/ROOT/root_v5.34.18_slc6_amd64/bin/thisroot.sh
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib64/dcap

#cd /mnt/t3nfs01/data01/shome/mmarionn/dev/MPAF_Jan 
cd /mnt/t3nfs01/data01/shome/jhoss/analysis/MPAF/
source setup.sh
mkdir -p /scratch/$USER/logs/

name=${1##*/}

analysis -c $1 # &> /scratch/$USER/logs/$name.out
cp /scratch/$USER/logs/$name.out $MPAF/workdir/logs/SUSY3L/
#gfal-copy  file://///scratch/$USER/logs/$1.log  srm://t3se01.psi.ch/pnfs/psi.ch/cms/trivcat/store/user/jhoss/logs/$1.log
rm /scratch/$USER/logs/$name.out



