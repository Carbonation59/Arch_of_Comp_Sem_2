#!/usr/bin/bash


        function die(){
                echo ERROR: NO FILE ARGUMENTS >&2
                exit 1
        }

        function die1(){
                echo NO SUFFIX IN THIS FILE >&2
        }

        FILE="$1"

        if (( $# == 0 )); then
                die
        fi

        while (($#>0)); do
                PLACE_OF_POINT=0;
                POINT=${FILE:$PLACE_OF_POINT:1}
                while [[ $POINT != '.' ]]; do
                        PLACE_OF_POINT=$(($PLACE_OF_POINT+1))
                        POINT=${FILE:$PLACE_OF_POINT:1}
                        if (( $PLACE_OF_POINT == ${#FILE} )); then
                                shift
                                FILE="$1"
                                die1
                                if (($#==0)); then
                                        exit 1
                                fi
                                break
                        fi
                done
                if (( $PLACE_OF_POINT == ${#FILE} )); then
                                break
                fi
                COUNT=1
                NEW_NAME=${FILE:0:$PLACE_OF_POINT}-$COUNT${FILE:$PLACE_OF_POINT:${#FILE}-$PLACE_OF_POINT}
                while [[ -e "$NEW_NAME" ]]; do
                        NEW_NAME=${FILE:0:$PLACE_OF_POINT}-$COUNT${FILE:$PLACE_OF_POINT:${#FILE}-$PLACE_OF_POINT}
                        COUNT=$(($COUNT+1))
                done
                cp "$FILE" "$NEW_NAME"
                shift
                FILE="$1"
        done
