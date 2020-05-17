cmd_firmware/embedsky_mfc_fw.bin.gen.o := arm-linux-gcc -Wp,-MD,firmware/.embedsky_mfc_fw.bin.gen.o.d  -nostdinc -isystem /opt/EmbedSky/4.4.6/lib/gcc/arm-embedsky-linux-gnueabi/4.4.6/include -I/home/andy/tq210/opt/EmbedSky/TQ210/Kernel_3.0.8_TQ210_for_Linux_v2.1/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include include/generated/autoconf.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-s5pv210/include -Iarch/arm/plat-s5p/include -Iarch/arm/plat-samsung/include -D__ASSEMBLY__ -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables  -D__LINUX_ARM_ARCH__=7 -march=armv7-a  -include asm/unified.h -msoft-float        -c -o firmware/embedsky_mfc_fw.bin.gen.o firmware/embedsky_mfc_fw.bin.gen.S

source_firmware/embedsky_mfc_fw.bin.gen.o := firmware/embedsky_mfc_fw.bin.gen.S

deps_firmware/embedsky_mfc_fw.bin.gen.o := \
  /home/andy/tq210/opt/EmbedSky/TQ210/Kernel_3.0.8_TQ210_for_Linux_v2.1/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
    $(wildcard include/config/thumb2/kernel.h) \

firmware/embedsky_mfc_fw.bin.gen.o: $(deps_firmware/embedsky_mfc_fw.bin.gen.o)

$(deps_firmware/embedsky_mfc_fw.bin.gen.o):
