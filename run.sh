#!/bin/bash
qemu-system-x86_64 -audiodev alsa,id=foo -hda Image/x64BareBonesImage.qcow2 -m 512 -machine pcspk-audiodev=foo