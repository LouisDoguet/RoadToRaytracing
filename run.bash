#!/bin/bash

SETUP="$1"

if [[ "$SETUP" == "GRADIENT" ]]; then
    OUTPUT_FILE="gradient"
elif [[ "$SETUP" == "SIMPLE_RAY" ]]; then
    OUTPUT_FILE="simple_ray"
elif [[ "$SETUP" == "SPHERE" ]]; then
    OUTPUT_FILE="sphere"
else
    echo "[!] Error : setup '$SETUP' not found"
fi

echo "[*] Running program, output -> $OUTPUT_FILE"
TIMEFORMAT="[*] Elapsed time: %3R s"
time "./output/$OUTPUT_FILE" > "./output/$OUTPUT_FILE.ppm"

echo "[✓] Done."