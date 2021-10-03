pass=""
for item in $( cat pricelist | tr " " / ) ; do
    if [ "$1" = "$(dirname $item | tr / " " )" ] ; then 
        echo $(expr $(basename $item) \* $2)
        pass=y
        break
    fi
    done
[ -z $pass ] && echo "item not found"