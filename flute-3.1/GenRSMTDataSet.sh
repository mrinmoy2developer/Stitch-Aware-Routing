if [ $# -ne 2 ]
then
    echo 'Usage sh GenRSMTDataSet.sh <Degree> <NoofRSMTsNeeded>'
else
    Degree=$1
    NoOfNets=$2
    a=0
    fname="GeneratedRSMTs/RSMT-$Degree-$NoOfNets.txt"
    while [ $a -lt $NoOfNets ]
    do
        ./rand-pts -r $Degree | ./flute-net >> $fname
        a=`expr $a + 1`
    done
    echo "The RSMTs are generated in the file $fname$"
fi
