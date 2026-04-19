#!/bin/bash

# Save the command for later
qemu-system-x86_64 \
  -drive if=pflash,format=raw,readonly=on,file=/Users/patrick/opt/homebrew/share/qemu/edk2-x86_64-code.fd \
  -drive format=raw,file=labos-agarta.img
