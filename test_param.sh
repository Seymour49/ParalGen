#!/bin/sh

EXE1="./build/paralGen "
echo $EXE1
$EXE1

EXE2="./build/paralGen --uCross --freqEval --randPop --bestS --fitnessID -n 15"
echo $EXE2
$EXE2

EXE3="./build/paralGen --monoPCross --closeEval 0.2 --irandPop --randS --ageID -n 10"
echo $EXE3
$EXE3

EXE4="./build/paralGen --multiPCross 3 --freqEval --freqPop 0.3 --tournamentS 8 --ageID -n 40 -g 250"
echo $EXE4
$EXE4