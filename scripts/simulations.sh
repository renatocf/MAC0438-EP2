#!/usr/bin/env bash

echo &> sequential_results
echo &> concurrent_results

for xVal in 0.78539816339744830961566075 3.141592653589793238462643 4.7123889803846898576939645; do
	for nThreads in 1 4 16 0; do
		for precision in 1000; do
			for i in 0 1 2 3 4; do 
				echo ./bin/Cosine $nThreads f $precision $xVal s;
				echo ./bin/Cosine $nThreads f $precision $xVal s &>> sequential_results.txt;
				echo &>> sequential_results;
				time ./bin/Cosine $nThreads f $precision $xVal s &>> sequential_results.txt;
				echo ; echo ;
			done
			for j in 0 1 2 3 4; do 
				echo ./bin/Cosine $nThreads m $precision $xVal d;
				echo ./bin/Cosine $nThreads m $precision $xVal d &>> concurrent_results.txt;
				echo &>> concurrent_results;
				time ./bin/Cosine $nThreads m $precision $xVal d &>> concurrent_results.txt;
				echo ; echo ;
			done
		done
	done
done