#!/bin/bash


# Check if a filename argument was provided.
if [ -z "$1" ]; then
    echo "Usage: $0 <filename_without_extension>"
    exit 1
fi


./maincode "$1.city" 

echo "Generated $1.satinput from $1.city."