cmd_arch/arm/boot/uImage := /bin/bash /home/andy/tq210/opt/EmbedSky/TQ210/Kernel_3.0.8_TQ210_for_Linux_v2.1/scripts/mkuboot.sh -A arm -O linux -T kernel -C none -a 0x20008000 -e 0x20008000 -n 'Linux-3.0.8-EmbedSky' -d arch/arm/boot/zImage arch/arm/boot/uImage
