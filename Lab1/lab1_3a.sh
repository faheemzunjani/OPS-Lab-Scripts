#! /bin/bash

read inp

if [ -f $inp ] ;
then 
	echo "$inp is a file";
elif [ -d $inp ] ;
then 
	echo "$inp is a directory";
else 
	echo "$inp is neither a file nor a directory";
fi
