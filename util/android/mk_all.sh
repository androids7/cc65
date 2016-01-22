#! /bin/bash

if [ -z "$CC65ANDROID_WORKDIR" ] ; then
	echo "CC65ANDROID_WORKDIR not set"
	exit 1
fi

mkdir -p "$CC65ANDROID_WORKDIR"

if [ ! -d "$CC65ANDROID_WORKDIR/source" ] ; then
	( cd "$CC65ANDROID_WORKDIR"
	#git clone https://github.com/cc65/cc65 source
	git clone ~/git/cc65 source
	)
fi

export CC65ANDROID_WORKDIR
export CC65ANDROID_NDK

./mk_share.sh
for arch in arm x86 mips
do
	for elf in pie nopie static
	do
		./mk_bin.sh $arch $elf
	done
done
