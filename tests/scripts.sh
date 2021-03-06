#! /bin/sh
#
# Copyright 2018 Gavin D. Howard
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
# REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
# OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.
#

set -e

script="$0"

testdir=$(dirname "${script}")

if [ "$#" -eq 0 ]; then
	echo "usage: $script dir [exec args...]"
	exit 1
else
	d="$1"
	shift
fi

if [ "$#" -gt 0 ]; then
	exe="$1"
	shift
else
	exe="$testdir/../bin/$d"
fi

out1="$testdir/../.log_bc.txt"
out2="$testdir/../.log_test.txt"

if [ "$d" = "bc" ]; then
	options="-lq"
	halt="halt"
else
	options="-x"
	halt="q"
fi

scriptdir="$testdir/$d/scripts"

for s in $scriptdir/*.$d; do

	f=$(basename -- "$s")
	name="${f%.*}"

	if [ "$f" = "timeconst.bc" ]; then
		continue
	fi

	echo "Running $d script: $f"

	orig="$testdir/$name.txt"
	results="$scriptdir/$name.txt"

	if [ -f "$orig" ]; then
		res="$orig"
	elif [ -f "$results" ]; then
		res="$results"
	else
		echo "$halt" | $d "$s" > "$out1"
		res="$out1"
	fi

	echo "$halt" | "$exe" "$@" $options "$s" > "$out2"

	diff "$res" "$out2"

done

rm -rf "$out1" "$out2"
