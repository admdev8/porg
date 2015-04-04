#!/bin/bash
set -e

TMPFILE=$(mktemp)

./test1 > $TMPFILE
ec=$(diff -b ${srcdir}/test1.correct $TMPFILE)
rm $TMPFILE

exit $ec
