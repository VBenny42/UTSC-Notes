cat "/u/ajr/x" | tr -c -d [:alpha:] | wc -m 
# Deletes everything that is not a letter from file, and then uses wc