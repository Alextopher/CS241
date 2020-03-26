#!/bin/sh

# Compile
gcc atob.c -g -o bin/atob
gcc jabber.c -g -o bin/jabber
gcc wocky.c -g -o bin/wocky
gcc btoa.c -g -o bin/btoa

# Run in order
./bin/atob ${1} bit.txt
./bin/jabber bit.txt zap.txt
./bin/wocky zap.txt kapow.txt
./bin/btoa kapow.txt out.txt

# Print all
<< ////
echo --${1}--
cat ${1}
echo

echo --bit-${1}--
cat bit.txt
echo

echo --zap-${1}--
cat zap.txt
echo

echo --kapow-${1}--
cat kapow.txt
echo

echo --out.txt--
cat out.txt
echo
////
