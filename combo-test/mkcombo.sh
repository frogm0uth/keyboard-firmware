#!/bin/sh 

# test

letters1="A B C D E F G"
letters2="A B C D E F G H I J K L M N"
letters3="A B C D E F G H I J K L M N O P Q"
letters4="A B C D E F G H I J K L M N O P Q R S T"
letters=$letters3
for a in $letters
do
    for b in $letters
    do
        if [[ $a < $b ]]
        then
           echo "SUBS( _COMBO_${a}${b}_, \"($a$b)\", KC_$a, KC_$b)"
        fi
    done
done

