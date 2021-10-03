#!/bin/sh

sand=$(grep -l "sand" *)
for file in $(echo "$sand"); do
    rm "$file"
done