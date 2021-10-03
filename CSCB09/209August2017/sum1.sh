sum=0

while read num; do
    sum=$(expr $sum + $num)
done
echo $sum