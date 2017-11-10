#!/bin/bash
set -e

TMPFILE=$(mktemp)

./test1.exe > $TMPFILE
diff -b test1.correct $TMPFILE
rm $TMPFILE

./FindProcessByName_test.exe
