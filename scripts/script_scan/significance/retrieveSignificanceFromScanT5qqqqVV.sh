#!/bin/bash

echo -n "" > Significance_T5qqqqVV_scan.txt

mydir=/mnt/t3nfs01/data01/shome/jhoss/logs

for i in `ls $mydir/*.log`; do

spl=`echo $i | tr '_' ' '`

sig="T5qqqqVV"
m1=`echo $spl | awk '{print $4}'`
m1=${m1#m}
m2=`echo $spl | awk '{print $5}'`
m2=${m2%.txt.log}
m2=${m2#m}

#echo $m1
#echo $m2

signif=`grep "Significance"    $i | awk '{print $2}'`
pval=`grep "p-value"    $i | awk '{print $3}'`

pval=${pval%)}
#echo $signif
#echo $pval

#$sig"\t"
if [[ -n "$signif" ]]; then
    echo -e $m1"\t"$m2"\t"$signif"\t"$pval >> Significance_T5qqqqVV_scan.txt
fi
#break


done
