#! /bin/bash

make re && make clean

tests=("1 800 200 200" "5 800 200 200 15" "5 800 200 200 3" "4 410 200 200 15" "4 310 200 100 15" "200 60 60 60" "200 70 60 60" "4 200 205 200" "200 800 200 200 15")

function tester(){
	ARG=${tests[$1]}
	echo "TEST" $1 "->" $ARG
	./philo $ARG >> output_$1.txt 2> errors_$1.txt
	echo "=============================================================" >> output.txt
}

for ((i = 0; i < ${#tests[@]}; i++))
do
    tester $i;
	read -t 5 -n 1 key  # Read a single character within a 5-second
	if [ $? != 0 ]; then
			exit
	fi
done

rm philo

: '
TEST 0 -> 1 800 200 200 -> not eat and not die ?
TEST 1 -> 5 800 200 200 15 -> none should die
TEST 2 -> 5 800 200 200 3  -> none should die and stops
TEST 3 -> 4 410 200 200 15 -> none should die
TEST 4 -> 4 310 200 100 15 -> one should die ?
TEST 5 -> 200 60 60 60 -> one should die
TEST 6 -> 200 70 60 60 15-> none should die
TEST 7 -> 4 200 205 200 -> one should die
TEST 8 -> 200 800 200 200 15 -> none should die
'