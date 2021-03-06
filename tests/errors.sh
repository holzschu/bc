#! /bin/bash
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

# WARNING: Test files cannot have empty lines!

checkcrash() {

	local error="$1"
	shift

	local name="$1"
	shift

	if [ "$error" -gt 127 ]; then
		echo ""
		echo "$d crashed on test:"
		echo ""
		echo "    $name"
		echo ""
		echo "exiting..."
		exit "$error"
	fi
}

checktest()
{
	local error="$1"
	shift

	local name="$1"
	shift

	local out="$1"
	shift

	local exebase="$1"
	shift

	checkcrash "$error" "$name"

	if [ "$error" -eq 0 ]; then
		echo ""
		echo "$d returned no error on test:"
		echo ""
		echo "    $name"
		echo ""
		echo "exiting..."
		exit 127
	fi

	if [ ! -s "$out" ]; then
		echo ""
		echo "$d produced no error message on test:"
		echo ""
		echo "    $name"
		echo ""
		echo "exiting..."
		exit "$error"
	fi

	# Display the error messages if not directly running exe.
	# This allows the script to print valgrind output.
	if [ "$exebase" != "bc" -a "$exebase" != "dc" ]; then
		cat "$out"
	fi
}

script="$0"
testdir=$(dirname "$script")

if [ "$#" -eq 0 ]; then
	echo "usage: $script dir [exec args...]"
	exit 1
else
	d="$1"
	shift
fi

if [ "$#" -lt 1 ]; then
	exe="$testdir/../bin/$d"
else
	exe="$1"
	shift
fi

out="$testdir/../.log_test.txt"

exebase=$(basename "$exe")

posix="posix_errors"

if [ "$d" = "bc" ]; then
	opts="-l"
	halt="halt"
else
	opts="-x"
	halt="q"
fi

for testfile in $testdir/$d/*errors.txt; do

	if [ -z "${testfile##*$posix*}" ]; then

		line="last"
		echo "$line" | "$exe" "$@" "-lw"  2> "$out" > /dev/null
		err="$?"

		if [ "$err" -ne 0 ]; then
			echo "$d returned an error ($err) on POSIX warning tests"
			echo "exiting..."
			exit 1
		fi

		checktest "1" "$line" "$out" "$exebase"

		options="-ls"
	else
		options="$opts"
	fi

	base=$(basename "$testfile")
	base="${base%.*}"
	echo "Running $base..."

	while read -r line; do

		rm -f "$out"

		echo "$line" | "$exe" "$@" "$options" 2> "$out" > /dev/null
		err="$?"

		checktest "$err" "$line" "$out" "$exebase"

	done < "$testfile"

done

for testfile in $testdir/$d/errors/*.txt; do

	echo "Running error file $testfile..."

	echo "$halt" | "$exe" "$@" $opts "$testfile" 2> "$out" > /dev/null
	err="$?"

	checktest "$err" "$testfile" "$out" "$exebase"

	echo "Running error file $testfile through cat..."

	cat "$testfile" | "$exe" "$@" $opts 2> "$out" > /dev/null
	err="$?"

	checkcrash "$err" "$testfile"

done
