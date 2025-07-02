#!/bin/bash

SETUP="$1"

if [[ "$SETUP" == "GRADIENT" ]]; then
    OUTPUT_FILE="gradient"
elif [[ "$SETUP" == "SIMPLE_RAY" ]]; then
    OUTPUT_FILE="simple_ray"
fi

echo "[*] Running program, output -> $OUTPUT_FILE"
"./output/$OUTPUT_FILE" >> "./output/$OUTPUT_FILE.ppm"

echo "[✓] Done."