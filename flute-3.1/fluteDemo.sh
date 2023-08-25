#!/bin/bash
declare -a terminals
if [ $# -lt 2 ]; then
    echo -e "Please provide 1 number and solver as an argument:-\n ./fluteDemo.sh <num_terminals>"
    exit 1
fi

while getopts ":c:s:" opt; do
  case $opt in
    s)
      seed=$OPTARG
      ;;
    c)
      code=$OPTARG
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

terminals=("$@")
u=${#terminals[@]}
echo "Running $code on ${#terminals[@]} test cases..."

i=1
truncate --size 0 in.txt
echo -e "$u">> in.txt
for itr in "${terminals[@]}"
do
    echo -e "$itr">> in.txt

    ./rand-pts -r "$itr" -seed $seed>> in.txt

    ((i++))
done

# Print the first 10 lines of in.txt
head -n 20 in.txt && echo -e "...\n"

make flute-demo

echo "Total running time..."
output=$(time ./$code 2>&1)

# Check the exit status
if [ $? -ne 0 ]; then
    echo "Runtime error occurred."
    echo "Error message: $output"
    exit 1
fi

# No runtime error occurred
echo -e "\nExecution completed successfully."

echo -e "Output(wirelengths):$(cat out.txt)\n"
