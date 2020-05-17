cmd_firmware/built-in.o :=  arm-linux-ld -EL    -r -o firmware/built-in.o firmware/sd8686_helper.bin.gen.o firmware/sd8686.bin.gen.o firmware/embedsky_mfc_fw.bin.gen.o 
