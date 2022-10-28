#!/bin/bash
<<<<<<< HEAD
qemu-system-x86_64 -audiodev alsa,id=foo -hda Image/x64BareBonesImage.qcow2 -m 512 -machine pcspk-audiodev=foo
=======
qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -audiodev coreaudio,id=audio0 -machine pcspk-audiodev=audio0 
>>>>>>> b95920a (beep working git add *git add *)
