#!/bin/bash
set -e

TMPFILE=$(mktemp)

./test1 > $TMPFILE
ec=$(diff -b ${srcdir}/test1.correct $TMPFILE)
rm $TMPFILE

if [[ $ec == 1 ]]; then
	exit $ec
fi

./FindProcessByName_test
ec=$?

# 0 is tests passed OK

exit $ec
