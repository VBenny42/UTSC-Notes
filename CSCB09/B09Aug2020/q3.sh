# Assuming an argument will be provided like the actual make function
filename=$(basename "$1" .tex)
# Checks if argument provided exists, then check if either pdf does not exist, 
# or if pdf exists and tex file is newer
[ -e "$1" ] && ( [ ! -e "$filename".pdf ] || ( [ -e "$filename".pdf ] && 
    [ "$1" -nt "$filename".pdf ] ) ) && pdflatex "$1"
