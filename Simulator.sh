#!/bin/bash
declare -a limits
display_help() {
    echo "Usage: ./Simulator.sh [options] <lower limit of #terminals> <upper limit of #terminals>"
    echo "Options:"
    echo "  -h : Display this help message"
    echo "  -s : Enter seed value for random number generator"
    echo "  -n : Number of Test Cases to Run"
    echo -e "  -n : Number of Test Cases to Run\n"

    # Add more help information for other options if needed
}
if [[ $1 == "-h" ]]; then
    display_help
    exit 0
fi
algo="fgc"
in_file="."

while getopts ":a:n:s:i:" opt; do
  case $opt in
    s|seed)
      seed=$OPTARG
      ;;
    n|iterstions)
      iterations=$OPTARG
      ;;
    a|algo)
      algo=$OPTARG
      ;;
    i|input)
      in_file=$OPTARG
      ;;
    \?)
      echo "Invalid option: -$OPTARG"
      exit 1
      ;;
    :)
      echo "Option -$OPTARG requires an argument."
      exit 1
      ;;
  esac
done

shift $((OPTIND - 1))
limits=("$@")
u=${#limits[@]}
nterms=()

# echo $in_file
# echo $algo
# echo $seed
# echo $iterations
# echo $limits

if [ "$in_file" != "." ]; then
    if [ ! -f "$in_file/in_${iterations}_${limits[0]}-${limits[1]}.txt" ]; then
        cat "Error! there so no such file as $in_file/in_${iterations}_${limits[0]}-${limits[1]}.txt in the specified path!"
        exit 1
    fi
else
    echo "Generating $iterations test cases..."
    for ((i=0; i<$iterations; i++)); do
        random_int=$((RANDOM % (${limits[ 1]}-${limits[0]}+1) + ${limits[0]}))  # Generate random integer within the closed interval
        # Store the random integer in the array
        nterms[$i]=$random_int
    done
    if [ ! -f "$in_file/in_${iterations}_${limits[0]}-${limits[1]}.txt" ]; then
        # Create the file
        touch "$in_file/in_${iterations}_${limits[0]}-${limits[1]}.txt"
    else
      truncate --size 0 "$in_file/in_${iterations}_${limits[0]}-${limits[1]}.txt"
    fi
    echo -e "${iterations}">> "$in_file/in_${iterations}_${limits[0]}-${limits[1]}.txt"
    i=1
    for itr in "${nterms[@]}"
    do
        echo -e "$itr">> "$in_file/in_${iterations}_${limits[0]}-${limits[1]}.txt"
        ./flute-3.1/rand-pts -r "$itr" >> "$in_file/in_${iterations}_${limits[0]}-${limits[1]}.txt"
        ((i++))
    done
fi

echo "Running on $iterations test cases with #terminals between ${limits[0]} & ${limits[1]}..."
echo -e "\nFirst 20 lines of the test cases..."
# Print the first 10 lines of in.txt
head -n 20 "$in_file/in_${iterations}_${limits[0]}-${limits[1]}.txt" && echo -e "...\n"

case "$algo" in
  *f* )
    echo "Running Flute 1st..."
    cd flute-3.1
    make flute-demo 
    output=$(time ./flute-demo ../"$in_file/in_${iterations}_${limits[0]}-${limits[1]}.txt" ../flute_out_${iterations}_${limits[0]}-${limits[1]}.txt ../flute_logs_${iterations}_${limits[0]}-${limits[1]}.txt >&1)
    echo "Total running time..."
    # Check the exit status
    if [ $? -ne 0 ]; then
        echo "Runtime error occurred."
        echo "Error message: $output"
        exit 1
    fi
    echo -e "Flute executed and files saved successfully."
    cd '../'
    ;;
esac

case "$algo" in
  *g* )
    echo -e "\nRunning Geosteiner Next..."
    cd ./geosteiner-5.3
    make my_demo  
    output=$(time ./my_demo ../$in_file/in_${iterations}_${limits[0]}-${limits[1]}.txt ../geosteiner_out_${iterations}_${limits[0]}-${limits[1]}.txt ../geosteiner_logs_${iterations}_${limits[0]}-${limits[1]}.txt >&1)
    echo "Total running time..."
    # Check the exit status
    if [ $? -ne 0 ]; then
        echo "Runtime error occurred."
        echo "Error message: $output"
        exit 1
    fi
    echo -e "Geosteiner executed and files saved successfully."
    cd '../'
    ;;
esac

case "$algo" in
  *c* )
    echo -e "\nRunning Ishan's Cockayne last..."
    g++ -w -O3 -std=c++23 "Steiner Tree/Code/RSMT.cpp" -o "Steiner Tree/Code/RSMT"
    output=$(time ./"Steiner Tree/Code/RSMT" $in_file/in_${iterations}_${limits[0]}-${limits[1]}.txt cockayne_out_${iterations}_${limits[0]}-${limits[1]}.txt cockayne_logs_${iterations}_${limits[0]}-${limits[1]}.txt >&1)
    echo "Total running time..."
    # Check the exit status
    if [ $? -ne 0 ]; then
        echo "Runtime error occurred."
        echo "Error message: $output"
        exit 1
    fi
    echo -e "Cockayne executed and files saved successfully."
    cd '../'
    ;;
esac

# No runtime error occurred
echo -e "\nExecution completed successfully."
