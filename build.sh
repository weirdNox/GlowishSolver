#!/usr/bin/env bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
clang -g -O2 "${DIR}/main.c" -o solver
