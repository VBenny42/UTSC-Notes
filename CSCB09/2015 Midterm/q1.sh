inhome=
inother=

for name in $(cut -d : -f 6 /etc/passwd) ; do
    f=$(echo $name | grep '^/cmshome/')
    if [ -n "$f" ] ; then
        inhome=$(expr $inhome + 1)
    else 
        inother=$(expr $inother + 1)
    fi
done
# echo "$inhome $inother"
sum=$(expr $inhome + $inother)
echo $((100 * $inhome/$sum))