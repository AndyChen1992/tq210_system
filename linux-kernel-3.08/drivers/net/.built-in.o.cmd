cmd_drivers/net/built-in.o :=  arm-linux-ld -EL    -r -o drivers/net/built-in.o drivers/net/mii.o drivers/net/Space.o drivers/net/loopback.o drivers/net/ppp_generic.o drivers/net/ppp_async.o drivers/net/ppp_synctty.o drivers/net/ppp_deflate.o drivers/net/bsd_comp.o drivers/net/pppox.o drivers/net/pppolac.o drivers/net/pppopns.o drivers/net/slhc.o drivers/net/dummy.o drivers/net/dm9000.o drivers/net/arm/built-in.o drivers/net/usb/built-in.o drivers/net/wireless/built-in.o 
