#!/bin/sh
bindir=$(pwd)
cd /home/christina/Documents/M1/hai819i/TP1_code/TP1/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "xYES" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		/usr/bin/gdb -batch -command=$bindir/gdbscript --return-child-result /home/christina/Documents/M1/hai819i/TP1_code/build/TP1 
	else
		"/home/christina/Documents/M1/hai819i/TP1_code/build/TP1"  
	fi
else
	"/home/christina/Documents/M1/hai819i/TP1_code/build/TP1"  
fi
