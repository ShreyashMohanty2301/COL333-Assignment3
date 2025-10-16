#!/bin/bash


if [ -z "$1" ]; then
    echo "Usage: $0 <filename_without_extension>"
    exit 1
fi

./generate_output "$1.satoutput" "$1.city"

echo "Generated final metro map in $1.metromap."