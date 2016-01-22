#! /bin/bash

if [ -z "$CC65ANDROID_WORKDIR" ] ; then
	echo "CC65ANDROID_WORKDIR not set"
	exit 1
fi

cd $CC65ANDROID_WORKDIR

export prefix="$CC65ANDROID_WORKDIR/cc65"

( cd source
make clean
make
( cd doc ; make html )
make install )

DIST="$prefix/share/cc65"

cp source/LICENSE source/README.md "$DIST"
mkdir -p "$DIST/doc"
cp source/html/* "$DIST/doc"

( cd "$prefix/share"
OUT=../../cc65-android-share.zip
rm -f $OUT
zip -r $OUT cc65 )
