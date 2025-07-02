#!/bin/bash

SETUP="$1"

OUTPUT="$2"

if [[ "$SETUP" == "GRADIENT" ]]; then
    OUTPUT_FILE="gradient"
elif [[ "$SETUP" == "SIMPLE_RAY" ]]; then
    OUTPUT_FILE="simple_ray"
elif [[ "$SETUP" == "SPHERE" ]]; then
    OUTPUT_FILE="sphere"
elif [[ "$SETUP" == "GROUND" ]]; then
    OUTPUT_FILE="ground"
elif [[ "$SETUP" == "CAMERA" ]]; then
    OUTPUT_FILE="camera"
else
    echo "[!] Error : setup '$SETUP' not found"
fi

if [[ "$OUTPUT" == "" ]]; then
    echo "[*] Running program, output -> $OUTPUT_FILE"
    TIMEFORMAT="[*] Elapsed time: %3R s"
    time "./output/$OUTPUT_FILE" > "./output/$OUTPUT_FILE.ppm"
else
    echo "[*] Running program, output -> $OUTPUT_FILE"
    TIMEFORMAT="[*] Elapsed time: %3R s"
    time "./output/$OUTPUT_FILE" > "./output/$OUTPUT.ppm"
fi

echo "[✓] Done."