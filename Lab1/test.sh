#! /bin/bash

echo -e "enter the user name :\c"
read usr
tuser=`who | tr -s " " | head -1 | cut -d " " -f1`
if [ "$tuser" = "$usr" ]
then
tm=`who | tr -s " " | head -1 | cut -d " " -f4`
uhr=`echo $tm | cut -d ":" -f1`
umin=`echo $tm | cut -d ":" -f2`
shr=`date "+%H"`
smin=`date "+%M"`
if [ $smin -lt $umin ]
then
shr=`expr $shr - 1`
smin=`expr $smin + 60`
fi
h=`expr $shr - $uhr`
m=`expr $smin - $umin`
echo "user name : $usr"
echo "login period : $h : $m"
else
echo "Invalid User"
fi
