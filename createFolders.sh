#!/bin/zsh

# Loop to create directories from Lec1 to Lec56
for i in {1..56}; do
    mkdir "Lec$i"
done
``
echo "56 lecture folders created successfully!"