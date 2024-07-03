#!/bin/bash

let count=0;
for f in $(ls ./extratests/*.txt); do 
	./a.out <$f > ./extratests/`basename $f .txt`.output; 
done;

for f in $(ls ./extratests/*.output); do
	diff -Bw $f  ./extratests/`basename $f .output`.txt.expected > ./extratests/`basename $f .output`.diff;
done

for f in $(ls extratests/*.diff); do
	echo "========================================================";
	echo "FILE:" `basename $f .output`;
	echo "========================================================";
	if [ -s $f ]; then
		cat ./extratests/`basename $f .diff`.txt;
		echo "--------------------------------------------------------";
		cat $f
	else
		count=$((count+1));
		echo "NO ERRORS HERE!";
	fi
done

echo $count;

rm extratests/*.output
rm extratests/*.diff
