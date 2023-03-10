#!/bin/bash

first_file_out=$1
second_file_true=$2

first_num_out=$(grep -Eo "[+-]?[0-9]+(\.[0-9]+)?" "$first_file_out")
second_num_true=$(grep -Eo "[+-]?[0-9]+(\.[0-9]+)?" "$second_file_true")

if [[ "$first_num_out" == "$second_num_true" ]]; then
    exit 0
else
    exit 1
fi