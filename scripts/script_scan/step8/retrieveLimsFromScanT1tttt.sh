#!/bin/bash

echo -n "" > Limits_T1tttt_scan.txt

mydir=/shome/jhoss/logs

for i in `ls $mydir/*.log`; do

spl=`echo $i | tr '_' ' '`

sig="T1tttt"
m1=`echo $spl | awk '{print $2}'`
m1=${m1#T1tttt}
m2=`echo $spl | awk '{print $3}'`
m2=${m2%.txt.log}

#echo $m1
#echo $m2

#echo $m2

obs=`grep "Observed"    $i | awk '{print $5}'`
exp=`grep "Expected 50" $i | awk '{print $5}'`
d1s=`grep "Expected 16" $i | awk '{print $5}'`
u1s=`grep "Expected 84" $i | awk '{print $5}'`
u2s=`grep "Expected 97" $i | awk '{print $5}'`
d2s=`grep "Expected  2" $i | awk '{print $5}'`

#$sig"\t"
if [[ -n "$exp" ]]; then
    echo -e $m1"\t"$m2"\t"$obs"\t"$exp"\t"$d1s"\t"$u1s"\t"$d2s"\t"$u2s >> Limits_T1tttt_scan.txt
fi



done