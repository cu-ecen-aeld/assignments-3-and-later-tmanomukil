#!/bin/bash

# Check for required arguments
if [ $# -ne 2 ]; then
  echo "Error: Please provide both file path and string to write."
  echo "Usage: $0 <file path> <string to write>"
  exit 1
fi

# Define variables
writefile="$1"
writestr="$2"

# Create directories if they don't exist
mkdir -p "$(dirname "$writefile")"

# Write to the file
if ! echo "$writestr" > "$writefile"; then
  echo "Error: Could not write to file '$writefile'."
  exit 1
fi

# Success message
echo "Successfully wrote '$writestr' to '$writefile'."

exit 0