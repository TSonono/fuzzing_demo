#!/bin/sh

echo "Hex: $1"
xxd -ps $1 | tr -d '\n' && echo ""