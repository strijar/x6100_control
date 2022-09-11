#!/bin/sh

cmd="admin -R default --proto raw,msgpack"

$cmd -c set_vfo --arglist '[ 1 ]' --argdict '{ "freq" : 7074000, "mode" : 3 }' 192.168.1.214 55555
$cmd -c set_rxvol --arglist '[ 10 ]' 192.168.1.214 55555
