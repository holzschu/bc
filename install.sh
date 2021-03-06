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

usage() {
	printf "usage: %s install_dir bin_dir\n" "$0" 1>&2
	exit 1
}

script=$(realpath "$0")
scriptdir=$(dirname "$script")

INSTALL="$scriptdir/safe-install.sh"

test "$#" -gt 1 || usage

installdir="$1"
shift

bindir="$1"
shift

cd "$bindir"

for exe in ./*; do

	base=$(basename "$exe")

	if [ -L "$exe" ]; then
		L=$(ls -dl "$exe")
		link=$(echo ${L#*-> })
		"$INSTALL" -Dlm 755 "$link" "$installdir/$base"
	else
		"$INSTALL" -Dm 755 "$exe" "$installdir/$base"
	fi

done
