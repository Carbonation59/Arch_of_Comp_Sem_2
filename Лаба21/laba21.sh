#!/usr/bin/bash


        if(($#<1)); then
                echo "Wrong usage of $0: no arguments. Try '$0 ?' for more information." >&2
                exit 1
        fi
        syph="$1"
        numb_of_syph="${#syph}"
        if [[ "$1" == "?" ]]; then
                if(($#>1)); then
                        echo "Error: '?' should be used without any arguments" >&2
                        exit 1
                fi
                echo ""
                echo "  $0: $0 [KEY] .[SUFFIX] "
                echo ""
                echo "  Creates alternative file names for files ending with .[SUFFIX] by moving SUFFIX to the beginnig of the file names and removing the dot."
                echo "  Files' suffixes must match the suffix given."
                echo "  Input files are derived from the current directory"
                echo ""
                echo "  Keys:"
                echo "  '?' - output a usage message and exit"
                echo ""
                exit 1
        fi
        if [[ "${syph:0:1}" != "." ]]; then
                echo "Wrong suffix for $0. Try '$0 ?' for more information." >&2
                exit 1
        fi
        list="$(mktemp)"
        ls >"$list"
        number_of_arguments=$(wc -l $list| cut -f 1 -d" ")
        while(($number_of_arguments>0)); do
                number_of_arguments=$((number_of_arguments-1))
                file="$(echo "$(head -n1 "$list")")"
                numb_of_file="${#file}"
                file1="$(mktemp)"
                grep -v "^$(echo "$file")$" "$list" >"$file1"
                echo "$(cat "$file1")" >"$list"
                numb_of_file_without_syph=$((numb_of_file-numb_of_syph))
                file_without_syph="${file:0:$numb_of_file_without_syph}"
                syph_of_file="${file:$numb_of_file_without_syph:$((numb_of_file-numb_of_file_without_syph))}"
                if [[ "$syph_of_file" != "$syph" ]]; then
                        echo ""$file": Files' suffixes do not match $1. Try '$0 ?' for more information"
                else
                        syph_without_point="${syph:1:$((numb_of_syph-1))}"
                        name_of_copy="$(mktemp)"
                        echo ""$syph_without_point""$file_without_syph"" >"$name_of_copy"
                        cp "$file" "$(cat "$name_of_copy")"
                        rm "$name_of_copy"
                fi
                rm "$file1"
        done
        rm "$list"
