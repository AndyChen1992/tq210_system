cmd_arch/arm/boot/compressed/decompress.o := arm-linux-gcc -Wp,-MD,arch/arm/boot/compressed/.decompress.o.d  -nostdinc -isystem /opt/EmbedSky/4.4.6/lib/gcc/arm-embedsky-linux-gnueabi/4.4.6/include -I/home/andy/tq210/opt/EmbedSky/TQ210/Kernel_3.0.8_TQ210_for_Linux_v2.1/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include include/generated/autoconf.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-s5pv210/include -Iarch/arm/plat-s5p/include -Iarch/arm/plat-samsung/include -w -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Wno-format-security -fno-delete-null-pointer-checks -O2 -marm -fno-dwarf2-cfi-asm -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -Wframe-larger-than=1024 -fno-stack-protector -fomit-frame-pointer -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -fpic -fno-builtin    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(decompress)"  -D"KBUILD_MODNAME=KBUILD_STR(decompress)" -c -o arch/arm/boot/compressed/decompress.o arch/arm/boot/compressed/decompress.c

source_arch/arm/boot/compressed/decompress.o := arch/arm/boot/compressed/decompress.c

deps_arch/arm/boot/compressed/decompress.o := \
    $(wildcard include/config/kernel/gzip.h) \
    $(wildcard include/config/kernel/lzo.h) \
    $(wildcard include/config/kernel/lzma.h) \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  include/linux/compiler-gcc4.h \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /home/andy/tq210/opt/EmbedSky/TQ210/Kernel_3.0.8_TQ210_for_Linux_v2.1/arch/arm/include/asm/types.h \
  include/asm-generic/int-ll64.h \
  /home/andy/tq210/opt/EmbedSky/TQ210/Kernel_3.0.8_TQ210_for_Linux_v2.1/arch/arm/include/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/linux/posix_types.h \
  include/linux/stddef.h \
  /home/andy/tq210/opt/EmbedSky/TQ210/Kernel_3.0.8_TQ210_for_Linux_v2.1/arch/arm/include/asm/posix_types.h \
  include/linux/linkage.h \
  /home/andy/tq210/opt/EmbedSky/TQ210/Kernel_3.0.8_TQ210_for_Linux_v2.1/arch/arm/include/asm/linkage.h \
  /home/andy/tq210/opt/EmbedSky/TQ210/Kernel_3.0.8_TQ210_for_Linux_v2.1/arch/arm/include/asm/string.h \
  arch/arm/boot/compressed/../../../../lib/decompress_inflate.c \
  arch/arm/boot/compressed/../../../../lib/zlib_inflate/inftrees.c \
  include/linux/zutil.h \
  include/linux/zlib.h \
  include/linux/zconf.h \
  include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/spinlock/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/compaction.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
  arch/arm/boot/compressed/../../../../lib/zlib_inflate/inftrees.h \
  arch/arm/boot/compressed/../../../../lib/zlib_inflate/inffast.c \
    $(wildcard include/config/have/efficient/unaligned/access.h) \
  arch/arm/boot/compressed/../../../../lib/zlib_inflate/inflate.h \
  arch/arm/boot/compressed/../../../../lib/zlib_inflate/inffast.h \
  arch/arm/boot/compressed/../../../../lib/zlib_inflate/inflate.c \
  arch/arm/boot/compressed/../../../../lib/zlib_inflate/infutil.h \
  arch/arm/boot/compressed/../../../../lib/zlib_inflate/inffixed.h \
  include/linux/decompress/mm.h \

arch/arm/boot/compressed/decompress.o: $(deps_arch/arm/boot/compressed/decompress.o)

$(deps_arch/arm/boot/compressed/decompress.o):
