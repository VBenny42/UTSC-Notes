# Gets all files in current directory with f plus one or more digits
files=$(find * -type f -regex "f[0-9][0-9]*")

for file in $(echo "$files"); do
    # Gets number from file after "f"
    num=$(echo "$file" | cut -d "f" -f 2)
    num=$(expr $num + 1)
    mv "$file" "f$num"
done