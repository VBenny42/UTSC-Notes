list=
for item in $( cat pricelist | tr " " / ) ; do
    list="$list$(dirname $item | tr / " " )\n"
    done
echo $list | sort | uniq -d