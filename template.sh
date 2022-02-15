#!/lib/sh

# Creates a new template file and add basic add_executable to CMakeLists.txt

set -e

highest=$(ls -r -- problem-[0-9][0-9][0-9].c | head -1 | grep -P "[0-9][0-9][0-9]" -o )
name=problem-$(printf "%03d" $(expr $highest + 1))

cat <<EOF >$name.c
#include <stdio.h>

// TODO: Not implemented

int main() {
    return 0;
}

EOF

echo "add_executable($name $name.c)" >> CMakeLists.txt
