# Exp 1:
(ligar e0 ao switch do t63 e do t64)
ifconfig eth0 up
ifconfig eth0 172.16.60.254/24 (in tux64)
ifconfig eth0 up
ifconfig eth0 172.16.60.1/24 (in tux63)

# Exp 2:
ifconfig eth0 up
ifconfig eth0 172.16.61.1/24 (in tux62)

## In gtkterm:
/interface bridge add name=bridge60
/interface bridge add name=bridge61
/interface bridge print

#### Remove ports from default bridge:
/interface bridge port remove [find interface =ether1]
/interface bridge port remove [find interface =ether2]
/interface bridge port remove [find interface =ether3]

#### Add ports to bridge60:
/interface bridge port add bridge=bridge60 interface=ether1
/interface bridge port add bridge=bridge60 interface=ether2
/interface bridge port add bridge=bridge61 interface=ether3

# Exp 3:
ifconfig eth1 up (in tux64)
ifconfig eth1 172.16.61.253/24 (in tux64)

## In gtkterm:
/interface bridge port remove [find interface =ether4]
/interface bridge port add bridge=bridge61 interface=ether4

echo 1 > /proc/sys/net/ipv4/ip_forward (tux64)
echo 0 > /proc/sys/net/ipv4/icmp_echo_ignore_broadcasts (tux64)

route add -net 172.16.61.0/24 gw 172.16.60.254 (in tux63)
route add -net 172.16.60.0/24 gw 172.16.61.253 (in tux62)

# Exp 4:
reset router:
In gtk term -> /system reset-configuration

In router gtkterm add ip address of eth1 (connected to 6.1) and eth2 (connected to switch)
/ip address add address=172.16.1.69/24 interface=ether1
/ip address add address=172.16.61.254/24 interface=ether2

In switch gtkterm add router eth2 (the one connected to the swtich) to bridge61
/interface bridge port remove [find interface =ether5]
/interface bridge port add bridge=bridge61 interface=ether5
/ip route add dst-address=172.16.60.0/24 gateway=172.16.61.253
/ip route add dst-address=0.0.0.0/0 gateway=172.16.1.254

in tux63:
route add default gw 172.16.60.254

in tux64:
route add default gw 172.16.61.254

in tux62:
route add default gw 172.16.61.254

