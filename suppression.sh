#!/bin/bash

# Check if exactly two arguments are provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <x> <y>"
    exit 1
fi

x=$1
y=$2

# Check if x is either 0 or 1
if [ "$x" -eq 0 ]; then
    echo "Running suppression_patricia.c with arguument $y"
    # ./suppression_patricia "$y"
elif [ "$x" -eq 1 ]; then
    echo "Running suppression_trie.c with argument $y"
    ./suppression_trie "$y"
else
    echo "Error: x must be 0 or 1"
    exit 1
fi