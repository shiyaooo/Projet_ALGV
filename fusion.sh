#!/bin/bash
#chmod +x fusion.sh

# Check if exactly two arguments are provided
if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <x> <y> <z>"
    exit 1
fi

x=$1
y=$2
z=$3

# Check if x is either 0 or 1
if [ "$x" -eq 0 ]; then
    echo "Running prefixe_patricia.c with argument $y"
    ./fusion_patricia "$y" "$z"
elif [ "$x" -eq 1 ]; then
    echo "Running fusion_trie.c with argument $y"
    #./fusion_trie "$y" "$z"
else
    echo "Error: x must be 0 or 1"
    exit 1
fi