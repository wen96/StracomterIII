#!/bin/bash

	suma=0
	for file in $(find * -type f | grep -v -e "3rdParty" -e "Box2D"); do 
		ext=${file#*.}
		if [ $ext = "cc" -o $ext = "h" ]; then
			subsuma=$(wc -l $file | cut -d ' ' -f 1)
			let suma+=$subsuma
			fName=$(echo $file | wc -m)
			let tabSize=$fName/8
			let nTabs=6-$tabSize
			if [ $(expr $fName % 8) = 0 ];then
				let nTabs+=1
			fi 
			line="$file"
			for i in `seq 1 $nTabs`; do
				line="$line\t"
			done;
			line="$line ~ $subsuma \t/ $suma"
			echo -e $line
		fi
	done
	echo $suma
