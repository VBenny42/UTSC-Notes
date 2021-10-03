max=0
maxname=

while [ $# -gt 0 ]; do
    # that stat format is what works on my mac, "stat --format="%s" $1" works on mathlab
    if [ $max -le $(stat -f "%z" $1) ] ; then
        max=$(stat -f "%z" $1)
        maxname=$1
    fi
    shift
done

echo "$max $maxname"