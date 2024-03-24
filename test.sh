#! /bin/bash

make re && make clean

tests=("1 800 200 200" "5 800 200 200 1" "5 800 200 200 2" "4 410 200 200 1" "4 310 200 100 1" "200 60 60 60")

function tester(){
	ARG=${tests[$1]}
	echo "TEST" $1 "->" $ARG
	./philo $ARG >> output.txt 2> errors.txt
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
