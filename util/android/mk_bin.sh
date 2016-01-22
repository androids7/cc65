#! /bin/bash

if [ -z "$CC65ANDROID_WORKDIR" ] ; then
	echo "CC65ANDROID_WORKDIR not set"
	exit 1
fi

if [ $# -ne 2 ] ; then
	echo "usage: mk_bin.sh arch elf"
	exit 1
fi

if [ "$1" == "arm" ] ; then
	ID=3
	TOOL=arm-linux-androideabi
elif [ "$1" == "x86" ] ; then
	ID=9
	TOOL=i686-linux-android
elif [ "$1" == "mips" ] ; then
	ID=9
	TOOL=mipsel-linux-android
else
	echo "invalid arch"
	exit 1
fi
ARCH=$1

cd $CC65ANDROID_WORKDIR

TOOLCHAIN=toolchain-$1-$ID
if [ ! -d $TOOLCHAIN ] ; then
	if [ -z "$CC65ANDROID_NDK" ] ; then
		echo "CC65ANDROID_NDK not set"
		exit 1
	fi
	$CC65ANDROID_NDK/build/tools/make-standalone-toolchain.sh \
	--arch=$1 --platform=android-$ID \
	--install-dir="$CC65ANDROID_WORKDIR/$TOOLCHAIN"
fi

export PATH="$PATH:$CC65ANDROID_WORKDIR/$TOOLCHAIN/bin"
export CROSS_COMPILE=$TOOL-
if [ "$2" == "nopie" ] ; then
	:
elif [ "$2" == "pie" ] ; then
	export USER_CFLAGS=-fPIE
	export LDFLAGS="-fPIE -pie"
elif [ "$2" == "static" ] ; then
	export LDFLAGS="-static"
else
	echo "invalid elf"
	exit 1
fi
ELF=$2

( cd source
make clean
make bin )

export prefix="$CC65ANDROID_WORKDIR/cc65"

( cd "$prefix/bin" && for i in *
do
	cp ../../source/bin/$i.exe $i
	$TOOL-strip $i
done )

( cd "$prefix"
OUT=../cc65-android-bin-$1-$ELF.zip
rm -f $OUT
zip -r $OUT bin )
