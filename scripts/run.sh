#!/bin/bash

# Save the command for later
qemu-system-x86_64 \
  -drive if=pflash,format=raw,readonly=on,file=/Users/patrick/opt/homebrew/share/qemu/edk2-x86_64-code.fd \
  -drive format=raw,file=labos-agarta.img

# Tell Qemu to print debugs to the terminal
# -d int,cpu_reset 2>&1 | head -50
