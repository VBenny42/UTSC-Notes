sum=0
for number in $(cat /u/ajr/t) ; do
    sum=$(expr $sum + $number)
    done
echo $(expr $sum + 10)