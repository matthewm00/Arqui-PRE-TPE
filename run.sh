#!/bin/bash
qemu-system-x86_64  -hda Image/x64BareBonesImage.qcow2  -cpu qemu64,mmx=on,sse=on,sse2=on,sse3=on,sse4.2=on,sse4.1=on,aes=on,pclmulqdq=on -m 512 -rtc base=localtime
