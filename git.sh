#!/bin/bash
echo "Modifications éffectuées:"
dif=$(git diff)
echo $dif
if [ "$dif" = "" ];then
	echo "Aucune modification"
else
	if [ "$# -eq 0" ];then
		git add *
	else
		git add $*
	fi
	msg="auto commit by "$USER
	echo "Message ? (y/n):"
	read choix
	if [ "$choix" = "y" ];then
		echo "Entrer message :"
		read msg
	fi
	git pull
	git commit -m  "$msg"
	git push
fi
