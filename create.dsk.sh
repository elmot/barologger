#!/bin/sh
echo NO | mkdosfs -n BARO_ELMOT -F16 baro.dsk -S512 -s1 -h0 -vv -h 0 -f1 -r16 -m - >disk.param
mount -oloop -tmsdos baro.dsk /mnt
touch /mnt/LEFT_200.min
dd if=/dev/urandom of=/mnt/BARO.TXT bs=100k count=1
ls -latr /mnt
umount /mnt
