for file in $(ls | grep "^q") ; do
    mv "$file" "q$file"
    done