cmd_net/netfilter/built-in.o :=  arm-linux-ld -EL    -r -o net/netfilter/built-in.o net/netfilter/netfilter.o net/netfilter/nf_tproxy_core.o net/netfilter/x_tables.o net/netfilter/xt_tcpudp.o net/netfilter/xt_qtaguid_print.o net/netfilter/xt_qtaguid.o net/netfilter/xt_socket.o net/netfilter/ipvs/built-in.o 
