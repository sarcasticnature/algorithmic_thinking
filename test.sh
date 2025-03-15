#!/bin/bash

RED="\e[31m"
GREEN="\e[32m"
ENDCOLOR="\e[0m"

if [ "$#" -lt 3 ]; then
    printf "${RED}Usage: %s <application> <input file> <ground truth output file>\n${ENDCOLOR}" "$0"
    exit 1
fi

app="$1"
infile="$2"
truthfile="$3"

if [ ! -f "$infile" ]; then
    printf "${RED}Input file %s is missing\n${ENDCOLOR}" "$infile"
    exit 1
fi
if [ ! -f "$truthfile" ]; then
    printf "${RED}Ground truth file %s is missing\n${ENDCOLOR}" "$truthfile"
    exit 1
fi

outfile=$(mktemp)
timefile=$(mktemp)

/usr/bin/time -f "%e" "$app" "$infile" 2> "$timefile" > "$outfile" || {
    printf "${RED}Application %s failed with exit code %d\n${ENDCOLOR}" "$app" "$?"
    exit 1
}

delta=$(diff -y -W 80 "$truthfile" "$outfile")
if [ "$?" -ne 0 ]; then
    printf "${RED}Application %s failed to produce the correct output; diff is:\n%s\n${ENDCOLOR}" \
           "$app" \
           "$delta"
    exit 1
fi

runtime=$(cat "$timefile")
timely=$(echo "$4>$runtime" | bc -l)
if [ ! -z "$4" ] && [ "$timely" -eq 0 ]; then
    printf "${RED}Application %s took longer than %f to run; actual time is %f\n${ENDCOLOR}" \
            "$app" \
            "$4" \
            "$runtime"
    exit 1
fi

rm "$outfile"
rm "$timefile"
printf "${GREEN}Test of %s with input %s succeeded in %f seconds\n${ENDCOLOR}" "$app" "$infile" "$runtime"

exit 0
