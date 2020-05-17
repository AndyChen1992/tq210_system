cmd_.tmp_kallsyms2.o := arm-linux-gcc -Wp,-MD,./..tmp_kallsyms2.o.d -D__ASSEMBLY__ -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables  -D__LINUX_ARM_ARCH__=7 -march=armv7-a  -include asm/unified.h -msoft-float    -nostdinc -isystem /opt/EmbedSky/4.4.6/lib/gcc/arm-embedsky-linux-gnueabi/4.4.6/include -I/home/andy/tq210/opt/EmbedSky/TQ210/Kernel_3.0.8_TQ210_for_Linux_v2.1/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include include/generated/autoconf.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-s5pv210/include -Iarch/arm/plat-s5p/include -Iarch/arm/plat-samsung/include    -c -o .tmp_kallsyms2.o .tmp_kallsyms2.S

source_.tmp_kallsyms2.o := .tmp_kallsyms2.S

deps_.tmp_kallsyms2.o := \
  /home/andy/tq210/opt/EmbedSky/TQ210/Kernel_3.0.8_TQ210_for_Linux_v2.1/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
    $(wildcard include/config/thumb2/kernel.h) \
  /home/andy/tq210/opt/EmbedSky/TQ210/Kernel_3.0.8_TQ210_for_Linux_v2.1/arch/arm/include/asm/types.h \
  include/asm-generic/int-ll64.h \
  /home/andy/tq210/opt/EmbedSky/TQ210/Kernel_3.0.8_TQ210_for_Linux_v2.1/arch/arm/include/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
    $(wildcard include/config/64bit.h) \

.tmp_kallsyms2.o: $(deps_.tmp_kallsyms2.o)

$(deps_.tmp_kallsyms2.o):
