notdigit=$(find * -not -name "[0-9][0-9]*")

for file in $(echo "$notdigit"); do
    grep -w ".*q.*" "$file" | uniq
done