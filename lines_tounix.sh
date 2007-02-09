#!/bin/sh

# kill CRs
sed -e 's/\r//g' $1 > $1.bk
# kill trailing blank lines
sed -e :a -e '/^\n*$/{$d;N;};/\n$/ba' $1.bk > $1
# add one back
echo >> $1
# kill the temp file
rm $1.bk
