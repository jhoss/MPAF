#!/bin/bash


mydir=/mnt/t3nfs01/data01/shome/jhoss/logs/T5qqqqWZ_800_500

for dir in $mydir/*; do
    #echo $dir
    #folder=`echo $dir | tr '/' ' '`
    #echo -n "" > LimitsPerSR_T5ttttdeg.txt
    
    #for i in `ls $dir/*.log`; do

    #echo $i
    spl=`echo $dir | tr '_' ' '`
    m1=`echo $spl | awk '{print $6}'`
    m2=`echo $spl | awk '{print $7}'`
    sr=`echo $spl | awk '{print $8}'`
    m1=${m1#"m"}
    m2=${m2#"m"}
    sr=${sr%".log"}
    sr=${sr#"SR"}

    echo $m1 " " $m2 " " $sr

    obs=`grep "Observed"    $dir | awk '{print $5}'`
    exp=`grep "Expected 50" $dir | awk '{print $5}'`
    d1s=`grep "Expected 16" $dir | awk '{print $5}'`
    u1s=`grep "Expected 84" $dir | awk '{print $5}'`
    u2s=`grep "Expected 97" $dir | awk '{print $5}'`
    d2s=`grep "Expected  2" $dir | awk '{print $5}'`

    #$sig"\t"
    #if [[ -n "$exp" ]]; then
    echo -e $sr"\t"$m1"\t"$m2"\t"$obs"\t"$exp"\t"$d1s"\t"$u1s>> LimitsPerSR_T5qqqqWZ_800_500.txt
    echo $m1 " " $m2
    #fi
    #break

done


