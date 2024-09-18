#!/bin/sh
filesdir=$1
searchstr=$2

if [ $# -ne 2 ]; then
    echo "Illegal number of parameters" && exit 1
fi

if ! [ -d "$filesdir" ]; then
    echo "filesdir must be a directory" && exit 1 
fi

Y=$(grep -r $searchstr $filesdir | wc -l)

X=$(grep -rl $searchstr $filesdir | wc -l) 

echo "The number of files are $X and the number of matching lines are $Y"