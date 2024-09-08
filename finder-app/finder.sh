#!/bin/bash

# Check if the number of arguments is correct
if [ "$#" -ne 2 ]; then
  echo "Error: You must specify exactly two arguments: a directory and a search string."
  exit 1
fi

# Assign arguments to variables
filesdir=$1
searchstr=$2

# Check if the provided directory exists and is a directory
if [ ! -d "$filesdir" ]; then
  echo "Error: The specified path '$filesdir' is not a directory or does not exist."
  exit 1
fi

# Initialize counters
file_count=0
matching_lines_count=0

# Find all files in the directory and subdirectories
while IFS= read -r -d '' file; do
  if [ -f "$file" ]; then
    # Increment file count
    ((file_count++))
    
    # Search for matching lines in the file
    while IFS= read -r line; do
      if [[ "$line" == *"$searchstr"* ]]; then
        ((matching_lines_count++))
      fi
    done < "$file"
  fi
done < <(find "$filesdir" -type f -print0)

# Print the results
echo "The number of files are $file_count and the number of matching lines are $matching_lines_count"
