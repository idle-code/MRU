#!/usr/local//bin/bash
if [ "$1" ]; then
        cat "$1" | sed '
        / [aeiouwzAEIOUWZ] *$/ {
        N
        s/  *\([aeiouwzAEIOUWZ]\)\n */ \1~/g
        }' | sed 's/^ *\([aeiouwzAEIOUWZ]\)  */ \1~/g'  | sed 's/  *\([aeiouwzAEIOUWZ]\)  */ \1~/g'
else
        echo przyklad uzycia - nazwa_skryptu nazwa_pliku 
fi

