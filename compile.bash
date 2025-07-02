#!/bin/bash

CXX=g++
CXXFLAGS="-std=c++17 -O2"

SETUP="$1"

INCLUDES=(-Icommon)
SOURCES=(main.cpp common/color.cpp)

if [[ "$SETUP" == "SPHERE" ]]; then
    INCLUDES+=(-Isrc/sphere)
    SOURCES+=(src/sphere/sphere.cpp)
    EXE_NAME="sphere"
    echo "[*] Building sphere module."

elif [[ "$SETUP" == "GRADIENT" ]]; then
    INCLUDES+=(-Isrc/gradient)
    SOURCES+=(src/gradient/gradient.cpp)
    EXE_NAME="gradient"
    echo "[*] Building gradient module."

elif [[ "$SETUP" == "SIMPLE_RAY" ]]; then
    INCLUDES+=(-Isrc/simple_ray)
    SOURCES+=(src/simple_ray/simple_ray.cpp)
    EXE_NAME="simple_ray"
    echo "[*] Building simple ray module."
else
    echo "[!] Building error : wrong setup '$SETUP'"
fi

echo "[*] Compiling ..."
$CXX $CXXFLAGS "${INCLUDES[@]}" "${SOURCES[@]}" -o "output/$EXE_NAME"

if [[ $? -eq 0 ]]; then
    echo "[✓] Build successful: output/$EXE_NAME"
else
    echo "[!] Compilation failed."
    exit 1
fi
