#!/bin/bash
set -euo pipefail

sh configure.sh --disable-history --disable-nls --disable-man-pages
make gen/lib.c gen/lib2.c gen/bc_help.c gen/dc_help.c
swift run --package-path xcfs build
